/*
 *  .file oglplus/enums/buffer_indexed_target.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/buffer_indexed_target.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// TRANSFORM_FEEDBACK_BUFFER
TransformFeedback,
/// UNIFORM_BUFFER
Uniform

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_TRANSFORM_FEEDBACK_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNIFORM_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Uniform = GL_UNIFORM_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

