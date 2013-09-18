/*
 *  .file oglplus/enums/debug_output_severity_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/debug_output_severity.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	DebugOutputSeverity*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_DEBUGOUTPUTSEVERITY)
#define OGLPLUS_IMPL_EVN_DEBUGOUTPUTSEVERITY
{
switch(value)
{
#if defined GL_DEBUG_SEVERITY_HIGH
	case GL_DEBUG_SEVERITY_HIGH: return StrLit("DEBUG_SEVERITY_HIGH");
#endif
#if defined GL_DEBUG_SEVERITY_MEDIUM
	case GL_DEBUG_SEVERITY_MEDIUM: return StrLit("DEBUG_SEVERITY_MEDIUM");
#endif
#if defined GL_DEBUG_SEVERITY_LOW
	case GL_DEBUG_SEVERITY_LOW: return StrLit("DEBUG_SEVERITY_LOW");
#endif
#if defined GL_DEBUG_SEVERITY_NOTIFICATION
	case GL_DEBUG_SEVERITY_NOTIFICATION: return StrLit("DEBUG_SEVERITY_NOTIFICATION");
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

