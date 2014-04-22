/*
 *  .file oglplus/enums/ext/graphics_reset_status_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/graphics_reset_status.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	GraphicsResetStatus
> ValueRange_(GraphicsResetStatus*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_GRAPHICSRESETSTATUS)
#define OGLPLUS_IMPL_EVR_GRAPHICSRESETSTATUS
{
static const GLenum _values[] = {
#if defined GL_NO_ERROR
GL_NO_ERROR,
#endif
#if defined GL_GUILTY_CONTEXT_RESET_ARB
GL_GUILTY_CONTEXT_RESET_ARB,
#endif
#if defined GL_INNOCENT_CONTEXT_RESET_ARB
GL_INNOCENT_CONTEXT_RESET_ARB,
#endif
#if defined GL_UNKNOWN_CONTEXT_RESET_ARB
GL_UNKNOWN_CONTEXT_RESET_ARB,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	GraphicsResetStatus
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

