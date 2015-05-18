/*
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
//[oglplus_example_hello_world_1
#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <oglplus/all.hpp>
//]
//[oglplus_example_hello_world_2
class Example
{
private:
	oglplus::__Context gl;

	oglplus::__VertexShader vs;

	oglplus::__FragmentShader fs;

	oglplus::__Program prog;

	oglplus::__VertexArray triangle;

	oglplus::__Buffer verts;
public:
	Example(void)
	{
		using namespace oglplus;

		vs.Source(
			"#version 330\n"
			"in vec3 Position;"
			"void main(void)"
			"{"
			"	gl_Position = vec4(Position, 1.0);"
			"}"
		);
		vs.Compile();

		fs.Source(
			"#version 330\n"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(1.0, 0.0, 0.0, 1.0);"
			"}"
		);
		fs.Compile();

		prog.AttachShader(vs);
		prog.AttachShader(fs);

		prog.Link();
		prog.Use();

		triangle.Bind();

		GLfloat triangle_verts[9] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

		verts.Bind(__BufferTarget::Array);
		__Buffer::Data(
			__BufferTarget::Array,
			9,
			triangle_verts
		);

		__VertexArrayAttrib vert_attr(prog, "Position");
		vert_attr.Setup<GLfloat>(3);
		vert_attr.Enable();

		gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		gl.ClearDepth(1.0f);
	}

	void Display(void)
	{
		using namespace oglplus;

		gl.Clear().ColorBuffer().DepthBuffer();

		gl.DrawArrays(__PrimitiveType::Triangles, 0, 3);
	}
};
//]
//[oglplus_example_hello_world_3
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
//]
//[oglplus_example_hello_world_4
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("OGLplus+GLUT+GLEW");

	if(glewInit() == GLEW_OK) try
	{
		glGetError();
		SingleExample example;
		glutDisplayFunc(&SingleExample::Display);
		glutMainLoop();
		return 0;
	}
	catch(oglplus::__Error& err)
	{
		std::cerr
			<< "Error (in "
			<< err.GLFunc()
			<< "'): "
			<< err.what()
			<< " ["
			<< err.SourceFile()
			<< ":"
			<< err.SourceLine()
			<< "] "
			<< std::endl;
	}
	return 1;
}
//]

