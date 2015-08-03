/**
 *  @file oglplus/texgen/render_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/config/basic.hpp>
#include <oglplus/context.hpp>
#include <oglplus/vertex_attrib.hpp>
#include <oglplus/uniform.hpp>
#include <oglplus/prog_var/optional.hpp>
#include <sstream>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
void
RenderNode::
_init_prog(void)
{
	_vs.Source(
		"#version 330\n"
		"layout (location = 0) in vec2 Position;\n"
		"layout (location = 1) in vec2 Coordinate;\n"
		"out vec3 oglptgCoordinate;\n"
		"void main(void)\n"
		"{\n"
		"	gl_Position = vec4(Position, 0.0, 1.0);\n"
		"	oglptgCoordinate = vec3(Coordinate, 0.0);\n"
		"}\n"
	).Compile();

	_prog.AttachShader(_vs).AttachShader(_fs);
}

OGLPLUS_LIB_FUNC
void
RenderNode::
_update_prog(void)
{
	_prog.DetachShader(_fs).Link();

	const unsigned glsl_version = 150; // TODO

	std::stringstream source;

	source << "#version " << glsl_version << "\n";
	source << "in vec3 oglptgCoordinate;\n";
	source << "uniform vec3 oglptgCoordDelta;\n";
	source << _input.Definitions(glsl_version) << "\n";
	source << "out vec4 fragColor;\n";
	source << "void main(void)\n";
	source << "{\n";
	source << "	fragColor = " << _input.Expression(glsl_version) << "(vec3(0,0,0));\n";
	source << "}\n";

	_fs.Source(source.str()).Compile();

	_prog.AttachShader(_fs).Link();
}

OGLPLUS_LIB_FUNC
void
RenderNode::
_init_vao(void)
{
	_vao.Bind();

	{
		GLfloat position_data[8] = {
				-1.0f, -1.0f,
				-1.0f, +1.0f,
				+1.0f, -1.0f,
				+1.0f, +1.0f
		};
		_position.Bind(Buffer::Target::Array);
		Buffer::Data(Buffer::Target::Array, 8, position_data);
		VertexArrayAttrib vert_attr(0);
		vert_attr.Setup<GLfloat>(2);
		vert_attr.Enable();
	}

	{
		GLfloat coordinate_data[12] = {
				0.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 0.0f,
				1.0f, 1.0f
		};
		_coordinate.Bind(Buffer::Target::Array);
		Buffer::Data(Buffer::Target::Array, 8, coordinate_data);
		VertexArrayAttrib vert_attr(1);
		vert_attr.Setup<GLfloat>(2);
		vert_attr.Enable();
	}

	NoVertexArray().Bind();
}

OGLPLUS_LIB_FUNC
RenderNode::
RenderNode(void)
 : _input(*this, "Input", Vec4f(0.5f))
{
	_init_vao();
	_init_prog();
	_update_prog();
}

OGLPLUS_LIB_FUNC
RenderNode&
RenderNode::
Activate(void)
{
	_prog.Use();
	_vao.Bind();
	return *this;
}

OGLPLUS_LIB_FUNC
RenderNode&
RenderNode::
Deactivate(void)
{
	NoVertexArray().Bind();
	NoProgram().Use();
	return *this;
}

OGLPLUS_LIB_FUNC
std::size_t
RenderNode::
InputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
InputSlot&
RenderNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	return _input;
}

OGLPLUS_LIB_FUNC
void
RenderNode::
Render(void)
{
	auto vpe = oglplus::Context::Viewport();

	Optional<Uniform<Vec3f>>(_prog, "oglptgCoordDelta").TrySet(Vec3f(
		1.0f/vpe.Width(), 1.0f/vpe.Height(), 1.f
	));

	oglplus::Context::DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
}


OGLPLUS_LIB_FUNC
void
RenderNode::
Validate(InputSlot& input)
{
	assert(&input == &_input);
	// TODO
}

OGLPLUS_LIB_FUNC
void
RenderNode::
Update(void)
{
	_update_prog();
	Activate();
	Render();
}

} // namespace texgen
} // namespace oglplus

