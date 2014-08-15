//  File doc/quickbook/oglplus/quickref/enums/polygon_mode.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/polygon_mode.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_polygon_mode
namespace oglplus {

enum class PolygonMode : GLenum
{
	Point = GL_POINT,
	Line  = GL_LINE,
	Fill  = GL_FILL
};

template <>
__Range<PolygonMode> __EnumValueRange<PolygonMode>(void);

__StrCRef __EnumValueName(PolygonMode);

} // namespace oglplus
//]
