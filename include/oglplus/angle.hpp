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

#include <cmath>

namespace oglplus {

/// Class implementing angle-related functionality
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
	 : _val_rad(val_deg * (M_PI / 180.0))
	{ }
public:
	/// Constructs a zero angle
	Angle(void)
	 : _val_rad(T(0))
	{ }

	Angle(const Angle&) = default;

	template <typename U>
	Angle(const Angle<U>& other)
	 : _val_rad(T(other.Value()))
	{ }

	/// Constructs a new angle from value in degrees
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
/**
 *  @param val_rad a value in radians
 *
 *  @see Degrees
 *  @see ArcSin
 *  @see ArcCos
 *  @see ArcTan
 */
inline Angle<GLfloat> Radians(GLfloat val_rad)
{
	return Angle<GLfloat>::Radians(val_rad);
}

/// Creates a new angle using the arc sine function
/**
 *  @param x the value must be between -1.0 and 1.0
 *
 *  @see Radians
 *  @see Degrees
 *  @see ArcCos
 *  @see ArcTan
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
 *  @see ArcSin
 *  @see ArcTan
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
 *  @see ArcSin
 *  @see ArcTan
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
 *  @see ArcSin
 *  @see ArcTan
 */
inline Angle<GLfloat> ArcTan(GLfloat y, GLfloat x)
{
	return Angle<GLfloat>::Radians(::std::atan2(y, x));
}

/// Creates a new angle from a value in degrees
/**
 *  @param val_deg a value in degrees
 *
 *  @see Radians
 *  @see ArcSin
 *  @see ArcCos
 *  @see ArcTan
 */
inline Angle<GLfloat> Degrees(GLfloat val_deg)
{
	return Angle<GLfloat>::Degrees(val_deg);
}

} // namespace oglplus

#endif // include guard
