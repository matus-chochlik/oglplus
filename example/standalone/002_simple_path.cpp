/**
 *  @example standalone/002_simple_path.cpp
 *  @brief Shows simple usage of the NV_path_rendering extension
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "glut_glew_example.hpp"

#include <oglplus/all.hpp>
#include <oglplus/ext/ARB_compatibility.hpp>
#include <oglplus/ext/NV_path_rendering.hpp>

class PathExample
 : public oglplus::SingleExample
{
private:
	oglplus::Context gl;
	oglplus::ARB_compatibility glc;
	oglplus::NV_path_rendering pr;
public:
	PathExample(int argc, const char* argv[])
	{
		using namespace oglplus;

		gl.ClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	}

	void Render(void)
	{
		using namespace oglplus;

		gl.Clear().ColorBuffer();
	}

	void Reshape(void)
	{
		using namespace oglplus;

		gl.Viewport(Width(), Height());
	}
};

int main(int argc, char* argv[])
{
	return oglplus::GlutGlewMain<PathExample>(
		"Simple example of NV_path_rendering",
		argc, argv
	);
}

