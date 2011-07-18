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

namespace oglplus {

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

} // namespace oglplus

#endif // include guard
