/**
 *  @file oglplus/texgen/global_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_GLOBAL_NODE_HPP
#define OGLPLUS_TEXGEN_GLOBAL_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_output.hpp>

namespace oglplus {
namespace texgen {

class BaseGlobalOutputSlot
 : public BaseOutputSlot
{
public:
	BaseGlobalOutputSlot(Node& parent);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;
};

class GlobalCoordinateSlot
 : public BaseGlobalOutputSlot
{
public:
	GlobalCoordinateSlot(Node& parent);

	const char* Name(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, unsigned version)
	OGLPLUS_OVERRIDE;
};

class GlobalNode
 : public BaseNode
{
private:
	GlobalCoordinateSlot _coordinate;
public:
	GlobalNode(void);

	std::size_t OutputCount(void)
	OGLPLUS_OVERRIDE;

	OutputSlot& Output(std::size_t i)
	OGLPLUS_OVERRIDE;
};


} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/global_node.ipp>
//#endif

#endif // include guard
