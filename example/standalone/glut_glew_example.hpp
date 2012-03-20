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
#include <GL/glut.h>

#include <cassert>
#include <iostream>
#include <chrono>

#include <oglplus/site_config.hpp>
#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/compile_error.hpp>

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
	std::chrono::time_point<std::chrono::system_clock> _now;
	double _frame_time;

	void _update(void)
	{
		static const double period =
			double(std::chrono::system_clock::period::num)/
			double(std::chrono::system_clock::period::den);
		_now = std::chrono::system_clock::now();
		_frame_time = (_now - _start).count() * period;
	}

	size_t _width, _height;

	void _resize(size_t width, size_t height)
	{
		_width = width;
		_height = height;
	}

	size_t _prev_mouse_x, _prev_mouse_y;
	size_t _curr_mouse_x, _curr_mouse_y;

	void _mouse_move(size_t mouse_x, size_t mouse_y)
	{
		_prev_mouse_x = _curr_mouse_x;
		_prev_mouse_y = _curr_mouse_y;;
		_curr_mouse_x = mouse_x;
		_curr_mouse_y = mouse_y;
	}

public:
	double FrameTime(void) const { return _frame_time; }

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

	SingleExample(const SingleExample&) = delete;

	SingleExample(void)
	 : _width(800)
	 , _height(800)
	{
		assert(!SingleInstance());
		SingleInstance() = this;
	}

	~SingleExample(void)
	{
		assert(SingleInstance());
		SingleInstance() = nullptr;
	}

	void Startup(size_t width, size_t height)
	{
		_resize(width, height);
		Reshape();

		_mouse_move(_width/2, _height/2);
		_mouse_move(_width/2, _height/2);
		PassiveMotion();

		_start = std::chrono::system_clock::now();
		_update();
	}

	virtual void Render(void) = 0;

	static void DisplayFunc(void)
	{
		assert(SingleInstance());
		SingleInstance()->_update();
		SingleInstance()->Render();
		glutSwapBuffers();
	}

	virtual void Reshape(void) = 0;

	static void ReshapeFunc(int width, int height)
	{
		assert(SingleInstance());
		SingleInstance()->_resize(width, height);
		SingleInstance()->Reshape();
	}

	virtual void Motion(void)
	{
	}

	static void MotionFunc(int x, int y)
	{
		assert(SingleInstance());
		SingleInstance()->_mouse_move(x, y);
		SingleInstance()->Motion();
	}

	virtual void PassiveMotion(void)
	{
	}

	static void PassiveMotionFunc(int x, int y)
	{
		assert(SingleInstance());
		SingleInstance()->_mouse_move(x, y);
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
	Example example;
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
		glutReshapeFunc(&Example::ReshapeFunc);

		glutMotionFunc(&Example::MotionFunc);
		glutPassiveMotionFunc(&Example::PassiveMotionFunc);

		glutDisplayFunc(&Example::DisplayFunc);
		glutIdleFunc(&Example::DisplayFunc);

		example.Startup(width, height);
	}

	void Run(int argc, const char* argv[])
	{
		glutMainLoop();
	}
};

template <typename Example>
int GlutGlewMain(const char* title, int argc, char* argv[])
{
	try
	{
		size_t width = 800, height = 600;
		GlutGlewExampleApp<Example> app(
			100, 100,
			width, height,
			title,
			argc, argv
		);
		app.Run(argc, const_cast<const char**>(argv));
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
