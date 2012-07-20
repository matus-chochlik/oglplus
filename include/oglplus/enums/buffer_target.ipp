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
Uniform,
/// EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD
ExternalVirtualMemory

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_ARRAY_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Array)
#  pragma push_macro("Array")
#  undef Array
   OGLPLUS_ENUM_CLASS_VALUE(Array, GL_ARRAY_BUFFER)
#  pragma pop_macro("Array")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Array, GL_ARRAY_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ATOMIC_COUNTER_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(AtomicCounter)
#  pragma push_macro("AtomicCounter")
#  undef AtomicCounter
   OGLPLUS_ENUM_CLASS_VALUE(AtomicCounter, GL_ATOMIC_COUNTER_BUFFER)
#  pragma pop_macro("AtomicCounter")
# else
   OGLPLUS_ENUM_CLASS_VALUE(AtomicCounter, GL_ATOMIC_COUNTER_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COPY_READ_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(CopyRead)
#  pragma push_macro("CopyRead")
#  undef CopyRead
   OGLPLUS_ENUM_CLASS_VALUE(CopyRead, GL_COPY_READ_BUFFER)
#  pragma pop_macro("CopyRead")
# else
   OGLPLUS_ENUM_CLASS_VALUE(CopyRead, GL_COPY_READ_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COPY_WRITE_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(CopyWrite)
#  pragma push_macro("CopyWrite")
#  undef CopyWrite
   OGLPLUS_ENUM_CLASS_VALUE(CopyWrite, GL_COPY_WRITE_BUFFER)
#  pragma pop_macro("CopyWrite")
# else
   OGLPLUS_ENUM_CLASS_VALUE(CopyWrite, GL_COPY_WRITE_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DRAW_INDIRECT_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DrawIndirect)
#  pragma push_macro("DrawIndirect")
#  undef DrawIndirect
   OGLPLUS_ENUM_CLASS_VALUE(DrawIndirect, GL_DRAW_INDIRECT_BUFFER)
#  pragma pop_macro("DrawIndirect")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DrawIndirect, GL_DRAW_INDIRECT_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ELEMENT_ARRAY_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ElementArray)
#  pragma push_macro("ElementArray")
#  undef ElementArray
   OGLPLUS_ENUM_CLASS_VALUE(ElementArray, GL_ELEMENT_ARRAY_BUFFER)
#  pragma pop_macro("ElementArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ElementArray, GL_ELEMENT_ARRAY_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PIXEL_PACK_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(PixelPack)
#  pragma push_macro("PixelPack")
#  undef PixelPack
   OGLPLUS_ENUM_CLASS_VALUE(PixelPack, GL_PIXEL_PACK_BUFFER)
#  pragma pop_macro("PixelPack")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PixelPack, GL_PIXEL_PACK_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PIXEL_UNPACK_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(PixelUnpack)
#  pragma push_macro("PixelUnpack")
#  undef PixelUnpack
   OGLPLUS_ENUM_CLASS_VALUE(PixelUnpack, GL_PIXEL_UNPACK_BUFFER)
#  pragma pop_macro("PixelUnpack")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PixelUnpack, GL_PIXEL_UNPACK_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TEXTURE_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(TextureBuffer)
#  pragma push_macro("TextureBuffer")
#  undef TextureBuffer
   OGLPLUS_ENUM_CLASS_VALUE(TextureBuffer, GL_TEXTURE_BUFFER)
#  pragma pop_macro("TextureBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TextureBuffer, GL_TEXTURE_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(TransformFeedback)
#  pragma push_macro("TransformFeedback")
#  undef TransformFeedback
   OGLPLUS_ENUM_CLASS_VALUE(TransformFeedback, GL_TRANSFORM_FEEDBACK_BUFFER)
#  pragma pop_macro("TransformFeedback")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TransformFeedback, GL_TRANSFORM_FEEDBACK_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNIFORM_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Uniform)
#  pragma push_macro("Uniform")
#  undef Uniform
   OGLPLUS_ENUM_CLASS_VALUE(Uniform, GL_UNIFORM_BUFFER)
#  pragma pop_macro("Uniform")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Uniform, GL_UNIFORM_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ExternalVirtualMemory)
#  pragma push_macro("ExternalVirtualMemory")
#  undef ExternalVirtualMemory
   OGLPLUS_ENUM_CLASS_VALUE(ExternalVirtualMemory, GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD)
#  pragma pop_macro("ExternalVirtualMemory")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ExternalVirtualMemory, GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

