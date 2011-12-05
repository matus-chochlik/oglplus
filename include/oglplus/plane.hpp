/**
 *  @file oglplus/plane.hpp
 *  @brief Plane in 3D space utility class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PLANE_1107121519_HPP
#define OGLPLUS_PLANE_1107121519_HPP

#include <cmath>

namespace oglplus {

/// Class implementing plane-related functionality
/** @c Plane is a lightweight class allowing more natural construction and
 *  usage of 2D planes in 3D space.
 *
 *  @ingroup math_utils
 */
template <typename T>
class Plane
{
private:
	Vector<T, 4> _equation;
public:
	Plane(T a, T b, T c, T d)
	 : _equation(a, b, c, d)
	{ }

	Plane(const Vector<T, 4>& v)
	 : _equation(v)
	{ }

	struct _FromTriangle { };

	Plane(
		_FromTriangle,
		const Vector<T, 3>& p0,
		const Vector<T, 3>& p1,
		const Vector<T, 3>& p2
	): _equation(
		Normalized(Cross(p1-p0, p2-p0)),
		-Dot(Normalized(Cross(p1-p0, p2-p0)), p0)
	)
	{ }

	static inline Plane FromTriangle(
		const Vector<T, 3>& p0,
		const Vector<T, 3>& p1,
		const Vector<T, 3>& p2
	)
	{
		return Plane(
			_FromTriangle(),
			p0, p1, p2
		);
	}

	struct _FromPointAndVectors { };

	Plane(
		_FromPointAndVectors,
		const Vector<T, 3>& p,
		const Vector<T, 3>& v1,
		const Vector<T, 3>& v2
	): _equation(
		Normalized(Cross(v1, v2)),
		-Dot(Normalized(Cross(v1, v2)), p)
	)
	{ }

	static inline Plane FromPointAndVectors(
		const Vector<T, 3>& p,
		const Vector<T, 3>& v1,
		const Vector<T, 3>& v2
	)
	{
		return Plane(
			_FromPointAndVectors(),
			p, v1, v2
		);
	}

	struct _FromNormal { };

	Plane(_FromNormal, const Vector<T, 3>& normal)
	 : _equation(normal, T(0))
	{ }

	static inline Plane FromNormal(const Vector<T, 3>& normal)
	{
		return Plane(_FromNormal(), normal);
	}

	const Vector<T, 4>& Equation(void) const
	{
		return _equation;
	}
};

typedef Plane<GLfloat> Planef;

} // namespace oglplus

#endif // include guard
