/**
 *  @file oglplus/math/angle.hpp
 *  @brief Angle utility class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_MATH_ANGLE_1107121519_HPP
#define OGLPLUS_MATH_ANGLE_1107121519_HPP

#include <oglplus/config/compiler.hpp>
#include <eagine/math/angle.hpp>

#include <cassert>
#include <type_traits>

namespace oglplus {

template <typename T>
using Angle = ::eagine::math::angle<T>;

#if OGLPLUS_DOCUMENTATION_ONLY || defined(GL_FLOAT)
/// Instantiation of Angle using GL floating-point as underlying type
typedef Angle<GLfloat> Anglef;

typedef GLfloat AngleValueType;
#elif defined(AL_VERSION_1_1)
typedef ALfloat AngleValueType;
#else
typedef double AngleValueType;
#endif

template <typename T>
inline
T Sin(Angle<T> a)
{
	return ::eagine::math::sin(a);
}

template <typename T>
inline
T Cos(Angle<T> a)
{
	return ::eagine::math::cos(a);
}

template <typename T>
inline
T Tan(Angle<T> a)
{
	return ::eagine::math::tan(a);
}

template <typename T = AngleValueType>
using Radian = ::eagine::unit::quantity< ::eagine::unit::radian, T>;

inline
Angle<AngleValueType> Radians(AngleValueType x)
{
	return Radian<AngleValueType>(x);
}

template <typename T = AngleValueType>
using Degree = ::eagine::unit::quantity< ::eagine::unit::degree, T>;

inline
Angle<AngleValueType> Degrees(AngleValueType x)
{
	return Degree<AngleValueType>(x);
}

template <typename T = AngleValueType>
using FullCircle = ::eagine::unit::quantity< ::eagine::unit::turn, T>;

inline
Angle<AngleValueType> FullCircles(AngleValueType x)
{
	return FullCircle<AngleValueType>(x);
}

template <typename T = AngleValueType>
using RightAngle = ::eagine::unit::quantity< ::eagine::unit::quarter, T>;

inline
Angle<AngleValueType> RightAngles(AngleValueType x)
{
	return RightAngle<AngleValueType>(x);
}

/// Creates a new angle using the arc sine function
/**
 *  @param x the value must be between -1.0 and 1.0
 *
 *  @see Radians
 *  @see Degrees
 *  @see FullCircles
 *  @see RightAngles
 *  @see ArcCos
 *  @see ArcTan
 *
 *  @ingroup math_utils
 */
inline
Angle<AngleValueType> ArcSin(AngleValueType x)
{
	return ::eagine::math::asin<AngleValueType>(x);
}

/// Creates a new angle using the arc cosine function
/**
 *  @param x the value must be between -1.0 and 1.0
 *
 *  @see Radians
 *  @see Degrees
 *  @see FullCircles
 *  @see RightAngles
 *  @see ArcSin
 *  @see ArcTan
 *
 *  @ingroup math_utils
 */
inline
Angle<AngleValueType> ArcCos(AngleValueType x)
{
	return ::eagine::math::acos<AngleValueType>(x);
}

/// Creates a new angle using the arc tangent function
/**
 *
 *  @see Radians
 *  @see Degrees
 *  @see FullCircles
 *  @see RightAngles
 *  @see ArcSin
 *  @see ArcTan
 *
 *  @ingroup math_utils
 */
inline
Angle<AngleValueType> ArcTan(AngleValueType x)
{
	return ::eagine::math::atan<AngleValueType>(x);
}

/// Creates a new angle using the arc tangent function with 2 parameters
/**
 *
 *  @see Radians
 *  @see Degrees
 *  @see FullCircles
 *  @see RightAngles
 *  @see ArcSin
 *  @see ArcTan
 *
 *  @ingroup math_utils
 */
inline
Angle<AngleValueType> ArcTan(AngleValueType y, AngleValueType x)
{
	return ::eagine::math::atan2<AngleValueType>(y, x);
}

