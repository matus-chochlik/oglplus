/**
 *  @file oglplus/texgen/worley_node.ipp
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
Worley2DOutputSlot::
Worley2DOutputSlot(Node& parent, unsigned order)
 : BaseOutputSlot(parent)
 , _cell_offs(parent, "CellOffset", Vec2f(0.5,0.5))
 , _coord(parent)
 , _order(order)
{
	assert(order > 0);
}

OGLPLUS_LIB_FUNC
const char*
Worley2DOutputSlot::
TypeName(void)
{
	return "Worley2D";
}

OGLPLUS_LIB_FUNC
SlotDataType
Worley2DOutputSlot::
ValueType(void)
{
	return SlotDataType::FloatVec4;
}

OGLPLUS_LIB_FUNC
std::ostream&
Worley2DOutputSlot::
Definitions(std::ostream& result, CompileContext& context)
{
	_cell_offs.Definitions(result, context);

	const SlotDataType v2 = SlotDataType::FloatVec2;
	const SlotDataType v3 = SlotDataType::FloatVec3;

	result << "vec4 ";
	AppendId(result);
	result << "(vec3 po, vec3 so)\n";
	result << "{\n";

	result << "	vec3 tc = ";
	ConversionPrefix(result, _coord._coord.ValueType(), v3);
	_coord._coord.Expression(result, context) << "(po, so)";
	ConversionSuffix(result, _coord._coord.ValueType(), v3,0,0,0,0) << ";\n";

	result << "	vec2 nc = ";
	ConversionPrefix(result, _coord._cells.ValueType(), v2);
	_coord._cells.Expression(result, context) << "(po, so)";
	ConversionSuffix(result, _coord._cells.ValueType(), v2,1,1,1,1) << ";\n";

	result << "	vec2 inc = vec2(1)/nc;\n";

	result << "	const vec2 of[9] = vec2[9](\n";
	result << "		vec2(-1,-1),\n";
	result << "		vec2(-1, 0),\n";
	result << "		vec2(-1, 1),\n";
	result << "		vec2( 0,-1),\n";
	result << "		vec2( 0, 0),\n";
	result << "		vec2( 0, 1),\n";
	result << "		vec2( 1,-1),\n";
	result << "		vec2( 1, 0),\n";
	result << "		vec2( 1, 1)\n";
	result << "	);\n";

	result << "	float md[" << _order << "] = float[" << _order << "](";
	for(unsigned i=1; i<_order; ++i)
	{
		result << "2.0,";
	}
	result << "2.0);\n";

	result << "	int mc[" << _order << "] = int[" << _order << "](";
	for(unsigned i=1; i<_order; ++i)
	{
		result << "4,";
	}
	result << "4);\n";

	result << "	for(int c=0; c<9; ++c)\n";
	result << "	{\n";
	result << "		vec2 cc = floor(tc.xy*nc+so.xy+of[c])*inc;\n";
	result << "		vec2 co = ";
	ConversionPrefix(result, _cell_offs.ValueType(), v2);
	_cell_offs.Expression(result, context) << "(po, so+vec3(of[c],0))";
	ConversionSuffix(result, _cell_offs.ValueType(), v2,0.5,0.5,0,0) << ";\n";

	result << "		float d = distance(tc.xy, cc+co*inc);\n";
	result << "		for(int i=0; i<" << _order << "; ++i)\n";
	result << "		{\n";
	result << "			if(md[i] > d)\n";
	result << "			{\n";
	result << "				for(int j="<<_order-1<<"; j>i; --j)\n";
	result << "				{\n";
	result << "					md[j] = md[j-1];\n";
	result << "					mc[j] = mc[j-1];\n";
	result << "				}\n";
	result << "				md[i] = d;\n";
	result << "				mc[i] = c;\n";
	result << "				break;\n";
	result << "			}\n";
	result << "		}\n";
	result << "	}\n";

	result << "	vec2 cc = floor(tc.xy*nc+so.xy+of[mc["<<_order-1<<"]])*inc;\n";

	result << "	return vec4(cc, 0, md["<<_order-1<<"]*min(nc.x,nc.y)/sqrt(2.0));\n";
	result << "}\n";

	return result;
}

OGLPLUS_LIB_FUNC
Worley2DNode::
Worley2DNode(unsigned order)
 : _output(*this, order)
{ }

OGLPLUS_LIB_FUNC
Worley2DNode&
Worley2DNode::
SetCellCount(const Vec2f& cc)
{
	_output._coord._cells.Fallback().SetValue(cc);
	return *this;
}

OGLPLUS_LIB_FUNC
const char*
Worley2DNode::
TypeName(void)
{
	return _output.TypeName();
}

OGLPLUS_LIB_FUNC
std::size_t
Worley2DNode::
InputCount(void)
{
	return 2;
}

OGLPLUS_LIB_FUNC
InputSlot&
Worley2DNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._cell_offs;
	return _output._coord._coord;
}

OGLPLUS_LIB_FUNC
std::size_t
Worley2DNode::
OutputCount(void)
{
	return 2;
}

OGLPLUS_LIB_FUNC
OutputSlot&
Worley2DNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	if(i == 0) return _output;
	return _output._coord;
}

} // namespace texgen
} // namespace oglplus

