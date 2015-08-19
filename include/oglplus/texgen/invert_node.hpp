/**
 *  @file oglplus/texgen/invert_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_INVERT_NODE_HPP
#define OGLPLUS_TEXGEN_INVERT_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/adaptive_output.hpp>

namespace oglplus {
namespace texgen {

class InvertNode;

class InvertOutputSlot
 : public BaseOutputSlot
{
private:
	friend class InvertNode;

	FallbackInputSlot<AdaptiveConstantOutputSlot,true> _input;
public:
	InvertOutputSlot(Node& parent);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;
};

class InvertNode
 : public SingleBaseOutputNode
{
private:
	InvertOutputSlot _output;
public:
	InvertNode(void);

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	BaseOutputSlot& SingleOutput(void)
	OGLPLUS_OVERRIDE;
};


} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/invert_node.ipp>
//#endif

#endif // include guard
