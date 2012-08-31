/**
 *  @file oglplus/provoke_mode.hpp
 *  @brief OpenGL provoking vertex mode enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PROVOKE_MODE_1201041118_HPP
#define OGLPLUS_PROVOKE_MODE_1201041118_HPP

namespace oglplus {

/// Provoking vertex selection mode (for flatshading) enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{ProvokingVertex}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ProvokeMode, GLenum)
#include <oglplus/enums/provoke_mode.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	ProvokeMode*,
	EnumBaseType<ProvokeMode>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/provoke_mode.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif

} // namespace oglplus

#endif // include guard
