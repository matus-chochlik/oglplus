/*
 *  .file eglplus/enums/render_buffer.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/render_buffer.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/render_buffer.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void eglplus_py_render_buffer(void)
{
	boost::python::enum_<eglplus::RenderBuffer>("RenderBuffer")
#if defined EGL_SINGLE_BUFFER
# if defined SingleBuffer
#  pragma push_macro("SingleBuffer")
#  undef SingleBuffer
	.value("SingleBuffer", eglplus::RenderBuffer::SingleBuffer)
#  pragma pop_macro("SingleBuffer")
# else
	.value("SingleBuffer", eglplus::RenderBuffer::SingleBuffer)
# endif
#endif
#if defined EGL_BACK_BUFFER
# if defined BackBuffer
#  pragma push_macro("BackBuffer")
#  undef BackBuffer
	.value("BackBuffer", eglplus::RenderBuffer::BackBuffer)
#  pragma pop_macro("BackBuffer")
# else
	.value("BackBuffer", eglplus::RenderBuffer::BackBuffer)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::RenderBuffer) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::RenderBuffer
		>
	>("aux_CastIterRange_RenderBuffer");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::RenderBuffer
	> (*PEnumValueRange)(eglplus::RenderBuffer) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
