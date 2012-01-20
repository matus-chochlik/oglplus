/*
 *  .file oglplus/enums/buffer_target.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/buffer_target.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// ARRAY_BUFFER
Array,
/// ATOMIC_COUNTER_BUFFER
AtomicCounter,
/// COPY_READ_BUFFER
CopyRead,
/// COPY_WRITE_BUFFER
CopyWrite,
/// DRAW_INDIRECT_BUFFER
DrawIndirect,
/// ELEMENT_ARRAY_BUFFER
ElementArray,
/// PIXEL_PACK_BUFFER
PixelPack,
/// PIXEL_UNPACK_BUFFER
PixelUnpack,
/// TEXTURE_BUFFER
TextureBuffer,
/// TRANSFORM_FEEDBACK_BUFFER
TransformFeedback,
/// UNIFORM_BUFFER
Uniform

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_ARRAY_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Array = GL_ARRAY_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ATOMIC_COUNTER_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
AtomicCounter = GL_ATOMIC_COUNTER_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COPY_READ_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
CopyRead = GL_COPY_READ_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COPY_WRITE_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
CopyWrite = GL_COPY_WRITE_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DRAW_INDIRECT_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
DrawIndirect = GL_DRAW_INDIRECT_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ELEMENT_ARRAY_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
ElementArray = GL_ELEMENT_ARRAY_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PIXEL_PACK_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
PixelPack = GL_PIXEL_PACK_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PIXEL_UNPACK_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
PixelUnpack = GL_PIXEL_UNPACK_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TEXTURE_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TextureBuffer = GL_TEXTURE_BUFFER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
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

#endif // OGLPLUS_DOCUMENTATION_ONLY

