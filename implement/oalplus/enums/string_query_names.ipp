/*
 *  .file oalplus/enums/string_query_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/string_query.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OALPLUS_LIB_FUNC StrLit ValueName_(
	StringQuery*,
	ALenum value
)
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVN_STRINGQUERY)
#define OALPLUS_IMPL_EVN_STRINGQUERY
{
switch(value)
{
#if defined AL_VERSION
	case AL_VERSION: return StrLit("VERSION");
#endif
#if defined AL_RENDERER
	case AL_RENDERER: return StrLit("RENDERER");
#endif
#if defined AL_VENDOR
	case AL_VENDOR: return StrLit("VENDOR");
#endif
#if defined AL_EXTENSIONS
	case AL_EXTENSIONS: return StrLit("EXTENSIONS");
#endif
	default:;
}
OALPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

