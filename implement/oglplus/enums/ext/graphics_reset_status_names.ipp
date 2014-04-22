/*
 *  .file oglplus/enums/ext/graphics_reset_status_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/graphics_reset_status.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	GraphicsResetStatus*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_GRAPHICSRESETSTATUS)
#define OGLPLUS_IMPL_EVN_GRAPHICSRESETSTATUS
{
switch(value)
{
#if defined GL_NO_ERROR
	case GL_NO_ERROR: return StrLit("NO_ERROR");
#endif
#if defined GL_GUILTY_CONTEXT_RESET_ARB
	case GL_GUILTY_CONTEXT_RESET_ARB: return StrLit("GUILTY_CONTEXT_RESET_ARB");
#endif
#if defined GL_INNOCENT_CONTEXT_RESET_ARB
	case GL_INNOCENT_CONTEXT_RESET_ARB: return StrLit("INNOCENT_CONTEXT_RESET_ARB");
#endif
#if defined GL_UNKNOWN_CONTEXT_RESET_ARB
	case GL_UNKNOWN_CONTEXT_RESET_ARB: return StrLit("UNKNOWN_CONTEXT_RESET_ARB");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

