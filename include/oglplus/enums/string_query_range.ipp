/*
 *  .file oglplus/enums/string_query_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/string_query.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	StringQuery
> EnumValueRange(StringQuery*)
OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
static const GLenum _values[] = {
#if defined GL_RENDERER
GL_RENDERER,
#endif
#if defined GL_VENDOR
GL_VENDOR,
#endif
#if defined GL_VERSION
GL_VERSION,
#endif
#if defined GL_SHADING_LANGUAGE_VERSION
GL_SHADING_LANGUAGE_VERSION,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	StringQuery
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#endif

