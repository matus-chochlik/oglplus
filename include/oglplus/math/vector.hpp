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

namespace oglplus {

template <typename T, unsigned N>
using Vector = ::eagine::math::vector<T, N>;

template <typename T, unsigned N>
using Vec = ::eagine::math::tvec<T, N>;

#ifdef GL_FLOAT
typedef Vec<GLfloat, 1> Vec1f;
typedef Vec<GLfloat, 2> Vec2f;
typedef Vec<GLfloat, 3> Vec3f;
typedef Vec<GLfloat, 4> Vec4f;
#endif

#ifdef GL_DOUBLE
typedef Vec<GLdouble, 1> Vec1d;
typedef Vec<GLdouble, 2> Vec2d;
typedef Vec<GLdouble, 3> Vec3d;
typedef Vec<GLdouble, 4> Vec4d;
#endif

template <typename T, unsigned N>
static inline
T Dot(const Vector<T, N>& a, const Vector<T, N>& b)
noexcept
{
	return dot(a, b);
}

template <typename T>
static inline
Vector<T, 3> Cross(const Vector<T, 3>& a, const Vector<T, 3>& b)
noexcept
{
	return cross(a, b);
}

template <typename T, unsigned N>
static inline
T Distance(const Vector<T, N>& a, const Vector<T, N>& b)
noexcept
{
	return distance(a, b);
}

template <typename T, unsigned N>
static inline
T Length(const Vector<T, N>& a)
noexcept
{
	return length(a);
}

template <typename T, unsigned N>
static inline
Vector<T, N> Normalized(const Vector<T, N>& a)
noexcept
{
	return normalized(a);
}

} // namespace oglplus

#endif // include guard
