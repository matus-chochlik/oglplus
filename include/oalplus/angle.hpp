/**
 *  @file oalplus/angle.hpp
 *  @brief Implementation of angle.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_ANGLE_1303201602_HPP
#define OALPLUS_ANGLE_1303201602_HPP

#include <oalplus/config.hpp>
#include <oglplus/angle.hpp>

namespace oalplus {

/// Reused Angle<T> template from OGLplus
using oglplus::Angle;
/// Instantiation of Angle using float as data type
typedef Angle<ALfloat> Anglef;

using oglplus::Radians;
using oglplus::Degrees;
using oglplus::FullCircle;
using oglplus::FullCircles;
using oglplus::RightAngles;
using oglplus::RightAngle;
using oglplus::ArcSin;
using oglplus::ArcCos;
using oglplus::ArcTan;

} // namespace oalplus

#endif // include guard
