/*
 *  .file oglplus/enums/framebuffer_color_attachment.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/framebuffer_color_attachment.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/framebuffer.hpp>

#include <boost/python.hpp>

void oglplus_py_framebuffer_color_attachment(void)
{
	boost::python::enum_<oglplus::FramebufferColorAttachment>("FramebufferColorAttachment")
#if defined GL_COLOR_ATTACHMENT0
# if defined _0
#  pragma push_macro("_0")
#  undef _0
	.value("_0", oglplus::FramebufferColorAttachment::_0)
#  pragma pop_macro("_0")
# else
	.value("_0", oglplus::FramebufferColorAttachment::_0)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT1
# if defined _1
#  pragma push_macro("_1")
#  undef _1
	.value("_1", oglplus::FramebufferColorAttachment::_1)
#  pragma pop_macro("_1")
# else
	.value("_1", oglplus::FramebufferColorAttachment::_1)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT2
# if defined _2
#  pragma push_macro("_2")
#  undef _2
	.value("_2", oglplus::FramebufferColorAttachment::_2)
#  pragma pop_macro("_2")
# else
	.value("_2", oglplus::FramebufferColorAttachment::_2)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT3
# if defined _3
#  pragma push_macro("_3")
#  undef _3
	.value("_3", oglplus::FramebufferColorAttachment::_3)
#  pragma pop_macro("_3")
# else
	.value("_3", oglplus::FramebufferColorAttachment::_3)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT4
# if defined _4
#  pragma push_macro("_4")
#  undef _4
	.value("_4", oglplus::FramebufferColorAttachment::_4)
#  pragma pop_macro("_4")
# else
	.value("_4", oglplus::FramebufferColorAttachment::_4)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT5
# if defined _5
#  pragma push_macro("_5")
#  undef _5
	.value("_5", oglplus::FramebufferColorAttachment::_5)
#  pragma pop_macro("_5")
# else
	.value("_5", oglplus::FramebufferColorAttachment::_5)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT6
# if defined _6
#  pragma push_macro("_6")
#  undef _6
	.value("_6", oglplus::FramebufferColorAttachment::_6)
#  pragma pop_macro("_6")
# else
	.value("_6", oglplus::FramebufferColorAttachment::_6)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT7
# if defined _7
#  pragma push_macro("_7")
#  undef _7
	.value("_7", oglplus::FramebufferColorAttachment::_7)
#  pragma pop_macro("_7")
# else
	.value("_7", oglplus::FramebufferColorAttachment::_7)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT8
# if defined _8
#  pragma push_macro("_8")
#  undef _8
	.value("_8", oglplus::FramebufferColorAttachment::_8)
#  pragma pop_macro("_8")
# else
	.value("_8", oglplus::FramebufferColorAttachment::_8)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT9
# if defined _9
#  pragma push_macro("_9")
#  undef _9
	.value("_9", oglplus::FramebufferColorAttachment::_9)
#  pragma pop_macro("_9")
# else
	.value("_9", oglplus::FramebufferColorAttachment::_9)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT10
# if defined _10
#  pragma push_macro("_10")
#  undef _10
	.value("_10", oglplus::FramebufferColorAttachment::_10)
#  pragma pop_macro("_10")
# else
	.value("_10", oglplus::FramebufferColorAttachment::_10)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT11
# if defined _11
#  pragma push_macro("_11")
#  undef _11
	.value("_11", oglplus::FramebufferColorAttachment::_11)
#  pragma pop_macro("_11")
# else
	.value("_11", oglplus::FramebufferColorAttachment::_11)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT12
# if defined _12
#  pragma push_macro("_12")
#  undef _12
	.value("_12", oglplus::FramebufferColorAttachment::_12)
#  pragma pop_macro("_12")
# else
	.value("_12", oglplus::FramebufferColorAttachment::_12)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT13
# if defined _13
#  pragma push_macro("_13")
#  undef _13
	.value("_13", oglplus::FramebufferColorAttachment::_13)
#  pragma pop_macro("_13")
# else
	.value("_13", oglplus::FramebufferColorAttachment::_13)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT14
# if defined _14
#  pragma push_macro("_14")
#  undef _14
	.value("_14", oglplus::FramebufferColorAttachment::_14)
#  pragma pop_macro("_14")
# else
	.value("_14", oglplus::FramebufferColorAttachment::_14)
# endif
#endif
#if defined GL_COLOR_ATTACHMENT15
# if defined _15
#  pragma push_macro("_15")
#  undef _15
	.value("_15", oglplus::FramebufferColorAttachment::_15)
#  pragma pop_macro("_15")
# else
	.value("_15", oglplus::FramebufferColorAttachment::_15)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::FramebufferColorAttachment) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
