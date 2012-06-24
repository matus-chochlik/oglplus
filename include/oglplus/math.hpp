/**
 *  @file oglplus/math.hpp
 *  @brief Math utilities
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_MATH_1107121519_HPP
#define OGLPLUS_MATH_1107121519_HPP

#include <oglplus/config.hpp>

#include <cmath>

namespace oglplus {
namespace math {

#ifdef M_PI
inline OGLPLUS_CONSTEXPR decltype(M_PI) pi(void)
OGLPLUS_NOEXCEPT_IF(M_PI)
{
	return M_PI;
}
#else
inline decltype(std::atan(1.0) * 4.0) pi(void)
OGLPLUS_NOEXCEPT_IF(std::atan(1.0) * 4.0)
{
	static auto _pi = std::atan(1.0) * 4.0;
	return _pi;
}
#endif

} // namespace math
} // namespace oglplus

#endif // include guard
