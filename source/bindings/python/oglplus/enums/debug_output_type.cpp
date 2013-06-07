/*
 *  .file oglplus/enums/debug_output_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/debug_output_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/opt/debug_output.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_debug_output_type(void)
{
	boost::python::enum_<oglplus::DebugOutputType>("DebugOutputType")
#if defined GL_DEBUG_TYPE_ERROR
# if defined Error
#  pragma push_macro("Error")
#  undef Error
	.value("Error", oglplus::DebugOutputType::Error)
#  pragma pop_macro("Error")
# else
	.value("Error", oglplus::DebugOutputType::Error)
# endif
#endif
#if defined GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR
# if defined DeprecatedBehavior
#  pragma push_macro("DeprecatedBehavior")
#  undef DeprecatedBehavior
	.value("DeprecatedBehavior", oglplus::DebugOutputType::DeprecatedBehavior)
#  pragma pop_macro("DeprecatedBehavior")
# else
	.value("DeprecatedBehavior", oglplus::DebugOutputType::DeprecatedBehavior)
# endif
#endif
#if defined GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR
# if defined UndefinedBehavior
#  pragma push_macro("UndefinedBehavior")
#  undef UndefinedBehavior
	.value("UndefinedBehavior", oglplus::DebugOutputType::UndefinedBehavior)
#  pragma pop_macro("UndefinedBehavior")
# else
	.value("UndefinedBehavior", oglplus::DebugOutputType::UndefinedBehavior)
# endif
#endif
#if defined GL_DEBUG_TYPE_PORTABILITY
# if defined Portability
#  pragma push_macro("Portability")
#  undef Portability
	.value("Portability", oglplus::DebugOutputType::Portability)
#  pragma pop_macro("Portability")
# else
	.value("Portability", oglplus::DebugOutputType::Portability)
# endif
#endif
#if defined GL_DEBUG_TYPE_PERFORMANCE
# if defined Performance
#  pragma push_macro("Performance")
#  undef Performance
	.value("Performance", oglplus::DebugOutputType::Performance)
#  pragma pop_macro("Performance")
# else
	.value("Performance", oglplus::DebugOutputType::Performance)
# endif
#endif
#if defined GL_DEBUG_TYPE_MARKER
# if defined Marker
#  pragma push_macro("Marker")
#  undef Marker
	.value("Marker", oglplus::DebugOutputType::Marker)
#  pragma pop_macro("Marker")
# else
	.value("Marker", oglplus::DebugOutputType::Marker)
# endif
#endif
#if defined GL_DEBUG_TYPE_PUSH_GROUP
# if defined PushGroup
#  pragma push_macro("PushGroup")
#  undef PushGroup
	.value("PushGroup", oglplus::DebugOutputType::PushGroup)
#  pragma pop_macro("PushGroup")
# else
	.value("PushGroup", oglplus::DebugOutputType::PushGroup)
# endif
#endif
#if defined GL_DEBUG_TYPE_POP_GROUP
# if defined PopGroup
#  pragma push_macro("PopGroup")
#  undef PopGroup
	.value("PopGroup", oglplus::DebugOutputType::PopGroup)
#  pragma pop_macro("PopGroup")
# else
	.value("PopGroup", oglplus::DebugOutputType::PopGroup)
# endif
#endif
#if defined GL_DEBUG_TYPE_OTHER
# if defined Other
#  pragma push_macro("Other")
#  undef Other
	.value("Other", oglplus::DebugOutputType::Other)
#  pragma pop_macro("Other")
# else
	.value("Other", oglplus::DebugOutputType::Other)
# endif
#endif
#if defined GL_DONT_CARE
# if defined DontCare
#  pragma push_macro("DontCare")
#  undef DontCare
	.value("DontCare", oglplus::DebugOutputType::DontCare)
#  pragma pop_macro("DontCare")
# else
	.value("DontCare", oglplus::DebugOutputType::DontCare)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::DebugOutputType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::DebugOutputType
		>
	>("aux_CastIterRange_DebugOutputType");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::DebugOutputType
	> (*PEnumValueRange)(oglplus::DebugOutputType) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
