//  File doc/quickbook/oglplus/quickref/enums/blit_filter.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/blit_filter.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_blit_filter
namespace oglplus {

enum class BlitFilter : GLenum
{
	Nearest = GL_NEAREST,
	Linear  = GL_LINEAR
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<BlitFilter> __EnumValueRange<BlitFilter>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(BlitFilter);
#endif

} // namespace oglplus
//]
