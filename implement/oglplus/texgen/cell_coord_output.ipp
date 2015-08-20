/**
 *  @file oglplus/texgen/cell_coord_output.ipp
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
CellCoordOutputSlot::
CellCoordOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _coord(parent, "Coordinate")
 , _cells(parent, "CellCount", Vec2f(16,16))
 , _version(0)
{ }

OGLPLUS_LIB_FUNC
const char*
CellCoordOutputSlot::
Name(void)
{
	return "Coordinate";
}

OGLPLUS_LIB_FUNC
const char*
CellCoordOutputSlot::
TypeName(void)
{
	return "CellCoord";
}

OGLPLUS_LIB_FUNC
SlotDataType
CellCoordOutputSlot::
ValueType(void)
{
	return SlotDataType::FloatVec3;
}

OGLPLUS_LIB_FUNC
std::ostream&
CellCoordOutputSlot::
Definitions(std::ostream& result, CompileContext& context)
{
	_coord.Definitions(result, context);
	_cells.Definitions(result, context);

	const SlotDataType v2 = SlotDataType::FloatVec2;
	const SlotDataType v3 = SlotDataType::FloatVec3;

	result << "vec3 ";
	AppendId(result);
	result << "(vec3 po, vec3 so)\n";
	result << "{\n";

	result << "	vec3 tc = ";
	ConversionPrefix(result, _coord.ValueType(), v3);
	_coord.Expression(result, context) << "(po, so)";
	ConversionSuffix(result, _coord.ValueType(), v3,0,0,0,0) << ";\n";

	result << "	vec2 nc = ";
	ConversionPrefix(result, _cells.ValueType(), v2);
	_cells.Expression(result, context) << "(po, so)";
	ConversionSuffix(result, _cells.ValueType(), v2,1,1,1,1) << ";\n";

	result << "	return vec3(floor(tc.xy*nc+so.xy)/nc,tc.z);\n";

	result << "}\n";

	return result;
}

OGLPLUS_LIB_FUNC
bool
CellCoordOutputSlot::
Render(const RenderParams& params)
{
	if(_version < params.version)
	{
		_version = params.version;
		return BaseOutputSlot::Render(params);
	}
	return true;
}

} // namespace texgen
} // namespace oglplus

