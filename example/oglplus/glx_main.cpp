/*
 *  .file example/glx_main.cpp
 *  Implements GLX-based program main function for running examples
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>

#if OGLPLUS_LINK_LIBRARY
# include <oglplus/lib.hpp>
#endif

#include <oglplus/glx/context.hpp>
#include <oglplus/glx/fb_configs.hpp>
#include <oglplus/glx/version.hpp>
#include <oglplus/glx/pixmap.hpp>
#include <oglplus/x11/window.hpp>
#include <oglplus/x11/color_map.hpp>
#include <oglplus/x11/visual_info.hpp>
#include <oglplus/x11/display.hpp>

#include <oglplus/os/steady_clock.hpp>

#include <oglplus/config.hpp>

#include <oglplus/ext/ARB_debug_output.hpp>

#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cassert>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "example.hpp"
#include "example_main.hpp"

namespace oglplus {

class ThreadSemaphore
{
private:
	unsigned _value;
	std::mutex _mutex;
	std::condition_variable _cv;

	void _decr(void)
	{
		std::unique_lock<std::mutex> lock(_mutex);
		while(_value == 0) _cv.wait(lock);
		--_value;
	}

	void _incr(unsigned n)
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_value += n;
		_cv.notify_all();
	}
public:
	ThreadSemaphore(unsigned initial = 0)
	 : _value(initial)
	{ }

	void Wait(unsigned n = 1)
	{
		while(n--) _decr();
	}

	void Signal(unsigned n = 1)
	{
		_incr(n);
	}
};

struct ExampleThreadData
{
	unsigned thread_index;
	ExampleThread* example_thread;
	std::string error_message;

	struct Common
	{
		Example* example;
		const ExampleParams& example_params;
		const ExampleClock& clock;
		const x11::ScreenNames& screen_names;
		const x11::Display& display;
		const x11::VisualInfo& vi;
		const glx::FBConfig& fbc;
		const glx::Context& ctx;
		ThreadSemaphore& thread_ready;
		ThreadSemaphore& master_ready;
		bool failure;
		bool done;
	}* _pcommon;
	Common& common(void)
	{
		assert(_pcommon);
		return *_pcommon;
	}
};

void example_thread_main(ExampleThreadData& data)
{
	const ExampleThreadData::Common& common = data.common();
	const x11::ScreenNames& sn = common.screen_names;
	// pick one of the available display screens
	// for this thread
	std::size_t disp_idx = data.thread_index;
	if(sn.size() > 1) ++disp_idx;
	disp_idx %= sn.size();
	// open the picked display
	x11::Display display(sn[disp_idx].c_str());
	// initialize the pixelmaps and the sharing context
	x11::Pixmap xpm(display, common.vi, 8, 8);
	glx::Pixmap gpm(display, common.vi, xpm);
	glx::Context ctx(display, common.fbc, common.ctx, 3, 3);

	ctx.MakeCurrent(gpm);

	// signal that the context is created
	common.thread_ready.Signal();

	// wait for the example to be created
	// in the main thread
	common.master_ready.Wait();
	// if something failed - quit
	if(common.failure)
	{
		common.thread_ready.Signal();
		return;
	}
	else
	{
		try
		{
			assert(common.example);
			// call makeExampleThread
			std::unique_ptr<ExampleThread> example_thread(
				makeExampleThread(
					*common.example,
					data.thread_index,
					common.example_params
				)
			);
			data.example_thread = example_thread.get();
			// signal that it is created
			common.thread_ready.Signal();
			// wait for the main thread
			common.master_ready.Wait();
			// if something failed - quit
			if(common.failure) return;

			// start rendering
			while(!common.done && !common.failure)
			{
				example_thread->Render(common.clock);
				glFlush();
			}
			data.example_thread = nullptr;
		}
		catch(...)
		{
			data.example_thread = nullptr;
			throw;
		}
	}
	ctx.Release(display);
}

void call_example_thread_main(ExampleThreadData& data)
{
	ExampleThreadData::Common& common = data.common();
	struct main_wrapper
	{
		void (*main_func)(ExampleThreadData&);
		ExampleThreadData& data;

		int operator()(void) const
		{
			main_func(data);
			return 0;
		}
	} wrapped_main = {example_thread_main, data};

	std::stringstream errstr;
	if(example_guarded_exec(wrapped_main, errstr) != 0)
	{
		common.failure = true;
		data.error_message = errstr.str();
		common.thread_ready.Signal();
	}
}

void run_example_loop(
	const x11::Display& display,
	const x11::Window& win,
	const glx::Context& ctx,
	std::unique_ptr<Example>& example,
	ExampleThreadData::Common& common,
	ExampleClock& clock,
	GLuint width,
	GLuint height
)
{
	std::cout << "-+-[Begin]" << std::endl;
#if GL_ARB_debug_output && !OGLPLUS_NO_LAMBDAS
	ARB_debug_output dbg;
	ARB_debug_output::LogSink sink(
		[](const ARB_debug_output::CallbackData& data) -> void
		{
			std::cout << " |" << std::endl;
			std::cout << " +-+-[" << data.id << "] '" <<
				data.message << "'" << std::endl;
			std::cout << " | +---[source]   '" <<
				EnumValueName(data.source).c_str()  << "'" << std::endl;
			std::cout << " | +---[type]     '" <<
				EnumValueName(data.type).c_str()  << "'" << std::endl;
			std::cout << " | `---[severity] '" <<
				EnumValueName(data.severity).c_str()  << "'" << std::endl;
		}
	);

	dbg.Control(
		DebugOutputARBSource::DontCare,
		DebugOutputARBType::DontCare,
		DebugOutputARBSeverity::Low,
		true
	);

	dbg.InsertMessage(
		DebugOutputARBSource::Application,
		DebugOutputARBType::Other,
		0,
		DebugOutputARBSeverity::Low,
		"Starting main loop"
	);
#endif // GL_ARB_debug_output

	win.SelectInput(
		StructureNotifyMask|
		PointerMotionMask|
		KeyPressMask
	);
	::Atom wmDelete = ::XInternAtom(display, "WM_DELETE_WINDOW", True);
	::XSetWMProtocols(display, win, &wmDelete, 1);

	XEvent event;
	os::steady_clock os_clock;
	bool done = false;
	while(!done && !common.failure)
	{
		while(display.NextEvent(event))
		{
			switch(event.type)
			{
				case ClientMessage:
				case DestroyNotify:
					done = true;
					break;
				case MotionNotify:
					example->MouseMove(
						event.xmotion.x,
						height-
						event.xmotion.y,
						width,
						height
					);
					break;
				case KeyPress:
					if(::XLookupKeysym(
						&event.xkey,
						0
					) == XK_Escape) done = true;
					break;
				default:;
			}
		}
		clock.Update(os_clock.seconds());
		if(!example->Continue(clock)) break;
		example->Render(clock);
		ctx.SwapBuffers(win);
	}
	std::cout << " `-[Done]" << std::endl;
}

void make_screenshot(
	const x11::Display& display,
	const x11::Window& win,
	const glx::Context& ctx,
	std::unique_ptr<Example>& example,
	ExampleClock& clock,
	GLuint width,
	GLuint height,
	const char* screenshot_path
)
{
	XEvent event;

	double s = example->HeatUpTime();
	double t = example->ScreenshotTime();
	double dt = example->FrameTime();

	clock.Update(s);

	// heat-up
	while(true)
	{
		while(display.NextEvent(event));
		s += dt;
		clock.Update(s);
		example->Render(clock);
		if(s < t) ctx.SwapBuffers(win);
		else break;
	}
	while(display.NextEvent(event));
	glFinish();
	//save it to a file
	std::vector<char> pixels(width * height * 3);
	glReadPixels(
		0, 0,
		width,
		height,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		pixels.data()
	);
	std::ofstream output(screenshot_path);
	output.write(pixels.data(), pixels.size());
	ctx.SwapBuffers(win);
}

void run_example(const x11::Display& display, const char* screenshot_path)
{
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

	const GLuint width = 800, height = 600;

	x11::Window win(
		display,
		vi,
		x11::Colormap(display, vi),
		"OGLplus example",
		width, height
	);

	x11::ScreenNames screen_names;

	ExampleParams params;
	params.max_threads = 128;
	params.num_gpus = screen_names.size(); // TODO: something more reliable
	setupExample(params);
	params.Check();

	glx::Context ctx(display, fbc, 3, 3);

	ctx.MakeCurrent(win);

	// The clock for animation timing
	ExampleClock clock;

	std::vector<std::thread> threads;
	ThreadSemaphore thread_ready, master_ready;
	ExampleThreadData::Common example_thread_common_data = {
		nullptr,
		params,
		clock,
		screen_names,
		display,
		vi,
		fbc,
		ctx,
		thread_ready,
		master_ready,
		false /*failure*/,
		false /*done*/
	};
	try
	{
		// Initialize the GL API library (GLEW/GL3W/...)
		oglplus::GLAPIInitializer api_init;

		// things required for multi-threaded examples
		std::vector<ExampleThreadData> thread_data;

		// prepare the example data
		for(unsigned t=0; t!=params.num_threads; ++t)
		{
			ExampleThreadData example_thread_data = {
				t, nullptr, std::string(),
				&example_thread_common_data
			};
			thread_data.push_back(example_thread_data);
		}

		// start the examples and let them
		// create their own contexts shared with
		// the main context
		for(unsigned t=0; t!=params.num_threads; ++t)
		{
			threads.emplace_back(
				call_example_thread_main,
				std::ref(thread_data[t])
			);
			// wait for the thread to create
			// an off-screen context
			thread_ready.Wait();
			// check for errors
			if(!thread_data[t].error_message.empty())
			{
				example_thread_common_data.failure = true;
				example_thread_common_data.master_ready.Signal(t);
				throw std::runtime_error(
					thread_data[t].error_message
				);
			}
		}

		// make the example
		std::unique_ptr<Example> example(makeExample(params));

		// tell the threads about the example
		// and let them call makeExampleThread
		example_thread_common_data.example = example.get();
		for(unsigned t=0; t!=params.num_threads; ++t)
		{
			// signal that the example is ready
			master_ready.Signal();
			// wait for the threads to call makeExampleThread
			thread_ready.Wait();
		}
		// check for potential errors and let
		// the example do additional thread-related preparations
		for(unsigned t=0; t!=params.num_threads; ++t)
		{
			if(!thread_data[t].error_message.empty())
			{
				example_thread_common_data.failure = true;
				example_thread_common_data.master_ready.Signal(
					params.num_threads
				);
				throw std::runtime_error(
					thread_data[t].error_message
				);
			}
			assert(thread_data[t].example_thread);
			example->PrepareThread(t,*thread_data[t].example_thread);
		}
		// signal that the example threads may start
		// rendering
		master_ready.Signal(params.num_threads);

		example->Reshape(width, height);
		example->MouseMove(width/2, height/2, width, height);

		if(screenshot_path)
		{
			make_screenshot(
				display,
				win,
				ctx,
				example,
				clock,
				width,
				height,
				screenshot_path
			);
		}
		else
		{
			run_example_loop(
				display,
				win,
				ctx,
				example,
				example_thread_common_data,
				clock,
				width,
				height
			);
		}
		example_thread_common_data.done = true;
		// cancel the example threads
		for(unsigned t=0; t!=params.num_threads; ++t)
		{
			if(thread_data[t].example_thread)
				thread_data[t].example_thread->Cancel();
		}
		// join the example threads
		for(unsigned t=0; t!=params.num_threads; ++t)
		{
			threads[t].join();
		}

		for(unsigned t=0; t!=params.num_threads; ++t)
		{
			if(!thread_data[t].error_message.empty())
				throw std::runtime_error(
					thread_data[t].error_message
				);
		}
	}
	catch(...)
	{
		example_thread_common_data.failure = true;
		master_ready.Signal(params.num_threads);
		try {for(auto& thread : threads) thread.join(); }
		catch(...){ }
		throw;
	}
	ctx.Release(display);
}

} // namespace oglplus

int glx_example_main(int argc, char ** argv)
{
	// check if we want to do a screenshot
	const char* screenshot_path = 0;
	if((argc == 3) && (std::strcmp(argv[1], "--screenshot") == 0))
		screenshot_path = argv[2];
	//
	// run the main loop
	oglplus::run_example(oglplus::x11::Display(), screenshot_path);
	return 0;
}

int main (int argc, char ** argv)
{
	return oglplus::example_main(glx_example_main, argc, argv);
}

