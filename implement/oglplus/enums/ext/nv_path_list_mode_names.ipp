//  File implement/oglplus/enums/ext/nv_path_list_mode_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/nv_path_list_mode.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	PathNVListMode*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVLISTMODE)
#define OGLPLUS_IMPL_EVN_PATHNVLISTMODE
{
switch(value)
{
#if defined GL_ACCUM_ADJACENT_PAIRS_NV
	case GL_ACCUM_ADJACENT_PAIRS_NV: return CStrRef("ACCUM_ADJACENT_PAIRS_NV");
#endif
#if defined GL_ADJACENT_PAIRS_NV
	case GL_ADJACENT_PAIRS_NV: return CStrRef("ADJACENT_PAIRS_NV");
#endif
#if defined GL_FIRST_TO_REST_NV
	case GL_FIRST_TO_REST_NV: return CStrRef("FIRST_TO_REST_NV");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

