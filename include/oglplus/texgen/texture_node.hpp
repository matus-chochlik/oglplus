/**
 *  @file oglplus/texgen/texture_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_TEXTURE_NODE_HPP
#define OGLPLUS_TEXGEN_TEXTURE_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/base_output.hpp>
#include <oglplus/texgen/global_node.hpp>
#include <oglplus/texture.hpp>

namespace oglplus {
namespace texgen {

class TextureNode;

class TextureOutputSlot
 : public BaseOutputSlot
{
private:
	friend class TextureNode;

	FallbackInputSlot<GlobalCoordinateSlot, true> _coord;

	Texture _texture;
	TextureTarget _target;
	PixelDataFormat _format;
public:
	TextureOutputSlot(
		Node& parent,
		Texture&&,
		TextureTarget,
		PixelDataFormat
	);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, unsigned version)
	OGLPLUS_OVERRIDE;
};

class TextureNode
 : public BaseNode
{
private:
	TextureOutputSlot _output;
public:
	TextureNode(Texture&&, TextureTarget, PixelDataFormat);

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	std::size_t OutputCount(void)
	OGLPLUS_OVERRIDE;

	OutputSlot& Output(std::size_t i)
	OGLPLUS_OVERRIDE;
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/texture_node.ipp>
//#endif

#endif // include guard
