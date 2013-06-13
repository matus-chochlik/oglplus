/*
 *  .file oalplus/enums/source_state.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/source_state.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/source_state.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oalplus_py_source_state(void)
{
	boost::python::enum_<oalplus::SourceState>("SourceState")
#if defined AL_INITIAL
# if defined Initial
#  pragma push_macro("Initial")
#  undef Initial
	.value("Initial", oalplus::SourceState::Initial)
#  pragma pop_macro("Initial")
# else
	.value("Initial", oalplus::SourceState::Initial)
# endif
#endif
#if defined AL_PLAYING
# if defined Playing
#  pragma push_macro("Playing")
#  undef Playing
	.value("Playing", oalplus::SourceState::Playing)
#  pragma pop_macro("Playing")
# else
	.value("Playing", oalplus::SourceState::Playing)
# endif
#endif
#if defined AL_PAUSED
# if defined Paused
#  pragma push_macro("Paused")
#  undef Paused
	.value("Paused", oalplus::SourceState::Paused)
#  pragma pop_macro("Paused")
# else
	.value("Paused", oalplus::SourceState::Paused)
# endif
#endif
#if defined AL_STOPPED
# if defined Stopped
#  pragma push_macro("Stopped")
#  undef Stopped
	.value("Stopped", oalplus::SourceState::Stopped)
#  pragma pop_macro("Stopped")
# else
	.value("Stopped", oalplus::SourceState::Stopped)
# endif
#endif
	;

	oalplus::StrLit (*PEnumValueName)(oalplus::SourceState) =
		&oalplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oalplus_py_export_range<
		oalplus::aux::CastIterRange<
			const ALenum*,
			oalplus::SourceState
		>
	>("aux_CastIterRange_SourceState");

	oalplus::aux::CastIterRange<
		const ALenum*,
		oalplus::SourceState
	> (*PEnumValueRange)(oalplus::SourceState) =
		&oalplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
