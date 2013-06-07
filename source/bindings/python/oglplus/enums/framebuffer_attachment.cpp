/*
 *  .file oglplus/enums/framebuffer_attachment.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/framebuffer_attachment.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/framebuffer.hpp>

#include <boost/python.hpp>

void oglplus_py_framebuffer_attachment(void)
{
	boost::python::enum_<oglplus::FramebufferAttachment>("FramebufferAttachment")
#if defined GL_COLOR_ATTACHMENT0
# if defined Color
#  pragma push_macro("Color")
#  undef Color
	.value("Color", oglplus::FramebufferAttachment::Color)
#  pragma pop_macro("Color")
# else
	.value("Color", oglplus::FramebufferAttachment::Color)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT1
# if defined Color1
#  pragma push_macro("Color1")
#  undef Color1
	.value("Color1", oglplus::FramebufferAttachment::Color1)
#  pragma pop_macro("Color1")
# else
	.value("Color1", oglplus::FramebufferAttachment::Color1)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT2
# if defined Color2
#  pragma push_macro("Color2")
#  undef Color2
	.value("Color2", oglplus::FramebufferAttachment::Color2)
#  pragma pop_macro("Color2")
# else
	.value("Color2", oglplus::FramebufferAttachment::Color2)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT3
# if defined Color3
#  pragma push_macro("Color3")
#  undef Color3
	.value("Color3", oglplus::FramebufferAttachment::Color3)
#  pragma pop_macro("Color3")
# else
	.value("Color3", oglplus::FramebufferAttachment::Color3)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT4
# if defined Color4
#  pragma push_macro("Color4")
#  undef Color4
	.value("Color4", oglplus::FramebufferAttachment::Color4)
#  pragma pop_macro("Color4")
# else
	.value("Color4", oglplus::FramebufferAttachment::Color4)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT5
# if defined Color5
#  pragma push_macro("Color5")
#  undef Color5
	.value("Color5", oglplus::FramebufferAttachment::Color5)
#  pragma pop_macro("Color5")
# else
	.value("Color5", oglplus::FramebufferAttachment::Color5)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT6
# if defined Color6
#  pragma push_macro("Color6")
#  undef Color6
	.value("Color6", oglplus::FramebufferAttachment::Color6)
#  pragma pop_macro("Color6")
# else
	.value("Color6", oglplus::FramebufferAttachment::Color6)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT7
# if defined Color7
#  pragma push_macro("Color7")
#  undef Color7
	.value("Color7", oglplus::FramebufferAttachment::Color7)
#  pragma pop_macro("Color7")
# else
	.value("Color7", oglplus::FramebufferAttachment::Color7)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT8
# if defined Color8
#  pragma push_macro("Color8")
#  undef Color8
	.value("Color8", oglplus::FramebufferAttachment::Color8)
#  pragma pop_macro("Color8")
# else
	.value("Color8", oglplus::FramebufferAttachment::Color8)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT9
# if defined Color9
#  pragma push_macro("Color9")
#  undef Color9
	.value("Color9", oglplus::FramebufferAttachment::Color9)
#  pragma pop_macro("Color9")
# else
	.value("Color9", oglplus::FramebufferAttachment::Color9)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT10
# if defined Color10
#  pragma push_macro("Color10")
#  undef Color10
	.value("Color10", oglplus::FramebufferAttachment::Color10)
#  pragma pop_macro("Color10")
# else
	.value("Color10", oglplus::FramebufferAttachment::Color10)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT11
# if defined Color11
#  pragma push_macro("Color11")
#  undef Color11
	.value("Color11", oglplus::FramebufferAttachment::Color11)
#  pragma pop_macro("Color11")
# else
	.value("Color11", oglplus::FramebufferAttachment::Color11)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT12
# if defined Color12
#  pragma push_macro("Color12")
#  undef Color12
	.value("Color12", oglplus::FramebufferAttachment::Color12)
#  pragma pop_macro("Color12")
# else
	.value("Color12", oglplus::FramebufferAttachment::Color12)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT13
# if defined Color13
#  pragma push_macro("Color13")
#  undef Color13
	.value("Color13", oglplus::FramebufferAttachment::Color13)
#  pragma pop_macro("Color13")
# else
	.value("Color13", oglplus::FramebufferAttachment::Color13)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT14
# if defined Color14
#  pragma push_macro("Color14")
#  undef Color14
	.value("Color14", oglplus::FramebufferAttachment::Color14)
#  pragma pop_macro("Color14")
# else
	.value("Color14", oglplus::FramebufferAttachment::Color14)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT15
# if defined Color15
#  pragma push_macro("Color15")
#  undef Color15
	.value("Color15", oglplus::FramebufferAttachment::Color15)
#  pragma pop_macro("Color15")
# else
	.value("Color15", oglplus::FramebufferAttachment::Color15)
# endif
#endif
#if defined GL_DEPTH_ATTACHMENT
# if defined Depth
#  pragma push_macro("Depth")
#  undef Depth
	.value("Depth", oglplus::FramebufferAttachment::Depth)
#  pragma pop_macro("Depth")
# else
	.value("Depth", oglplus::FramebufferAttachment::Depth)
# endif
#endif
#if defined GL_STENCIL_ATTACHMENT
# if defined Stencil
#  pragma push_macro("Stencil")
#  undef Stencil
	.value("Stencil", oglplus::FramebufferAttachment::Stencil)
#  pragma pop_macro("Stencil")
# else
	.value("Stencil", oglplus::FramebufferAttachment::Stencil)
# endif
#endif
#if defined GL_DEPTH_STENCIL_ATTACHMENT
# if defined DepthStencil
#  pragma push_macro("DepthStencil")
#  undef DepthStencil
	.value("DepthStencil", oglplus::FramebufferAttachment::DepthStencil)
#  pragma pop_macro("DepthStencil")
# else
	.value("DepthStencil", oglplus::FramebufferAttachment::DepthStencil)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::FramebufferAttachment) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
