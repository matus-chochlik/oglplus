/**
 *  @file oglplus/angle.hpp
 *  @brief Angle utility class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_ANGLE_1107121519_HPP
#define OGLPLUS_ANGLE_1107121519_HPP

#include <oglplus/config.hpp>

#include <cmath>
#include <cassert>

namespace oglplus {

/// Class implementing planar angle-related functionality
/** @c Angle is a lightweight class allowing more natural construction and
 *  usage of planar angle values. The storage requirements are the same
 *  as for the template parameter type @c T and the @c Angle template gives
 *  the @c T type special meaning and implements a set of angle-related member
 *  functions. There are also several associated free functions for creating
 *  new instances of @c Angle.
 *
 *  @see oglplus::Radians
 *  @see oglplus::Degrees
 *  @see oglplus::FullCircles
 *  @see oglplus::RightAngles
 *  @see oglplus::ArcSin
 *  @see oglplus::ArcCos
 *  @see oglplus::ArcTan
 *
 *  @ingroup math_utils
 */
template <typename T>
class Angle
{
private:
	// the angle value in radians
	T _val_rad;

	struct _Radians { };
	Angle(T val_rad, _Radians)
	 : _val_rad(val_rad)
	{ }

	struct _Degrees { };
	Angle(T val_deg, _Degrees)
	 : _val_rad(T(val_deg * (M_PI / 180.0)))
	{ }
public:
	/// Constructs a zero angle
	Angle(void)
	 : _val_rad(T(0))
	{ }

#if !OGLPLUS_NO_DEFAULTED_FUNCTIONS
	/// Angle is copy constructible
	Angle(const Angle&) = default;
#endif

	/// Copy construction from angles using different representation type
	template <typename U>
	Angle(const Angle<U>& other)
	 : _val_rad(T(other.Value()))
	{ }

	/// Constructs a new angle from value in radians
	static inline Angle Radians(T val_rad)
	{
		return Angle(val_rad, _Radians());
	}

	/// Constructs a new angle from value in degrees
	static inline Angle Degrees(T val_deg)
	{
		return Angle(val_deg, _Degrees());
	}

	/// Returns the value of the angle in radians
	inline T Value(void) const
	{
		return _val_rad;
	}

	/// Returns the value of the angle in degrees
	inline T ValueInDegrees(void) const
	{
		return _val_rad * T(180.0 / M_PI);
	}

	/// Equality comparison
	friend bool operator == (const Angle& a, const Angle& b)
	{
		return a._val_rad == b._val_rad;
	}

	/// Inequality comparison
	friend bool operator != (const Angle& a, const Angle& b)
	{
		return a._val_rad != b._val_rad;
	}

	/// Less than comparison
	friend bool operator <  (const Angle& a, const Angle& b)
	{
		return a._val_rad <  b._val_rad;
	}

	/// Greater than comparison
	friend bool operator >  (const Angle& a, const Angle& b)
	{
		return a._val_rad >  b._val_rad;
	}

	/// Less than/equal comparison
	friend bool operator <= (const Angle& a, const Angle& b)
	{
		return a._val_rad <= b._val_rad;
	}

	/// Greater than/equal comparison
	friend bool operator >= (const Angle& a, const Angle& b)
	{
		return a._val_rad >=  b._val_rad;
	}

	/// Negation
	friend Angle Negated(const Angle& angle)
	{
		return Angle(-angle._val_rad, _Radians());
	}

	/// Negation operator
	friend Angle operator - (const Angle& angle)
	{
		return Negated(angle);
	}

	/// Addition
	friend Angle Add(const Angle& a, const Angle& b)
	{
		return Angle(a._val_rad + b._val_rad, _Radians());
	}

	/// Addition operator
	friend Angle operator + (const Angle& a, const Angle& b)
	{
		return Add(a, b);
	}

	/// Subtraction
	friend Angle Subtract(const Angle& a, const Angle& b)
	{
		return Angle(a._val_rad - b._val_rad, _Radians());
	}

	/// Subtraction operator
	friend Angle operator - (const Angle& a, const Angle& b)
	{
		return Subtract(a, b);
	}

	/// Multiplication by constant
	friend Angle Multiply(const Angle& a, T mult)
	{
		return Angle(a._val_rad * mult, _Radians());
	}

	/// Multiplication by constant operator
	friend Angle operator * (const Angle& a, T mult)
	{
		return Multiply(a, mult);
	}

	/// Multiplication by constant operator
	friend Angle operator * (T mult, const Angle& a)
	{
		return Multiply(a, mult);
	}

	/// Returns the sine of the angle
	friend inline T Sin(const Angle& a)
	{
		return ::std::sin(a._val_rad);
	}

