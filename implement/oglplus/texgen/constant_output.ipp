/**
 *  @file oglplus/texgen/constant_output.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/config/basic.hpp>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
BaseConstantOutputSlot::
BaseConstantOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
{ }

OGLPLUS_LIB_FUNC
SlotDataType
BaseConstantOutputSlot::
_t(TypeTag<GLfloat>)
{ return SlotDataType::Float; }

OGLPLUS_LIB_FUNC
SlotDataType
BaseConstantOutputSlot::
_t(TypeTag<Vec2f>)
{ return SlotDataType::FloatVec2; }

OGLPLUS_LIB_FUNC
SlotDataType
BaseConstantOutputSlot::
_t(TypeTag<Vec3f>)
{ return SlotDataType::FloatVec3; }

OGLPLUS_LIB_FUNC
SlotDataType
BaseConstantOutputSlot::
_t(TypeTag<Vec4f>)
{ return SlotDataType::FloatVec4; }

OGLPLUS_LIB_FUNC
void
BaseConstantOutputSlot::
_format_head(std::ostream& os, const char* type_name)
{
	os	<< type_name << " ";
	AppendId(os);
	os	<< "(vec3 po, vec3 so)";
	os	<< "{";
}

OGLPLUS_LIB_FUNC
void
BaseConstantOutputSlot::
_format_tail(std::ostream& os)
{
	os	<< "}\n";
}

OGLPLUS_LIB_FUNC
void
BaseConstantOutputSlot::
_format(std::ostream& os, GLfloat v)
{
	os	<< "return float(" << v << ");";
}

OGLPLUS_LIB_FUNC
void
BaseConstantOutputSlot::
_format(std::ostream& os, const Vec2f& v)
{
	os	<< "return vec2("
		<< v[0] << ","
		<< v[1] << ");";
}

OGLPLUS_LIB_FUNC
void
BaseConstantOutputSlot::
_format(std::ostream& os, const Vec3f& v)
{
	os	<< "return vec3("
		<< v[0] << ","
		<< v[1] << ","
		<< v[2] << ");";
}

OGLPLUS_LIB_FUNC
void
BaseConstantOutputSlot::
_format(std::ostream& os, const Vec4f& v)
{
	os	<< "return vec4("
		<< v[0] << ","
		<< v[1] << ","
		<< v[2] << ","
		<< v[3] << ");";
}

OGLPLUS_LIB_FUNC
const char*
BaseConstantOutputSlot::
TypeName(void)
{
	return "Const";
}

OGLPLUS_LIB_FUNC
bool
BaseConstantOutputSlot::
SupportsValueType(SlotDataType type)
{
	return
		(SlotDataType::FloatVec4 == type)||
		(SlotDataType::FloatVec3 == type)||
		(SlotDataType::FloatVec2 == type)||
		(SlotDataType::Float == type);
}


OGLPLUS_LIB_FUNC
std::unique_ptr<OutputSlot>
BaseConstantOutputSlot::
MakeNew(Node& parent, SlotDataType type)
{
	if(SlotDataType::FloatVec4 == type)
	{
		return std::unique_ptr<OutputSlot>(
			new ConstantOutputSlot<Vec4f>(parent, Vec4f(0))
		);
	}

	if(SlotDataType::FloatVec3 == type)
	{
		return std::unique_ptr<OutputSlot>(
			new ConstantOutputSlot<Vec3f>(parent, Vec3f(0))
		);
	}

	if(SlotDataType::FloatVec2 == type)
	{
		return std::unique_ptr<OutputSlot>(
			new ConstantOutputSlot<Vec2f>(parent, Vec2f(0))
		);
	}

	if(SlotDataType::Float == type)
	{
		return std::unique_ptr<OutputSlot>(
			new ConstantOutputSlot<GLfloat>(parent, 0)
		);
	}

	return std::unique_ptr<OutputSlot>();
}

} // namespace texgen
} // namespace oglplus

