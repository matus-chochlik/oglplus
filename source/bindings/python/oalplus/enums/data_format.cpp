/*
 *  .file oalplus/enums/data_format.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/data_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/data_format.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oalplus_py_data_format(void)
{
	boost::python::enum_<oalplus::DataFormat>("DataFormat")
#if defined AL_FORMAT_MONO8
# if defined Mono8
#  pragma push_macro("Mono8")
#  undef Mono8
	.value("Mono8", oalplus::DataFormat::Mono8)
#  pragma pop_macro("Mono8")
# else
	.value("Mono8", oalplus::DataFormat::Mono8)
# endif
#endif
#if defined AL_FORMAT_MONO16
# if defined Mono16
#  pragma push_macro("Mono16")
#  undef Mono16
	.value("Mono16", oalplus::DataFormat::Mono16)
#  pragma pop_macro("Mono16")
# else
	.value("Mono16", oalplus::DataFormat::Mono16)
# endif
#endif
#if defined AL_FORMAT_STEREO8
# if defined Stereo8
#  pragma push_macro("Stereo8")
#  undef Stereo8
	.value("Stereo8", oalplus::DataFormat::Stereo8)
#  pragma pop_macro("Stereo8")
# else
	.value("Stereo8", oalplus::DataFormat::Stereo8)
# endif
#endif
#if defined AL_FORMAT_STEREO16
# if defined Stereo16
#  pragma push_macro("Stereo16")
#  undef Stereo16
	.value("Stereo16", oalplus::DataFormat::Stereo16)
#  pragma pop_macro("Stereo16")
# else
	.value("Stereo16", oalplus::DataFormat::Stereo16)
# endif
#endif
	;

	oalplus::StrLit (*PEnumValueName)(oalplus::DataFormat) =
		&oalplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oalplus_py_export_range<
		oalplus::aux::CastIterRange<
			const ALenum*,
			oalplus::DataFormat
		>
	>("aux_CastIterRange_DataFormat");

	oalplus::aux::CastIterRange<
		const ALenum*,
		oalplus::DataFormat
	> (*PEnumValueRange)(oalplus::DataFormat) =
		&oalplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
