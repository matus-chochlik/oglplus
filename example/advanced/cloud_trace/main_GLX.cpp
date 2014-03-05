/**
 *  @example advanced/cloud_trace/main_GLX.cpp
 *  @brief GLX-based implementation of the main function.
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "main_common.hpp"
#include "app_data.hpp"
#include "resources.hpp"
#include "renderer.hpp"
#include "raytracer.hpp"
#include "saver.hpp"
#include "threads.hpp"

#include <oglplus/gl.hpp>
#include <oglplus/fix_gl_version.hpp>

#include <oglplus/glx/context.hpp>
#include <oglplus/glx/fb_configs.hpp>
#include <oglplus/glx/version.hpp>
#include <oglplus/glx/pixmap.hpp>
#include <oglplus/x11/window.hpp>
#include <oglplus/x11/color_map.hpp>
#include <oglplus/x11/visual_info.hpp>
#include <oglplus/x11/display.hpp>

#include <oglplus/config.hpp>

#include <stdexcept>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

namespace oglplus {
namespace cloud_trace {

class CommonData
{
public:
	const x11::Display& display;
	const glx::FBConfig& fb_config;
	const x11::VisualInfo& visual_info;
	const glx::Context& context;
private:

	const unsigned max_tiles;
	unsigned tile, face;
	bool keep_running;


	std::vector<std::exception_ptr> thread_errors;

	std::mutex mutex;

	RaytracerResources* p_rt_res;
public:
	Semaphore master_ready;
	Semaphore thread_ready;

	CommonData(
		const AppData& app_data,
		const x11::Display& disp,
		const glx::FBConfig& fbc,
		const x11::VisualInfo& vi,
		const glx::Context& ctx
	): display(disp)
	 , fb_config(fbc)
	 , visual_info(vi)
	 , context(ctx)
	 , max_tiles(app_data.tiles())
	 , tile(0)
	 , face(0)
	 , keep_running(true)
	 , p_rt_res(nullptr)
	{ }

	void RtRes(RaytracerResources& rt_res)
	{
		p_rt_res = &rt_res;
	}

	RaytracerResources& RtRes(void)
	{
		assert(p_rt_res != nullptr);
		return *p_rt_res;
	}

	std::unique_lock<std::mutex> Lock(void)
	{
		return std::unique_lock<std::mutex>(mutex);
	}

	void PushError(std::exception_ptr&& err)
	{
		std::lock_guard<std::mutex> lock(mutex);
		thread_errors.push_back(std::move(err));
		keep_running = false;
	}

	void RethrowErrors(void)
	{
		for(auto& ep: thread_errors)
		{
			if(ep != nullptr)
			{
				std::rethrow_exception(ep);
			}
		}
	}

	void Stop(void)
	{
		std::lock_guard<std::mutex> lock(mutex);
		keep_running = false;
	}

	bool Done(void)
	{
		std::lock_guard<std::mutex> lock(mutex);
		return !keep_running;
	}

	unsigned Face(void)
	{
		return face;
	}

	bool FaceDone(void)
	{
		std::lock_guard<std::mutex> lock(mutex);

		return (tile >= max_tiles);
	}

	void NextFace(void)
	{
		std::lock_guard<std::mutex> lock(mutex);

		if(face < 5)
		{
			++face;
			tile = 0;
		}
		else keep_running = false;
	}

	bool NextFaceTile(unsigned& rt_tile)
	{
		std::lock_guard<std::mutex> lock(mutex);

		rt_tile = tile;

		if(keep_running)
		{
			if(tile < max_tiles)
			{
				++tile;
				return true;
			}
		}
		return false;
	}
};

void thread_loop(AppData& app_data, CommonData& common, unsigned id)
{
	Context gl;
	Raytracer raytracer(app_data, common.RtRes());
	raytracer.Use(app_data);

	while(!common.Done())
	{
		// the first thread is responsible for clearing
		// the shared texture into which the raytraced
		// tiles are copied
		if(id == 0)
		{
			raytracer.ClearDest(app_data);
			// signal this to the master
			common.thread_ready.Signal();
		}

		// all threads must wait until the shared texture
		// is cleared
		common.master_ready.Wait();

		if(common.Done()) break;

		raytracer.InitFrame(app_data, common.Face());

		unsigned tile = 0;
		while(common.NextFaceTile(tile))
		{
			raytracer.Raytrace(app_data, tile);
			gl.Finish();

			auto lock = common.Lock();
			raytracer.BlitBuffers(app_data, tile);
			lock.unlock();
		}

		// signal to the master that the raytracing
		// of the current face has finished
		common.thread_ready.Signal();

		// wait for the master to save the face image
		common.master_ready.Wait();
	}
}

void window_loop(
	const x11::Window& window,
	AppData& app_data,
	CommonData& common,
	Renderer& renderer,
	std::size_t n_threads
)
{
	Context gl;
	renderer.Use(app_data);
	Saver saver(app_data);

	window.SelectInput(StructureNotifyMask| PointerMotionMask| KeyPressMask);
	::Atom wmDelete = ::XInternAtom(common.display, "WM_DELETE_WINDOW", True);
	::XSetWMProtocols(common.display, window, &wmDelete, 1);
	::XEvent event;

	while(!common.Done())
	{
		// wait for the first thread to clear the shared texture
		common.thread_ready.Wait();
		// signal all threads that they can start raytracing tiles
		common.master_ready.Signal(n_threads);

		while(!common.FaceDone())
		{
			while(common.display.NextEvent(event))
			{
				switch(event.type)
				{
					case ClientMessage:
					case DestroyNotify:
						common.Stop();
						break;
					case ConfigureNotify:
						app_data.render_width = event.xconfigure.width;
						app_data.render_height = event.xconfigure.height;
						break;
					case MotionNotify:
						break;
					case KeyPress:
						if(::XLookupKeysym(&event.xkey, 0) == XK_Escape)
							common.Stop();
						break;
					default:;
				}
			}

			if(common.Done()) break;

			auto lock = common.Lock();
			renderer.Render(app_data);
			gl.Finish();
			lock.unlock();

			common.context.SwapBuffers(window);
		}

		// wait for all raytracer threads to finish
		common.thread_ready.Wait(n_threads);

		auto lock = common.Lock();
		renderer.Render(app_data);
		gl.Finish();
		lock.unlock();

		common.context.SwapBuffers(window);

		// save the face image
		saver.SaveFrame(app_data, common.Face());
		// switch the face
		common.NextFace();

		// signal that the master is ready to render
		// the next face
		common.master_ready.Signal(n_threads);
	}
}

void main_thread(
	AppData& app_data,
	CommonData& common,
	const std::string& screen_name,
	unsigned id
)
{
	x11::Display display(screen_name.empty()?nullptr:screen_name.c_str());

	x11::Pixmap xpm(display, common.visual_info, 8, 8);
	glx::Pixmap gpm(display, common.visual_info, xpm);
	glx::Context context(display, common.fb_config, common.context, 3, 3);

	context.MakeCurrent(gpm);

	common.thread_ready.Signal();

	common.master_ready.Wait();

	try { thread_loop(app_data, common, id); }
	catch(...)
	{
		common.PushError(std::current_exception());
	}

	context.Release(display);
}

int main_GLX(AppData& app_data)
{
	::XInitThreads();
	x11::Display display;

	static int visual_attribs[] =
	{
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		None
	};
	glx::Version version(display);
	version.AssertAtLeast(1, 3);

	glx::FBConfig fbc = glx::FBConfigs(
		display,
		visual_attribs
	).FindBest(display);

	x11::VisualInfo vi(display, fbc);

	x11::Window window(
		display,
		vi,
		x11::Colormap(display, vi),
		"CloudTrace",
		app_data.render_width,
		app_data.render_height
	);

	glx::Context context(display, fbc, 3, 3);
	context.MakeCurrent(window);

	GLAPIInitializer api_init;
	{
		CommonData common(app_data, display, fbc, vi, context);

		std::vector<std::thread> threads;

		try
		{
			if(app_data.raytracer_params.empty())
			{
				app_data.raytracer_params.push_back(std::string());
			}

			for(auto& param: app_data.raytracer_params)
			{
				threads.push_back(
					std::thread(
						main_thread,
						std::ref(app_data),
						std::ref(common),
						std::cref(param),
						0
					)
				);
				common.thread_ready.Wait();
			}
		}
		catch (...)
		{
			for(auto& t: threads) t.join();
			throw;
		}

		ResourceAllocator res_alloc;
		RaytracerResources rt_res(app_data, res_alloc);
		Renderer renderer(app_data, rt_res.dest_tex_unit);

		common.RtRes(rt_res);
		common.master_ready.Signal(threads.size());

		try
		{
			window_loop(
				window,
				app_data,
				common,
				renderer,
				threads.size()
			);
			for(auto& t: threads) t.join();
		}
		catch (...)
		{
			for(auto& t: threads) t.join();
			throw;
		}

		common.RethrowErrors();
	}

	context.Release(display);

	return 0;
}

} // namespace cloud_trace
} // namespace oglplus

int main (int argc, char ** argv)
{
	using oglplus::cloud_trace::main_GLX;
	using oglplus::cloud_trace::AppData;

	AppData app_data;
	app_data.use_x_rt_screens = true;
	app_data.ParseArgs(argc, argv);
	return do_run_main(main_GLX, app_data);
}

