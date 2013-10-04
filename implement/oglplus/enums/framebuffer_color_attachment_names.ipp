/*
 *  .file oglplus/enums/framebuffer_color_attachment_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/framebuffer_color_attachment.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	FramebufferColorAttachment*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_FRAMEBUFFERCOLORATTACHMENT)
#define OGLPLUS_IMPL_EVN_FRAMEBUFFERCOLORATTACHMENT
{
switch(value)
{
#if defined GL_COLOR_ATTACHMENT0
	case GL_COLOR_ATTACHMENT0: return StrLit("COLOR_ATTACHMENT0");
#endif
#if defined GL_COLOR_ATTACHMENT1
	case GL_COLOR_ATTACHMENT1: return StrLit("COLOR_ATTACHMENT1");
#endif
#if defined GL_COLOR_ATTACHMENT2
	case GL_COLOR_ATTACHMENT2: return StrLit("COLOR_ATTACHMENT2");
#endif
#if defined GL_COLOR_ATTACHMENT3
	case GL_COLOR_ATTACHMENT3: return StrLit("COLOR_ATTACHMENT3");
#endif
#if defined GL_COLOR_ATTACHMENT4
	case GL_COLOR_ATTACHMENT4: return StrLit("COLOR_ATTACHMENT4");
#endif
#if defined GL_COLOR_ATTACHMENT5
	case GL_COLOR_ATTACHMENT5: return StrLit("COLOR_ATTACHMENT5");
#endif
#if defined GL_COLOR_ATTACHMENT6
	case GL_COLOR_ATTACHMENT6: return StrLit("COLOR_ATTACHMENT6");
#endif
#if defined GL_COLOR_ATTACHMENT7
	case GL_COLOR_ATTACHMENT7: return StrLit("COLOR_ATTACHMENT7");
#endif
#if defined GL_COLOR_ATTACHMENT8
	case GL_COLOR_ATTACHMENT8: return StrLit("COLOR_ATTACHMENT8");
#endif
#if defined GL_COLOR_ATTACHMENT9
	case GL_COLOR_ATTACHMENT9: return StrLit("COLOR_ATTACHMENT9");
#endif
#if defined GL_COLOR_ATTACHMENT10
	case GL_COLOR_ATTACHMENT10: return StrLit("COLOR_ATTACHMENT10");
#endif
#if defined GL_COLOR_ATTACHMENT11
	case GL_COLOR_ATTACHMENT11: return StrLit("COLOR_ATTACHMENT11");
#endif
#if defined GL_COLOR_ATTACHMENT12
	case GL_COLOR_ATTACHMENT12: return StrLit("COLOR_ATTACHMENT12");
#endif
#if defined GL_COLOR_ATTACHMENT13
	case GL_COLOR_ATTACHMENT13: return StrLit("COLOR_ATTACHMENT13");
#endif
#if defined GL_COLOR_ATTACHMENT14
	case GL_COLOR_ATTACHMENT14: return StrLit("COLOR_ATTACHMENT14");
#endif
#if defined GL_COLOR_ATTACHMENT15
	case GL_COLOR_ATTACHMENT15: return StrLit("COLOR_ATTACHMENT15");
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

