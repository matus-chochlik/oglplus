/**
 *  @file oglplus/texgen/stripes_node.ipp
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
StripesOutputSlot::
StripesOutputSlot(Node& parent)
 : _coord(parent, "Coordinate")
 , _coeff(parent, "Coefficients", Vec3f(1,1,1))
 , _repeat(parent, "Repeat", Vec3f(8,8,8))
{ }

OGLPLUS_LIB_FUNC
const char*
StripesOutputSlot::
TypeName(void)
{
	return "Stripes";
}

OGLPLUS_LIB_FUNC
SlotDataType
StripesOutputSlot::
ValueType(void)
{
	return SlotDataType::Float;
}

OGLPLUS_LIB_FUNC
std::ostream&
StripesOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_coord.Definitions(result, version);
	_coeff.Definitions(result, version);
	_repeat.Definitions(result, version);

	result << "float ";
	AppendId(result);
	result << "(vec3 o)\n";
	result << "{\n";
	result << "	vec3 c = ";
	_coord.Expression(result, version) << "(o);\n";
	result << "	c *= ";
	_coeff.Expression(result, version) << "(o);\n";
	result << "	c *= ";
	_repeat.Expression(result, version) << "(o);\n";
	result << "	return float(int(abs(floor(c.x+c.y+c.z)))%2);\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
StripesNode::
StripesNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
StripesNode&
StripesNode::
SetCoeff(Vec3f coeff)
{
	_output._coeff.Fallback().SetValue(coeff);
	return *this;
}

OGLPLUS_LIB_FUNC
StripesNode&
StripesNode::
SetRepeat(Vec3f scale)
{
	_output._repeat.Fallback().SetValue(scale);
	return *this;
}

OGLPLUS_LIB_FUNC
std::size_t
StripesNode::
InputCount(void)
{
	return 3;
}

OGLPLUS_LIB_FUNC
InputSlot&
StripesNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._coord;
	if(i == 1) return _output._coeff;
	return _output._repeat;
}

OGLPLUS_LIB_FUNC
std::size_t
StripesNode::
OutputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
OutputSlot&
StripesNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	return _output;
}

} // namespace texgen
} // namespace oglplus

