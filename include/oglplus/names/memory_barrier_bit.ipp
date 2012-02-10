/*
 *  .file oglplus/names/memory_barrier_bit.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/memory_barrier_bit.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT
	case GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT: return "VERTEX_ATTRIB_ARRAY_BARRIER_BIT";
#endif
#if defined GL_ELEMENT_ARRAY_BARRIER_BIT
	case GL_ELEMENT_ARRAY_BARRIER_BIT: return "ELEMENT_ARRAY_BARRIER_BIT";
#endif
#if defined GL_UNIFORM_BARRIER_BIT
	case GL_UNIFORM_BARRIER_BIT: return "UNIFORM_BARRIER_BIT";
#endif
#if defined GL_TEXTURE_FETCH_BARRIER_BIT
	case GL_TEXTURE_FETCH_BARRIER_BIT: return "TEXTURE_FETCH_BARRIER_BIT";
#endif
#if defined GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
	case GL_SHADER_IMAGE_ACCESS_BARRIER_BIT: return "SHADER_IMAGE_ACCESS_BARRIER_BIT";
#endif
#if defined GL_COMMAND_BARRIER_BIT
	case GL_COMMAND_BARRIER_BIT: return "COMMAND_BARRIER_BIT";
#endif
#if defined GL_PIXEL_BUFFER_BARRIER_BIT
	case GL_PIXEL_BUFFER_BARRIER_BIT: return "PIXEL_BUFFER_BARRIER_BIT";
#endif
#if defined GL_TEXTURE_UPDATE_BARRIER_BIT
	case GL_TEXTURE_UPDATE_BARRIER_BIT: return "TEXTURE_UPDATE_BARRIER_BIT";
#endif
#if defined GL_BUFFER_UPDATE_BARRIER_BIT
	case GL_BUFFER_UPDATE_BARRIER_BIT: return "BUFFER_UPDATE_BARRIER_BIT";
#endif
#if defined GL_FRAMEBUFFER_BARRIER_BIT
	case GL_FRAMEBUFFER_BARRIER_BIT: return "FRAMEBUFFER_BARRIER_BIT";
#endif
#if defined GL_TRANSFORM_FEEDBACK_BARRIER_BIT
	case GL_TRANSFORM_FEEDBACK_BARRIER_BIT: return "TRANSFORM_FEEDBACK_BARRIER_BIT";
#endif
#if defined GL_ATOMIC_COUNTER_BARRIER_BIT
	case GL_ATOMIC_COUNTER_BARRIER_BIT: return "ATOMIC_COUNTER_BARRIER_BIT";
#endif
#if defined GL_ALL_BARRIER_BITS
	case GL_ALL_BARRIER_BITS: return "ALL_BARRIER_BITS";
#endif
	default:;
}

