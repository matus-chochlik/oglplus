/**
 *  @file oglplus/texgen/border_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_BORDER_NODE_HPP
#define OGLPLUS_TEXGEN_BORDER_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/adaptive_output.hpp>

namespace oglplus {
namespace texgen {

class Border2DNode;

class Border2DOutputSlot
 : public BaseOutputSlot
{
private:
	friend class Border2DNode;

	FallbackInputSlot<AdaptiveConstantOutputSlot,true> _input;

	const char* _sl_func;
public:
	Border2DOutputSlot(Node& parent, const char* sl_func);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, unsigned version)
	OGLPLUS_OVERRIDE;
};

class Border2DNode
 : public BaseNode
{
private:
	Border2DOutputSlot _output;
protected:
	Border2DNode(const char* sl_func);
public:

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	std::size_t OutputCount(void)
	OGLPLUS_OVERRIDE;

	OutputSlot& Output(std::size_t i)
	OGLPLUS_OVERRIDE;
};

class Grow2DNode
 : public Border2DNode
{
public:
	Grow2DNode(void);
};

class Shrink2DNode
 : public Border2DNode
{
public:
	Shrink2DNode(void);
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/border_node.ipp>
//#endif

#endif // include guard
