/*
 *  .file example/glut_main.cpp
 *  Implements GLUT-based program main function for running examples
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>

#if OGLPLUS_USE_FREEGLUT
# include <GL/freeglut.h>
#else
# include <GL/glut.h>
#endif

#include <cstring>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

#include <oglplus/site_config.hpp>

#if OGLPLUS_LINK_LIBRARY
# include <oglplus/lib.hpp>
#endif

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/compile_error.hpp>
#include <oglplus/opt/application.hpp>

#include <oglplus/query.hpp>

#include <oglplus/os/steady_clock.hpp>

#include "example.hpp"

namespace oglplus {

class SingleExample
{
private:
	static SingleExample*& SingleInstance(void)
	{
		static SingleExample* wrapper = nullptr;
		return wrapper;
	}

	os::steady_clock _os_clock;
	ExampleClock _clock;
	double _fps_time, _prim_count;
	unsigned long _frame_no;
	GLuint _width, _height;
	ExampleParams _params;
	std::unique_ptr<Example> _example;
	std::unique_ptr<Query> _primitive_query;

	const char* _screenshot_path;

	SingleExample(const SingleExample&);
public:

	Example* operator ->(void)
	{
		assert(SingleInstance());
		return SingleInstance()->_example.get();
	}

	SingleExample(GLuint width, GLuint height, const char* screenshot_path)
	 : _fps_time(0.0)
	 , _prim_count(0.0)
	 , _frame_no(0)
	 , _width(width)
	 , _height(height)
	 , _params()
	 , _example(makeExample(_params))
	 , _primitive_query(new Query())
	 , _screenshot_path(screenshot_path)
	{
		assert(!SingleInstance());
		SingleInstance() = this;

		_example->Reshape(width, height);
		_example->MouseMove(width/2, height/2, width, height);
		_os_clock.reset();

		if(_screenshot_path)
			_clock.Update(_example->HeatUpTime());
	}

	~SingleExample(void)
	{
		assert(SingleInstance());
		SingleInstance() = nullptr;
	}

	void Quit(void)
	{
#if OGLPLUS_USE_FREEGLUT
		glutLeaveMainLoop();
#else
		exit(0);
#endif
	}

	void Close(void)
	{
		_primitive_query.reset();
		_example.reset();
	}

	static void CloseFunc(void)
	{
		assert(SingleInstance());
		SingleInstance()->Close();
	}

	void Display(void)
	{
		_clock.Update(_os_clock.seconds());
		double frame_time = _clock.Now().Seconds();
		_frame_no++;

		GLuint primitives_per_frame = 0;
		{
			auto query_exec = _primitive_query->Execute(
				Query::Target::PrimitivesGenerated,
				primitives_per_frame
			);
			_example->Render(_clock);
			glutSwapBuffers();
		}
		_prim_count += double(primitives_per_frame);

		const double fps_interval = 10.0;
		const double this_interval = frame_time - _fps_time;
		if(this_interval >= fps_interval)
		{
			_fps_time = frame_time;
			std::cout.width(5);
			std::cout.precision(3);
			std::cout << _frame_no << " frames in "
				<< std::fixed << this_interval << " seconds = "
				<< std::fixed << _frame_no/this_interval << " FPS; "
				<< std::scientific << _prim_count/this_interval << " PPS; "
				<< std::scientific << _prim_count/_frame_no << " PPF; "
				<< std::endl;
			_frame_no = 0;
			_prim_count = 0.0;
		}
	}

	static void DisplayFunc(void)
	{
		assert(SingleInstance());
		SingleInstance()->Display();
	}

	void Screenshot(void)
	{
		_example->Render(_clock);
		if(_clock.Now().Seconds() >= _example->ScreenshotTime())
		{
			glFinish();
			std::vector<char> pixels(_width * _height * 3);
			glReadPixels(
				0, 0,
				_width,
				_height,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				pixels.data()
			);
			std::ofstream output(_screenshot_path);
			output.write(pixels.data(), pixels.size());
			Quit();
		}
		glutSwapBuffers();
		_clock.Advance(_example->FrameTime());
	}

	static void ScreenshotFunc(void)
	{
		assert(SingleInstance());
		SingleInstance()->Screenshot();
	}

	void Reshape(int width, int height)
	{
		_width = width;
		_height= height;
		_example->Reshape(width, height);
	}

	static void ReshapeFunc(int width, int height)
	{
		assert(SingleInstance());
		SingleInstance()->Reshape(width, height);
	}

	void Motion(int x, int y)
	{
		_example->MouseMove(x, _height-y, _width, _height);
	}

	static void MotionFunc(int x, int y)
	{
		assert(SingleInstance());
		SingleInstance()->Motion(x, y);
	}

	void KeyPress(unsigned char /*k*/)
	{
		// TODO
	}

	static void KeyboardFunc(unsigned char k, int, int)
	{
		if(k == 0x1B) // Escape
		{
			assert(SingleInstance());
			SingleInstance()->Quit();
		}
		else
		{
			assert(SingleInstance());
			SingleInstance()->KeyPress(k);
		}
	}
};

} // namespace oglplus

