/*
 *  .file oalplus/enums/distance_model_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/distance_model.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OALPLUS_LIB_FUNC StrLit ValueName_(
	DistanceModel*,
	ALenum value
)
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVN_DISTANCEMODEL)
#define OALPLUS_IMPL_EVN_DISTANCEMODEL
{
switch(value)
{
#if defined AL_NONE
	case AL_NONE: return StrLit("NONE");
#endif
#if defined AL_INVERSE_DISTANCE
	case AL_INVERSE_DISTANCE: return StrLit("INVERSE_DISTANCE");
#endif
#if defined AL_INVERSE_DISTANCE_CLAMPED
	case AL_INVERSE_DISTANCE_CLAMPED: return StrLit("INVERSE_DISTANCE_CLAMPED");
#endif
#if defined AL_LINEAR_DISTANCE
	case AL_LINEAR_DISTANCE: return StrLit("LINEAR_DISTANCE");
#endif
#if defined AL_LINEAR_DISTANCE_CLAMPED
	case AL_LINEAR_DISTANCE_CLAMPED: return StrLit("LINEAR_DISTANCE_CLAMPED");
#endif
#if defined AL_EXPONENT_DISTANCE
	case AL_EXPONENT_DISTANCE: return StrLit("EXPONENT_DISTANCE");
#endif
#if defined AL_EXPONENT_DISTANCE_CLAMPED
	case AL_EXPONENT_DISTANCE_CLAMPED: return StrLit("EXPONENT_DISTANCE_CLAMPED");
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

