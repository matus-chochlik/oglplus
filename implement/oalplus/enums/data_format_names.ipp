/*
 *  .file oalplus/enums/data_format_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/data_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OALPLUS_LIB_FUNC StrLit ValueName_(
	DataFormat*,
	ALenum value
)
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVN_DATAFORMAT)
#define OALPLUS_IMPL_EVN_DATAFORMAT
{
switch(value)
{
#if defined AL_FORMAT_MONO8
	case AL_FORMAT_MONO8: return StrLit("FORMAT_MONO8");
#endif
#if defined AL_FORMAT_MONO16
	case AL_FORMAT_MONO16: return StrLit("FORMAT_MONO16");
#endif
#if defined AL_FORMAT_STEREO8
	case AL_FORMAT_STEREO8: return StrLit("FORMAT_STEREO8");
#endif
#if defined AL_FORMAT_STEREO16
	case AL_FORMAT_STEREO16: return StrLit("FORMAT_STEREO16");
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

