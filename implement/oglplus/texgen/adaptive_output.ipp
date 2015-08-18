/**
 *  @file oglplus/texgen/adaptive_output.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/config/basic.hpp>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
bool
AdaptiveConstantOutputSlot::
CanProvideValueType(SlotDataType type)
{
	return BaseConstantOutputSlot::SupportsValueType(type);
}

OGLPLUS_LIB_FUNC
void
AdaptiveConstantOutputSlot::
RequireValueType(SlotDataType type)
{
	if(ValueType() != type)
	{
		Assign(BaseConstantOutputSlot::MakeNew(Parent(), type));
	}
}

} // namespace texgen
} // namespace oglplus

