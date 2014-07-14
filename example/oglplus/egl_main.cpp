/*
 *  .file example/oglplus/egl_main.cpp
 *  Implements EGL-based program main function for running examples
 *  .note This harness does only off-screen rendering into an EGL Pbuffer
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/config/fix_gl_version.hpp>
#include <eglplus/egl.hpp>

#define EGL_CONTEXT_MAJOR_VERSION       0x3098
#define EGL_CONTEXT_MINOR_VERSION       0x30FB
#define EGL_CONTEXT_OPENGL_PROFILE_MASK 0x30FD
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT 0x00000001

#include <oglplus/os/steady_clock.hpp>

#include <oglplus/math/vector.hpp>
#include <oglplus/math/curve.hpp>

#include <eglplus/all.hpp>

#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
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
		const eglplus::Display& display;
		const eglplus::Config& config;
		const eglplus::SurfaceAttribs surface_attribs;
		const eglplus::ContextAttribs context_attribs;
		const eglplus::Context& context;
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

	eglplus::Display display;

	eglplus::Surface surface = eglplus::Surface::Pbuffer(
		display,
		common.config,
		common.surface_attribs.Get()
	);

	eglplus::BindAPI(eglplus::RenderingAPI::OpenGL);

	eglplus::Context context(
		display,
		common.config,
		common.context,
		common.context_attribs.Get()
	);

	context.MakeCurrent(surface);

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
				unsigned part_no = 0;
				double comp = 0.0;
				do
				{
					comp = example_thread->RenderPart(
						part_no++,
						common.clock
					);
					glFlush();
				}
				while(comp < 1.0);
			}
			data.example_thread = nullptr;
		}
		catch(...)
		{
			data.example_thread = nullptr;
			throw;
		}
	}
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

void run_framedump_loop(
	eglplus::Surface& surface,
	std::unique_ptr<Example>& example,
	ExampleClock& clock,
	GLuint width,
	GLuint height,
	const char* framedump_prefix
)
{
	std::vector<char> txtbuf(1024);
	std::cin.getline(txtbuf.data(), txtbuf.size());
	if(std::strcmp(framedump_prefix, txtbuf.data()) != 0) return;

	const std::size_t mouse_path_pts = 7;
	std::vector<Vec2f> mouse_path_pos(mouse_path_pts);
	std::vector<Vec2f> mouse_path_dir(mouse_path_pts);

	for(std::size_t p=0; p!= mouse_path_pts; ++p)
	{
		mouse_path_pos[p] = Vec2f(
			std::rand() % width,
			std::rand() % height
		);
		mouse_path_dir[p] = Vec2f(
			(std::rand()%2?1.0:-1.0)*10.0f*
			(0.2+float(std::rand())/float(RAND_MAX)*0.8),
			(std::rand()%2?1.0:-1.0)*10.0f*
			(0.2+float(std::rand())/float(RAND_MAX)*0.8)
		);
	}

	typedef CubicBezierLoop<Vec2f, double> Loop;

	double t = 0.0;
	double period = 1.0 / 25.0;
	GLuint frame_no = 0;
	std::vector<char> pixels(width * height * 4);

	GLuint border = 32;

	while(true)
	{
		Vec2f mouse_pos = Loop(mouse_path_pos).Position(t*0.2);

		for(std::size_t p=0; p!= mouse_path_pts; ++p)
		{
			Vec2f dir = mouse_path_dir[p];
			Vec2f pos = mouse_path_pos[p];

			if((pos.x() < border) && (dir.x() < 0.0))
				dir = Vec2f(-dir.x(), dir.y());
			if((pos.y() < border) && (dir.y() < 0.0))
				dir = Vec2f( dir.x(),-dir.y());
			if((pos.x() > width-border) && (dir.x() > 0.0))
				dir = Vec2f(-dir.x(), dir.y());
			if((pos.y() >height-border) && (dir.y() > 0.0))
				dir = Vec2f( dir.x(),-dir.y());

			mouse_path_dir[p] = dir;
			mouse_path_pos[p] = pos + dir;
		}

		float mouse_x = mouse_pos.x();
		float mouse_y = mouse_pos.y();

		if(mouse_x < 0.0f) mouse_x = 0.0f;
		if(mouse_y < 0.0f) mouse_y = 0.0f;
		if(mouse_x > width) mouse_x = width;
		if(mouse_y > height) mouse_y = height;

		example->MouseMove(
			GLuint(mouse_x),
			GLuint(mouse_y),
			width,
			height
		);

		t += period;
		clock.Update(t);
		if(!example->Continue(clock)) break;

		unsigned part_no = 0;
		double comp = 0.0;
		do
		{
			comp = example->RenderPart(part_no++, clock);
		}
		while(comp < 1.0);

		glFinish();
		glReadPixels(
			0, 0,
			width,
			height,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			pixels.data()
		);
		glFinish();
		surface.SwapBuffers();
		std::stringstream filename;
		filename <<
			framedump_prefix <<
			std::setfill('0') << std::setw(6) <<
			frame_no << ".rgba";
		{
			std::ofstream file(filename.str());
			file.write(pixels.data(), pixels.size());
			file.flush();
		}
		std::cout << filename.str() << std::endl;
		++frame_no;

		txtbuf.resize(filename.str().size()+1);
		std::cin.getline(txtbuf.data(), txtbuf.size());

		if(std::strncmp(
			filename.str().c_str(),
			txtbuf.data(),
			txtbuf.size()
		) != 0) break;
	}
}

void make_screenshot(
	eglplus::Surface& surface,
	std::unique_ptr<Example>& example,
	ExampleClock& clock,
	GLuint width,
	GLuint height,
	const char* screenshot_path
)
{
	double s = example->HeatUpTime();
	double t = example->ScreenshotTime();
	double dt = example->FrameTime();

	clock.Update(s);

	// heat-up
	while(s < t)
	{
		s += dt;
		clock.Update(s);

		unsigned part_no = 0;
		double comp = 0.0;
		do
		{
			comp = example->RenderPart(part_no++, clock);
		}
		while(comp < 1.0);
		if(s < t) surface.SwapBuffers();
	}
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
	surface.SwapBuffers();
}


void run_example(
	const eglplus::Display& display,
	const char* screenshot_path,
	const char* framedump_prefix,
	const GLuint width,
	const GLuint height,
	int argc,
	char ** argv
)
{
	eglplus::Configs configs(
		display,
		eglplus::ConfigAttribs()
			.Add(eglplus::ConfigAttrib::RedSize, 8)
			.Add(eglplus::ConfigAttrib::GreenSize, 8)
			.Add(eglplus::ConfigAttrib::BlueSize, 8)
			.Add(eglplus::ConfigAttrib::DepthSize, 24)
			.Add(eglplus::ConfigAttrib::StencilSize, 8)
			.Add(eglplus::ColorBufferType::RGBBuffer)
			.Add(eglplus::RenderableTypeBit::OpenGL)
			.Add(eglplus::SurfaceTypeBit::Pbuffer)
			.Get()
	);

	eglplus::Config config = configs.First();


	eglplus::SurfaceAttribs surface_attribs = eglplus::SurfaceAttribs()
			.Add(eglplus::SurfaceAttrib::Width, GLint(width))
			.Add(eglplus::SurfaceAttrib::Height, GLint(height));

	eglplus::Surface surface = eglplus::Surface::Pbuffer(
		display,
		config,
		surface_attribs.Get()
	);

	eglplus::BindAPI(eglplus::RenderingAPI::OpenGL);

	eglplus::ContextAttribs context_attribs =
		eglplus::ContextAttribs()
			.Add(eglplus::ContextAttrib::MajorVersion, 3)
			.Add(eglplus::ContextAttrib::MinorVersion, 3)
			.Add(eglplus::OpenGLProfileBit::Core);

	eglplus::Context context(
		display,
		config,
		context_attribs.Get()
	);

	context.MakeCurrent(surface);

	ExampleParams params(argc, argv);
	params.quality = 1.0;
	params.max_threads = 128;
	params.num_gpus = 1;
	setupExample(params);
	params.Check();

	ExampleClock clock;

	std::vector<std::thread> threads;
	ThreadSemaphore thread_ready, master_ready;
	ExampleThreadData::Common example_thread_common_data = {
		nullptr,
		params,
		clock,
		display,
		config,
		surface_attribs,
		context_attribs,
		context,
		thread_ready,
		master_ready,
		false, //failure
		false //done
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
				surface,
				example,
				clock,
				width,
				height,
				screenshot_path
			);
		}
		else if(framedump_prefix)
		{
			run_framedump_loop(
				surface,
				example,
				clock,
				width,
				height,
				framedump_prefix
			);
		}
		else assert(!"Never should get here!");

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
}

} // namespace oglplus

int egl_example_main(int argc, char ** argv)
{
	const char* screenshot_path = nullptr;
	const char* framedump_prefix = nullptr;
	if((argc >= 3) && (std::strcmp(argv[1], "--screenshot") == 0))
		screenshot_path = argv[2];
	if((argc >= 3) && (std::strcmp(argv[1], "--frame-dump") == 0))
		framedump_prefix = argv[2];

	GLuint width = 0, height = 0;

	if(screenshot_path || framedump_prefix)
	{
		for(int a=3; a<argc; ++a)
			argv[a-2] = argv[a];
		argc -= 2;

		int a=1;
		while(a<argc)
		{
			if(std::strcmp(argv[a], "--width") == 0 && (a+1<argc))
			{
				width = std::atoi(argv[a+1]);
				for(int b=a+1; b<argc; ++b)
					argv[b-2] = argv[b];
				argc -= 2;
			}
			else if(std::strcmp(argv[a], "--height") == 0 && (a+1<argc))
			{
				height = std::atoi(argv[a+1]);
				for(int b=a+1; b<argc; ++b)
					argv[b-2] = argv[b];
				argc -= 2;
			}
			else ++a;
		}
	}
	else
	{
		std::cout <<
			"--screenshot or --framedump option "
			"must be specified" <<
			std::endl;
		return 1;
	}

	if(!width) width = 800;
	if(!height) height = 600;
	//
	eglplus::Display display;
	eglplus::LibEGL egl(display);
	// run the main loop
	oglplus::run_example(
		display,
		screenshot_path,
		framedump_prefix,
		width,
		height,
		argc,
		argv
	);
	return 0;
}

int main (int argc, char ** argv)
{
	return oglplus::example_main(egl_example_main, argc, argv);
}

