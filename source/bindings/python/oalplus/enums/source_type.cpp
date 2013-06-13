/*
 *  .file oalplus/enums/source_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/source_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/source_type.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oalplus_py_source_type(void)
{
	boost::python::enum_<oalplus::SourceType>("SourceType")
#if defined AL_UNDETERMINED
# if defined Undetermined
#  pragma push_macro("Undetermined")
#  undef Undetermined
	.value("Undetermined", oalplus::SourceType::Undetermined)
#  pragma pop_macro("Undetermined")
# else
	.value("Undetermined", oalplus::SourceType::Undetermined)
# endif
#endif
#if defined AL_STATIC
# if defined Static
#  pragma push_macro("Static")
#  undef Static
	.value("Static", oalplus::SourceType::Static)
#  pragma pop_macro("Static")
# else
	.value("Static", oalplus::SourceType::Static)
# endif
#endif
#if defined AL_STREAMING
# if defined Streaming
#  pragma push_macro("Streaming")
#  undef Streaming
	.value("Streaming", oalplus::SourceType::Streaming)
#  pragma pop_macro("Streaming")
# else
	.value("Streaming", oalplus::SourceType::Streaming)
# endif
#endif
	;

	oalplus::StrLit (*PEnumValueName)(oalplus::SourceType) =
		&oalplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oalplus_py_export_range<
		oalplus::aux::CastIterRange<
			const ALenum*,
			oalplus::SourceType
		>
	>("aux_CastIterRange_SourceType");

	oalplus::aux::CastIterRange<
		const ALenum*,
		oalplus::SourceType
	> (*PEnumValueRange)(oalplus::SourceType) =
		&oalplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
