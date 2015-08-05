/**
 *  @file oglplus/texgen/swizzle_node.ipp
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
SwizzleOutputSlot::
SwizzleOutputSlot(Node& parent, String swizzle)
 : _input(parent, "Input", Vec4f(0))
 , _swizzle(swizzle)
{
	assert(_swizzle.length() >= 1);
	assert(_swizzle.length() <= 4);
}

OGLPLUS_LIB_FUNC
const char*
SwizzleOutputSlot::
TypeName(void)
{
	return "Swizzle";
}

OGLPLUS_LIB_FUNC
SlotDataType
SwizzleOutputSlot::
ValueType(void)
{
	short n = _swizzle.length();

	if(n == 4) return SlotDataType::FloatVec4;
	if(n == 3) return SlotDataType::FloatVec3;
	if(n == 2) return SlotDataType::FloatVec2;
	if(n == 1) return SlotDataType::Float;

	return _input.ValueType();
}

OGLPLUS_LIB_FUNC
std::ostream&
SwizzleOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_input.Definitions(result, version);

	result << DataTypeName(ValueType()) << " ";
	AppendId(result);
	result << "(vec3 o)\n";
	result << "{\n";
	result << "	return ";
	_input.Expression(result, version);
	result << "(o)." << _swizzle << ";\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
SwizzleNode::
SwizzleNode(String swizzle)
 : _output(*this, swizzle)
{ }

OGLPLUS_LIB_FUNC
std::size_t
SwizzleNode::
InputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
InputSlot&
SwizzleNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	return _output._input;
}

OGLPLUS_LIB_FUNC
std::size_t
SwizzleNode::
OutputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
OutputSlot&
SwizzleNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	return _output;
}

} // namespace texgen
} // namespace oglplus

