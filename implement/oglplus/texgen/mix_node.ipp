/**
 *  @file oglplus/texgen/mix_node.ipp
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
MixOutputSlot::
MixOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _zero(parent, "Zero", Vec4f(0.0f))
 , _one(parent, "One", Vec4f(1.0f))
 , _value(parent, "Value", 0.5f)
{
	_zero.AddSibling(_one);
	_one.AddSibling(_zero);
}

OGLPLUS_LIB_FUNC
const char*
MixOutputSlot::
TypeName(void)
{
	return "Mix";
}

OGLPLUS_LIB_FUNC
SlotDataType
MixOutputSlot::
ValueType(void)
{
	assert(_zero.ValueType() == _one.ValueType());
	return _one.ValueType();
}

OGLPLUS_LIB_FUNC
std::ostream&
MixOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_zero.Definitions(result, version);
	_one.Definitions(result, version);
	_value.Definitions(result, version);

	SlotDataType type = CommonDataType(_zero.ValueType(), _one.ValueType());

	result << DataTypeName(ValueType()) << " ";
	AppendId(result);
	result << "(vec3 po, vec3 so){\n\t";

	result << "return mix(\n\t\t";
	ConversionPrefix(result, _zero.ValueType(), type);
	_zero.Expression(result, version) << "(po, so)";
	ConversionSuffix(result, _zero.ValueType(), type);
	result << ",\n\t\t";
	ConversionPrefix(result, _one.ValueType(), type);
	_one.Expression(result, version) << "(po, so)";
	ConversionSuffix(result, _one.ValueType(), type);
	result << ",\n\t\t";

	if(
		(DataTypeDims(_value.ValueType()) == 1) ||
		(!DataTypeConvertible(_value.ValueType(), type))
	)
	{
		ConversionPrefix(result, _value.ValueType(), SlotDataType::Float);
		_value.Expression(result, version) << "(po, so)";
		ConversionSuffix(result, _value.ValueType(), SlotDataType::Float);
	}
	else
	{
		ConversionPrefix(result, _value.ValueType(), type);
		_value.Expression(result, version) << "(po, so)";
		ConversionSuffix(result, _value.ValueType(), type);
	}
	result << "\n\t);\n}\n";
	return result;
}

OGLPLUS_LIB_FUNC
MixNode::
MixNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
std::size_t
MixNode::
InputCount(void)
{
	return 3;
}

OGLPLUS_LIB_FUNC
InputSlot&
MixNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._zero;
	if(i == 1) return _output._one;
	return _output._value;
}

OGLPLUS_LIB_FUNC
BaseOutputSlot&
MixNode::
SingleOutput(void)
{
	return _output;
}

OGLPLUS_LIB_FUNC
void
MixNode::
Validate(InputSlot&)
{
	// TODO
}

} // namespace texgen
} // namespace oglplus

