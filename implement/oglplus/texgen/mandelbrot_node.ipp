/**
 *  @file oglplus/texgen/mandelbrot_node.ipp
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
MandelbrotOutputSlot::
MandelbrotOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _coord(parent, "Coordinate")
 , _offset(parent, "Offset", Vec3f(-0.75f,-0.5f,0))
 , _scale(parent, "Scale", Vec3f(2,2,1))
{ }

OGLPLUS_LIB_FUNC
const char*
MandelbrotOutputSlot::
TypeName(void)
{
	return "Mandelbrot";
}

OGLPLUS_LIB_FUNC
SlotDataType
MandelbrotOutputSlot::
ValueType(void)
{
	return SlotDataType::FloatVec2;
}

OGLPLUS_LIB_FUNC
std::ostream&
MandelbrotOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_coord.Definitions(result, version);
	_offset.Definitions(result, version);
	_scale.Definitions(result, version);

	const SlotDataType v3 = SlotDataType::FloatVec3;

	result << "vec2 ";
	AppendId(result);
	result << "(vec3 o)\n";
	result << "{\n";
	result << "	vec2 z = vec2(0.0, 0.0);\n";
	result << "	vec3 k = ";
	ConversionPrefix(result, _coord.ValueType(), v3);
	_coord.Expression(result, version) << "(o)";
	ConversionSuffix(result, _coord.ValueType(), v3,0,0,0,0) << ";\n";
	result << "	k += ";
	ConversionPrefix(result, _offset.ValueType(), v3);
	_offset.Expression(result, version) <<"(o)";
	ConversionSuffix(result, _offset.ValueType(), v3) << ";\n";
	result << "	k *= ";
	ConversionPrefix(result, _scale.ValueType(), v3);
	_scale.Expression(result, version) << "(o)";
	ConversionSuffix(result, _scale.ValueType(), v3) << ";\n";
	result << "	vec2 c = k.xy;\n";
	result << "	int i = 0;\n";
	result << "	const int max = 128;\n"; // TODO variable max?
	result << "	while((i < max) && (distance(z, c) < 2.0))\n";
	result << "	{\n";
	result << "		z = vec2(\n";
	result << "			z.x * z.x - z.y * z.y + c.x,\n";
	result << "			2.0 * z.x * z.y + c.y\n";
	result << "		);\n";
	result << "		++i;\n";
	result << "	}\n";
	result << "	return vec2(\n";
	result << "		float(i)/float(max),\n";
	result << "		distance(z, c)*0.5\n";
	result << "	);\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
MandelbrotNode::
MandelbrotNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
std::size_t
MandelbrotNode::
InputCount(void)
{
	return 3;
}

OGLPLUS_LIB_FUNC
InputSlot&
MandelbrotNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._coord;
	if(i == 1) return _output._offset;
	return _output._scale;
}

OGLPLUS_LIB_FUNC
std::size_t
MandelbrotNode::
OutputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
OutputSlot&
MandelbrotNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	return _output;
}

} // namespace texgen
} // namespace oglplus

