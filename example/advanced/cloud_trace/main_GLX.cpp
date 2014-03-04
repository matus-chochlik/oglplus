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

	const unsigned max_tiles;
	unsigned tile, face;
	bool keep_running;


	std::vector<std::exception_ptr> thread_errors;

	std::mutex mutex;
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
	{ }

	bool Done(void)
	{
		std::unique_lock<std::mutex> lock(mutex);
		return !keep_running;
	}

	bool NextTraceTask(unsigned& rt_face, unsigned& rt_tile)
	{
		std::unique_lock<std::mutex> lock(mutex);

		rt_face = face;
		rt_tile = tile;

		keep_running &= (face < 6);

		if(keep_running)
		{
			if(++tile >= max_tiles)
			{
				tile = 0;
				++face;
			}
			return true;
		}
		return false;
	}
};

void thread_loop(
	AppData& app_data,
	CommonData& common,
	RaytracerResources& rt_res
)
{
	Context gl;
	Raytracer raytracer(app_data, rt_res);
	raytracer.Use(app_data);

	unsigned face, tile;

	while(common.NextTraceTask(face, tile))
	{
		raytracer.Raytrace(app_data, face, tile);
		gl.Finish();

		std::unique_lock<std::mutex> lock(common.mutex);
		raytracer.BlitBuffers(app_data, tile);
		lock.unlock();
	}
}

void window_loop(
	const x11::Window& window,
	AppData& app_data,
	CommonData& common,
	Renderer& renderer
)
{
	Context gl;
	renderer.Use(app_data);
	//Saver saver(app_data); TODO

	window.SelectInput(StructureNotifyMask| PointerMotionMask| KeyPressMask);
	::Atom wmDelete = ::XInternAtom(common.display, "WM_DELETE_WINDOW", True);
	::XSetWMProtocols(common.display, window, &wmDelete, 1);
	::XEvent event;

	while(!common.Done())
	{
		while(common.display.NextEvent(event))
		{
			switch(event.type)
			{
				case ClientMessage:
				case DestroyNotify:
					common.keep_running = false;
					break;
				case ConfigureNotify:
					app_data.render_width = event.xconfigure.width;
					app_data.render_height = event.xconfigure.height;
					break;
				case MotionNotify:
					break;
				case KeyPress:
					if(::XLookupKeysym(&event.xkey, 0) == XK_Escape)
						common.keep_running = false;
					break;
				default:;
			}
		}

		std::unique_lock<std::mutex> lock(common.mutex);
		renderer.Render(app_data);
		gl.Finish();
		lock.unlock();

		common.context.SwapBuffers(window);
	}
}

void main_thread(
	AppData& app_data,
	CommonData& common,
	RaytracerResources& rt_res
)
{
	// TODO: use display_names
	x11::Display display;

	x11::Pixmap xpm(display, common.visual_info, 8, 8);
	glx::Pixmap gpm(display, common.visual_info, xpm);
	glx::Context context(display, common.fb_config, common.context, 3, 3);

	context.MakeCurrent(gpm);

	common.thread_ready.Signal();

	try { thread_loop(app_data, common, rt_res); }
	catch(...)
	{
		std::unique_lock<std::mutex> lock(common.mutex);
		common.thread_errors.push_back(std::current_exception());
		common.keep_running = false;
		lock.unlock();
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

		ResourceAllocator res_alloc;
		RaytracerResources rt_res(app_data, res_alloc);
		Renderer renderer(app_data, rt_res.dest_tex_unit);

		std::vector<std::thread> threads;

		try
		{
			{
				threads.push_back(
					std::thread(
						main_thread,
						std::ref(app_data),
						std::ref(common),
						std::ref(rt_res)
					)
				);
				common.thread_ready.Wait();
			}

			window_loop(window, app_data, common, renderer);

			for(auto& t: threads) t.join();
		}
		catch (...)
		{
			for(auto& t: threads) t.join();
			throw;
		}

		for(auto& ep: common.thread_errors)
		{
			if(ep != nullptr)
			{
				std::rethrow_exception(ep);
			}
		}

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

	AppData app_data(argc, argv);
	return do_run_main(main_GLX, app_data);
}

