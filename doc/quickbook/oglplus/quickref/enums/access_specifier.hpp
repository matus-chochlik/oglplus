//  File doc/quickbook/oglplus/quickref/enums/access_specifier.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/access_specifier.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_access_specifier
namespace oglplus {

enum class AccessSpecifier : GLenum
{
	ReadOnly  = GL_READ_ONLY,
	WriteOnly = GL_WRITE_ONLY,
	ReadWrite = GL_READ_WRITE
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<AccessSpecifier> __EnumValueName<AccessSpecifier>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(AccessSpecifier);
#endif

} // namespace oglplus
//]
