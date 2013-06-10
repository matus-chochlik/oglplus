/*
 *  .file oglplus/enums/renderbuffer_target.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/renderbuffer_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/renderbuffer.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_renderbuffer_target(void)
{
	boost::python::enum_<oglplus::RenderbufferTarget>("RenderbufferTarget")
#if defined GL_RENDERBUFFER
# if defined Renderbuffer
#  pragma push_macro("Renderbuffer")
#  undef Renderbuffer
	.value("Renderbuffer", oglplus::RenderbufferTarget::Renderbuffer)
#  pragma pop_macro("Renderbuffer")
# else
	.value("Renderbuffer", oglplus::RenderbufferTarget::Renderbuffer)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::RenderbufferTarget) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::RenderbufferTarget
		>
	>("aux_CastIterRange_RenderbufferTarget");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::RenderbufferTarget
	> (*PEnumValueRange)(oglplus::RenderbufferTarget) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
