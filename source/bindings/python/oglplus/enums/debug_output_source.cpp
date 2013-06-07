/*
 *  .file oglplus/enums/debug_output_source.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/debug_output_source.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/opt/debug_output.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_debug_output_source(void)
{
	boost::python::enum_<oglplus::DebugOutputSource>("DebugOutputSource")
#if defined GL_DEBUG_SOURCE_API
# if defined API
#  pragma push_macro("API")
#  undef API
	.value("API", oglplus::DebugOutputSource::API)
#  pragma pop_macro("API")
# else
	.value("API", oglplus::DebugOutputSource::API)
# endif
#endif
#if defined GL_DEBUG_SOURCE_WINDOW_SYSTEM
# if defined WindowSystem
#  pragma push_macro("WindowSystem")
#  undef WindowSystem
	.value("WindowSystem", oglplus::DebugOutputSource::WindowSystem)
#  pragma pop_macro("WindowSystem")
# else
	.value("WindowSystem", oglplus::DebugOutputSource::WindowSystem)
# endif
#endif
#if defined GL_DEBUG_SOURCE_SHADER_COMPILER
# if defined ShaderCompiler
#  pragma push_macro("ShaderCompiler")
#  undef ShaderCompiler
	.value("ShaderCompiler", oglplus::DebugOutputSource::ShaderCompiler)
#  pragma pop_macro("ShaderCompiler")
# else
	.value("ShaderCompiler", oglplus::DebugOutputSource::ShaderCompiler)
# endif
#endif
#if defined GL_DEBUG_SOURCE_THIRD_PARTY
# if defined ThirdParty
#  pragma push_macro("ThirdParty")
#  undef ThirdParty
	.value("ThirdParty", oglplus::DebugOutputSource::ThirdParty)
#  pragma pop_macro("ThirdParty")
# else
	.value("ThirdParty", oglplus::DebugOutputSource::ThirdParty)
# endif
#endif
#if defined GL_DEBUG_SOURCE_APPLICATION
# if defined Application
#  pragma push_macro("Application")
#  undef Application
	.value("Application", oglplus::DebugOutputSource::Application)
#  pragma pop_macro("Application")
# else
	.value("Application", oglplus::DebugOutputSource::Application)
# endif
#endif
#if defined GL_DEBUG_SOURCE_OTHER
# if defined Other
#  pragma push_macro("Other")
#  undef Other
	.value("Other", oglplus::DebugOutputSource::Other)
#  pragma pop_macro("Other")
# else
	.value("Other", oglplus::DebugOutputSource::Other)
# endif
#endif
#if defined GL_DONT_CARE
# if defined DontCare
#  pragma push_macro("DontCare")
#  undef DontCare
	.value("DontCare", oglplus::DebugOutputSource::DontCare)
#  pragma pop_macro("DontCare")
# else
	.value("DontCare", oglplus::DebugOutputSource::DontCare)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::DebugOutputSource) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::DebugOutputSource
		>
	>("aux_CastIterRange_DebugOutputSource");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::DebugOutputSource
	> (*PEnumValueRange)(oglplus::DebugOutputSource) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
