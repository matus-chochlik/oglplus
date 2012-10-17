/**
 *  @example standalone/002_rectangle_glut_glew.cpp
 *  @brief Shows the basic usage of OGLplus with GLUT and GLEW.
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <oglplus/all.hpp>

class Example
{
private:
	oglplus::Context gl;

	oglplus::VertexShader vs;

	oglplus::GeometryShader gs;

	oglplus::FragmentShader fs;

	oglplus::Program prog;
public:
	Example(void)
	{
		using namespace oglplus;

		// Set the vertex shader source
		vs.Source(" \
			#version 330\n \
			void main(void) { } \
		");
		// compile it
		vs.Compile();

		// Set the geometry shader source
		gs.Source(" \
			#version 330\n \
			layout (points) in; \
			layout (triangle_strip, max_vertices=4) out;\
			out vec3 geomColor; \
			void main(void) \
			{ \
				gl_Position = vec4(-1.0,-1.0, 0.0, 1.0); \
				geomColor = vec3(0.0, 0.0, 0.0); \
				EmitVertex(); \
				gl_Position = vec4(-1.0, 1.0, 0.0, 1.0); \
				geomColor = vec3(1.0, 0.0, 0.0); \
				EmitVertex(); \
				gl_Position = vec4( 1.0,-1.0, 0.0, 1.0); \
				geomColor = vec3(0.0, 1.0, 0.0); \
				EmitVertex(); \
				gl_Position = vec4( 1.0, 1.0, 0.0, 1.0); \
				geomColor = vec3(0.0, 0.0, 1.0); \
				EmitVertex(); \
				EndPrimitive(); \
			} \
		");
		// compile it
		gs.Compile();

		// set the fragment shader source
		fs.Source(" \
			#version 330\n \
			in vec3 geomColor; \
			out vec3 fragColor; \
			void main(void) \
			{ \
				fragColor = geomColor; \
			} \
		");
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(gs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		gl.ClearDepth(1.0f);
	}

	void Display(void)
	{
		using namespace oglplus;

		gl.Clear().ColorBuffer().DepthBuffer();

		gl.DrawArrays(PrimitiveType::Points, 0, 1);
	}
};

class SingleExample
{
private:
	static Example*& SingleInstance(void)
	{
		static Example* test = nullptr;
		return test;
	}

	SingleExample(const SingleExample&);
public:

	SingleExample(void)
	{
		assert(!SingleInstance());
		SingleInstance() = new Example();
	}

	~SingleExample(void)
	{
		assert(SingleInstance());
		delete SingleInstance();
		SingleInstance() = nullptr;
	}

	static void Display(void)
	{
		assert(SingleInstance());
		SingleInstance()->Display();
		glutSwapBuffers();
	}
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("OGLplus+GLUT+GLEW");

	if(glewInit() == GLEW_OK) try
	{
		SingleExample example;
		glutDisplayFunc(&SingleExample::Display);
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
	catch(oglplus::Error& err)
	{
		std::cerr <<
			"Error (in " << err.GLSymbol() << ", " <<
			err.ClassName() << ": '" <<
			err.ObjectDescription() << "'): " <<
			err.what() <<
			" [" << err.File() << ":" << err.Line() << "] ";
		std::cerr << std::endl;
		err.Cleanup();
	}
	return 1;
}

