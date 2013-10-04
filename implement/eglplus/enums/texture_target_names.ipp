/*
 *  .file eglplus/enums/texture_target_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/texture_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	TextureTarget*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_TEXTURETARGET)
#define EGLPLUS_IMPL_EVN_TEXTURETARGET
{
switch(value)
{
#if defined EGL_NO_TEXTURE
	case EGL_NO_TEXTURE: return StrLit("NO_TEXTURE");
#endif
#if defined EGL_TEXTURE_2D
	case EGL_TEXTURE_2D: return StrLit("TEXTURE_2D");
#endif
	default:;
}
EGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

