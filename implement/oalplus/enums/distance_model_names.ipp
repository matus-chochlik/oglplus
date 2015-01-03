//  File implement/oalplus/enums/distance_model_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oalplus/distance_model.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OALPLUS_LIB_FUNC CStrRef ValueName_(
	DistanceModel*,
	ALenum value
) noexcept
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVN_DISTANCEMODEL)
#define OALPLUS_IMPL_EVN_DISTANCEMODEL
{
switch(value)
{
#if defined AL_NONE
	case AL_NONE: return CStrRef("NONE");
#endif
#if defined AL_INVERSE_DISTANCE
	case AL_INVERSE_DISTANCE: return CStrRef("INVERSE_DISTANCE");
#endif
#if defined AL_INVERSE_DISTANCE_CLAMPED
	case AL_INVERSE_DISTANCE_CLAMPED: return CStrRef("INVERSE_DISTANCE_CLAMPED");
#endif
#if defined AL_LINEAR_DISTANCE
	case AL_LINEAR_DISTANCE: return CStrRef("LINEAR_DISTANCE");
#endif
#if defined AL_LINEAR_DISTANCE_CLAMPED
	case AL_LINEAR_DISTANCE_CLAMPED: return CStrRef("LINEAR_DISTANCE_CLAMPED");
#endif
#if defined AL_EXPONENT_DISTANCE
	case AL_EXPONENT_DISTANCE: return CStrRef("EXPONENT_DISTANCE");
#endif
#if defined AL_EXPONENT_DISTANCE_CLAMPED
	case AL_EXPONENT_DISTANCE_CLAMPED: return CStrRef("EXPONENT_DISTANCE_CLAMPED");
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

