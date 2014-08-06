//  File doc/quickbook/oglplus/quickref/enums/framebuffer_target.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/framebuffer_target.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_framebuffer_target
namespace oglplus {

enum class FramebufferTarget : GLenum
{
	Draw = GL_DRAW_FRAMEBUFFER,
	Read = GL_READ_FRAMEBUFFER
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<FramebufferTarget> __EnumValueRange<FramebufferTarget>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(FramebufferTarget);
#endif

} // namespace oglplus
//]
