/**
 *  @file oglplus/texgen/adaptive_output.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_ADAPTIVE_OUTPUT_HPP
#define OGLPLUS_TEXGEN_ADAPTIVE_OUTPUT_HPP

#include <oglplus/texgen/delegate_output.hpp>
#include <oglplus/texgen/constant_output.hpp>

namespace oglplus {
namespace texgen {

class AdaptiveConstantOutputSlot
 : public DelegateOutputSlot
{
public:
	template <typename T>
	AdaptiveConstantOutputSlot(T v)
	 : DelegateOutputSlot(
		std::unique_ptr<OutputSlot>(new ConstantOutputSlot<T>(v))
	)
	{ }

	template <typename T>
	void SetValue(T v)
	{
		DelegateOutputSlot::Assign(
			std::unique_ptr<OutputSlot>(new ConstantOutputSlot<T>(v))
		);
	}

	bool CanProvideValueType(SlotDataType type);

	void RequireValueType(SlotDataType type);
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/adaptive_output.ipp>
//#endif

#endif // include guard
