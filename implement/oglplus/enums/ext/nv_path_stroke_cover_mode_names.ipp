/*
 *  .file oglplus/enums/ext/nv_path_stroke_cover_mode_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_stroke_cover_mode.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	PathNVStrokeCoverMode*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVSTROKECOVERMODE)
#define OGLPLUS_IMPL_EVN_PATHNVSTROKECOVERMODE
{
switch(value)
{
#if defined GL_CONVEX_HULL_NV
	case GL_CONVEX_HULL_NV: return StrCRef("CONVEX_HULL_NV");
#endif
#if defined GL_BOUNDING_BOX_NV
	case GL_BOUNDING_BOX_NV: return StrCRef("BOUNDING_BOX_NV");
#endif
#if defined GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV
	case GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV: return StrCRef("BOUNDING_BOX_OF_BOUNDING_BOXES_NV");
#endif
#if defined GL_PATH_STROKE_COVER_MODE_NV
	case GL_PATH_STROKE_COVER_MODE_NV: return StrCRef("PATH_STROKE_COVER_MODE_NV");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrCRef();
}
#else
;
#endif
} // namespace enums

