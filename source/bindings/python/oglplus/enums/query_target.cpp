/*
 *  .file oglplus/enums/query_target.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/query_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/query.hpp>

#include <boost/python.hpp>

void oglplus_py_query_target(void)
{
	boost::python::enum_<oglplus::QueryTarget>("QueryTarget")
#if defined GL_TIME_ELAPSED
# if defined TimeElapsed
#  pragma push_macro("TimeElapsed")
#  undef TimeElapsed
	.value("TimeElapsed", oglplus::QueryTarget::TimeElapsed)
#  pragma pop_macro("TimeElapsed")
# else
	.value("TimeElapsed", oglplus::QueryTarget::TimeElapsed)
# endif
#endif
#if defined GL_TIMESTAMP
# if defined Timestamp
#  pragma push_macro("Timestamp")
#  undef Timestamp
	.value("Timestamp", oglplus::QueryTarget::Timestamp)
#  pragma pop_macro("Timestamp")
# else
	.value("Timestamp", oglplus::QueryTarget::Timestamp)
# endif
#endif
#if defined GL_SAMPLES_PASSED
# if defined SamplesPassed
#  pragma push_macro("SamplesPassed")
#  undef SamplesPassed
	.value("SamplesPassed", oglplus::QueryTarget::SamplesPassed)
#  pragma pop_macro("SamplesPassed")
# else
	.value("SamplesPassed", oglplus::QueryTarget::SamplesPassed)
# endif
#endif
#if defined GL_ANY_SAMPLES_PASSED
# if defined AnySamplesPassed
#  pragma push_macro("AnySamplesPassed")
#  undef AnySamplesPassed
	.value("AnySamplesPassed", oglplus::QueryTarget::AnySamplesPassed)
#  pragma pop_macro("AnySamplesPassed")
# else
	.value("AnySamplesPassed", oglplus::QueryTarget::AnySamplesPassed)
# endif
#endif
#if defined GL_PRIMITIVES_GENERATED
# if defined PrimitivesGenerated
#  pragma push_macro("PrimitivesGenerated")
#  undef PrimitivesGenerated
	.value("PrimitivesGenerated", oglplus::QueryTarget::PrimitivesGenerated)
#  pragma pop_macro("PrimitivesGenerated")
# else
	.value("PrimitivesGenerated", oglplus::QueryTarget::PrimitivesGenerated)
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
# if defined TransformFeedbackPrimitivesWritten
#  pragma push_macro("TransformFeedbackPrimitivesWritten")
#  undef TransformFeedbackPrimitivesWritten
	.value("TransformFeedbackPrimitivesWritten", oglplus::QueryTarget::TransformFeedbackPrimitivesWritten)
#  pragma pop_macro("TransformFeedbackPrimitivesWritten")
# else
	.value("TransformFeedbackPrimitivesWritten", oglplus::QueryTarget::TransformFeedbackPrimitivesWritten)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::QueryTarget) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
