/**
 *  @file oglplus/data_type.hpp
 *  @brief Data type-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_DATA_TYPE_1107121519_HPP
#define OGLPLUS_DATA_TYPE_1107121519_HPP

#include <oglplus/config.hpp>

namespace oglplus {

/// A tag template used mainly for data-type-based function overload dispatching
template <typename GLtype>
struct TypeTag
{ };

/// OpenGL data type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{DrawElements}
 *  @glfunref{VertexAttribPointer}
 */
enum class DataType : GLenum
{
#include <oglplus/enums/data_type.ipp>
};

inline const GLchar* EnumValueName(DataType value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/data_type.ipp>
#endif
	return "";
}

DataType GetDataType(GLbyte*)
{
	return DataType::Byte;
}

DataType GetDataType(GLshort*)
{
	return DataType::Short;
}

DataType GetDataType(GLint*)
{
	return DataType::Int;
}

DataType GetDataType(GLubyte*)
{
	return DataType::UnsignedByte;
}

DataType GetDataType(GLushort*)
{
	return DataType::UnsignedShort;
}

DataType GetDataType(GLuint*)
{
	return DataType::UnsignedInt;
}

DataType GetDataType(GLfloat*)
{
	return DataType::Float;
}

DataType GetDataType(GLdouble*)
{
	return DataType::Double;
}

/// Returns the DataType for the specified type @p T
template <typename T>
DataType GetDataType(void)
{
	return GetDataType((T*)nullptr);
}


/// OpenGL Shading Language data type enumeration
/**
 *  @ingroup enumerations
 */
enum class SLDataType : GLenum
{
#include <oglplus/enums/sl_data_type.ipp>
};

inline const GLchar* EnumValueName(SLDataType value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/sl_data_type.ipp>
#endif
	return "";
}

} // namespace oglplus

#endif // include guard