int main(int argc, char* argv[])
{
	oglplus::Application::ParseCommandLineOptions(argc, argv);

	GLuint width = 800, height = 600;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100,100);
	glutCreateWindow("OGLplus example");

	try
	{
		oglplus::GLAPIInitializer api_init;
		using oglplus::SingleExample;

		const char* screenshot_path = nullptr;
		if((argc == 3) && (std::strcmp(argv[1], "--screenshot") == 0))
			screenshot_path = argv[2];

		SingleExample example(width, height, screenshot_path);
		if(screenshot_path)
		{
			glutDisplayFunc(&SingleExample::ScreenshotFunc);
			glutIdleFunc(&SingleExample::ScreenshotFunc);
		}
		else
		{
			glutDisplayFunc(&SingleExample::DisplayFunc);
			glutIdleFunc(&SingleExample::DisplayFunc);
		}
		glutReshapeFunc(&SingleExample::ReshapeFunc);

		if(example->UsesMouseMotion())
		{
			glutMotionFunc(&SingleExample::MotionFunc);
			glutPassiveMotionFunc(&SingleExample::MotionFunc);
		}

		glutKeyboardFunc(&SingleExample::KeyboardFunc);
#if OGLPLUS_USE_FREEGLUT
		glutSetOption(
			GLUT_ACTION_ON_WINDOW_CLOSE,
			GLUT_ACTION_GLUTMAINLOOP_RETURNS
		);
		glutCloseFunc(&SingleExample::CloseFunc);
#endif

		glutMainLoop();
		return 0;
	}
	catch(oglplus::ProgramBuildError& pbe)
	{
		std::cerr <<
			"Error (in " << pbe.GLSymbol() << ", " <<
			pbe.ClassName() << " (" <<
			pbe.BindTarget() << "): '" <<
			pbe.ObjectDescription() << "'): " <<
			pbe.what() << ": " <<
			pbe.Log() <<
			std::endl;
		pbe.Cleanup();
	}
	catch(oglplus::LimitError& le)
	{
		std::cerr <<
			"Limit error: ("<< le.Value() << ") exceeds (" <<
			le.GLSymbol() << " == " << le.Limit() << ") " <<
			" [" << le.File() << ":" << le.Line() << "] " <<
			std::endl;
		le.Cleanup();
	}
	catch(oglplus::Error& err)
	{
		std::cerr <<
			"Error (in " << err.GLSymbol() << ", " <<
			err.ClassName() << ": '" <<
			err.ObjectDescription() << "' bound to '" <<
			err.BindTarget() << "'): " <<
			err.what() <<
			" [" << err.File() << ":" << err.Line() << "] ";
		auto i = err.Properties().begin(), e = err.Properties().end();
		while(i != e)
		{
			std::cerr << "<" << i->first << "='" << i->second << "'>";
			++i;
		}
		std::cerr <<std::endl;
		err.Cleanup();
	}
	catch(std::exception& se)
	{
		std::cerr << "Error: " << se.what() << std::endl;
	}
	return 1;
}

