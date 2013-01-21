/*
 *  .file oglplus/enums/texture_wrap_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_wrap.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	TextureWrap*,
	GLenum value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
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
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#endif

