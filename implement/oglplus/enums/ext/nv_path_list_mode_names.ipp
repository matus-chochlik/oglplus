/*
 *  .file oglplus/enums/ext/nv_path_list_mode_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_list_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PathNVListMode*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVLISTMODE)
#define OGLPLUS_IMPL_EVN_PATHNVLISTMODE
{
switch(value)
{
#if defined GL_ACCUM_ADJACENT_PAIRS_NV
	case GL_ACCUM_ADJACENT_PAIRS_NV: return StrLit("ACCUM_ADJACENT_PAIRS_NV");
#endif
#if defined GL_ADJACENT_PAIRS_NV
	case GL_ADJACENT_PAIRS_NV: return StrLit("ADJACENT_PAIRS_NV");
#endif
#if defined GL_FIRST_TO_REST_NV
	case GL_FIRST_TO_REST_NV: return StrLit("FIRST_TO_REST_NV");
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

