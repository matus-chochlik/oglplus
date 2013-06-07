/*
 *  .file oglplus/enums/face.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/face.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/face_mode.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_face(void)
{
	boost::python::enum_<oglplus::Face>("Face")
#if defined GL_FRONT
# if defined Front
#  pragma push_macro("Front")
#  undef Front
	.value("Front", oglplus::Face::Front)
#  pragma pop_macro("Front")
# else
	.value("Front", oglplus::Face::Front)
# endif
#endif
#if defined GL_BACK
# if defined Back
#  pragma push_macro("Back")
#  undef Back
	.value("Back", oglplus::Face::Back)
#  pragma pop_macro("Back")
# else
	.value("Back", oglplus::Face::Back)
# endif
#endif
#if defined GL_FRONT_AND_BACK
# if defined FrontAndBack
#  pragma push_macro("FrontAndBack")
#  undef FrontAndBack
	.value("FrontAndBack", oglplus::Face::FrontAndBack)
#  pragma pop_macro("FrontAndBack")
# else
	.value("FrontAndBack", oglplus::Face::FrontAndBack)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::Face) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::Face
		>
	>("aux_CastIterRange_Face");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::Face
	> (*PEnumValueRange)(oglplus::Face) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
