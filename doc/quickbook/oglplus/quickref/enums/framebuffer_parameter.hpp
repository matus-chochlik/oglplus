//  File doc/quickbook/oglplus/quickref/enums/framebuffer_parameter.hpp
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
//[oglplus_enums_framebuffer_parameter

enum class FramebufferParameter : GLenum
{
	FramebufferDefaultWidth                = GL_FRAMEBUFFER_DEFAULT_WIDTH,
	FramebufferDefaultHeight               = GL_FRAMEBUFFER_DEFAULT_HEIGHT,
	FramebufferDefaultLayers               = GL_FRAMEBUFFER_DEFAULT_LAYERS,
	FramebufferDefaultSamples              = GL_FRAMEBUFFER_DEFAULT_SAMPLES,
	FramebufferDefaultFixedSampleLocations = GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
};

template <>
__Range<FramebufferParameter> __EnumValueRange<FramebufferParameter>(void);

__StrCRef __EnumValueName(FramebufferParameter);

//]
