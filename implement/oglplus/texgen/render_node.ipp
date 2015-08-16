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

	const SlotDataType v4 = SlotDataType::FloatVec4;

	std::stringstream source;

	source << "#version " << glsl_version << "\n";
	source << "in vec3 oglptgCoordinate;\n";
	source << "uniform vec3 oglptgCoordDelta;\n";
	source << "uniform vec3 oglptgOutputSize;\n";
	_input.Definitions(source, glsl_version) << "\n";
	source << "out vec4 fragColor;\n";
	source << "void main(void)\n";
	source << "{\n";
	source << "	fragColor = ";
	ConversionPrefix(source, _input.ValueType(), v4);
	_input.Expression(source, glsl_version);
	source << "(vec3(0,0,0))";
	ConversionSuffix(source, _input.ValueType(), v4, 0,0,0,1);
	source << ";\n";
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
RenderNode(unsigned xdiv, unsigned ydiv)
 : _input(*this, "Input", Vec4f(0.5f))
 , _xdiv(xdiv)
 , _ydiv(ydiv)
 , _tile(0)
 , _render_version(0)
{
	_render_params.version = 1;
	assert(_xdiv > 0);
	assert(_ydiv > 0);
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
}

OGLPLUS_LIB_FUNC
bool
RenderNode::
Render(const RenderParams& params)
{
	if(_render_version < params.version)
	{
		if(_tile == 0)
		{
			if(!_input.Render(params))
			{
				return false;
			}

			Optional<Uniform<Vec3f>>(_prog, "oglptgCoordDelta").TrySet(
				Vec3f(1.0f/params.width, 1.0f/params.height, 1.0f)
			);

			Optional<Uniform<Vec3f>>(_prog, "oglptgOutputSize").TrySet(
				Vec3f(params.width, params.height, 1.0f)
			);
		}

		unsigned xtile = _tile%_xdiv;
		unsigned ytile = _tile/_xdiv;

		GLint w = params.width/_xdiv;
		GLint h = params.height/_ydiv;

		oglplus::Context::Enable(Capability::ScissorTest);
		oglplus::Context::Scissor(xtile*w, ytile*h, w+1, h+1);
		oglplus::Context::DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
		oglplus::Context::Disable(Capability::ScissorTest);

		if(++_tile < _xdiv*_ydiv)
		{
			return false;
		}

		_tile = 0;
		_render_version = params.version;
	}
	return true;
}

OGLPLUS_LIB_FUNC
bool
RenderNode::
Render(void)
{
	auto vpe = oglplus::Context::Viewport();
	_render_params.width = vpe.Width();
	_render_params.height = vpe.Height();

	if(Render(_render_params))
	{
		++_render_params.version;
		return true;
	}
	return false;
}

} // namespace texgen
} // namespace oglplus

