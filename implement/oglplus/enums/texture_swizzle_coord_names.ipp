/*
 *  .file oglplus/enums/texture_swizzle_coord_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_swizzle_coord.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	TextureSwizzleCoord*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_TEXTURESWIZZLECOORD)
#define OGLPLUS_IMPL_EVN_TEXTURESWIZZLECOORD
{
switch(value)
{
#if defined GL_TEXTURE_SWIZZLE_R
	case GL_TEXTURE_SWIZZLE_R: return StrLit("TEXTURE_SWIZZLE_R");
#endif
#if defined GL_TEXTURE_SWIZZLE_G
	case GL_TEXTURE_SWIZZLE_G: return StrLit("TEXTURE_SWIZZLE_G");
#endif
#if defined GL_TEXTURE_SWIZZLE_B
	case GL_TEXTURE_SWIZZLE_B: return StrLit("TEXTURE_SWIZZLE_B");
#endif
#if defined GL_TEXTURE_SWIZZLE_A
	case GL_TEXTURE_SWIZZLE_A: return StrLit("TEXTURE_SWIZZLE_A");
#endif
#if defined GL_TEXTURE_SWIZZLE_RGBA
	case GL_TEXTURE_SWIZZLE_RGBA: return StrLit("TEXTURE_SWIZZLE_RGBA");
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

