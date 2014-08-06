//  File doc/quickbook/oglplus/quickref/enums/ext/compat_matrix_mode.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/compat_matrix_mode.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_ext_compat_matrix_mode
namespace oglplus {

enum class CompatibilityMatrixMode : GLenum
{
	Projection = GL_PROJECTION,
	Modelview  = GL_MODELVIEW,
	Texture    = GL_TEXTURE,
	Color      = GL_COLOR
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<CompatibilityMatrixMode> __EnumValueName<CompatibilityMatrixMode>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(CompatibilityMatrixMode);
#endif

} // namespace oglplus
//]
