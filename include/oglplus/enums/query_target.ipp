/*
 *  .file oglplus/enums/query_target.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/query_target.txt' instead.
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// TIME_ELAPSED: Time elapsed query
TimeElapsed,
/// TIMESTAMP: Current timestamp query
Timestamp,
/// SAMPLES_PASSED: Number of samples passed query
SamplesPassed,
/// ANY_SAMPLES_PASSED
AnySamplesPassed,
/// PRIMITIVED_GENERATED: Number of primitives generated
PrimitivedGenerated,
/// TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN: TFB primitives written
TransformFeedbackPrimitivesWritten

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_TIME_ELAPSED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TimeElapsed = GL_TIME_ELAPSED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TIMESTAMP
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Timestamp = GL_TIMESTAMP
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLES_PASSED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
SamplesPassed = GL_SAMPLES_PASSED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ANY_SAMPLES_PASSED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
AnySamplesPassed = GL_ANY_SAMPLES_PASSED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PRIMITIVED_GENERATED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
PrimitivedGenerated = GL_PRIMITIVED_GENERATED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TransformFeedbackPrimitivesWritten = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

