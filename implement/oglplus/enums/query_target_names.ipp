/*
 *  .file oglplus/enums/query_target_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/query_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	QueryTarget*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_QUERYTARGET)
#define OGLPLUS_IMPL_EVN_QUERYTARGET
{
switch(value)
{
#if defined GL_TIME_ELAPSED
	case GL_TIME_ELAPSED: return StrLit("TIME_ELAPSED");
#endif
#if defined GL_TIMESTAMP
	case GL_TIMESTAMP: return StrLit("TIMESTAMP");
#endif
#if defined GL_SAMPLES_PASSED
	case GL_SAMPLES_PASSED: return StrLit("SAMPLES_PASSED");
#endif
#if defined GL_ANY_SAMPLES_PASSED
	case GL_ANY_SAMPLES_PASSED: return StrLit("ANY_SAMPLES_PASSED");
#endif
#if defined GL_PRIMITIVES_GENERATED
	case GL_PRIMITIVES_GENERATED: return StrLit("PRIMITIVES_GENERATED");
#endif
#if defined GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
	case GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN: return StrLit("TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN");
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

