/**
 *  @file oglplus/texgen/global_node.ipp
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
BaseGlobalOutputSlot::
BaseGlobalOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
{ }

OGLPLUS_LIB_FUNC
const char*
BaseGlobalOutputSlot::
TypeName(void)
{
	return "Global";
}

OGLPLUS_LIB_FUNC
GlobalCoordinateSlot::
GlobalCoordinateSlot(Node& parent)
 : BaseGlobalOutputSlot(parent)
{ }

OGLPLUS_LIB_FUNC
const char*
GlobalCoordinateSlot::
Name(void)
{
	return "Coordinate";
}

OGLPLUS_LIB_FUNC
SlotDataType
GlobalCoordinateSlot::
ValueType(void)
{
	return SlotDataType::FloatVec3;
}

OGLPLUS_LIB_FUNC
std::ostream&
GlobalCoordinateSlot::
Definitions(std::ostream& result, unsigned)
{
	result << "vec3 ";
	AppendId(result);
	result << "(vec3 po, vec3 so){return ";
	result << "oglptgCoordinate+po*oglptgCoordDelta";
	result << ";}\n";

	return result;
}

OGLPLUS_LIB_FUNC
GlobalNode::
GlobalNode(void)
 : _coordinate(*this)
{ }

OGLPLUS_LIB_FUNC
const char*
GlobalNode::
TypeName(void)
{
	return "Global";
}

OGLPLUS_LIB_FUNC
std::size_t
GlobalNode::
OutputCount(void)
{
	return 1;
}

OGLPLUS_LIB_FUNC
OutputSlot&
GlobalNode::
Output(std::size_t i)
{
	assert(i < OutputCount());
	return _coordinate;
}

} // namespace texgen
} // namespace oglplus

