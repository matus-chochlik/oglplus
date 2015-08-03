/**
 *  @file oglplus/texgen/blur_node.ipp
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
Blur2DOutputSlot::
Blur2DOutputSlot(Node& parent)
 : _input(parent, "Input", Vec4f(0))
{ }

OGLPLUS_LIB_FUNC
const char*
Blur2DOutputSlot::
TypeName(void)
{
	return "Blur2D";
}

OGLPLUS_LIB_FUNC
SlotDataType
Blur2DOutputSlot::
ValueType(void)
{
	return _input.ValueType();
}

OGLPLUS_LIB_FUNC
std::ostream&
Blur2DOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_input.Definitions(result, version);
	result << DataTypeName(ValueType()) << " ";
	AppendId(result);
	result << "(vec3 o)\n";
	result << "{\n";
	result << "	" << DataTypeName(ValueType()) << "\n";
	result << "	r  = ";
	_input.Expression(result, version);
	result << "(o+vec3( 0, 0, 0))*0.20;\n";
	result << "	r += ";
	_input.Expression(result, version);
	result << "(o+vec3(-1, 0, 0))*0.15;\n";
	result << "	r += ";
	_input.Expression(result, version);
	result << "(o+vec3( 1, 0, 0))*0.15;\n";
	result << "	r += ";
	_input.Expression(result, version);
	result << "(o+vec3( 0,-1, 0))*0.15;\n";
	result << "	r += ";
	_input.Expression(result, version);
	result << "(o+vec3( 0, 1, 0))*0.15;\n";
	result << "	r += ";
	_input.Expression(result, version);
	result << "(o+vec3(-1,-1, 0))*0.05;\n";
	result << "	r += ";
	_input.Expression(result, version);
	result << "(o+vec3(-1, 1, 0))*0.05;\n";
	result << "	r += ";
	_input.Expression(result, version);
	result << "(o+vec3( 1,-1, 0))*0.05;\n";
	result << "	r += ";
	_input.Expression(result, version);
	result << "(o+vec3( 1, 1, 0))*0.05;\n";
	result << "	return r;\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
Blur2DNode::
Blur2DNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
std::size_t
Blur2DNode::
InputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
InputSlot&
Blur2DNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	return _output._input;
}

OGLPLUS_LIB_FUNC
std::size_t
Blur2DNode::
OutputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
OutputSlot&
Blur2DNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	return _output;
}

} // namespace texgen
} // namespace oglplus

