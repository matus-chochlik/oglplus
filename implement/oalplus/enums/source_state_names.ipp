/*
 *  .file oalplus/enums/source_state_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/source_state.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OALPLUS_LIB_FUNC StrLit ValueName_(
	SourceState*,
	ALenum value
)
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVN_SOURCESTATE)
#define OALPLUS_IMPL_EVN_SOURCESTATE
{
switch(value)
{
#if defined AL_INITIAL
	case AL_INITIAL: return StrLit("INITIAL");
#endif
#if defined AL_PLAYING
	case AL_PLAYING: return StrLit("PLAYING");
#endif
#if defined AL_PAUSED
	case AL_PAUSED: return StrLit("PAUSED");
#endif
#if defined AL_STOPPED
	case AL_STOPPED: return StrLit("STOPPED");
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

