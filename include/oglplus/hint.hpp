/**
 *  @file oglplus/hint.hpp
 *  @brief Enumeration of hint targets and options
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_HINT_1201201108_HPP
#define OGLPLUS_HINT_1201201108_HPP

namespace oglplus {

/// Enumeration of hint targets
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Hint}
 */
OGLPLUS_ENUM_CLASS_BEGIN(HintTarget, GLenum)
#include <oglplus/enums/hint_target.ipp>
OGLPLUS_ENUM_CLASS_END

inline StrLit EnumValueName(HintTarget value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/hint_target.ipp>
#endif
	return StrLit();
}

/// Enumeration of hint options
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Hint}
 */
OGLPLUS_ENUM_CLASS_BEGIN(HintOption, GLenum)
#include <oglplus/enums/hint_option.ipp>
OGLPLUS_ENUM_CLASS_END

inline StrLit EnumValueName(HintOption value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/hint_option.ipp>
#endif
	return StrLit();
}

} // namespace oglplus

#endif // include guard
