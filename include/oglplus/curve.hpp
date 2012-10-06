/**
 *  @file oglplus/curve.hpp
 *  @brief Quadratic, cubic and higher-order (bezier) curves and splines
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CURVE_1107121519_HPP
#define OGLPLUS_CURVE_1107121519_HPP

#include <oglplus/vector.hpp>
#include <oglplus/auxiliary/ct_math.hpp>

#include <vector>
#include <cmath>
#include <cassert>

namespace oglplus {

/// A sequence of Bezier curves, connected at end points
/** This class stores the data for a sequence of connected Bezier curves
 *  of a given @c Order. The begin of the i-th curve (segment) is connected
 *  with the end of the (i-1)-th curve and the end of the i-th curve is
 *  connected with the begin of the (i+1)-th curve. Between the begin and
 *  end (control) points there is a fixed number (Order - 1) of curve control
 *  points. The curves pass through the begin and end and are influenced
 *  by the other control points.
 *
 *  @see CubicBezierLoop
 *
 *  @ingroup math_utils
 */
template <typename Type, typename Parameter, size_t Order>
class BezierCurves
{
private:
	::std::vector<Type> _points;
public:
	/// Checks if the sequence of control points is OK for this curve type
	static bool PointsOk(const ::std::vector<Type>& points)
	{
		if(points.empty()) return false;
		if((points.size() - 1) % Order != 0) return false;
		return true;
	}

	/// Creates the bezier curves from the control @c points
	/** The number of points must be (C * Order + 1) where
	 *  @em C is the number of curves (segments) in the sequence.
	 */
	BezierCurves(::std::vector<Type>&& points)
	 : _points(std::move(points))
	{
		assert(PointsOk(_points));
	}

	/// Creates the bezier curves from the control @c points
	/** The number of points must be (C * Order + 1) where
	 *  @em C is the number of curves (segments) in the sequence.
	 */
	BezierCurves(const ::std::vector<Type>& points)
	 : _points(points)
	{
		assert(PointsOk(_points));
	}

	/// Returns the count of individual curves in the sequence
	size_t SegmentCount(void) const
	{
		return (_points.size() - 1) / Order;
	}

	/// Returns the contol points of the curve
	const ::std::vector<Type>& ControlPoints(void) const
	{
		return _points;
	}

	/// Wraps the parameter value to [0.0, 1.0]
	static Parameter Wrap(Parameter t)
	{
		const Parameter zero(0);
		const Parameter one(1);
		if(t < zero) t += ::std::floor(::std::fabs(t))+one;
		else if(t > one) t -= ::std::floor(t);
		assert(t >= zero && t <= one);
		return t;
	}

	/// Gets the point on the curve at position t (must be between 0.0, 1.0)
	Type Position01(Parameter t) const
	{
		const Parameter zero(0);
		const Parameter one(1);

		OGLPLUS_FAKE_USE(zero);
		OGLPLUS_FAKE_USE(one);
		assert(t >= zero && t <= one);

		Parameter toffs = t*SegmentCount();
		size_t poffs = size_t(toffs) * Order;
		assert(poffs < _points.size() - Order);
		Parameter t_sub = toffs - ::std::floor(toffs);
		return aux::Bezier<Type, Parameter, Order>::Position(
			_points.data() + poffs,
			_points.size() - poffs,
			t_sub
		);
	}

	/// Gets the point on the curve at position t wrapped to [0.0, 1.0]
	Type Position(Parameter t) const
	{
		return Position01(Wrap(t));
	}

	/// Makes a sequence of points on the curve (n points per segment)
	void Approximate(std::vector<Type>& dest, size_t n) const
	{
		size_t s = SegmentCount();
		dest.resize(s*n+1);
		auto p = dest.begin(), e = dest.end();
		const Parameter t_step = Parameter(1)/n;
		typedef aux::Bezier<Type, Parameter, Order> b;
		for(size_t i=0; i!=s; ++i)
		{
			size_t poffs = i*Order;
			Parameter t_sub = Parameter(0);
			const Type* data = _points.data() + poffs;
			size_t size = _points.size() - poffs;
			for(size_t j=0; j!=n; ++j)
			{
				assert(p != e);
				*p = Type(b::Position(data, size, t_sub));
				++p;
				t_sub += t_step;
			}
		}
		assert(p != e);
		*p = _points.back();
		++p;
		OGLPLUS_FAKE_USE(e);
		assert(p == e);
	}

	/// Returns a sequence of points on the curve (n points per segment)
	::std::vector<Type> Approximate(size_t n) const
	{
		::std::vector<Type> result;
		Approximate(result, n);
		return result;
	}
};

/// A closed smooth cubic Bezier spline passing through all input points
/** This class constructs a closed sequence of Bezier curves that are smooth
 *  at the curve connection points. The control points between the begin
 *  and end points of each segment are calculated automatically to make
 *  the transition between the individual segments smooth.
 *
 *  @ingroup math_utils
 */
template <typename Type, typename Parameter>
class CubicBezierLoop
 : public BezierCurves<Type, Parameter, 3>
{
private:
	static std::vector<Type> _make_cpoints(
		const std::vector<Type>& points,
		Parameter r
	)
	{
		size_t i = 0, n = points.size();
		assert(n != 0);
		std::vector<Type> result(points.size() * 3 + 1);
		auto ir = result.begin(), er = result.end();
		while(i != n)
		{
			size_t a = (n+i-1)%n;
			size_t b = i;
			size_t c = (i+1)%n;
			size_t d = (i+2)%n;
			assert(ir != er);
			*ir = points[b];
			++ir;
			assert(ir != er);
			*ir = Type(points[b] + (points[c] - points[a])*r);
			++ir;
			assert(ir != er);
			*ir = Type(points[c] + (points[b] - points[d])*r);
			++ir;
			++i;
		}
		assert(ir != er);
		*ir = points[0]; ++ir;
		OGLPLUS_FAKE_USE(er);
		assert(ir == er);
		return result;
	}
public:
	/// Creates a loop passing through the sequence of the input points
	CubicBezierLoop(
		const ::std::vector<Type>& points,
		Parameter r = Parameter(1)/Parameter(3)
	): BezierCurves<Type, Parameter, 3>(_make_cpoints(points, r))
	{ }
};

} // namespace oglplus

#endif // include guard
