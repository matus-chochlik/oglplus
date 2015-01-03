//  File implement/oglplus/enums/graphics_reset_status_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/graphics_reset_status.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	GraphicsResetStatus*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_GRAPHICSRESETSTATUS)
#define OGLPLUS_IMPL_EVN_GRAPHICSRESETSTATUS
{
switch(value)
{
#if defined GL_NO_ERROR
	case GL_NO_ERROR: return CStrRef("NO_ERROR");
#endif
#if defined GL_GUILTY_CONTEXT_RESET
	case GL_GUILTY_CONTEXT_RESET: return CStrRef("GUILTY_CONTEXT_RESET");
#endif
#if defined GL_INNOCENT_CONTEXT_RESET
	case GL_INNOCENT_CONTEXT_RESET: return CStrRef("INNOCENT_CONTEXT_RESET");
#endif
#if defined GL_UNKNOWN_CONTEXT_RESET
	case GL_UNKNOWN_CONTEXT_RESET: return CStrRef("UNKNOWN_CONTEXT_RESET");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

