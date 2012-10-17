/*
 *  @file standalone/glut_glew_example.hpp
 *  @brief Implements GLUT/GLEW-based program main function for running examples
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef __OGLPLUS_STANDALONE_GLUT_GLEW_EXAMPLE_1203161253_HPP__
#define __OGLPLUS_STANDALONE_GLUT_GLEW_EXAMPLE_1203161253_HPP__

#include <GL/glew.h>

#include <oglplus/config.hpp>

#if OGLPLUS_USE_FREEGLUT
# include <GL/freeglut.h>
#else
# include <GL/glut.h>
#endif

#include <cassert>
#include <iostream>
#include <chrono>

#include <oglplus/error.hpp>
#include <oglplus/compile_error.hpp>

namespace oglplus {

class StandaloneExample
{
private:
	std::chrono::time_point<std::chrono::system_clock> _start;
	std::chrono::time_point<std::chrono::system_clock> _now;
	double _frame_time, _frame_duration;
	unsigned long _frame_number;

	size_t _width, _height;

	size_t _prev_mouse_x, _prev_mouse_y;
	size_t _curr_mouse_x, _curr_mouse_y;

public:
	void HandleUpdate(void)
	{
		static const double period =
			double(std::chrono::system_clock::period::num)/
			double(std::chrono::system_clock::period::den);
		auto now = std::chrono::system_clock::now();
		_frame_duration = (now - _now).count() * period;
		_now = now;
		_frame_time = (_now - _start).count() * period;
		++_frame_number;
	}

	void HandleResize(size_t width, size_t height)
	{
		_width = width;
		_height = height;
	}

	void HandleMouseMove(size_t mouse_x, size_t mouse_y)
	{
		_prev_mouse_x = _curr_mouse_x;
		_prev_mouse_y = _curr_mouse_y;;
		_curr_mouse_x = mouse_x;
		_curr_mouse_y = mouse_y;
	}


	double FrameTime(void) const { return _frame_time; }
	double FrameDuration(void) const { return _frame_duration; }
	unsigned long FrameNumber(void) const { return _frame_number; }

	double CurrentFPS(void) const { return 1.0 / _frame_duration; }
	double AverageFPS(void) const { return _frame_number / _frame_time; }

	size_t Width(void) const { return _width; }
	size_t Height(void) const { return _height; }
	double Aspect(void) const { return double(_width)/double(_height); }

	size_t MouseX(void) const { return _curr_mouse_x; }
	size_t MouseY(void) const { return _curr_mouse_y; }

	int MouseDiffX(void) const
	{
		return _curr_mouse_x - _prev_mouse_x;
	}

	int MouseDiffY(void) const
	{
		return _curr_mouse_y - _prev_mouse_y;
	}

	double NormMouseX(void) const
	{
		return double(2*_curr_mouse_x)/_width - 1.0;
	}

	double NormMouseY(void) const
	{
		return double(2*_curr_mouse_y)/_height - 1.0;
	}

	double NormMouseDiffX(void) const
	{
		return double(2*MouseDiffX())/_width;
	}

	double NormMouseDiffY(void) const
	{
		return double(2*MouseDiffY())/_height;
	}

private:
	StandaloneExample(const StandaloneExample&);
public:

	StandaloneExample(void)
	 : _width(800)
	 , _height(800)
	{ }

	void Startup(size_t width, size_t height)
	{
		HandleResize(width, height);
		Reshape();

		HandleMouseMove(_width/2, _height/2);
		HandleMouseMove(_width/2, _height/2);
		PassiveMotion();

		_start = std::chrono::system_clock::now();
		_frame_number = 0;
		HandleUpdate();
	}

	virtual void Render(void) = 0;

	virtual void Reshape(void) = 0;

	virtual void Motion(void)
	{
	}

	virtual void PassiveMotion(void)
	{
	}
};

template <typename Example>
class SingleExampleTpl
{
private:
	static Example*& SingleInstance(void)
	{
		static Example* _ptr = nullptr;
		return _ptr;
	}
public:
	SingleExampleTpl(int argc, const char** argv)
	{
		assert(!SingleInstance());
		SingleInstance() = new Example(argc, argv);
	}

	~SingleExampleTpl(void)
	{
		delete SingleInstance();
	}

	void Startup(size_t width, size_t height)
	{
		assert(SingleInstance());
		SingleInstance()->Startup(width, height);
	}

	static void CloseFunc(void)
	{
		assert(SingleInstance());
		delete SingleInstance();
		SingleInstance() = nullptr;
	}

	static void DisplayFunc(void)
	{
		assert(SingleInstance());
		SingleInstance()->HandleUpdate();
		SingleInstance()->Render();
		glutSwapBuffers();
	}

	static void ReshapeFunc(int width, int height)
	{
		assert(SingleInstance());
		SingleInstance()->HandleResize(width, height);
		SingleInstance()->Reshape();
	}

	static void MotionFunc(int x, int y)
	{
		assert(SingleInstance());
		SingleInstance()->HandleMouseMove(x, y);
		SingleInstance()->Motion();
	}

	static void PassiveMotionFunc(int x, int y)
	{
		assert(SingleInstance());
		SingleInstance()->HandleMouseMove(x, y);
		SingleInstance()->PassiveMotion();
	}
};

class GlutInit
{
protected:
	GlutInit(
		size_t xpos,
		size_t ypos,
		size_t width,
		size_t height,
		const char* window_title,
		int &argc,
		char* argv[]
	)
	{
		glutInit(&argc, argv);

		glutInitDisplayMode(
			GLUT_DOUBLE |
			GLUT_RGBA |
			GLUT_DEPTH |
			GLUT_STENCIL
		);

		glutInitWindowPosition(xpos, ypos);
		glutInitWindowSize(width, height);

		glutCreateWindow(window_title);
	}
};

class GlewInit
{
protected:
	GlewInit(void)
	{
		if(glewInit() != GLEW_OK)
		{
			throw std::runtime_error(
				"GLEW initialization error"
			);
		}
	}
};

template <typename Example>
class GlutGlewExampleApp
 : public GlutInit
 , public GlewInit
{
private:
	typedef SingleExampleTpl<Example> SingleExample;
	SingleExample example;

	GlutGlewExampleApp(const GlutGlewExampleApp&);
public:
	GlutGlewExampleApp(
		size_t xpos,
		size_t ypos,
		size_t width,
		size_t height,
		const char* window_title,
		int &argc,
		char* argv[]
	): GlutInit(
		xpos,
		ypos,
		width,
		height,
		window_title,
		argc,
		argv
	), GlewInit()
	 , example(argc, const_cast<const char**>(argv))
	{
		glutReshapeFunc(&SingleExample::ReshapeFunc);

		glutMotionFunc(&SingleExample::MotionFunc);
		glutPassiveMotionFunc(&SingleExample::PassiveMotionFunc);

		glutDisplayFunc(&SingleExample::DisplayFunc);
		glutIdleFunc(&SingleExample::DisplayFunc);

		example.Startup(width, height);
	}

	void Run(int /*argc*/, const char** /*argv*/)
	{
#if OGLPLUS_USE_FREEGLUT
		glutSetOption(
			GLUT_ACTION_ON_WINDOW_CLOSE,
			GLUT_ACTION_GLUTMAINLOOP_RETURNS
		);
		glutCloseFunc(&SingleExample::CloseFunc);
#endif
		glutMainLoop();
	}
};

template <typename Example>
int GlutGlewMain(const char* title, int argc, char* argv[])
{
	try
	{
		std::cout << "Started" << std::endl;
		{
			size_t width = 800, height = 600;
			GlutGlewExampleApp<Example> app(
				100, 100,
				width, height,
				title,
				argc, argv
			);
			app.Run(argc, const_cast<const char**>(argv));
		}
		std::cout << "Finished" << std::endl;
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

} // namespace oglplus

#endif
