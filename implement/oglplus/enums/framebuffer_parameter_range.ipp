//  File implement/oglplus/enums/framebuffer_parameter_range.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/framebuffer_parameter.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2017 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	FramebufferParameter
> ValueRange_(FramebufferParameter*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_FRAMEBUFFERPARAMETER)
#define OGLPLUS_IMPL_EVR_FRAMEBUFFERPARAMETER
{
static const GLenum _values[] = {
#if defined GL_FRAMEBUFFER_DEFAULT_WIDTH
GL_FRAMEBUFFER_DEFAULT_WIDTH,
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_HEIGHT
GL_FRAMEBUFFER_DEFAULT_HEIGHT,
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_LAYERS
GL_FRAMEBUFFER_DEFAULT_LAYERS,
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_SAMPLES
GL_FRAMEBUFFER_DEFAULT_SAMPLES,
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	FramebufferParameter
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

