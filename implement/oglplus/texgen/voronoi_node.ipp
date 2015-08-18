/**
 *  @file oglplus/texgen/voronoi_node.ipp
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
Voronoi2DOutputSlot::
CoordSlot::
CoordSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _coord(parent, "Coordinate")
 , _cells(parent, "CellCount", Vec2f(16,16))
 , _version(0)
{ }

OGLPLUS_LIB_FUNC
const char*
Voronoi2DOutputSlot::
CoordSlot::
Name(void)
{
	return "Coordinate";
}

OGLPLUS_LIB_FUNC
const char*
Voronoi2DOutputSlot::
CoordSlot::
TypeName(void)
{
	return "Vrni2DCoord";
}

OGLPLUS_LIB_FUNC
SlotDataType
Voronoi2DOutputSlot::
CoordSlot::
ValueType(void)
{
	return SlotDataType::FloatVec3;
}

OGLPLUS_LIB_FUNC
std::ostream&
Voronoi2DOutputSlot::
CoordSlot::
Definitions(std::ostream& result, unsigned version)
{
	_coord.Definitions(result, version);
	_cells.Definitions(result, version);

	const SlotDataType v2 = SlotDataType::FloatVec2;
	const SlotDataType v3 = SlotDataType::FloatVec3;

	result << "vec3 ";
	AppendId(result);
	result << "(vec3 o)\n";
	result << "{\n";
	result << "	vec3 tc = ";
	ConversionPrefix(result, _coord.ValueType(), v3);
	_coord.Expression(result, version) << "(o)";
	ConversionSuffix(result, _coord.ValueType(), v3,0,0,0,0) << ";\n";

	result << "	vec2 cc = ";
	ConversionPrefix(result, _cells.ValueType(), v2);
	_cells.Expression(result, version) << "(o)";
	ConversionSuffix(result, _cells.ValueType(), v2,1,1,1,1) << ";\n";

	result << "	return vec3(floor(tc.xy*cc)/cc,tc.z);\n";

	result << "}\n";

	return result;
}

OGLPLUS_LIB_FUNC
bool
Voronoi2DOutputSlot::
CoordSlot::
Render(const RenderParams& params)
{
	if(_version < params.version)
	{
		_version = params.version;
		return BaseOutputSlot::Render(params);
	}
	return true;
}

OGLPLUS_LIB_FUNC
Voronoi2DOutputSlot::
Voronoi2DOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _cell_offs(parent, "CellOffset", Vec2f(0.5,0.5))
 , _coord(parent)
{ }

OGLPLUS_LIB_FUNC
const char*
Voronoi2DOutputSlot::
TypeName(void)
{
	return "Voronoi2D";
}

OGLPLUS_LIB_FUNC
SlotDataType
Voronoi2DOutputSlot::
ValueType(void)
{
	return SlotDataType::FloatVec2;
}

OGLPLUS_LIB_FUNC
std::ostream&
Voronoi2DOutputSlot::
Definitions(std::ostream& result, unsigned version)
{
	_cell_offs.Definitions(result, version);

	const SlotDataType v2 = SlotDataType::FloatVec2;

	result << "vec2 ";
	AppendId(result);
	result << "(vec3 o)\n";
	result << "{\n";

	result << "	vec2 co = ";
	ConversionPrefix(result, _cell_offs.ValueType(), v2);
	_cell_offs.Expression(result, version) << "(o)";
	ConversionSuffix(result, _cell_offs.ValueType(), v2,0.5,0.5,0,0) << ";\n";
	result << "	return co;\n";
	result << "}\n";

/*
                "float dist(vec2 tc, vec2 ofs)"
                "{"
                "       vec2 cc = floor(tc+ofs);"
                "       vec2 cp = texture(Tex, cc/textureSize(Tex, 0)).xy;"
                "       return distance(tc, cc+cp);"
                "}"
                "vec3 voronoi(vec2 tc)"
                "{"
                "       float md = 2.0;"
                "       int mc = 9;"
                "       for(int c=0; c<9; ++c)"
                "       {"
                "               float d = dist(tc, offs[c]);"
                "               if(md > d)"
                "               {"
                "                       md = d;"
                "                       mc = c;"
                "               }"
                "       }"
                "}"

*/

	return result;
}

OGLPLUS_LIB_FUNC
Voronoi2DNode::
Voronoi2DNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
const char*
Voronoi2DNode::
TypeName(void)
{
	return _output.TypeName();
}

OGLPLUS_LIB_FUNC
std::size_t
Voronoi2DNode::
InputCount(void)
{
	return 2;
}

OGLPLUS_LIB_FUNC
InputSlot&
Voronoi2DNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._cell_offs;
	return _output._coord._coord;
}

OGLPLUS_LIB_FUNC
std::size_t
Voronoi2DNode::
OutputCount(void)
{
	return 2;
}

OGLPLUS_LIB_FUNC
OutputSlot&
Voronoi2DNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	if(i == 0) return _output;
	return _output._coord;
}

} // namespace texgen
} // namespace oglplus

