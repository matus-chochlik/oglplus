//  File implement/oalplus/enums/source_type_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oalplus/source_type.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OALPLUS_LIB_FUNC CStrRef ValueName_(
	SourceType*,
	ALenum value
) noexcept
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVN_SOURCETYPE)
#define OALPLUS_IMPL_EVN_SOURCETYPE
{
switch(value)
{
#if defined AL_UNDETERMINED
	case AL_UNDETERMINED: return CStrRef("UNDETERMINED");
#endif
#if defined AL_STATIC
	case AL_STATIC: return CStrRef("STATIC");
#endif
#if defined AL_STREAMING
	case AL_STREAMING: return CStrRef("STREAMING");
#endif
	default:;
}
OALPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

