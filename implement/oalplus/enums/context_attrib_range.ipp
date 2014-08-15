/*
 *  .file oalplus/enums/context_attrib_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/context_attrib.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OALPLUS_LIB_FUNC aux::CastIterRange<
	const ALenum*,
	ContextAttrib
> ValueRange_(ContextAttrib*)
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVR_CONTEXTATTRIB)
#define OALPLUS_IMPL_EVR_CONTEXTATTRIB
{
static const ALenum _values[] = {
#if defined ALC_FREQUENCY
ALC_FREQUENCY,
#endif
#if defined ALC_REFRESH
ALC_REFRESH,
#endif
#if defined ALC_SYNC
ALC_SYNC,
#endif
#if defined ALC_MONO_SOURCES
ALC_MONO_SOURCES,
#endif
#if defined ALC_STEREO_SOURCES
ALC_STEREO_SOURCES,
#endif
0
};
return aux::CastIterRange<
	const ALenum*,
	ContextAttrib
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

