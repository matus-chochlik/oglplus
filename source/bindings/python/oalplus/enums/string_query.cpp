/*
 *  .file oalplus/enums/string_query.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/string_query.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/string_query.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oalplus_py_string_query(void)
{
	boost::python::enum_<oalplus::StringQuery>("StringQuery")
#if defined AL_VERSION
# if defined Version
#  pragma push_macro("Version")
#  undef Version
	.value("Version", oalplus::StringQuery::Version)
#  pragma pop_macro("Version")
# else
	.value("Version", oalplus::StringQuery::Version)
# endif
#endif
#if defined AL_RENDERER
# if defined Renderer
#  pragma push_macro("Renderer")
#  undef Renderer
	.value("Renderer", oalplus::StringQuery::Renderer)
#  pragma pop_macro("Renderer")
# else
	.value("Renderer", oalplus::StringQuery::Renderer)
# endif
#endif
#if defined AL_VENDOR
# if defined Vendor
#  pragma push_macro("Vendor")
#  undef Vendor
	.value("Vendor", oalplus::StringQuery::Vendor)
#  pragma pop_macro("Vendor")
# else
	.value("Vendor", oalplus::StringQuery::Vendor)
# endif
#endif
#if defined AL_EXTENSIONS
# if defined Extensions
#  pragma push_macro("Extensions")
#  undef Extensions
	.value("Extensions", oalplus::StringQuery::Extensions)
#  pragma pop_macro("Extensions")
# else
	.value("Extensions", oalplus::StringQuery::Extensions)
# endif
#endif
	;

	oalplus::StrLit (*PEnumValueName)(oalplus::StringQuery) =
		&oalplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oalplus_py_export_range<
		oalplus::aux::CastIterRange<
			const ALenum*,
			oalplus::StringQuery
		>
	>("aux_CastIterRange_StringQuery");

	oalplus::aux::CastIterRange<
		const ALenum*,
		oalplus::StringQuery
	> (*PEnumValueRange)(oalplus::StringQuery) =
		&oalplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
