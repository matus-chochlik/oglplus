/*
 *  .file oglplus/enums/debug_output_source_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/debug_output_source.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	DebugOutputSource*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_DEBUGOUTPUTSOURCE)
#define OGLPLUS_IMPL_EVN_DEBUGOUTPUTSOURCE
{
switch(value)
{
#if defined GL_DEBUG_SOURCE_API
	case GL_DEBUG_SOURCE_API: return StrLit("DEBUG_SOURCE_API");
#endif
#if defined GL_DEBUG_SOURCE_WINDOW_SYSTEM
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return StrLit("DEBUG_SOURCE_WINDOW_SYSTEM");
#endif
#if defined GL_DEBUG_SOURCE_SHADER_COMPILER
	case GL_DEBUG_SOURCE_SHADER_COMPILER: return StrLit("DEBUG_SOURCE_SHADER_COMPILER");
#endif
#if defined GL_DEBUG_SOURCE_THIRD_PARTY
	case GL_DEBUG_SOURCE_THIRD_PARTY: return StrLit("DEBUG_SOURCE_THIRD_PARTY");
#endif
#if defined GL_DEBUG_SOURCE_APPLICATION
	case GL_DEBUG_SOURCE_APPLICATION: return StrLit("DEBUG_SOURCE_APPLICATION");
#endif
#if defined GL_DEBUG_SOURCE_OTHER
	case GL_DEBUG_SOURCE_OTHER: return StrLit("DEBUG_SOURCE_OTHER");
#endif
#if defined GL_DONT_CARE
	case GL_DONT_CARE: return StrLit("DONT_CARE");
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

