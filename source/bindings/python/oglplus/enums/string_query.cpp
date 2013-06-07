/*
 *  .file oglplus/enums/string_query.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/string_query.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/string_query.hpp>

#include <boost/python.hpp>

void oglplus_py_string_query(void)
{
	boost::python::enum_<oglplus::StringQuery>("StringQuery")
#if defined GL_RENDERER
# if defined Renderer
#  pragma push_macro("Renderer")
#  undef Renderer
	.value("Renderer", oglplus::StringQuery::Renderer)
#  pragma pop_macro("Renderer")
# else
	.value("Renderer", oglplus::StringQuery::Renderer)
# endif
#endif
#if defined GL_VENDOR
# if defined Vendor
#  pragma push_macro("Vendor")
#  undef Vendor
	.value("Vendor", oglplus::StringQuery::Vendor)
#  pragma pop_macro("Vendor")
# else
	.value("Vendor", oglplus::StringQuery::Vendor)
# endif
#endif
#if defined GL_VERSION
# if defined Version
#  pragma push_macro("Version")
#  undef Version
	.value("Version", oglplus::StringQuery::Version)
#  pragma pop_macro("Version")
# else
	.value("Version", oglplus::StringQuery::Version)
# endif
#endif
#if defined GL_SHADING_LANGUAGE_VERSION
# if defined ShadingLanguageVersion
#  pragma push_macro("ShadingLanguageVersion")
#  undef ShadingLanguageVersion
	.value("ShadingLanguageVersion", oglplus::StringQuery::ShadingLanguageVersion)
#  pragma pop_macro("ShadingLanguageVersion")
# else
	.value("ShadingLanguageVersion", oglplus::StringQuery::ShadingLanguageVersion)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::StringQuery) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
