/**
 *  @file oglplus/texgen/components_node.ipp
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
ComponentsOutputSlot::
ComponentsOutputSlot(
	Node& parent,
	FallbackInputSlot<AdaptiveConstantOutputSlot,true>& input,
	unsigned index
): BaseOutputSlot(parent)
 , _input(input)
 , _index(index)
{
	assert(index < 4);
}

OGLPLUS_LIB_FUNC
const char*
ComponentsOutputSlot::
TypeName(void)
{
	static const char* names[4] = {"X","Y","Z","W"};
	assert(_index < 4);
	return names[_index];
}

OGLPLUS_LIB_FUNC
const char*
ComponentsOutputSlot::
Name(void)
{
	return TypeName();
}

OGLPLUS_LIB_FUNC
SlotDataType
ComponentsOutputSlot::
ValueType(void)
{
	return ScalarDataType(_input.ValueType());
}

OGLPLUS_LIB_FUNC
std::ostream&
ComponentsOutputSlot::
Definitions(std::ostream& result, CompileContext& context)
{
	result << "#ifndef OGLPTG_CMPNTS_" << GetId() << "\n";
	result << "#define OGLPTG_CMPNTS_" << GetId() << "\n";
	_input.Definitions(result, context);
	result << "#endif\n";

	result << DataTypeName(ValueType()) << " ";
	AppendId(result);
	result << "(vec3 po, vec3 so)\n";
	result << "{\n";

	result << "	return ";
	_input.Expression(result, context) << "(po, so)[";
	result << _index << "];\n";
	result << "}\n";

	return result;
}

OGLPLUS_LIB_FUNC
ComponentsNode::
ComponentsNode(void)
 : _input(*this, "Input", Vec4f(0))
 , _output_x(*this, _input, 0)
 , _output_y(*this, _input, 1)
 , _output_z(*this, _input, 2)
 , _output_w(*this, _input, 3)
{ }

OGLPLUS_LIB_FUNC
const char*
ComponentsNode::
TypeName(void)
{
	return "Components";
}

OGLPLUS_LIB_FUNC
std::size_t
ComponentsNode::
InputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
InputSlot&
ComponentsNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	return _input;
}

OGLPLUS_LIB_FUNC
std::size_t
ComponentsNode::
OutputCount(void)
{
	return 4;
}

OGLPLUS_LIB_FUNC
OutputSlot&
ComponentsNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	if(i == 0) return _output_x;
	if(i == 1) return _output_y;
	if(i == 2) return _output_z;
	return _output_w;
}

} // namespace texgen
} // namespace oglplus

