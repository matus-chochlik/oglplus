/**
 *  @file oglplus/compare_func.hpp
 *  @brief OpenGL test/comparison function enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CMP_FUNC_1107121519_HPP
#define OGLPLUS_CMP_FUNC_1107121519_HPP

namespace oglplus {

/// Comparison function type enumeration
/**
 *  @ingroup enumerations
 */
enum class CompareFunction : GLenum
{
#include <oglplus/enums/compare_function.ipp>
};

/// Alternate name for the CompareFunction enumeration
typedef CompareFunction CompareFn;

} // namespace oglplus

#endif // include guard
