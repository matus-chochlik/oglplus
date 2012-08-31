/*
 *  .file oglplus/enums/access_specifier_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/access_specifier.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	AccessSpecifier*,
	GLenum value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
switch(value)
{
#if defined GL_READ_ONLY
	case GL_READ_ONLY: return StrLit("READ_ONLY");
#endif
#if defined GL_WRITE_ONLY
	case GL_WRITE_ONLY: return StrLit("WRITE_ONLY");
#endif
#if defined GL_READ_WRITE
	case GL_READ_WRITE: return StrLit("READ_WRITE");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#endif

