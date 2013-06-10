/*
 *  .file eglplus/enums/string_query.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/string_query.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/string_query.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void eglplus_py_string_query(void)
{
	boost::python::enum_<eglplus::StringQuery>("StringQuery")
#if defined EGL_CLIENT_APIS
# if defined ClientAPIs
#  pragma push_macro("ClientAPIs")
#  undef ClientAPIs
	.value("ClientAPIs", eglplus::StringQuery::ClientAPIs)
#  pragma pop_macro("ClientAPIs")
# else
	.value("ClientAPIs", eglplus::StringQuery::ClientAPIs)
# endif
#endif
#if defined EGL_EXTENSIONS
# if defined Extensions
#  pragma push_macro("Extensions")
#  undef Extensions
	.value("Extensions", eglplus::StringQuery::Extensions)
#  pragma pop_macro("Extensions")
# else
	.value("Extensions", eglplus::StringQuery::Extensions)
# endif
#endif
#if defined EGL_VENDOR
# if defined Vendor
#  pragma push_macro("Vendor")
#  undef Vendor
	.value("Vendor", eglplus::StringQuery::Vendor)
#  pragma pop_macro("Vendor")
# else
	.value("Vendor", eglplus::StringQuery::Vendor)
# endif
#endif
#if defined EGL_VERSION
# if defined Version
#  pragma push_macro("Version")
#  undef Version
	.value("Version", eglplus::StringQuery::Version)
#  pragma pop_macro("Version")
# else
	.value("Version", eglplus::StringQuery::Version)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::StringQuery) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::StringQuery
		>
	>("aux_CastIterRange_StringQuery");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::StringQuery
	> (*PEnumValueRange)(eglplus::StringQuery) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
