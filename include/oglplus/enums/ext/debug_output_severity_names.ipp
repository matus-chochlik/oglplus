/*
 *  .file oglplus/enums/ext/debug_output_severity_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/debug_output_severity.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	DebugOutputSeverity*,
	GLenum value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
switch(value)
{
#if defined GL_DEBUG_SEVERITY_HIGH_ARB
	case GL_DEBUG_SEVERITY_HIGH_ARB: return StrLit("DEBUG_SEVERITY_HIGH_ARB");
#endif
#if defined GL_DEBUG_SEVERITY_MEDIUM_ARB
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: return StrLit("DEBUG_SEVERITY_MEDIUM_ARB");
#endif
#if defined GL_DEBUG_SEVERITY_LOW_ARB
	case GL_DEBUG_SEVERITY_LOW_ARB: return StrLit("DEBUG_SEVERITY_LOW_ARB");
#endif
#if defined GL_DONT_CARE
	case GL_DONT_CARE: return StrLit("DONT_CARE");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#endif

