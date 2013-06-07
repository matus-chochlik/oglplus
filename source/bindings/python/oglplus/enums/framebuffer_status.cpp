/*
 *  .file oglplus/enums/framebuffer_status.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/framebuffer_status.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/framebuffer.hpp>

#include <boost/python.hpp>

void oglplus_py_framebuffer_status(void)
{
	boost::python::enum_<oglplus::FramebufferStatus>("FramebufferStatus")
#if defined GL_FRAMEBUFFER_COMPLETE
# if defined Complete
#  pragma push_macro("Complete")
#  undef Complete
	.value("Complete", oglplus::FramebufferStatus::Complete)
#  pragma pop_macro("Complete")
# else
	.value("Complete", oglplus::FramebufferStatus::Complete)
# endif
#endif
#if defined GL_FRAMEBUFFER_UNDEFINED
# if defined Undefined
#  pragma push_macro("Undefined")
#  undef Undefined
	.value("Undefined", oglplus::FramebufferStatus::Undefined)
#  pragma pop_macro("Undefined")
# else
	.value("Undefined", oglplus::FramebufferStatus::Undefined)
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
# if defined IncompleteAttachment
#  pragma push_macro("IncompleteAttachment")
#  undef IncompleteAttachment
	.value("IncompleteAttachment", oglplus::FramebufferStatus::IncompleteAttachment)
#  pragma pop_macro("IncompleteAttachment")
# else
	.value("IncompleteAttachment", oglplus::FramebufferStatus::IncompleteAttachment)
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
# if defined IncompleteMissingAttachment
#  pragma push_macro("IncompleteMissingAttachment")
#  undef IncompleteMissingAttachment
	.value("IncompleteMissingAttachment", oglplus::FramebufferStatus::IncompleteMissingAttachment)
#  pragma pop_macro("IncompleteMissingAttachment")
# else
	.value("IncompleteMissingAttachment", oglplus::FramebufferStatus::IncompleteMissingAttachment)
# endif
#endif
#if defined GL_FRAMEBUFFER_UNSUPPORTED
# if defined Unsupported
#  pragma push_macro("Unsupported")
#  undef Unsupported
	.value("Unsupported", oglplus::FramebufferStatus::Unsupported)
#  pragma pop_macro("Unsupported")
# else
	.value("Unsupported", oglplus::FramebufferStatus::Unsupported)
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
# if defined IncompleteMultisample
#  pragma push_macro("IncompleteMultisample")
#  undef IncompleteMultisample
	.value("IncompleteMultisample", oglplus::FramebufferStatus::IncompleteMultisample)
#  pragma pop_macro("IncompleteMultisample")
# else
	.value("IncompleteMultisample", oglplus::FramebufferStatus::IncompleteMultisample)
# endif
#endif
#if defined GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
# if defined IncompleteLayerTargets
#  pragma push_macro("IncompleteLayerTargets")
#  undef IncompleteLayerTargets
	.value("IncompleteLayerTargets", oglplus::FramebufferStatus::IncompleteLayerTargets)
#  pragma pop_macro("IncompleteLayerTargets")
# else
	.value("IncompleteLayerTargets", oglplus::FramebufferStatus::IncompleteLayerTargets)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::FramebufferStatus) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
