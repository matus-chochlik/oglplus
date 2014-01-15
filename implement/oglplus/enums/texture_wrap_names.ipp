/*
 *  .file oglplus/enums/texture_wrap_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_wrap.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	TextureWrap*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_TEXTUREWRAP)
#define OGLPLUS_IMPL_EVN_TEXTUREWRAP
{
switch(value)
{
#if defined GL_CLAMP_TO_EDGE
	case GL_CLAMP_TO_EDGE: return StrLit("CLAMP_TO_EDGE");
#endif
#if defined GL_REPEAT
	case GL_REPEAT: return StrLit("REPEAT");
#endif
#if defined GL_CLAMP_TO_BORDER
	case GL_CLAMP_TO_BORDER: return StrLit("CLAMP_TO_BORDER");
#endif
#if defined GL_MIRRORED_REPEAT
	case GL_MIRRORED_REPEAT: return StrLit("MIRRORED_REPEAT");
#endif
#if defined GL_MIRROR_CLAMP_TO_EDGE
	case GL_MIRROR_CLAMP_TO_EDGE: return StrLit("MIRROR_CLAMP_TO_EDGE");
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

