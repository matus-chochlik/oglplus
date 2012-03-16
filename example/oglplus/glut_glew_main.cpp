/*
 *  .file example/glut_glew_main.cpp
 *  Implements GLUT/GLEW-based program main function for running examples
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <GL/glew.h>
#include <GL/glut.h>

#include <cassert>
#include <iostream>
#include <chrono>

#include <oglplus/site_config.hpp>
#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/compile_error.hpp>

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

	std::chrono::time_point<std::chrono::system_clock> _start;
	size_t _width, _height;
	ExampleParams _params;
	std::unique_ptr<Example> _example;
public:
	SingleExample(const SingleExample&) = delete;

	Example* operator ->(void)
	{
		assert(SingleInstance());
		return SingleInstance()->_example.get();
	}

	SingleExample(size_t width, size_t height)
	 : _width(width)
	 , _height(height)
	 , _params()
	 , _example(makeExample(_params))
	{
		assert(!SingleInstance());
		SingleInstance() = this;

		_example->Reshape(width, height);
		_example->MouseMove(width/2, height/2, width, height);
		_start = std::chrono::system_clock::now();
	}

	~SingleExample(void)
	{
		assert(SingleInstance());
		SingleInstance() = nullptr;
	}

	void Display(void)
	{
		static const double period =
			double(std::chrono::system_clock::period::num)/
			double(std::chrono::system_clock::period::den);
		auto now = std::chrono::system_clock::now();
		double frame_time = (now - _start).count() * period;

		_example->Render(frame_time);
		glutSwapBuffers();
	}

	static void DisplayFunc(void)
	{
		assert(SingleInstance());
		SingleInstance()->Display();
	}

	void Reshape(int width, int height)
	{
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
};

} // namespace oglplus

int main(int argc, char* argv[])
{
	size_t width = 800, height = 600;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100,100);
	glutCreateWindow("OGLplus+GLUT+GLEW");

	if(glewInit() == GLEW_OK) try
	{
		using oglplus::SingleExample;

		SingleExample example(width, height);
		glutDisplayFunc(&SingleExample::DisplayFunc);
		glutIdleFunc(&SingleExample::DisplayFunc);
		glutReshapeFunc(&SingleExample::ReshapeFunc);

		if(example->UsesMouseMotion())
		{
			glutMotionFunc(&SingleExample::MotionFunc);
			glutPassiveMotionFunc(&SingleExample::MotionFunc);
		}

		glutMainLoop();
		return 0;
	}
	catch(oglplus::ProgramBuildError& pbe)
	{
		std::cerr <<
			"Error (in " << pbe.GLSymbol() << ", " <<
			pbe.ClassName() << ": '" <<
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

