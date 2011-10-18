/*
 *  .file oglplus/enums/buffer_usage.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/buffer_usage.txt' instead.
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// STREAM_DRAW
StreamDraw,
/// STREAM_READ
StreamRead,
/// STREAM_COPY
StreamCopy,
/// STATIC_DRAW
StaticDraw,
/// STATIC_READ
StaticRead,
/// STATIC_COPY
StaticCopy,
/// DYNAMIC_DRAW
DynamicDraw,
/// DYNAMIC_READ
DynamicRead,
/// DYNAMIC_COPY
DynamicCopy

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_STREAM_DRAW
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
StreamDraw = GL_STREAM_DRAW
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STREAM_READ
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
StreamRead = GL_STREAM_READ
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STREAM_COPY
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
StreamCopy = GL_STREAM_COPY
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STATIC_DRAW
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
StaticDraw = GL_STATIC_DRAW
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STATIC_READ
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
StaticRead = GL_STATIC_READ
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STATIC_COPY
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
StaticCopy = GL_STATIC_COPY
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DYNAMIC_DRAW
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
DynamicDraw = GL_DYNAMIC_DRAW
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DYNAMIC_READ
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
DynamicRead = GL_DYNAMIC_READ
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DYNAMIC_COPY
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
DynamicCopy = GL_DYNAMIC_COPY
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

