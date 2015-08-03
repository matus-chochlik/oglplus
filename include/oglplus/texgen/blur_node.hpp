/**
 *  @file oglplus/texgen/blur_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_BLUR_NODE_HPP
#define OGLPLUS_TEXGEN_BLUR_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/adaptive_output.hpp>

namespace oglplus {
namespace texgen {

class Blur2DNode;

class Blur2DOutputSlot
 : public BaseOutputSlot
{
private:
	friend class Blur2DNode;

	FallbackInputSlot<AdaptiveConstantOutputSlot> _input;
public:
	Blur2DOutputSlot(Node& parent);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, unsigned version)
	OGLPLUS_OVERRIDE;
};

class Blur2DNode
 : public BaseNode
{
private:
	Blur2DOutputSlot _output;
public:
	Blur2DNode(void);

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
#include <oglplus/texgen/blur_node.ipp>
//#endif

#endif // include guard
