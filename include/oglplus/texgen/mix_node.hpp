/**
 *  @file oglplus/texgen/mix_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_MIX_NODE_HPP
#define OGLPLUS_TEXGEN_MIX_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/sibling_input.hpp>
#include <oglplus/texgen/constant_output.hpp>

namespace oglplus {
namespace texgen {

class MixNode;

class MixOutputSlot
 : public BaseOutputSlot
{
private:
	friend class MixNode;

	SiblingInputSlot _zero;
	SiblingInputSlot _one;
	FallbackInputSlot<ConstantOutputSlot<GLfloat>> _value;
public:
	MixOutputSlot(Node& parent);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;
};

class MixNode
 : public SingleBaseOutputNode
{
private:
	MixOutputSlot _output;
public:
	MixNode(void);

	template <typename T>
	MixNode& SetZero(T v)
	{
		_output._zero.SetValue(v);
		return *this;
	}

	template <typename T>
	MixNode& SetOne(T v)
	{
		_output._one.SetValue(v);
		return *this;
	}

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	BaseOutputSlot& SingleOutput(void)
	OGLPLUS_OVERRIDE;

	void Validate(InputSlot&)
	OGLPLUS_OVERRIDE;
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/mix_node.ipp>
//#endif

#endif // include guard
