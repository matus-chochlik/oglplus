/*
 *  .file oalplus/enums/context_attrib_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/context_attrib.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OALPLUS_LIB_FUNC StrLit ValueName_(
	ContextAttrib*,
	ALenum value
)
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVN_CONTEXTATTRIB)
#define OALPLUS_IMPL_EVN_CONTEXTATTRIB
{
switch(value)
{
#if defined ALC_FREQUENCY
	case ALC_FREQUENCY: return StrLit("FREQUENCY");
#endif
#if defined ALC_REFRESH
	case ALC_REFRESH: return StrLit("REFRESH");
#endif
#if defined ALC_SYNC
	case ALC_SYNC: return StrLit("SYNC");
#endif
#if defined ALC_MONO_SOURCES
	case ALC_MONO_SOURCES: return StrLit("MONO_SOURCES");
#endif
#if defined ALC_STEREO_SOURCES
	case ALC_STEREO_SOURCES: return StrLit("STEREO_SOURCES");
#endif
	default:;
}
OALPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

