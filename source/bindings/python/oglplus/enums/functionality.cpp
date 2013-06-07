/*
 *  .file oglplus/enums/functionality.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/functionality.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/capability.hpp>

#include <boost/python.hpp>

void oglplus_py_functionality(void)
{
	boost::python::enum_<oglplus::Functionality>("Functionality")
#if defined GL_CLIP_DISTANCE0
# if defined ClipDistance
#  pragma push_macro("ClipDistance")
#  undef ClipDistance
	.value("ClipDistance", oglplus::Functionality::ClipDistance)
#  pragma pop_macro("ClipDistance")
# else
	.value("ClipDistance", oglplus::Functionality::ClipDistance)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::Functionality) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
