/*
 *  .file oglplus/enums/framebuffer_target_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/framebuffer_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	FramebufferTarget*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_FRAMEBUFFERTARGET)
#define OGLPLUS_IMPL_EVN_FRAMEBUFFERTARGET
{
switch(value)
{
#if defined GL_DRAW_FRAMEBUFFER
	case GL_DRAW_FRAMEBUFFER: return StrLit("DRAW_FRAMEBUFFER");
#endif
#if defined GL_READ_FRAMEBUFFER
	case GL_READ_FRAMEBUFFER: return StrLit("READ_FRAMEBUFFER");
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

