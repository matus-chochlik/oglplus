/*
 *  .file oglplus/enums/buffer_usage.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/buffer_usage.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
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

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_STREAM_DRAW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(StreamDraw)
#  pragma push_macro("StreamDraw")
#  undef StreamDraw
   OGLPLUS_ENUM_CLASS_VALUE(StreamDraw, GL_STREAM_DRAW)
#  pragma pop_macro("StreamDraw")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StreamDraw, GL_STREAM_DRAW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STREAM_READ
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(StreamRead)
#  pragma push_macro("StreamRead")
#  undef StreamRead
   OGLPLUS_ENUM_CLASS_VALUE(StreamRead, GL_STREAM_READ)
#  pragma pop_macro("StreamRead")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StreamRead, GL_STREAM_READ)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STREAM_COPY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(StreamCopy)
#  pragma push_macro("StreamCopy")
#  undef StreamCopy
   OGLPLUS_ENUM_CLASS_VALUE(StreamCopy, GL_STREAM_COPY)
#  pragma pop_macro("StreamCopy")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StreamCopy, GL_STREAM_COPY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STATIC_DRAW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(StaticDraw)
#  pragma push_macro("StaticDraw")
#  undef StaticDraw
   OGLPLUS_ENUM_CLASS_VALUE(StaticDraw, GL_STATIC_DRAW)
#  pragma pop_macro("StaticDraw")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StaticDraw, GL_STATIC_DRAW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STATIC_READ
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(StaticRead)
#  pragma push_macro("StaticRead")
#  undef StaticRead
   OGLPLUS_ENUM_CLASS_VALUE(StaticRead, GL_STATIC_READ)
#  pragma pop_macro("StaticRead")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StaticRead, GL_STATIC_READ)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STATIC_COPY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(StaticCopy)
#  pragma push_macro("StaticCopy")
#  undef StaticCopy
   OGLPLUS_ENUM_CLASS_VALUE(StaticCopy, GL_STATIC_COPY)
#  pragma pop_macro("StaticCopy")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StaticCopy, GL_STATIC_COPY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DYNAMIC_DRAW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DynamicDraw)
#  pragma push_macro("DynamicDraw")
#  undef DynamicDraw
   OGLPLUS_ENUM_CLASS_VALUE(DynamicDraw, GL_DYNAMIC_DRAW)
#  pragma pop_macro("DynamicDraw")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DynamicDraw, GL_DYNAMIC_DRAW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DYNAMIC_READ
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DynamicRead)
#  pragma push_macro("DynamicRead")
#  undef DynamicRead
   OGLPLUS_ENUM_CLASS_VALUE(DynamicRead, GL_DYNAMIC_READ)
#  pragma pop_macro("DynamicRead")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DynamicRead, GL_DYNAMIC_READ)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DYNAMIC_COPY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DynamicCopy)
#  pragma push_macro("DynamicCopy")
#  undef DynamicCopy
   OGLPLUS_ENUM_CLASS_VALUE(DynamicCopy, GL_DYNAMIC_COPY)
#  pragma pop_macro("DynamicCopy")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DynamicCopy, GL_DYNAMIC_COPY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

