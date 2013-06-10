/*
 *  .file oglplus/enums/transform_feedback_primitive_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/transform_feedback_primitive_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/transform_feedback.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_transform_feedback_primitive_type(void)
{
	boost::python::enum_<oglplus::TransformFeedbackPrimitiveType>("TransformFeedbackPrimitiveType")
#if defined GL_TRIANGLES
# if defined Triangles
#  pragma push_macro("Triangles")
#  undef Triangles
	.value("Triangles", oglplus::TransformFeedbackPrimitiveType::Triangles)
#  pragma pop_macro("Triangles")
# else
	.value("Triangles", oglplus::TransformFeedbackPrimitiveType::Triangles)
# endif
#endif
#if defined GL_LINES
# if defined Lines
#  pragma push_macro("Lines")
#  undef Lines
	.value("Lines", oglplus::TransformFeedbackPrimitiveType::Lines)
#  pragma pop_macro("Lines")
# else
	.value("Lines", oglplus::TransformFeedbackPrimitiveType::Lines)
# endif
#endif
#if defined GL_POINTS
# if defined Points
#  pragma push_macro("Points")
#  undef Points
	.value("Points", oglplus::TransformFeedbackPrimitiveType::Points)
#  pragma pop_macro("Points")
# else
	.value("Points", oglplus::TransformFeedbackPrimitiveType::Points)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TransformFeedbackPrimitiveType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TransformFeedbackPrimitiveType
		>
	>("aux_CastIterRange_TransformFeedbackPrimitiveType");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TransformFeedbackPrimitiveType
	> (*PEnumValueRange)(oglplus::TransformFeedbackPrimitiveType) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
