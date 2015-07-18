/**
 *  @file oglplus/texgen/base_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_BASE_NODE_HPP
#define OGLPLUS_TEXGEN_BASE_NODE_HPP

#include <oglplus/texgen/interface.hpp>
#include <cassert>

namespace oglplus {
namespace texgen {

// BaseNode
class BaseNode
 : public Node
{
public:
	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t index)
	OGLPLUS_OVERRIDE;

	std::size_t OutputCount(void)
	OGLPLUS_OVERRIDE;

	OutputSlot& Output(std::size_t index)
	OGLPLUS_OVERRIDE;

	void Validate(InputSlot& input)
	OGLPLUS_OVERRIDE;

	void Update(void)
	OGLPLUS_OVERRIDE;
};

bool Connect(OutputSlot& output, InputSlot& input);
void Disconnect(OutputSlot& output, InputSlot& input);

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/base_node.ipp>
//#endif

#endif // include guard
