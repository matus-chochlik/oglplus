/*
 *  .file oglplus/enums/object_type_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/object_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	ObjectType
> EnumValueRange(ObjectType*)
OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
static const GLenum _values[] = {
#if defined GL_BUFFER
GL_BUFFER,
#endif
#if defined GL_FRAMEBUFFER
GL_FRAMEBUFFER,
#endif
#if defined GL_PROGRAM_PIPELINE
GL_PROGRAM_PIPELINE,
#endif
#if defined GL_PROGRAM
GL_PROGRAM,
#endif
#if defined GL_QUERY
GL_QUERY,
#endif
#if defined GL_RENDERBUFFER
GL_RENDERBUFFER,
#endif
#if defined GL_SAMPLER
GL_SAMPLER,
#endif
#if defined GL_SHADER
GL_SHADER,
#endif
#if defined GL_TEXTURE
GL_TEXTURE,
#endif
#if defined GL_TRANSFORM_FEEDBACK
GL_TRANSFORM_FEEDBACK,
#endif
#if defined GL_VERTEX_ARRAY
GL_VERTEX_ARRAY,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	ObjectType
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#endif

