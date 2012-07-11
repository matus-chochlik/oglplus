/**
 *  @file oglplus/blend_func.hpp
 *  @brief OpenGL blending function and equation enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BLEND_FUNC_1107121519_HPP
#define OGLPLUS_BLEND_FUNC_1107121519_HPP

namespace oglplus {

/// Blend function type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BlendFunc}
 */
enum class BlendFunction : GLenum
{
#include <oglplus/enums/blend_function.ipp>
};

inline StrLit EnumValueName(BlendFunction value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/blend_function.ipp>
#endif
	return StrLit();
}

/// Alternative name for the BlendFunction enumeration
typedef BlendFunction BlendFn;

/// Blend equation enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BlendEquation}
 */
enum class BlendEquation : GLenum
{
#include <oglplus/enums/blend_equation.ipp>
};

inline StrLit EnumValueName(BlendEquation value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/blend_equation.ipp>
#endif
	return StrLit();
}

/// Alternative name for the BlendEquation enumeration
typedef BlendEquation BlendEq;

} // namespace oglplus

#endif // include guard
