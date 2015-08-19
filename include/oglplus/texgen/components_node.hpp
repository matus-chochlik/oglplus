/**
 *  @file oglplus/texgen/components_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_COMPONENTS_NODE_HPP
#define OGLPLUS_TEXGEN_COMPONENTS_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/base_output.hpp>
#include <oglplus/texgen/global_node.hpp>
#include <oglplus/texgen/adaptive_output.hpp>

namespace oglplus {
namespace texgen {

class ComponentsOutputSlot
 : public BaseOutputSlot
{
public:
	FallbackInputSlot<AdaptiveConstantOutputSlot,true>& _input;
	unsigned _index;

	ComponentsOutputSlot(
		Node& parent,
		FallbackInputSlot<AdaptiveConstantOutputSlot,true>& input,
		unsigned index
	);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	const char* Name(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;
};

class ComponentsNode
 : public BaseNode
{
private:
	FallbackInputSlot<AdaptiveConstantOutputSlot,true> _input;

	ComponentsOutputSlot _output_x;
	ComponentsOutputSlot _output_y;
	ComponentsOutputSlot _output_z;
	ComponentsOutputSlot _output_w;
public:
	ComponentsNode(void);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

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
#include <oglplus/texgen/components_node.ipp>
//#endif

#endif // include guard
