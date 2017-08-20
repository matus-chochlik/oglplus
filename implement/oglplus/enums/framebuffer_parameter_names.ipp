//  File implement/oglplus/enums/framebuffer_parameter_names.ipp
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
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	FramebufferParameter*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_FRAMEBUFFERPARAMETER)
#define OGLPLUS_IMPL_EVN_FRAMEBUFFERPARAMETER
{
switch(value)
{
#if defined GL_FRAMEBUFFER_DEFAULT_WIDTH
	case GL_FRAMEBUFFER_DEFAULT_WIDTH: return StrCRef("FRAMEBUFFER_DEFAULT_WIDTH");
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_HEIGHT
	case GL_FRAMEBUFFER_DEFAULT_HEIGHT: return StrCRef("FRAMEBUFFER_DEFAULT_HEIGHT");
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_LAYERS
	case GL_FRAMEBUFFER_DEFAULT_LAYERS: return StrCRef("FRAMEBUFFER_DEFAULT_LAYERS");
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_SAMPLES
	case GL_FRAMEBUFFER_DEFAULT_SAMPLES: return StrCRef("FRAMEBUFFER_DEFAULT_SAMPLES");
#endif
#if defined GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
	case GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS: return StrCRef("FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrCRef();
}
#else
;
#endif
} // namespace enums

