/**
 *  @example advanced/cloud_trace/main_GLX.cpp
 *  @brief GLX-based implementation of the main function.
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "main_common.hpp"
#include "render_data.hpp"
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

struct CommonData
{
	const x11::Display& display;
	const glx::FBConfig& fb_config;
	const x11::VisualInfo& visual_info;
	const glx::Context& context;
	x11::ScreenNames screen_names;

	unsigned rt_front_tex_unit;
	unsigned face;
	double face_done;
	bool keep_running;

	std::mutex mutex;
	Semaphore master_ready;
	Semaphore thread_ready;

	CommonData(
		const x11::Display& disp,
		const glx::FBConfig& fbc,
		const x11::VisualInfo& vi,
		const glx::Context& ctx
	): display(disp)
	 , fb_config(fbc)
	 , visual_info(vi)
	 , context(ctx)
	 , face(0)
	 , face_done(0)
	 , keep_running(true)
	{ }
};

void thread_loop(
	CommonData& common,
	RenderData& data,
	Raytracer& raytracer
)
{
	raytracer.Use(data);

	while(common.keep_running)
	{
		if(common.face_done == 0)
		{
			raytracer.InitFrame(data, common.face_done);
		}

		if(common.face_done < 1)
		{
			double done = raytracer.Raytrace(data);

			std::unique_lock<std::mutex> lock(common.mutex);
			common.face_done = done;
			raytracer.SwapBuffers(data);
			common.rt_front_tex_unit = raytracer.FrontTexUnit();
			lock.unlock();
		}
		else if(common.face < 6)
		{
			if(common.face < 5)
			{
				common.face_done = 0;
				common.face++;
			}
			else common.keep_running = false;
		}
	}
}

void window_loop(
	const x11::Window& window,
	CommonData& common,
	RenderData& data,
	Renderer& renderer
)
{
	renderer.Use(data);
	Saver saver(data);

	window.SelectInput(StructureNotifyMask| PointerMotionMask| KeyPressMask);
	::Atom wmDelete = ::XInternAtom(common.display, "WM_DELETE_WINDOW", True);
	::XSetWMProtocols(common.display, window, &wmDelete, 1);
	::XEvent event;

	while(common.keep_running)
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
					data.render_width = event.xconfigure.width;
					data.render_height = event.xconfigure.height;
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

		if(common.face_done < 1)
		{
			std::unique_lock<std::mutex> lock(common.mutex);
			renderer.Render(data, common.rt_front_tex_unit);
			lock.unlock();
			common.context.SwapBuffers(window);
		}
		else if(common.face < 6)
		{
			common.context.SwapBuffers(window);
			saver.SaveFrame(data, common.face);
		}
	}
}

void main_thread(
	CommonData& common,
	RenderData& data,
	Raytracer& raytracer
)
{
	// TODO: use display_names
	const x11::Display& display = common.display;

	x11::Pixmap xpm(display, common.visual_info, 8, 8);
	glx::Pixmap gpm(display, common.visual_info, xpm);
	glx::Context context(display, common.fb_config, common.context, 3, 3);

	context.MakeCurrent(gpm);

	common.thread_ready.Signal();

	thread_loop(common, data, raytracer);

	context.Release(display);
}

int main_GLX(RenderData& data)
{
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
		data.render_width,
		data.render_height
	);

	glx::Context context(display, fbc, 3, 3);
	context.MakeCurrent(window);

	GLAPIInitializer api_init;
	{
		ResourceAllocator alloc;
		Renderer renderer(data, alloc);
		Raytracer raytracer(data, alloc);

		CommonData common(display, fbc, vi, context);

		std::vector<std::thread> threads;

		{
			threads.push_back(
				std::thread(
					main_thread,
					std::ref(common),
					std::ref(data),
					std::ref(raytracer)
				)
			);
			common.thread_ready.Wait();
		}

		window_loop(window, common, data, renderer);

		for(auto& t: threads) t.join();
	}

	context.Release(display);

	return 0;
}

} // namespace cloud_trace
} // namespace oglplus

int main (int argc, char ** argv)
{
	using oglplus::cloud_trace::main_GLX;
	using oglplus::cloud_trace::RenderData;

	RenderData data(argc, argv);
	return do_run_main(main_GLX, data);
}

