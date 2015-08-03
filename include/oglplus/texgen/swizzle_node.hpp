/**
 *  @file oglplus/texgen/swizzle_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_UNARY_NODE_HPP
#define OGLPLUS_TEXGEN_UNARY_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/adaptive_output.hpp>

namespace oglplus {
namespace texgen {

class SwizzleNode;

class SwizzleOutputSlot
 : public BaseOutputSlot
{
private:
	friend class SwizzleNode;

	FallbackInputSlot<AdaptiveConstantOutputSlot> _input;

	String _swizzle;
public:
	SwizzleOutputSlot(Node& parent, String swizzle);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, unsigned version)
	OGLPLUS_OVERRIDE;
};

class SwizzleNode
 : public BaseNode
{
private:
	SwizzleOutputSlot _output;
public:
	SwizzleNode(String swizzle);

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
#include <oglplus/texgen/swizzle_node.ipp>
//#endif

#endif // include guard
