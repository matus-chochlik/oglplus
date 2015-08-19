/**
 *  @file oglplus/texgen/posterize_node.ipp
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
PosterizeOutputSlot::
PosterizeOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _input(parent, "Input", Vec4f(0))
 , _levels(parent, "Levels", Vec4f(4))
{ }

OGLPLUS_LIB_FUNC
const char*
PosterizeOutputSlot::
TypeName(void)
{
	return "Posterize";
}

OGLPLUS_LIB_FUNC
SlotDataType
PosterizeOutputSlot::
ValueType(void)
{
	return _input.ValueType();
}

OGLPLUS_LIB_FUNC
std::ostream&
PosterizeOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_input.Definitions(result, version);
	_levels.Definitions(result, version);

	result << DataTypeName(ValueType()) << " ";
	AppendId(result);
	result << "(vec3 po, vec3 so)\n";
	result << "{\n";
	result << "	" << DataTypeName(ValueType()) << " lvls = ";
	ConversionPrefix(result, _levels.ValueType(), ValueType());
	_levels.Expression(result, version) <<"(po, so)";
	ConversionSuffix(result, _levels.ValueType(), ValueType(),4,4,4,4) << ";\n";
	result << "	lvls = max(lvls, ";
	result << DataTypeName(ValueType()) << "(1));\n";
	result << "	return floor(";
	_input.Expression(result, version);
	result << "(po, so)*lvls)/lvls;\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
PosterizeNode::
PosterizeNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
PosterizeNode&
PosterizeNode::
SetLevels(Vec4f levels)
{
	_output._levels.Fallback().SetValue(levels);
	return *this;
}

OGLPLUS_LIB_FUNC
std::size_t
PosterizeNode::
InputCount(void)
{
	return 2;
}

OGLPLUS_LIB_FUNC
InputSlot&
PosterizeNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._input;
	return _output._levels;
}

OGLPLUS_LIB_FUNC
BaseOutputSlot&
PosterizeNode::
SingleOutput(void)
{
	return _output;
}

} // namespace texgen
} // namespace oglplus

