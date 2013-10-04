/*
 *  .file oglplus/enums/transform_feedback_mode_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/transform_feedback_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	TransformFeedbackMode
> ValueRange_(TransformFeedbackMode*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_TRANSFORMFEEDBACKMODE)
#define OGLPLUS_IMPL_EVR_TRANSFORMFEEDBACKMODE
{
static const GLenum _values[] = {
#if defined GL_INTERLEAVED_ATTRIBS
GL_INTERLEAVED_ATTRIBS,
#endif
#if defined GL_SEPARATE_ATTRIBS
GL_SEPARATE_ATTRIBS,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	TransformFeedbackMode
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

