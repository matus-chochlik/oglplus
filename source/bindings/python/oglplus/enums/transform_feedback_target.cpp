/*
 *  .file oglplus/enums/transform_feedback_target.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/transform_feedback_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/transform_feedback.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_transform_feedback_target(void)
{
	boost::python::enum_<oglplus::TransformFeedbackTarget>("TransformFeedbackTarget")
#if defined GL_TRANSFORM_FEEDBACK
# if defined TransformFeedback
#  pragma push_macro("TransformFeedback")
#  undef TransformFeedback
	.value("TransformFeedback", oglplus::TransformFeedbackTarget::TransformFeedback)
#  pragma pop_macro("TransformFeedback")
# else
	.value("TransformFeedback", oglplus::TransformFeedbackTarget::TransformFeedback)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TransformFeedbackTarget) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TransformFeedbackTarget
		>
	>("aux_CastIterRange_TransformFeedbackTarget");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TransformFeedbackTarget
	> (*PEnumValueRange)(oglplus::TransformFeedbackTarget) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
