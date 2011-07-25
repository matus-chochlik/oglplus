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

/// OpenGL data type enumeration
enum class DataType : GLenum
{
	Byte = GL_BYTE,
	Short = GL_SHORT,
	Int = GL_INT,
	Fixed = GL_FIXED,
	Float = GL_FLOAT,
	HalfFloat = GL_HALF_FLOAT,
	Double = GL_DOUBLE,
	UnsignedByte = GL_UNSIGNED_BYTE,
	UnsignedShort = GL_UNSIGNED_SHORT,
	UnsignedInt = GL_UNSIGNED_INT
};

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

template <typename T>
DataType GetDataType(void)
{
	return GetDataType((T*)nullptr);
}

} // namespace oglplus

#endif // include guard
