/**
 *  @file oglplus/texgen/base_output.ipp
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
BaseOutputSlot::
~BaseOutputSlot(void)
OGLPLUS_NOEXCEPT(true)
{
	for(InputSlot* slot : _slots)
	{
		assert(slot);
		slot->Disconnect(*this);
	}
}

OGLPLUS_LIB_FUNC
const char*
BaseOutputSlot::
Name(void)
{
	return "Output";
}

OGLPLUS_LIB_FUNC
std::ostream&
BaseOutputSlot::
Definitions(std::ostream& result, unsigned)
{
	return result;
}

OGLPLUS_LIB_FUNC
bool
BaseOutputSlot::
IsConnected(InputSlot& slot)
{
	return _slots.find(&slot) != _slots.end();
}

OGLPLUS_LIB_FUNC
bool
BaseOutputSlot::
Connect(InputSlot& slot)
{
	if(slot.AcceptsValueType(ValueType()))
	{
		assert(!IsConnected(slot));
		_slots.insert(&slot);
		return true;
	}
	return false;
}

OGLPLUS_LIB_FUNC
void
BaseOutputSlot::
Disconnect(InputSlot& slot)
{
	assert(IsConnected(slot));
	_slots.erase(&slot);
}

OGLPLUS_LIB_FUNC
void
BaseOutputSlot::
UpdateConnected(void)
{
	for(InputSlot* slot : _slots)
	{
		assert(slot);
		slot->Update();
	}
}

OGLPLUS_LIB_FUNC
void
BaseOutputSlot::
AppendId(std::ostream& out, const char* name)
{
	out << "oglptg" << name << reinterpret_cast<std::intptr_t>(this);
}

OGLPLUS_LIB_FUNC
void
BaseOutputSlot::
AppendId(std::ostream& out)
{
	AppendId(out, TypeName());
}

OGLPLUS_LIB_FUNC
std::ostream&
BaseOutputSlot::
Expression(std::ostream& result, unsigned)
{
	AppendId(result);
	return result;
}

} // namespace texgen
} // namespace oglplus

