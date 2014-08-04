/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_math_angle
namespace oglplus {

template <typename T>
class Angle
{
public:
//]
//[oglplus_math_angle_ctrs
	Angle(void); /*<
	Constructs a zero angle.
	>*/
	Angle(const Angle&);

	template <typename U>
	Angle(const Angle<U>& other); /*<
	Constructs an angle from angle with different underlying type.
>*/
//]

//[oglplus_math_angle_ctr_fns
	static Angle Radians(T val_rad); /*<
	Constructs a new angle from a value in radians.
	>*/
	static Angle Degrees(T val_deg); /*<
	Constructs a new angle from a value in degrees.
	>*/
	static Angle ArcSin(T x); /*<
	Constructs a new angle as the arc sine of the specified value.
	>*/
	static Angle ArcCos(T x);  /*<
	Constructs a new angle as the arc sine of the specified value.
	>*/
//]

//[oglplus_math_angle_end
}; // class Angle

} // namespace oglplus
//]

