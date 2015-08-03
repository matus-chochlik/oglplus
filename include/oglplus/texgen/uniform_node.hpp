/**
 *  @file oglplus/texgen/uniform_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_UNIFORM_NODE_HPP
#define OGLPLUS_TEXGEN_UNIFORM_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/sibling_input.hpp>
#include <oglplus/texgen/constant_output.hpp>
#include <oglplus/texgen/global_node.hpp>
#include <oglplus/uniform.hpp>

namespace oglplus {
namespace texgen {

class UniformNode;

class UniformOutputSlot
 : public BaseOutputSlot
{
private:
	friend class UniformNode;
	SlotDataType _type;
	ProgVarLoc<tag::Uniform> _location;
public:
	UniformOutputSlot(Node& parent, SlotDataType type);

	void BindLocation(void);

	ProgVarLoc<tag::Uniform> GetLocation(void) { return _location; }

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, unsigned version)
	OGLPLUS_OVERRIDE;
};

class UniformNode
 : public BaseNode
{
private:
	UniformOutputSlot _output;
public:
	UniformNode(SlotDataType type);

	UniformNode& BindUniform(void)
	{
		_output.BindLocation();
		return *this;
	}

	template <typename T>
	UniformNode& SetValue(T value)
	{
		Typechecked<Uniform<T>>(_output.GetLocation()).Set(value);
		return *this;
	}

	std::size_t OutputCount(void)
	OGLPLUS_OVERRIDE;

	OutputSlot& Output(std::size_t i)
	OGLPLUS_OVERRIDE;
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/uniform_node.ipp>
//#endif

#endif // include guard
