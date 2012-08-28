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

	oglplus::PathNV path;
public:
	PathExample(int, const char**)
	{
		using namespace oglplus;

		PathNVCommand commands[] = {
			PathNVCommand::MoveTo,
			PathNVCommand::LineTo,
			PathNVCommand::LineTo,
			PathNVCommand::LineTo,
			PathNVCommand::LineTo,
			PathNVCommand::Close
		};

		GLfloat coords[] = {
			 0.00, 0.85,
			 0.65,-0.80,
			-0.85, 0.30,
			 0.85, 0.30,
			-0.65,-0.80
		};

		path.Commands(
			sizeof(commands)/sizeof(commands[0]),
			commands,
			sizeof(coords)/sizeof(coords[0]),
			coords
		);

		path.StrokeWidth(0.01);
		path.JoinStyle(PathNVJoinStyle::Round);

		GLfloat dash_array[] = {0.05, 0.02};

		path.DashArray(
			sizeof(dash_array)/sizeof(dash_array[0]),
			dash_array
		);

		glc.MatrixMode(CompatibilityMatrixMode::Projection);
		glc.LoadIdentity();
		glc.MatrixMode(CompatibilityMatrixMode::Modelview);
		glc.LoadIdentity();

		gl.ClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		gl.ClearStencil(0);
		gl.StencilMask(~0);
		gl.StencilFunc(CompareFunction::NotEqual, 0, 0x1F);
		gl.StencilOp(
			StencilOperation::Keep,
			StencilOperation::Keep,
			StencilOperation::Zero
		);

		gl.Enable(Capability::StencilTest);
	}

	void Render(void)
	{
		using namespace oglplus;

		gl.Clear().ColorBuffer().StencilBuffer();

		glc.Color(0.2, 0.2, 1.0);

		path.StencilFill(PathNVFillMode::CountUp, 0x1F);
		path.CoverFill(PathNVFillCoverMode::BoundingBox);

		glc.Color(0.1, 0.1, 0.1);

		path.StencilStroke(1, ~0);
		path.CoverStroke(PathNVStrokeCoverMode::ConvexHull);
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

