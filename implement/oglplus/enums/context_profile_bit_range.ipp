/*
 *  .file oglplus/enums/context_profile_bit_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/context_profile_bit.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	ContextProfileBit
> ValueRange_(ContextProfileBit*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_CONTEXTPROFILEBIT)
#define OGLPLUS_IMPL_EVR_CONTEXTPROFILEBIT
{
static const GLenum _values[] = {
#if defined GL_CONTEXT_CORE_PROFILE_BIT
GL_CONTEXT_CORE_PROFILE_BIT,
#endif
#if defined GL_CONTEXT_COMPATIBILITY_PROFILE_BIT
GL_CONTEXT_COMPATIBILITY_PROFILE_BIT,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	ContextProfileBit
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

