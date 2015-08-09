/**
 *  @file oglplus/texgen/interface.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/config/basic.hpp>
#include <oglplus/assert.hpp>
#include <iostream>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
const char*
DataTypeName(SlotDataType type)
{
	if(type == SlotDataType::Float) return "float";
	if(type == SlotDataType::FloatVec2) return "vec2";
	if(type == SlotDataType::FloatVec3) return "vec3";
	if(type == SlotDataType::FloatVec4) return "vec4";
	if(type == SlotDataType::Int) return "int";
	if(type == SlotDataType::IntVec2) return "ivec2";
	if(type == SlotDataType::IntVec3) return "ivec3";
	if(type == SlotDataType::IntVec4) return "ivec4";
	if(type == SlotDataType::Bool) return "bool";
	if(type == SlotDataType::BoolVec2) return "bvec2";
	if(type == SlotDataType::BoolVec3) return "bvec3";
	if(type == SlotDataType::BoolVec4) return "bvec4";

	return "_unknown_type_";
}

OGLPLUS_LIB_FUNC
unsigned
DataTypeDims(SlotDataType type)
{
	if(type == SlotDataType::Float) return 1;
	if(type == SlotDataType::FloatVec2) return 2;
	if(type == SlotDataType::FloatVec3) return 3;
	if(type == SlotDataType::FloatVec4) return 4;
	if(type == SlotDataType::Int) return 1;
	if(type == SlotDataType::IntVec2) return 2;
	if(type == SlotDataType::IntVec3) return 3;
	if(type == SlotDataType::IntVec4) return 4;
	if(type == SlotDataType::Bool) return 1;
	if(type == SlotDataType::BoolVec2) return 2;
	if(type == SlotDataType::BoolVec3) return 3;
	if(type == SlotDataType::BoolVec4) return 4;

	return 0;
}

OGLPLUS_LIB_FUNC
SlotDataType
ScalarDataType(SlotDataType type)
{
	switch(type)
	{
	case SlotDataType::BoolVec4:
		OGLPLUS_FALLTHROUGH
	case SlotDataType::BoolVec3:
		OGLPLUS_FALLTHROUGH
	case SlotDataType::BoolVec2:
		OGLPLUS_FALLTHROUGH
	case SlotDataType::Bool:
		return SlotDataType::Bool;

	case SlotDataType::IntVec4:
		OGLPLUS_FALLTHROUGH
	case SlotDataType::IntVec3:
		OGLPLUS_FALLTHROUGH
	case SlotDataType::IntVec2:
		OGLPLUS_FALLTHROUGH
	case SlotDataType::Int:
		return SlotDataType::Int;

	case SlotDataType::FloatVec4:
		OGLPLUS_FALLTHROUGH
	case SlotDataType::FloatVec3:
		OGLPLUS_FALLTHROUGH
	case SlotDataType::FloatVec2:
		OGLPLUS_FALLTHROUGH
	case SlotDataType::Float:
		OGLPLUS_FALLTHROUGH
	default:;
	}
	return SlotDataType::Float;
}

OGLPLUS_LIB_FUNC
SlotDataType
MakeDataType(SlotDataType scalar, unsigned dims)
{
	assert((dims >= 1) && (dims <= 4));

	switch(ScalarDataType(scalar))
	{
	case SlotDataType::Float:
		switch(dims)
		{
			case 1: return SlotDataType::Float;
			case 2: return SlotDataType::FloatVec2;
			case 3: return SlotDataType::FloatVec3;
			case 4: return SlotDataType::FloatVec4;
			default:;
		}
	case SlotDataType::Int:
		switch(dims)
		{
			case 1: return SlotDataType::Int;
			case 2: return SlotDataType::IntVec2;
			case 3: return SlotDataType::IntVec3;
			case 4: return SlotDataType::IntVec4;
			default:;
		}
	case SlotDataType::Bool:
		switch(dims)
		{
			case 1: return SlotDataType::Bool;
			case 2: return SlotDataType::BoolVec2;
			case 3: return SlotDataType::BoolVec3;
			case 4: return SlotDataType::BoolVec4;
			default:;
		}
	default:;
	}

	OGLPLUS_ABORT("Invalid scalar data type");
	return SlotDataType::Float;
}

OGLPLUS_LIB_FUNC
SlotDataType
CommonDataType(SlotDataType a, SlotDataType b)
{
	if(a == b) return a;

	unsigned da = DataTypeDims(a);
	unsigned db = DataTypeDims(b);
	unsigned ds = da>db?da:db;

	SlotDataType sa = ScalarDataType(a);
	SlotDataType sb = ScalarDataType(b);
	SlotDataType sc;

	if(sa == SlotDataType::Int || sb == SlotDataType::Int)
	{
		sc = SlotDataType::Int;
	}
	else if(sa == SlotDataType::Bool || sb == SlotDataType::Bool)
	{
		sc = SlotDataType::Bool;
	}
	else sc = SlotDataType::Float;

	return MakeDataType(sc, ds);
}

OGLPLUS_LIB_FUNC
bool
DataTypeConvertible(SlotDataType from, SlotDataType to)
{
	unsigned df = DataTypeDims(from);
	unsigned dt = DataTypeDims(to);

	return (df == 1) || (df >= dt);
}

OGLPLUS_LIB_FUNC
std::ostream&
ConversionPrefix(std::ostream& result, SlotDataType from, SlotDataType to)
{
	if(from != to)
	{
		result << DataTypeName(to) << "(";
	}
	return result;
}

OGLPLUS_LIB_FUNC
std::ostream&
ConversionSuffix(std::ostream& result, SlotDataType from, SlotDataType to)
{
	if(from != to)
	{
		result << ")";
	}
	return result;
}

OGLPLUS_LIB_FUNC
std::ostream&
ConversionSuffix(
	std::ostream& result,
	SlotDataType from,
	SlotDataType to,
	GLfloat x, GLfloat y, GLfloat z, GLfloat w
)
{
	if(from != to)
	{
		unsigned df = DataTypeDims(from);
		unsigned dt = DataTypeDims(to);

		if((df < 1) && (dt >= 1))
		{
			result << ",";
			result << x;
		}
		if((df < 2) && (dt >= 2))
		{
			result << ",";
			result << y;
		}
		if((df < 3) && (dt >= 3))
		{
			result << ",";
			result << z;
		}
		if((df < 4) && (dt >= 4))
		{
			result << ",";
			result << w;
		}
		result << ")";
	}
	return result;
}

} // namespace texgen
} // namespace oglplus

