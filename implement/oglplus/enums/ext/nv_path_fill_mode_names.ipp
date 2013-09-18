/*
 *  .file oglplus/enums/ext/nv_path_fill_mode_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_fill_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PathNVFillMode*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVFILLMODE)
#define OGLPLUS_IMPL_EVN_PATHNVFILLMODE
{
switch(value)
{
#if defined GL_INVERT
	case GL_INVERT: return StrLit("INVERT");
#endif
#if defined GL_COUNT_UP_NV
	case GL_COUNT_UP_NV: return StrLit("COUNT_UP_NV");
#endif
#if defined GL_COUNT_DOWN_NV
	case GL_COUNT_DOWN_NV: return StrLit("COUNT_DOWN_NV");
#endif
#if defined GL_PATH_FILL_MODE_NV
	case GL_PATH_FILL_MODE_NV: return StrLit("PATH_FILL_MODE_NV");
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