/// Returns a value on a sine wave at the specified point
/** This function returns the value of sin(2.PI.@p t), i.e.
 *  integer values of @p t are the ends of the previous full
 *  sine wave and the begining of the next "iteration".
 *  The following is true:
 *  @code
 *  SineWave(t) == sin(2.0*PI*t);
 *  SineWave(0.00) ==  0.0;
 *  SineWave(0.25) ==  1.0;
 *  SineWave(0.50) ==  0.0;
 *  SineWave(0.75) == -1.0;
 *  SineWave(1.00) ==  0.0;
 *  @endcode
 *
 *  @param t the point for which to calculate the value on the wave.
 *
 *  @see SineWave01
 *  @see CosineWave
 *
 *  @ingroup math_utils
 */
template <typename T>
inline
T SineWave(T t)
{
	using namespace ::eagine::unit;
	return ::eagine::math::sin(Angle<T>(FullCircle<T>(t)));
}

/// Returns a value on a sine wave transformed to range <0, 1>
/** This function returns the value of (sin(2.PI.@p t)+1)/2, i.e.
 *  integer values of @p t are the ends of the previous full
 *  sine wave and the begining of the next "iteration".
 *  The following is true:
 *  @code
 *  SineWave01(t) == (sin(2.0*PI*t)+1)/2;
 *  SineWave01(0.00) ==  0.5;
 *  SineWave01(0.25) ==  1.0;
 *  SineWave01(0.50) ==  0.5;
 *  SineWave01(0.75) ==  0.0;
 *  SineWave01(1.00) ==  0.5;
 *  @endcode
 *
 *  @param t the point for which to calculate the value on the wave.
 *
 *  @see SineWave
 *  @see CosineWave01
 *
 *  @ingroup math_utils
 */
template <typename T>
inline
T SineWave01(T t)
{
	return (SineWave(t)+T(1))/T(2);
}

/// Returns a value on a cosine wave at the specified point
/** This function returns the value of cos(2.PI.@p t), i.e.
 *  integer values of @p t are the ends of the previous full
 *  cosine wave and the begining of the next "iteration".
 *  The following is true:
 *  @code
 *  CosineWave(t) == cos(2.0*PI*t);
 *  CosineWave(0.00) ==  1.0;
 *  CosineWave(0.25) ==  0.0;
 *  CosineWave(0.50) == -1.0;
 *  CosineWave(0.75) ==  0.0;
 *  CosineWave(1.00) ==  1.0;
 *  @endcode
 *
 *  @param t the point for which to calculate the value on the wave.
 *
 *  @see SineWave
 *  @see CosineWave01
 *
 *  @ingroup math_utils
 */
template <typename T>
inline
T CosineWave(T t)
{
	using namespace ::eagine::unit;
	return ::eagine::math::cos(Angle<T>(FullCircle<T>(t)));
}

/// Returns a value on a cosine wave transformed to range <0, 1>
/** This function returns the value of (cos(2.PI.@p t)+1)/2, i.e.
 *  integer values of @p t are the ends of the previous full
 *  cosine wave and the begining of the next "iteration".
 *  The following is true:
 *  @code
 *  CosineWave(t) == (cos(2.0*PI*t)+1)/2;
 *  CosineWave(0.00) ==  1.0;
 *  CosineWave(0.25) ==  0.5;
 *  CosineWave(0.50) ==  0.0;
 *  CosineWave(0.75) ==  0.5;
 *  CosineWave(1.00) ==  1.0;
 *  @endcode
 *
 *  @param t the point for which to calculate the value on the wave.
 *
 *  @see CosineWave
 *  @see SineWave01
 *
 *  @ingroup math_utils
 */
template <typename T>
inline
T CosineWave01(T t)
{
	return (CosineWave(t)+T(1))/T(2);
}

} // namespace oglplus

#endif // include guard
