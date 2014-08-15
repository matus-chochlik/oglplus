/*
 *  .file oalplus/enums/source_type_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/source_type.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OALPLUS_LIB_FUNC StrCRef ValueName_(
	SourceType*,
	ALenum value
)
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVN_SOURCETYPE)
#define OALPLUS_IMPL_EVN_SOURCETYPE
{
switch(value)
{
#if defined AL_UNDETERMINED
	case AL_UNDETERMINED: return StrCRef("UNDETERMINED");
#endif
#if defined AL_STATIC
	case AL_STATIC: return StrCRef("STATIC");
#endif
#if defined AL_STREAMING
	case AL_STREAMING: return StrCRef("STREAMING");
#endif
	default:;
}
OALPLUS_FAKE_USE(value);
return StrCRef();
}
#else
;
#endif
} // namespace enums

