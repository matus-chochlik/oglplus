/**
 *  @file oglplus/texgen/checker_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/config/basic.hpp>
#include <sstream>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
CheckerOutputSlot::
CheckerOutputSlot(Node& parent)
 : _coord(parent, "Coordinate")
 , _scale(parent, "Scale", Vec3f(8,8,8))
{ }

OGLPLUS_LIB_FUNC
const char*
CheckerOutputSlot::
TypeName(void)
{
	return "Checker";
}

OGLPLUS_LIB_FUNC
SlotDataType
CheckerOutputSlot::
ValueType(void)
{
	return SlotDataType::Float;
}

OGLPLUS_LIB_FUNC
std::ostream&
CheckerOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_coord.Definitions(result, version);
	_scale.Definitions(result, version);

	result << "float ";
	AppendId(result);
	result << "(vec3 o)\n";
	result << "{\n";
	result << "	vec3 c = ";
	_coord.Expression(result, version) << "(o);\n";
	result << "	c *= ";
	_scale.Expression(result, version) << "(o);\n";
	result << "	return float((int(c.x)%2+int(c.y)%2+int(c.z)%2)%2);\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
CheckerNode::
CheckerNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
CheckerNode&
CheckerNode::
SetScale(Vec3f scale)
{
	_output._scale.Fallback().SetValue(scale);
	return *this;
}

OGLPLUS_LIB_FUNC
std::size_t
CheckerNode::
InputCount(void)
{
	return 2;
}

OGLPLUS_LIB_FUNC
InputSlot&
CheckerNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._coord;
	return _output._scale;
}

OGLPLUS_LIB_FUNC
std::size_t
CheckerNode::
OutputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
OutputSlot&
CheckerNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	return _output;
}

} // namespace texgen
} // namespace oglplus

