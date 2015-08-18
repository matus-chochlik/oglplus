/**
 *  @file oglplus/texgen/offset_node.ipp
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
OffsetOutputSlot::
OffsetOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _input(parent, "Input", Vec4f(0))
 , _offset(parent, "Offset", Vec3f(0))
{ }

OGLPLUS_LIB_FUNC
const char*
OffsetOutputSlot::
TypeName(void)
{
	return "Offset";
}

OGLPLUS_LIB_FUNC
SlotDataType
OffsetOutputSlot::
ValueType(void)
{
	return _input.ValueType();
}

OGLPLUS_LIB_FUNC
std::ostream&
OffsetOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_input.Definitions(result, version);
	_offset.Definitions(result, version);

	const SlotDataType v3 = SlotDataType::FloatVec3;

	result << DataTypeName(ValueType()) << " ";
	AppendId(result);
	result << "(vec3 po, vec3 so)\n";
	result << "{\n";
	result << "	return ";
	_input.Expression(result, version);
	result << "(po+";
	ConversionPrefix(result, _offset.ValueType(), v3);
	_offset.Expression(result, version) <<"(po, so)";
	ConversionSuffix(result, _offset.ValueType(), v3,0,0,0,0);
	result << ");\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
OffsetNode::
OffsetNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
OffsetNode&
OffsetNode::
SetOffset(Vec3f offset)
{
	_output._offset.Fallback().SetValue(offset);
	return *this;
}

OGLPLUS_LIB_FUNC
std::size_t
OffsetNode::
InputCount(void)
{
	return 2;
}

OGLPLUS_LIB_FUNC
InputSlot&
OffsetNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._input;
	return _output._offset;
}

OGLPLUS_LIB_FUNC
BaseOutputSlot&
OffsetNode::
SingleOutput(void)
{
	return _output;
}

} // namespace texgen
} // namespace oglplus

