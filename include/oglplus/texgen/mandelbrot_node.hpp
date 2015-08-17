/**
 *  @file oglplus/texgen/mandelbrot_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_MANDELBROT_NODE_HPP
#define OGLPLUS_TEXGEN_MANDELBROT_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/sibling_input.hpp>
#include <oglplus/texgen/constant_output.hpp>
#include <oglplus/texgen/global_node.hpp>

namespace oglplus {
namespace texgen {

class MandelbrotNode;

class MandelbrotOutputSlot
 : public BaseOutputSlot
{
private:
	friend class MandelbrotNode;

	FallbackInputSlot<GlobalCoordinateSlot,true> _coord;
	FallbackInputSlot<ConstantOutputSlot<Vec3f>> _offset;
	FallbackInputSlot<ConstantOutputSlot<Vec3f>> _scale;
public:
	MandelbrotOutputSlot(Node& parent);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, unsigned version)
	OGLPLUS_OVERRIDE;
};

class MandelbrotNode
 : public SingleBaseOutputNode
{
private:
	MandelbrotOutputSlot _output;
public:
	MandelbrotNode(void);

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
#include <oglplus/texgen/mandelbrot_node.ipp>
//#endif

#endif // include guard
