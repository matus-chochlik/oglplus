/*
 *  .file oglplus/enums/ext/debug_output_source_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/debug_output_source.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	DebugOutputARBSource*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_DEBUGOUTPUTARBSOURCE)
#define OGLPLUS_IMPL_EVN_DEBUGOUTPUTARBSOURCE
{
switch(value)
{
#if defined GL_DEBUG_SOURCE_API_ARB
	case GL_DEBUG_SOURCE_API_ARB: return StrLit("DEBUG_SOURCE_API_ARB");
#endif
#if defined GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: return StrLit("DEBUG_SOURCE_WINDOW_SYSTEM_ARB");
#endif
#if defined GL_DEBUG_SOURCE_SHADER_COMPILER_ARB
	case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: return StrLit("DEBUG_SOURCE_SHADER_COMPILER_ARB");
#endif
#if defined GL_DEBUG_SOURCE_THIRD_PARTY_ARB
	case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: return StrLit("DEBUG_SOURCE_THIRD_PARTY_ARB");
#endif
#if defined GL_DEBUG_SOURCE_APPLICATION_ARB
	case GL_DEBUG_SOURCE_APPLICATION_ARB: return StrLit("DEBUG_SOURCE_APPLICATION_ARB");
#endif
#if defined GL_DEBUG_SOURCE_OTHER_ARB
	case GL_DEBUG_SOURCE_OTHER_ARB: return StrLit("DEBUG_SOURCE_OTHER_ARB");
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

