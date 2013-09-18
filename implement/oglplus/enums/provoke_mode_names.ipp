/*
 *  .file oglplus/enums/provoke_mode_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/provoke_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	ProvokeMode*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PROVOKEMODE)
#define OGLPLUS_IMPL_EVN_PROVOKEMODE
{
switch(value)
{
#if defined GL_FIRST_VERTEX_CONVENTION
	case GL_FIRST_VERTEX_CONVENTION: return StrLit("FIRST_VERTEX_CONVENTION");
#endif
#if defined GL_LAST_VERTEX_CONVENTION
	case GL_LAST_VERTEX_CONVENTION: return StrLit("LAST_VERTEX_CONVENTION");
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

