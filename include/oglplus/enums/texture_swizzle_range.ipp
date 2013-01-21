/*
 *  .file oglplus/enums/texture_swizzle_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_swizzle.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	TextureSwizzle
> EnumValueRange(TextureSwizzle*)
OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
static const GLenum _values[] = {
#if defined GL_RED
GL_RED,
#endif
#if defined GL_GREEN
GL_GREEN,
#endif
#if defined GL_BLUE
GL_BLUE,
#endif
#if defined GL_ALPHA
GL_ALPHA,
#endif
#if defined GL_ZERO
GL_ZERO,
#endif
#if defined GL_ONE
GL_ONE,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	TextureSwizzle
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#endif

