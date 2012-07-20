/*
 *  .file oglplus/enums/memory_barrier_bit.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/memory_barrier_bit.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// VERTEX_ATTRIB_ARRAY_BARRIER_BIT
VertexAttribArray,
/// ELEMENT_ARRAY_BARRIER_BIT
ElementArray,
/// UNIFORM_BARRIER_BIT
Uniform,
/// TEXTURE_FETCH_BARRIER_BIT
TextureFetch,
/// SHADER_IMAGE_ACCESS_BARRIER_BIT
ShaderImageAccess,
/// COMMAND_BARRIER_BIT
Command,
/// PIXEL_BUFFER_BARRIER_BIT
PixelBuffer,
/// TEXTURE_UPDATE_BARRIER_BIT
TextureUpdate,
/// BUFFER_UPDATE_BARRIER_BIT
BufferUpdate,
/// FRAMEBUFFER_BARRIER_BIT
Framebuffer,
/// TRANSFORM_FEEDBACK_BARRIER_BIT
TransformFeedback,
/// ATOMIC_COUNTER_BARRIER_BIT
AtomicCounter,
/// ALL_BARRIER_BITS
All

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(VertexAttribArray)
#  pragma push_macro("VertexAttribArray")
#  undef VertexAttribArray
   OGLPLUS_ENUM_CLASS_VALUE(VertexAttribArray, GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT)
#  pragma pop_macro("VertexAttribArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(VertexAttribArray, GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ELEMENT_ARRAY_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ElementArray)
#  pragma push_macro("ElementArray")
#  undef ElementArray
   OGLPLUS_ENUM_CLASS_VALUE(ElementArray, GL_ELEMENT_ARRAY_BARRIER_BIT)
#  pragma pop_macro("ElementArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ElementArray, GL_ELEMENT_ARRAY_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNIFORM_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Uniform)
#  pragma push_macro("Uniform")
#  undef Uniform
   OGLPLUS_ENUM_CLASS_VALUE(Uniform, GL_UNIFORM_BARRIER_BIT)
#  pragma pop_macro("Uniform")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Uniform, GL_UNIFORM_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TEXTURE_FETCH_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(TextureFetch)
#  pragma push_macro("TextureFetch")
#  undef TextureFetch
   OGLPLUS_ENUM_CLASS_VALUE(TextureFetch, GL_TEXTURE_FETCH_BARRIER_BIT)
#  pragma pop_macro("TextureFetch")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TextureFetch, GL_TEXTURE_FETCH_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ShaderImageAccess)
#  pragma push_macro("ShaderImageAccess")
#  undef ShaderImageAccess
   OGLPLUS_ENUM_CLASS_VALUE(ShaderImageAccess, GL_SHADER_IMAGE_ACCESS_BARRIER_BIT)
#  pragma pop_macro("ShaderImageAccess")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ShaderImageAccess, GL_SHADER_IMAGE_ACCESS_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COMMAND_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Command)
#  pragma push_macro("Command")
#  undef Command
   OGLPLUS_ENUM_CLASS_VALUE(Command, GL_COMMAND_BARRIER_BIT)
#  pragma pop_macro("Command")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Command, GL_COMMAND_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PIXEL_BUFFER_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(PixelBuffer)
#  pragma push_macro("PixelBuffer")
#  undef PixelBuffer
   OGLPLUS_ENUM_CLASS_VALUE(PixelBuffer, GL_PIXEL_BUFFER_BARRIER_BIT)
#  pragma pop_macro("PixelBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PixelBuffer, GL_PIXEL_BUFFER_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TEXTURE_UPDATE_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(TextureUpdate)
#  pragma push_macro("TextureUpdate")
#  undef TextureUpdate
   OGLPLUS_ENUM_CLASS_VALUE(TextureUpdate, GL_TEXTURE_UPDATE_BARRIER_BIT)
#  pragma pop_macro("TextureUpdate")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TextureUpdate, GL_TEXTURE_UPDATE_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BUFFER_UPDATE_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(BufferUpdate)
#  pragma push_macro("BufferUpdate")
#  undef BufferUpdate
   OGLPLUS_ENUM_CLASS_VALUE(BufferUpdate, GL_BUFFER_UPDATE_BARRIER_BIT)
#  pragma pop_macro("BufferUpdate")
# else
   OGLPLUS_ENUM_CLASS_VALUE(BufferUpdate, GL_BUFFER_UPDATE_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Framebuffer)
#  pragma push_macro("Framebuffer")
#  undef Framebuffer
   OGLPLUS_ENUM_CLASS_VALUE(Framebuffer, GL_FRAMEBUFFER_BARRIER_BIT)
#  pragma pop_macro("Framebuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Framebuffer, GL_FRAMEBUFFER_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(TransformFeedback)
#  pragma push_macro("TransformFeedback")
#  undef TransformFeedback
   OGLPLUS_ENUM_CLASS_VALUE(TransformFeedback, GL_TRANSFORM_FEEDBACK_BARRIER_BIT)
#  pragma pop_macro("TransformFeedback")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TransformFeedback, GL_TRANSFORM_FEEDBACK_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ATOMIC_COUNTER_BARRIER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(AtomicCounter)
#  pragma push_macro("AtomicCounter")
#  undef AtomicCounter
   OGLPLUS_ENUM_CLASS_VALUE(AtomicCounter, GL_ATOMIC_COUNTER_BARRIER_BIT)
#  pragma pop_macro("AtomicCounter")
# else
   OGLPLUS_ENUM_CLASS_VALUE(AtomicCounter, GL_ATOMIC_COUNTER_BARRIER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ALL_BARRIER_BITS
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(All)
#  pragma push_macro("All")
#  undef All
   OGLPLUS_ENUM_CLASS_VALUE(All, GL_ALL_BARRIER_BITS)
#  pragma pop_macro("All")
# else
   OGLPLUS_ENUM_CLASS_VALUE(All, GL_ALL_BARRIER_BITS)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

