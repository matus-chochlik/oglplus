/**
 *  @file oglplus/texgen/stripes_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_STRIPES_NODE_HPP
#define OGLPLUS_TEXGEN_STRIPES_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/sibling_input.hpp>
#include <oglplus/texgen/constant_output.hpp>
#include <oglplus/texgen/global_node.hpp>

namespace oglplus {
namespace texgen {

class StripesNode;

class StripesOutputSlot
 : public BaseOutputSlot
{
private:
	friend class StripesNode;

	FallbackInputSlot<GlobalCoordinateSlot,true> _coord;
	FallbackInputSlot<ConstantOutputSlot<Vec3f>> _coeff;
	FallbackInputSlot<ConstantOutputSlot<Vec3f>> _repeat;
public:
	StripesOutputSlot(Node& parent);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;
};

class StripesNode
 : public SingleBaseOutputNode
{
private:
	StripesOutputSlot _output;
public:
	StripesNode(void);

	StripesNode& SetCoeff(Vec3f coeff);
	StripesNode& SetRepeat(Vec3f scale);

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
#include <oglplus/texgen/stripes_node.ipp>
//#endif

#endif // include guard