	/// Returns the cosine of the angle
	friend inline T Cos(const Angle& a)
	{
		return ::std::cos(a._val_rad);
	}

	/// Returns the tangent of the angle
	friend inline T Tan(const Angle& a)
	{
		return ::std::tan(a._val_rad);
	}
};

/// Creates a new angle from a value in radians
/** This function creates a new instance of @c Angle<GLfloat>
 *  from a floating-point value in radians.
 *
 *  @param val_rad a value in radians
 *
 *  @see Degrees
 *  @see FullCircles
 *  @see RightAngles
 *  @see ArcSin
 *  @see ArcCos
 *  @see ArcTan
 *
 *  @ingroup math_utils
 */
inline Angle<GLfloat> Radians(GLfloat val_rad)
{
	return Angle<GLfloat>::Radians(val_rad);
}

/// Creates a new angle from a value in degrees
/** This function creates a new instance of @c Angle<GLfloat>
 *  from a floating-point value in degrees.
 *  Examples:
 *  @code
 *  // create a 30 degree angle
 *  Degrees(30);
 *  // create a right angle
 *  Degrees(90);
 *  @endcode
 *
 *  @param val_deg a value in degrees
 *
 *  @see Radians
 *  @see FullCircles
 *  @see RightAngles
 *  @see ArcSin
 *  @see ArcCos
 *  @see ArcTan
 *
 *  @ingroup math_utils
 */
inline Angle<GLfloat> Degrees(GLfloat val_deg)
{
	return Angle<GLfloat>::Degrees(val_deg);
}

/// Creates a new angle from a value in "full circles" (i.e. 360 deg.)
/** This function creates a new angle from a value specifying the fraction
 *  of a full 360 degree (2 pi radians) angle. For example the following
 *  is true:
 *  @code
 *  FullCircles(0.125) == Degrees(45);
 *  FullCircles(0.25) == Degrees(90);
 *  FullCircles(0.25) == Radians(PI / 2);
 *  FullCircles(0.5) == Degrees(180);
 *  FullCircles(0.5) == Radians(PI);
 *  FullCircles(0.9) == Radians(2 * PI * 0.9);
 *  @endcode
 *
 *  @param value a value in 360-degree units
 *
 *  @see Radians
 *  @see Degrees
 *  @see ArcSin
 *  @see ArcCos
 *  @see ArcTan
 *
 *  @ingroup math_utils
 */
inline Angle<GLfloat> FullCircles(GLfloat value)
{
	return Angle<GLfloat>::Radians(GLfloat(value * M_PI * 2.0));
}

/// Creates a new angle from a value in "right angles" (i.e. 90 deg.)
/** This function creates a new angle from a value specifying the fraction
 *  of a quarter 90 degree (pi/2 radians) angle. For example the following
 *  is true:
 *  @code
 *  RightAngles(0.5) == Degrees(45);
 *  RightAngles(1.0) == Degrees(90);
 *  RightAngles(1.0) == Radians(PI / 2);
 *  RightAngles(2.0) == Degrees(180);
 *  RightAngles(2.0) == Radians(PI);
 *  RightAngles(0.9) == Radians(0.9 * PI / 2);
 *  @endcode
 *
 *  @param value a value in 90-degree units
 *
 *  @see Radians
 *  @see Degrees
 *  @see ArcSin
 *  @see ArcCos
 *  @see ArcTan
 *
 *  @ingroup math_utils
 */
inline Angle<GLfloat> RightAngles(GLfloat value)
{
	return Angle<GLfloat>::Radians(GLfloat(value * M_PI * 0.5));
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
inline Angle<GLfloat> ArcSin(GLfloat x)
{
	assert(-1.0f <= x && x <= 1.0f);
	return Angle<GLfloat>::Radians(::std::asin(x));
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
inline Angle<GLfloat> ArcCos(GLfloat x)
{
	assert(-1.0f <= x && x <= 1.0f);
	return Angle<GLfloat>::Radians(::std::acos(x));
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
inline Angle<GLfloat> ArcTan(GLfloat x)
{
	return Angle<GLfloat>::Radians(::std::atan(x));
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
inline Angle<GLfloat> ArcTan(GLfloat y, GLfloat x)
{
	return Angle<GLfloat>::Radians(::std::atan2(y, x));
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
 *  @ingroup math_utils
 */
template <typename T>
inline T SineWave(T t)
{
	return ::std::sin(T(2.0 * M_PI * t));
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
 *  @ingroup math_utils
 */
template <typename T>
inline T CosineWave(T t)
{
	return ::std::cos(T(2.0 * M_PI * t));
}

} // namespace oglplus

#endif // include guard
