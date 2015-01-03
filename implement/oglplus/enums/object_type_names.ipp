//  File implement/oglplus/enums/object_type_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/object_type.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	ObjectType*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_OBJECTTYPE)
#define OGLPLUS_IMPL_EVN_OBJECTTYPE
{
switch(value)
{
#if defined GL_BUFFER
	case GL_BUFFER: return CStrRef("BUFFER");
#endif
#if defined GL_FRAMEBUFFER
	case GL_FRAMEBUFFER: return CStrRef("FRAMEBUFFER");
#endif
#if defined GL_PROGRAM_PIPELINE
	case GL_PROGRAM_PIPELINE: return CStrRef("PROGRAM_PIPELINE");
#endif
#if defined GL_PROGRAM
	case GL_PROGRAM: return CStrRef("PROGRAM");
#endif
#if defined GL_QUERY
	case GL_QUERY: return CStrRef("QUERY");
#endif
#if defined GL_RENDERBUFFER
	case GL_RENDERBUFFER: return CStrRef("RENDERBUFFER");
#endif
#if defined GL_SAMPLER
	case GL_SAMPLER: return CStrRef("SAMPLER");
#endif
#if defined GL_SHADER
	case GL_SHADER: return CStrRef("SHADER");
#endif
#if defined GL_TEXTURE
	case GL_TEXTURE: return CStrRef("TEXTURE");
#endif
#if defined GL_TRANSFORM_FEEDBACK
	case GL_TRANSFORM_FEEDBACK: return CStrRef("TRANSFORM_FEEDBACK");
#endif
#if defined GL_VERTEX_ARRAY
	case GL_VERTEX_ARRAY: return CStrRef("VERTEX_ARRAY");
#endif
#if defined GL_NONE
	case GL_NONE: return CStrRef("NONE");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

