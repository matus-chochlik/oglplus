/*
 *  .file oglplus/enums/debug_output_severity.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/debug_output_severity.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/opt/debug_output.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_debug_output_severity(void)
{
	boost::python::enum_<oglplus::DebugOutputSeverity>("DebugOutputSeverity")
#if defined GL_DEBUG_SEVERITY_HIGH
# if defined High
#  pragma push_macro("High")
#  undef High
	.value("High", oglplus::DebugOutputSeverity::High)
#  pragma pop_macro("High")
# else
	.value("High", oglplus::DebugOutputSeverity::High)
# endif
#endif
#if defined GL_DEBUG_SEVERITY_MEDIUM
# if defined Medium
#  pragma push_macro("Medium")
#  undef Medium
	.value("Medium", oglplus::DebugOutputSeverity::Medium)
#  pragma pop_macro("Medium")
# else
	.value("Medium", oglplus::DebugOutputSeverity::Medium)
# endif
#endif
#if defined GL_DEBUG_SEVERITY_LOW
# if defined Low
#  pragma push_macro("Low")
#  undef Low
	.value("Low", oglplus::DebugOutputSeverity::Low)
#  pragma pop_macro("Low")
# else
	.value("Low", oglplus::DebugOutputSeverity::Low)
# endif
#endif
#if defined GL_DEBUG_SEVERITY_NOTIFICATION
# if defined Notification
#  pragma push_macro("Notification")
#  undef Notification
	.value("Notification", oglplus::DebugOutputSeverity::Notification)
#  pragma pop_macro("Notification")
# else
	.value("Notification", oglplus::DebugOutputSeverity::Notification)
# endif
#endif
#if defined GL_DONT_CARE
# if defined DontCare
#  pragma push_macro("DontCare")
#  undef DontCare
	.value("DontCare", oglplus::DebugOutputSeverity::DontCare)
#  pragma pop_macro("DontCare")
# else
	.value("DontCare", oglplus::DebugOutputSeverity::DontCare)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::DebugOutputSeverity) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::DebugOutputSeverity
		>
	>("aux_CastIterRange_DebugOutputSeverity");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::DebugOutputSeverity
	> (*PEnumValueRange)(oglplus::DebugOutputSeverity) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
