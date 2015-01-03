//  File implement/oglplus/enums/texture_min_filter_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/texture_min_filter.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	TextureMinFilter*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_TEXTUREMINFILTER)
#define OGLPLUS_IMPL_EVN_TEXTUREMINFILTER
{
switch(value)
{
#if defined GL_NEAREST
	case GL_NEAREST: return CStrRef("NEAREST");
#endif
#if defined GL_LINEAR
	case GL_LINEAR: return CStrRef("LINEAR");
#endif
#if defined GL_NEAREST_MIPMAP_NEAREST
	case GL_NEAREST_MIPMAP_NEAREST: return CStrRef("NEAREST_MIPMAP_NEAREST");
#endif
#if defined GL_NEAREST_MIPMAP_LINEAR
	case GL_NEAREST_MIPMAP_LINEAR: return CStrRef("NEAREST_MIPMAP_LINEAR");
#endif
#if defined GL_LINEAR_MIPMAP_NEAREST
	case GL_LINEAR_MIPMAP_NEAREST: return CStrRef("LINEAR_MIPMAP_NEAREST");
#endif
#if defined GL_LINEAR_MIPMAP_LINEAR
	case GL_LINEAR_MIPMAP_LINEAR: return CStrRef("LINEAR_MIPMAP_LINEAR");
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

