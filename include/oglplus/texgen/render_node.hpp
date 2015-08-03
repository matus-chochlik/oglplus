/**
 *  @file oglplus/texgen/render_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_RENDER_NODE_HPP
#define OGLPLUS_TEXGEN_RENDER_NODE_HPP

#include <oglplus/shader.hpp>
#include <oglplus/program.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/vertex_array.hpp>
#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/constant_output.hpp>

namespace oglplus {
namespace texgen {

class RenderNode
 : public BaseNode
{
private:
	VertexShader _vs;
	FragmentShader _fs;
	Program _prog;

	void _init_prog(void);
	void _update_prog(void);

	Buffer _position, _coordinate;
	VertexArray _vao;

	void _init_vao(void);

	FallbackInputSlot<ConstantOutputSlot<Vec4f>> _input;
public:
	RenderNode(void);

	RenderNode& Activate(void);
	RenderNode& Deactivate(void);

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t)
	OGLPLUS_OVERRIDE;

	void Render(void);

	void Validate(InputSlot& input)
	OGLPLUS_OVERRIDE;

	void Update(void)
	OGLPLUS_OVERRIDE;
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/render_node.ipp>
//#endif

#endif // include guard
