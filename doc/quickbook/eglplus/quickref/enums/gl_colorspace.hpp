//  File doc/quickbook/eglplus/quickref/enums/gl_colorspace.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/eglplus/gl_colorspace.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_gl_colorspace
namespace eglplus {

enum class GLColorspace : EGLenum
{
	sRGB   = EGL_GL_COLORSPACE_sRGB,
	Linear = EGL_GL_COLORSPACE_LINEAR
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<GLColorspace> __EnumValueRange<GLColorspace>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(GLColorspace);
#endif

} // namespace eglplus
//]
