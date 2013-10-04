/*
 *  .file oglplus/enums/string_query_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/string_query.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	StringQuery*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_STRINGQUERY)
#define OGLPLUS_IMPL_EVN_STRINGQUERY
{
switch(value)
{
#if defined GL_RENDERER
	case GL_RENDERER: return StrLit("RENDERER");
#endif
#if defined GL_VENDOR
	case GL_VENDOR: return StrLit("VENDOR");
#endif
#if defined GL_VERSION
	case GL_VERSION: return StrLit("VERSION");
#endif
#if defined GL_SHADING_LANGUAGE_VERSION
	case GL_SHADING_LANGUAGE_VERSION: return StrLit("SHADING_LANGUAGE_VERSION");
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

