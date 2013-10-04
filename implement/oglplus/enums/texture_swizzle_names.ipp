/*
 *  .file oglplus/enums/texture_swizzle_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_swizzle.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	TextureSwizzle*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_TEXTURESWIZZLE)
#define OGLPLUS_IMPL_EVN_TEXTURESWIZZLE
{
switch(value)
{
#if defined GL_RED
	case GL_RED: return StrLit("RED");
#endif
#if defined GL_GREEN
	case GL_GREEN: return StrLit("GREEN");
#endif
#if defined GL_BLUE
	case GL_BLUE: return StrLit("BLUE");
#endif
#if defined GL_ALPHA
	case GL_ALPHA: return StrLit("ALPHA");
#endif
#if defined GL_ZERO
	case GL_ZERO: return StrLit("ZERO");
#endif
#if defined GL_ONE
	case GL_ONE: return StrLit("ONE");
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

