/*
 *  .file oglplus/enums/transform_feedback_mode.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/transform_feedback_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/transform_feedback.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_transform_feedback_mode(void)
{
	boost::python::enum_<oglplus::TransformFeedbackMode>("TransformFeedbackMode")
#if defined GL_INTERLEAVED_ATTRIBS
# if defined InterleavedAttribs
#  pragma push_macro("InterleavedAttribs")
#  undef InterleavedAttribs
	.value("InterleavedAttribs", oglplus::TransformFeedbackMode::InterleavedAttribs)
#  pragma pop_macro("InterleavedAttribs")
# else
	.value("InterleavedAttribs", oglplus::TransformFeedbackMode::InterleavedAttribs)
# endif
#endif
#if defined GL_SEPARATE_ATTRIBS
# if defined SeparateAttribs
#  pragma push_macro("SeparateAttribs")
#  undef SeparateAttribs
	.value("SeparateAttribs", oglplus::TransformFeedbackMode::SeparateAttribs)
#  pragma pop_macro("SeparateAttribs")
# else
	.value("SeparateAttribs", oglplus::TransformFeedbackMode::SeparateAttribs)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TransformFeedbackMode) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TransformFeedbackMode
		>
	>("aux_CastIterRange_TransformFeedbackMode");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TransformFeedbackMode
	> (*PEnumValueRange)(oglplus::TransformFeedbackMode) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
