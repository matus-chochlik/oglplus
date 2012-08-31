/*
 *  .file oglplus/enums/texture_swizzle_coord_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_swizzle_coord.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	TextureSwizzleCoord
> EnumValueRange(TextureSwizzleCoord*)
OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
static const GLenum _values[] = {
#if defined GL_TEXTURE_SWIZZLE_R
GL_TEXTURE_SWIZZLE_R,
#endif
#if defined GL_TEXTURE_SWIZZLE_G
GL_TEXTURE_SWIZZLE_G,
#endif
#if defined GL_TEXTURE_SWIZZLE_B
GL_TEXTURE_SWIZZLE_B,
#endif
#if defined GL_TEXTURE_SWIZZLE_A
GL_TEXTURE_SWIZZLE_A,
#endif
#if defined GL_TEXTURE_SWIZZLE_RGBA
GL_TEXTURE_SWIZZLE_RGBA,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	TextureSwizzleCoord
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#endif

