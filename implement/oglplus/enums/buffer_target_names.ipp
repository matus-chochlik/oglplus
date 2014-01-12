/*
 *  .file oglplus/enums/buffer_target_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/buffer_target.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	BufferTarget*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_BUFFERTARGET)
#define OGLPLUS_IMPL_EVN_BUFFERTARGET
{
switch(value)
{
#if defined GL_ARRAY_BUFFER
	case GL_ARRAY_BUFFER: return StrLit("ARRAY_BUFFER");
#endif
#if defined GL_ATOMIC_COUNTER_BUFFER
	case GL_ATOMIC_COUNTER_BUFFER: return StrLit("ATOMIC_COUNTER_BUFFER");
#endif
#if defined GL_COPY_READ_BUFFER
	case GL_COPY_READ_BUFFER: return StrLit("COPY_READ_BUFFER");
#endif
#if defined GL_COPY_WRITE_BUFFER
	case GL_COPY_WRITE_BUFFER: return StrLit("COPY_WRITE_BUFFER");
#endif
#if defined GL_DISPATCH_INDIRECT_BUFFER
	case GL_DISPATCH_INDIRECT_BUFFER: return StrLit("DISPATCH_INDIRECT_BUFFER");
#endif
#if defined GL_DRAW_INDIRECT_BUFFER
	case GL_DRAW_INDIRECT_BUFFER: return StrLit("DRAW_INDIRECT_BUFFER");
#endif
#if defined GL_ELEMENT_ARRAY_BUFFER
	case GL_ELEMENT_ARRAY_BUFFER: return StrLit("ELEMENT_ARRAY_BUFFER");
#endif
#if defined GL_PIXEL_PACK_BUFFER
	case GL_PIXEL_PACK_BUFFER: return StrLit("PIXEL_PACK_BUFFER");
#endif
#if defined GL_PIXEL_UNPACK_BUFFER
	case GL_PIXEL_UNPACK_BUFFER: return StrLit("PIXEL_UNPACK_BUFFER");
#endif
#if defined GL_SHADER_STORAGE_BUFFER
	case GL_SHADER_STORAGE_BUFFER: return StrLit("SHADER_STORAGE_BUFFER");
#endif
#if defined GL_TEXTURE_BUFFER
	case GL_TEXTURE_BUFFER: return StrLit("TEXTURE_BUFFER");
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER
	case GL_TRANSFORM_FEEDBACK_BUFFER: return StrLit("TRANSFORM_FEEDBACK_BUFFER");
#endif
#if defined GL_UNIFORM_BUFFER
	case GL_UNIFORM_BUFFER: return StrLit("UNIFORM_BUFFER");
#endif
#if defined GL_QUERY_BUFFER
	case GL_QUERY_BUFFER: return StrLit("QUERY_BUFFER");
#endif
#if defined GL_PARAMETER_BUFFER_ARB
	case GL_PARAMETER_BUFFER_ARB: return StrLit("PARAMETER_BUFFER_ARB");
#endif
#if defined GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD
	case GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD: return StrLit("EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD");
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

