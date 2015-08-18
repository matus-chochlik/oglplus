/**
 *  @file oglplus/texgen/invert_node.ipp
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
InvertOutputSlot::
InvertOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _input(parent, "Input", Vec4f(0))
{ }

OGLPLUS_LIB_FUNC
const char*
InvertOutputSlot::
TypeName(void)
{
	return "Invert";
}

OGLPLUS_LIB_FUNC
SlotDataType
InvertOutputSlot::
ValueType(void)
{
	return _input.ValueType();
}

OGLPLUS_LIB_FUNC
std::ostream&
InvertOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_input.Definitions(result, version);

	result << DataTypeName(ValueType()) << " ";
	AppendId(result);
	result << "(vec3 po, vec3 so)\n";
	result << "{\n";
	result << "	return ";
	result << DataTypeName(ValueType()) << "(1)-";
	_input.Expression(result, version) << "(po, so);\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
InvertNode::
InvertNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
std::size_t
InvertNode::
InputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
InputSlot&
InvertNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	return _output._input;
}

OGLPLUS_LIB_FUNC
BaseOutputSlot&
InvertNode::
SingleOutput(void)
{
	return _output;
}

} // namespace texgen
} // namespace oglplus

