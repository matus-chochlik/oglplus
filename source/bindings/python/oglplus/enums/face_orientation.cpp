/*
 *  .file oglplus/enums/face_orientation.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/face_orientation.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/face_mode.hpp>

#include <boost/python.hpp>

void oglplus_py_face_orientation(void)
{
	boost::python::enum_<oglplus::FaceOrientation>("FaceOrientation")
#if defined GL_CW
# if defined CW
#  pragma push_macro("CW")
#  undef CW
	.value("CW", oglplus::FaceOrientation::CW)
#  pragma pop_macro("CW")
# else
	.value("CW", oglplus::FaceOrientation::CW)
# endif
#endif
#if defined GL_CCW
# if defined CCW
#  pragma push_macro("CCW")
#  undef CCW
	.value("CCW", oglplus::FaceOrientation::CCW)
#  pragma pop_macro("CCW")
# else
	.value("CCW", oglplus::FaceOrientation::CCW)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::FaceOrientation) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
