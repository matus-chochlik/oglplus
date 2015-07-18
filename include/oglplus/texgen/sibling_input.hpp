/**
 *  @file oglplus/texgen/sibling_input.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_SIBLING_INPUT_HPP
#define OGLPLUS_TEXGEN_SIBLING_INPUT_HPP

#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/adaptive_output.hpp>
#include <set>

namespace oglplus {
namespace texgen {

class SiblingInputSlot
 : public FallbackInputSlot<AdaptiveConstantOutputSlot>
{
private:
	typedef FallbackInputSlot<AdaptiveConstantOutputSlot> Base_;

	std::set<SiblingInputSlot*> _siblings;

	bool DoesAcceptValueType(SlotDataType type);
public:
	template <typename T>
	SiblingInputSlot(Node& parent, const char* name, T v)
	 : Base_(parent, name, v)
	{ }

	template <typename T>
	void SetValue(T v)
	{
		Fallback().SetValue(v);
	}

	void AddSibling(SiblingInputSlot& sibling);

	bool AcceptsValueType(SlotDataType type)
	OGLPLUS_OVERRIDE;

	bool Connect(OutputSlot& output)
	OGLPLUS_OVERRIDE;
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/sibling_input.ipp>
//#endif

#endif // include guard
