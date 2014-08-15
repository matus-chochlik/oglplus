/*
 *  .file oglplus/enums/ext/debug_output_severity_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/debug_output_severity.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	DebugOutputARBSeverity
> ValueRange_(DebugOutputARBSeverity*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_DEBUGOUTPUTARBSEVERITY)
#define OGLPLUS_IMPL_EVR_DEBUGOUTPUTARBSEVERITY
{
static const GLenum _values[] = {
#if defined GL_DEBUG_SEVERITY_HIGH_ARB
GL_DEBUG_SEVERITY_HIGH_ARB,
#endif
#if defined GL_DEBUG_SEVERITY_MEDIUM_ARB
GL_DEBUG_SEVERITY_MEDIUM_ARB,
#endif
#if defined GL_DEBUG_SEVERITY_LOW_ARB
GL_DEBUG_SEVERITY_LOW_ARB,
#endif
#if defined GL_DONT_CARE
GL_DONT_CARE,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	DebugOutputARBSeverity
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

