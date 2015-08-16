/**
 *  @file oglplus/texgen/base_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/config/basic.hpp>
#include <oglplus/assert.hpp>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
BaseNode::
BaseNode(void)
 : _render_input(0)
{ }

OGLPLUS_LIB_FUNC
std::size_t
BaseNode::
InputCount(void)
{
	return 0;
}

OGLPLUS_LIB_FUNC
InputSlot&
BaseNode::
Input(std::size_t)
{
	OGLPLUS_ABORT("Node does not have any inputs!");
	InputSlot* dummy = nullptr;
	assert(dummy != nullptr);
	return *dummy;
}

OGLPLUS_LIB_FUNC
std::size_t
BaseNode::
OutputCount(void)
{
	return 0;
}

OGLPLUS_LIB_FUNC
OutputSlot&
BaseNode::
Output(std::size_t)
{
	OGLPLUS_ABORT("Node does not have any outputs!");
	OutputSlot* dummy = nullptr;
	assert(dummy != nullptr);
	return *dummy;
}

OGLPLUS_LIB_FUNC
void
BaseNode::
Validate(InputSlot&)
{
	// TODO?
}

OGLPLUS_LIB_FUNC
void
BaseNode::
Update(void)
{
	for(std::size_t i=0,n=OutputCount(); i<n; ++i)
	{
		Output(i).UpdateConnected();
	}
}

OGLPLUS_LIB_FUNC
bool
BaseNode::
Render(const RenderParams& params)
{
	if(InputCount() > 0)
	{
		next:
		{
			if(_render_input >= InputCount())
			{
				_render_input = 0;
				return true;
			}

			if(Input(_render_input).Render(params))
			{
				++_render_input;
				goto next;
			}
		}

		return false;
	}
	return true;
}

OGLPLUS_LIB_FUNC
bool
Connect(OutputSlot& output, InputSlot& input)
{
	return
		input.Connect(output)&&
		output.Connect(input);
}

OGLPLUS_LIB_FUNC
void
Disconnect(OutputSlot& output, InputSlot& input)
{
	input.Disconnect(output);
	output.Disconnect(input);
}

} // namespace texgen
} // namespace oglplus

