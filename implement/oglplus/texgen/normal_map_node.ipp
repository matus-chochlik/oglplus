/**
 *  @file oglplus/texgen/normal_map_node.ipp
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
NormalMapOutputSlot::
NormalMapOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _input(parent, "Height", 0.0f)
{ }

OGLPLUS_LIB_FUNC
const char*
NormalMapOutputSlot::
TypeName(void)
{
	return "NormalMap";
}

OGLPLUS_LIB_FUNC
SlotDataType
NormalMapOutputSlot::
ValueType(void)
{
	return SlotDataType::FloatVec4;
}

OGLPLUS_LIB_FUNC
std::ostream&
NormalMapOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	const SlotDataType ft = SlotDataType::Float;

	_input.Definitions(result, version);
	result << "vec4 ";
	AppendId(result);
	result << "(vec3 o)\n";
	result << "{\n";
	result << "	float se = 0.05;\n"; // TODO variable strength
	result << "	float ce = ";
	ConversionPrefix(result, _input.ValueType(), ft);
 	_input.Expression(result, version) << "(o+vec3( 0, 0, 0))";
	ConversionSuffix(result, _input.ValueType(), ft) << ";\n";
	result << "	float px = ";
	ConversionPrefix(result, _input.ValueType(), ft);
	_input.Expression(result, version) << "(o+vec3(+1, 0, 0))";
	ConversionSuffix(result, _input.ValueType(), ft) << ";\n";
	result << "	float py = ";
	ConversionPrefix(result, _input.ValueType(), ft);
	_input.Expression(result, version) << "(o+vec3( 0,+1, 0))";
	ConversionSuffix(result, _input.ValueType(), ft) << ";\n";
	result << "	float nx = ";
	ConversionPrefix(result, _input.ValueType(), ft);
	_input.Expression(result, version) << "(o+vec3(-1, 0, 0))";
	ConversionSuffix(result, _input.ValueType(), ft) << ";\n";
	result << "	float ny = ";
	ConversionPrefix(result, _input.ValueType(), ft);
	_input.Expression(result, version) << "(o+vec3( 0,-1, 0))";
	ConversionSuffix(result, _input.ValueType(), ft) << ";\n";
	result << "	vec3 vpx = vec3(+se,  0, px-ce);\n";
	result << "	vec3 vpy = vec3(  0,+se, py-ce);\n";
	result << "	vec3 vnx = vec3(-se,  0, nx-ce);\n";
	result << "	vec3 vny = vec3(  0,-se, ny-ce);\n";
	result << "	return vec4(\n";
	result << "		normalize(\n";
	result << "			cross(vpx, vpy)+\n";
	result << "			cross(vpy, vnx)+\n";
	result << "			cross(vnx, vny)+\n";
	result << "			cross(vny, vpx)\n";
	result << "		), ce\n";
	result << "	);\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
NormalMapNode::
NormalMapNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
std::size_t
NormalMapNode::
InputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
InputSlot&
NormalMapNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	return _output._input;
}

OGLPLUS_LIB_FUNC
std::size_t
NormalMapNode::
OutputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
OutputSlot&
NormalMapNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	return _output;
}

} // namespace texgen
} // namespace oglplus

