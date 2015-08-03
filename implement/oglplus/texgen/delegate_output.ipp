/**
 *  @file oglplus/texgen/delegate_output.ipp
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
DelegateOutputSlot::
DelegateOutputSlot(std::unique_ptr<OutputSlot>&& output)
 : _output(std::move(output))
{ }

OGLPLUS_LIB_FUNC
void
DelegateOutputSlot::
Assign(std::unique_ptr<OutputSlot>&& output)
{
	_output = std::move(output);
}

OGLPLUS_LIB_FUNC
OutputSlot&
DelegateOutputSlot::
Output(void)
{
	assert(bool(_output));
	return *_output;
}

OGLPLUS_LIB_FUNC
const char*
DelegateOutputSlot::
Name(void)
{
	return Output().Name();
}

OGLPLUS_LIB_FUNC
SlotDataType
DelegateOutputSlot::
ValueType(void)
{
	return Output().ValueType();
}

OGLPLUS_LIB_FUNC
std::ostream&
DelegateOutputSlot::
Definitions(std::ostream& result, unsigned glsl_version)
{
	return Output().Definitions(result, glsl_version);
}

OGLPLUS_LIB_FUNC
std::ostream&
DelegateOutputSlot::
Expression(std::ostream& result, unsigned glsl_version)
{
	return Output().Expression(result, glsl_version);
}

OGLPLUS_LIB_FUNC
bool
DelegateOutputSlot::
IsConnected(InputSlot& input)
{
	return Output().IsConnected(input);
}

OGLPLUS_LIB_FUNC
bool
DelegateOutputSlot::
Connect(InputSlot& input)
{
	return Output().Connect(input);
}

OGLPLUS_LIB_FUNC
void
DelegateOutputSlot::
Disconnect(InputSlot& input)
{
	Output().Disconnect(input);
}

OGLPLUS_LIB_FUNC
void
DelegateOutputSlot::
UpdateConnected(void)
{
	Output().UpdateConnected();
}

} // namespace texgen
} // namespace oglplus

