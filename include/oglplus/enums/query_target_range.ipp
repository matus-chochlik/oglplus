/*
 *  .file oglplus/enums/query_target_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/query_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	QueryTarget
> EnumValueRange(QueryTarget*)
OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
static const GLenum _values[] = {
#if defined GL_TIME_ELAPSED
GL_TIME_ELAPSED,
#endif
#if defined GL_TIMESTAMP
GL_TIMESTAMP,
#endif
#if defined GL_SAMPLES_PASSED
GL_SAMPLES_PASSED,
#endif
#if defined GL_ANY_SAMPLES_PASSED
GL_ANY_SAMPLES_PASSED,
#endif
#if defined GL_PRIMITIVES_GENERATED
GL_PRIMITIVES_GENERATED,
#endif
#if defined GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	QueryTarget
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#endif

