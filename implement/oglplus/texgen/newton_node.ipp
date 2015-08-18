/**
 *  @file oglplus/texgen/newton_node.ipp
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
NewtonOutputSlot::
NewtonOutputSlot(Node& parent, NewtonFunction function)
 : BaseOutputSlot(parent)
 , _coord(parent, "Coordinate")
 , _offset(parent, "Offset", Vec3f(-0.5f,-0.5f,0))
 , _scale(parent, "Scale", Vec3f(4,4,1))
 , _function(function)
{ }

OGLPLUS_LIB_FUNC
const char*
NewtonOutputSlot::
TypeName(void)
{
	return "Newton";
}

OGLPLUS_LIB_FUNC
SlotDataType
NewtonOutputSlot::
ValueType(void)
{
	return SlotDataType::Float;
}

OGLPLUS_LIB_FUNC
std::ostream&
NewtonOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_coord.Definitions(result, version);
	_offset.Definitions(result, version);
	_scale.Definitions(result, version);

	result << "#ifndef OGLPTG_COMPLEX_DIV\n";
	result << "#define OGLPTG_COMPLEX_DIV\n";
	result << "vec2 oglptgComplexDiv(vec2 a, vec2 b)\n";
	result << "{\n";
	result << "	float d = dot(b, b);\n";
	result << "	return (d == 0.0)?a:vec2(\n";
	result << "		(a.x*b.x + a.y*b.y) / d,\n";
	result << "		(a.y*b.x - a.x*b.y) / d\n";
	result << "	);\n";
	result << "}\n";
	result << "#endif\n";

	if(_function == NewtonFunction::Xe3minus1)
	{
		result << "#ifndef OGLPTG_NEWTON_XE3MINUS1\n";
		result << "#define OGLPTG_NEWTON_XE3MINUS1\n";
		result << "vec2 oglptgNewton_fXe3Minus1(vec2 n)\n";
		result << "{\n";
		result << "	return vec2(\n";
		result << "		n.x*n.x*n.x - 3.0*n.x*n.y*n.y - 1.0,\n";
		result << "		-n.y*n.y*n.y + 3.0*n.x*n.x*n.y\n";
		result << "	);\n";
		result << "}\n";

		result << "vec2 oglptgNewton_dfXe3Minus1(vec2 n)\n";
		result << "{\n";
		result << "	return 3.0 * vec2(\n";
		result << "		n.x*n.x - n.y*n.y,\n";
		result << "		2.0 * n.x * n.y\n";
		result << "	);\n";
		result << "}\n";
		result << "#endif\n";
	}
	else if(_function == NewtonFunction::Xe4minus1)
	{
		result << "#ifndef OGLPTG_NEWTON_XE4MINUS1\n";
		result << "#define OGLPTG_NEWTON_XE4MINUS1\n";
		result << "vec2 oglptgNewton_fXe4Minus1(vec2 n)\n";
		result << "{\n";
		result << "	return vec2(\n";
		result << "		n.x*n.x*n.x*n.x +\n";
		result << "		n.y*n.y*n.y*n.y -\n";
		result << "		6.0*n.x*n.x*n.y*n.y - 1.0,\n";
		result << "		4.0*n.x*n.x*n.x*n.y -\n";
		result << "		4.0*n.x*n.y*n.y*n.y\n";
		result << "	);\n";
		result << "}\n";

		result << "vec2 oglptgNewton_dfXe4Minus1(vec2 n)\n";
		result << "{\n";
		result << "	return 4.0 * vec2(\n";
		result << "		 n.x*n.x*n.x - 3.0*n.x*n.y*n.y,\n";
		result << "		-n.y*n.y*n.y + 3.0*n.x*n.x*n.y\n";
		result << "	);\n";
		result << "}\n";
		result << "#endif\n";
	}

	const SlotDataType v3 = SlotDataType::FloatVec3;

	result << "float ";
	AppendId(result);
	result << "(vec3 po, vec3 so)\n";
	result << "{\n";
	result << "	vec3 k = ";
	ConversionPrefix(result, _coord.ValueType(), v3);
	_coord.Expression(result, version) << "(po, so)";
	ConversionSuffix(result, _coord.ValueType(), v3,0,0,0,0) << ";\n";
	result << "	k += ";
	ConversionPrefix(result, _offset.ValueType(), v3);
	_offset.Expression(result, version) <<"(po, so)";
	ConversionSuffix(result, _offset.ValueType(), v3) << ";\n";
	result << "	k *= ";
	ConversionPrefix(result, _scale.ValueType(), v3);
	_scale.Expression(result, version) << "(po, so)";
	ConversionSuffix(result, _scale.ValueType(), v3) << ";\n";
	result << ";\n";
	result << "	vec2 z = k.xy;\n";

	result << "	int i, max = 48;\n";
	result << "	for(i = 0; i < max; ++i)\n";
	result << "	{\n";
	result << "		vec2 zn = z - oglptgComplexDiv(\n";
	result << "			";

	if(_function == NewtonFunction::Xe3minus1)
	{
		result << "oglptgNewton_fXe3Minus1";
	}
	else if(_function == NewtonFunction::Xe4minus1)
	{
		result << "oglptgNewton_fXe4Minus1";
	}

	result << "(z),\n";
	result << "			";

	if(_function == NewtonFunction::Xe3minus1)
	{
		result << "oglptgNewton_dfXe3Minus1";
	}
	else if(_function == NewtonFunction::Xe4minus1)
	{
		result << "oglptgNewton_dfXe4Minus1";
	}

	result << "(z)\n";
	result << "		);\n";
	result << "		if(distance(zn, z) < 0.00001) break;\n";
	result << "		z = zn;\n";
	result << "	}\n";
	result << "	return float(i)/float(max);\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
NewtonNode::
NewtonNode(NewtonFunction function)
 : _output(*this, function)
{ }

OGLPLUS_LIB_FUNC
std::size_t
NewtonNode::
InputCount(void)
{
	return 3;
}

OGLPLUS_LIB_FUNC
InputSlot&
NewtonNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._coord;
	if(i == 1) return _output._offset;
	return _output._scale;
}

OGLPLUS_LIB_FUNC
BaseOutputSlot&
NewtonNode::
SingleOutput(void)
{
	return _output;
}

} // namespace texgen
} // namespace oglplus

