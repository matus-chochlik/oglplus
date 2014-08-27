/**
 *  @file oglplus/data_type.hpp
 *  @brief Data type-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DATA_TYPE_1107121519_HPP
#define OGLPLUS_DATA_TYPE_1107121519_HPP

#include <oglplus/enumerations.hpp>
#include <type_traits>

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
OGLPLUS_ENUM_CLASS_BEGIN(DataType, GLenum)
#include <oglplus/enums/data_type.ipp>
OGLPLUS_ENUM_CLASS_END(DataType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/data_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/data_type_range.ipp>
#endif

// Compile-time data type getter
template <typename T>
struct DataTypeCT;

template <>
struct DataTypeCT<GLbyte>
 : public std::integral_constant<DataType, DataType::Byte>
{ };

template <>
struct DataTypeCT<GLshort>
 : public std::integral_constant<DataType, DataType::Short>
{ };

template <>
struct DataTypeCT<GLint>
 : public std::integral_constant<DataType, DataType::Int>
{ };

template <>
struct DataTypeCT<GLubyte>
 : public std::integral_constant<DataType, DataType::UnsignedByte>
{ };

template <>
struct DataTypeCT<GLushort>
 : public std::integral_constant<DataType, DataType::UnsignedShort>
{ };

template <>
struct DataTypeCT<GLuint>
 : public std::integral_constant<DataType, DataType::UnsignedInt>
{ };

template <>
struct DataTypeCT<GLfloat>
 : public std::integral_constant<DataType, DataType::Float>
{ };

#ifdef GL_DOUBLE
template <>
struct DataTypeCT<GLdouble>
 : public std::integral_constant<DataType, DataType::Double>
{ };
#endif

/// Returns the DataType for the specified type @p T
template <typename T>
inline DataType GetDataType(void)
{
	return DataType(DataTypeCT<T>::value);
}

namespace aux {

template <typename T>
std::true_type _get_is_gl_data_type(T*, typename DataTypeCT<T>::type* = nullptr);
std::false_type _get_is_gl_data_type(...);

template <typename T>
struct _is_gl_data_type
{
	typedef decltype(_get_is_gl_data_type((T*)0)) type;
};

} // namespace aux

// Checks if type T is an OpenGL data type
template <typename T>
struct IsGLDataType
 : public aux::_is_gl_data_type<T>::type
{ };

/// OpenGL Shading Language data type enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(SLDataType, GLenum)
#include <oglplus/enums/sl_data_type.ipp>
OGLPLUS_ENUM_CLASS_END(SLDataType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/sl_data_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/sl_data_type_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
