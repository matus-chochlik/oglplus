/**
 *  @file oglplus/math/vector.hpp
 *  @brief A vector class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_VECTOR_1107121519_HPP
#define OGLPLUS_VECTOR_1107121519_HPP

#include <oglplus/config/compiler.hpp>
#include <eagine/math/tvec.hpp>
#include <eagine/math/vector_swizzles.hpp>

namespace oglplus {

template <typename T, unsigned N>
using Vector = ::eagine::math::vector_swizzles<::eagine::math::tvec<T, N>>;

#ifdef GL_INT
typedef Vector<GLint, 1> Vec1i;
typedef Vector<GLint, 2> Vec2i;
typedef Vector<GLint, 3> Vec3i;
typedef Vector<GLint, 4> Vec4i;
#endif

#ifdef GL_FLOAT
typedef Vector<GLfloat, 1> Vec1f;
typedef Vector<GLfloat, 2> Vec2f;
typedef Vector<GLfloat, 3> Vec3f;
typedef Vector<GLfloat, 4> Vec4f;
#endif

#ifdef GL_DOUBLE
typedef Vector<GLdouble, 1> Vec1d;
typedef Vector<GLdouble, 2> Vec2d;
typedef Vector<GLdouble, 3> Vec3d;
typedef Vector<GLdouble, 4> Vec4d;
#endif

template <typename T, unsigned N>
static inline
T Dot(
	const eagine::math::vector<T, N>& a,
	const eagine::math::vector<T, N>& b
) noexcept
{
	return dot(a, b);
}

template <typename T>
static inline
Vector<T, 2> Perpendicular(const eagine::math::vector<T, 2>& a)
noexcept
{
	return perpendicular(a);
}

template <typename T>
static inline
Vector<T, 3> Cross(
	const eagine::math::vector<T, 3>& a,
	const eagine::math::vector<T, 3>& b
) noexcept
{
	return cross(a, b);
}

template <typename T, unsigned N>
static inline
T Distance(
	const eagine::math::vector<T, N>& a,
	const eagine::math::vector<T, N>& b
) noexcept
{
	return distance(a, b);
}

template <typename T, unsigned N>
static inline
T Length(const eagine::math::vector<T, N>& a)
noexcept
{
	return length(a);
}

template <typename T, unsigned N>
static inline
Vector<T, N> Normalized(const eagine::math::vector<T, N>& a)
noexcept
{
	return normalized(a);
}

} // namespace oglplus

#endif // include guard
