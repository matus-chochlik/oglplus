/*
 *  .file oglplus/enums/framebuffer_target.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/framebuffer_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/framebuffer.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_framebuffer_target(void)
{
	boost::python::enum_<oglplus::FramebufferTarget>("FramebufferTarget")
#if defined GL_DRAW_FRAMEBUFFER
# if defined Draw
#  pragma push_macro("Draw")
#  undef Draw
	.value("Draw", oglplus::FramebufferTarget::Draw)
#  pragma pop_macro("Draw")
# else
	.value("Draw", oglplus::FramebufferTarget::Draw)
# endif
#endif
#if defined GL_READ_FRAMEBUFFER
# if defined Read
#  pragma push_macro("Read")
#  undef Read
	.value("Read", oglplus::FramebufferTarget::Read)
#  pragma pop_macro("Read")
# else
	.value("Read", oglplus::FramebufferTarget::Read)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::FramebufferTarget) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::FramebufferTarget
		>
	>("aux_CastIterRange_FramebufferTarget");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::FramebufferTarget
	> (*PEnumValueRange)(oglplus::FramebufferTarget) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
