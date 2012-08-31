/**
 *  @file oglplus/blit_filter.hpp
 *  @brief Enumeration of Blit operation filtering modes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BLIT_FILTER_1201201108_HPP
#define OGLPLUS_BLIT_FILTER_1201201108_HPP

namespace oglplus {

/// Enumeration of blit operation filtering modes
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BlitFramebuffer}
 */
OGLPLUS_ENUM_CLASS_BEGIN(BlitFilter, GLenum)
#include <oglplus/enums/blit_filter.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	BlitFilter*,
	EnumBaseType<BlitFilter>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/blit_filter.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif

} // namespace oglplus

#endif // include guard
