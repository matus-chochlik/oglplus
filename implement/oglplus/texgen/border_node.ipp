/**
 *  @file oglplus/texgen/border_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/config/basic.hpp>
#include <oglplus/texgen/data_type.hpp>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
Border2DOutputSlot::
Border2DOutputSlot(Node& parent, const char* sl_func)
 : BaseOutputSlot(parent)
 , _input(parent, "Input", Vec4f(0))
 , _sl_func(sl_func)
{ }

OGLPLUS_LIB_FUNC
const char*
Border2DOutputSlot::
TypeName(void)
{
	return "Border2D";
}

OGLPLUS_LIB_FUNC
SlotDataType
Border2DOutputSlot::
ValueType(void)
{
	return _input.ValueType();
}

OGLPLUS_LIB_FUNC
std::ostream&
Border2DOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_input.Definitions(result, version);
	result << DataTypeName(ValueType()) << " ";
	AppendId(result);
	result << "(vec3 o)\n";
	result << "{\n";
	result << "	" << DataTypeName(ValueType()) << "\n";
	result << "	r = ";
	_input.Expression(result, version);
	result << "(o+vec3( 0, 0, 0));\n";
	result << "	r = " << _sl_func << "(r,";
	_input.Expression(result, version);
	result << "(o+vec3(-1, 0, 0)));\n";
	result << "	r = " << _sl_func << "(r,";
	_input.Expression(result, version);
	result << "(o+vec3( 1, 0, 0)));\n";
	result << "	r = " << _sl_func << "(r,";
	_input.Expression(result, version);
	result << "(o+vec3( 0,-1, 0)));\n";
	result << "	r = " << _sl_func << "(r,";
	_input.Expression(result, version);
	result << "(o+vec3( 0, 1, 0)));\n";
	result << "	r = " << _sl_func << "(r,";
	_input.Expression(result, version);
	result << "(o+vec3(-1,-1, 0)));\n";
	result << "	r = " << _sl_func << "(r,";
	_input.Expression(result, version);
	result << "(o+vec3(-1, 1, 0)));\n";
	result << "	r = " << _sl_func << "(r,";
	_input.Expression(result, version);
	result << "(o+vec3( 1,-1, 0)));\n";
	result << "	r = " << _sl_func << "(r,";
	_input.Expression(result, version);
	result << "(o+vec3( 1, 1, 0)));\n";
	result << "	return r;\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
Border2DNode::
Border2DNode(const char* sl_func)
 : _output(*this, sl_func)
{ }

OGLPLUS_LIB_FUNC
std::size_t
Border2DNode::
InputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
InputSlot&
Border2DNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	return _output._input;
}

OGLPLUS_LIB_FUNC
std::size_t
Border2DNode::
OutputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
OutputSlot&
Border2DNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	return _output;
}

OGLPLUS_LIB_FUNC
Grow2DNode::
Grow2DNode(void)
 : Border2DNode("max")
{ }

OGLPLUS_LIB_FUNC
Shrink2DNode::
Shrink2DNode(void)
 : Border2DNode("min")
{ }

} // namespace texgen
} // namespace oglplus

