/*
 *  .file oalplus/enums/distance_model_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/distance_model.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OALPLUS_LIB_FUNC aux::CastIterRange<
	const ALenum*,
	DistanceModel
> ValueRange_(DistanceModel*)
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVR_DISTANCEMODEL)
#define OALPLUS_IMPL_EVR_DISTANCEMODEL
{
static const ALenum _values[] = {
#if defined AL_NONE
AL_NONE,
#endif
#if defined AL_INVERSE_DISTANCE
AL_INVERSE_DISTANCE,
#endif
#if defined AL_INVERSE_DISTANCE_CLAMPED
AL_INVERSE_DISTANCE_CLAMPED,
#endif
#if defined AL_LINEAR_DISTANCE
AL_LINEAR_DISTANCE,
#endif
#if defined AL_LINEAR_DISTANCE_CLAMPED
AL_LINEAR_DISTANCE_CLAMPED,
#endif
#if defined AL_EXPONENT_DISTANCE
AL_EXPONENT_DISTANCE,
#endif
#if defined AL_EXPONENT_DISTANCE_CLAMPED
AL_EXPONENT_DISTANCE_CLAMPED,
#endif
0
};
return aux::CastIterRange<
	const ALenum*,
	DistanceModel
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

