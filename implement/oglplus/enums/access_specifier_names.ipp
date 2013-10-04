/*
 *  .file oglplus/enums/access_specifier_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/access_specifier.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	AccessSpecifier*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_ACCESSSPECIFIER)
#define OGLPLUS_IMPL_EVN_ACCESSSPECIFIER
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
#else
;
#endif
} // namespace enums

