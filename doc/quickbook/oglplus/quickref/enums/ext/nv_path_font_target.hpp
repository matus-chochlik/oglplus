//  File doc/quickbook/oglplus/quickref/enums/ext/nv_path_font_target.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/nv_path_font_target.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_ext_nv_path_font_target

enum class PathNVFontTarget : GLenum
{
	Standard = GL_STANDARD_FONT_NAME_NV,
	System   = GL_SYSTEM_FONT_NAME_NV,
	FileName = GL_FILE_NAME_NV
};

template <>
__Range<PathNVFontTarget> __EnumValueRange<PathNVFontTarget>(void);

__StrCRef __EnumValueName(PathNVFontTarget);

//]
