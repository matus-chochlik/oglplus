/*
 *  .file oglplus/enums/renderbuffer_target_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/renderbuffer_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	RenderbufferTarget
> ValueRange_(RenderbufferTarget*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_RENDERBUFFERTARGET)
#define OGLPLUS_IMPL_EVR_RENDERBUFFERTARGET
{
static const GLenum _values[] = {
#if defined GL_RENDERBUFFER
GL_RENDERBUFFER,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	RenderbufferTarget
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

