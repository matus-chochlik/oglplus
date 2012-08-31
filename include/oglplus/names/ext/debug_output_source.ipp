/*
 *  .file oglplus/names/ext/debug_output_source.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/debug_output_source.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

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

