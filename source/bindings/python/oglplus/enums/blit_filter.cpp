/*
 *  .file oglplus/enums/blit_filter.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/blit_filter.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/blit_filter.hpp>

#include <boost/python.hpp>

void oglplus_py_blit_filter(void)
{
	boost::python::enum_<oglplus::BlitFilter>("BlitFilter")
#if defined GL_NEAREST
# if defined Nearest
#  pragma push_macro("Nearest")
#  undef Nearest
	.value("Nearest", oglplus::BlitFilter::Nearest)
#  pragma pop_macro("Nearest")
# else
	.value("Nearest", oglplus::BlitFilter::Nearest)
# endif
#endif
#if defined GL_LINEAR
# if defined Linear
#  pragma push_macro("Linear")
#  undef Linear
	.value("Linear", oglplus::BlitFilter::Linear)
#  pragma pop_macro("Linear")
# else
	.value("Linear", oglplus::BlitFilter::Linear)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::BlitFilter) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
