/*
 *  .file oglplus/enums/ext/nv_path_command_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_command.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PathNVCommand*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVCOMMAND)
#define OGLPLUS_IMPL_EVN_PATHNVCOMMAND
{
switch(value)
{
#if defined GL_CLOSE_PATH_NV
	case GL_CLOSE_PATH_NV: return StrLit("CLOSE_PATH_NV");
#endif
#if defined GL_MOVE_TO_NV
	case GL_MOVE_TO_NV: return StrLit("MOVE_TO_NV");
#endif
#if defined GL_RELATIVE_MOVE_TO_NV
	case GL_RELATIVE_MOVE_TO_NV: return StrLit("RELATIVE_MOVE_TO_NV");
#endif
#if defined GL_LINE_TO_NV
	case GL_LINE_TO_NV: return StrLit("LINE_TO_NV");
#endif
#if defined GL_RELATIVE_LINE_TO_NV
	case GL_RELATIVE_LINE_TO_NV: return StrLit("RELATIVE_LINE_TO_NV");
#endif
#if defined GL_HORIZONTAL_LINE_TO_NV
	case GL_HORIZONTAL_LINE_TO_NV: return StrLit("HORIZONTAL_LINE_TO_NV");
#endif
#if defined GL_RELATIVE_HORIZONTAL_LINE_TO_NV
	case GL_RELATIVE_HORIZONTAL_LINE_TO_NV: return StrLit("RELATIVE_HORIZONTAL_LINE_TO_NV");
#endif
#if defined GL_VERTICAL_LINE_TO_NV
	case GL_VERTICAL_LINE_TO_NV: return StrLit("VERTICAL_LINE_TO_NV");
#endif
#if defined GL_RELATIVE_VERTICAL_LINE_TO_NV
	case GL_RELATIVE_VERTICAL_LINE_TO_NV: return StrLit("RELATIVE_VERTICAL_LINE_TO_NV");
#endif
#if defined GL_QUADRATIC_CURVE_TO_NV
	case GL_QUADRATIC_CURVE_TO_NV: return StrLit("QUADRATIC_CURVE_TO_NV");
#endif
#if defined GL_RELATIVE_QUADRATIC_CURVE_TO_NV
	case GL_RELATIVE_QUADRATIC_CURVE_TO_NV: return StrLit("RELATIVE_QUADRATIC_CURVE_TO_NV");
#endif
#if defined GL_CUBIC_CURVE_TO_NV
	case GL_CUBIC_CURVE_TO_NV: return StrLit("CUBIC_CURVE_TO_NV");
#endif
#if defined GL_RELATIVE_CUBIC_CURVE_TO_NV
	case GL_RELATIVE_CUBIC_CURVE_TO_NV: return StrLit("RELATIVE_CUBIC_CURVE_TO_NV");
#endif
#if defined GL_SMOOTH_QUADRATIC_CURVE_TO_NV
	case GL_SMOOTH_QUADRATIC_CURVE_TO_NV: return StrLit("SMOOTH_QUADRATIC_CURVE_TO_NV");
#endif
#if defined GL_RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV
	case GL_RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV: return StrLit("RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV");
#endif
#if defined GL_SMOOTH_CUBIC_CURVE_TO_NV
	case GL_SMOOTH_CUBIC_CURVE_TO_NV: return StrLit("SMOOTH_CUBIC_CURVE_TO_NV");
#endif
#if defined GL_RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV
	case GL_RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV: return StrLit("RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV");
#endif
#if defined GL_SMALL_CCW_ARC_TO_NV
	case GL_SMALL_CCW_ARC_TO_NV: return StrLit("SMALL_CCW_ARC_TO_NV");
#endif
#if defined GL_RELATIVE_SMALL_CCW_ARC_TO_NV
	case GL_RELATIVE_SMALL_CCW_ARC_TO_NV: return StrLit("RELATIVE_SMALL_CCW_ARC_TO_NV");
#endif
#if defined GL_SMALL_CW_ARC_TO_NV
	case GL_SMALL_CW_ARC_TO_NV: return StrLit("SMALL_CW_ARC_TO_NV");
#endif
#if defined GL_RELATIVE_SMALL_CW_ARC_TO_NV
	case GL_RELATIVE_SMALL_CW_ARC_TO_NV: return StrLit("RELATIVE_SMALL_CW_ARC_TO_NV");
#endif
#if defined GL_LARGE_CCW_ARC_TO_NV
	case GL_LARGE_CCW_ARC_TO_NV: return StrLit("LARGE_CCW_ARC_TO_NV");
#endif
#if defined GL_RELATIVE_LARGE_CCW_ARC_TO_NV
	case GL_RELATIVE_LARGE_CCW_ARC_TO_NV: return StrLit("RELATIVE_LARGE_CCW_ARC_TO_NV");
#endif
#if defined GL_LARGE_CW_ARC_TO_NV
	case GL_LARGE_CW_ARC_TO_NV: return StrLit("LARGE_CW_ARC_TO_NV");
#endif
#if defined GL_RELATIVE_LARGE_CW_ARC_TO_NV
	case GL_RELATIVE_LARGE_CW_ARC_TO_NV: return StrLit("RELATIVE_LARGE_CW_ARC_TO_NV");
#endif
#if defined GL_RESTART_PATH_NV
	case GL_RESTART_PATH_NV: return StrLit("RESTART_PATH_NV");
#endif
#if defined GL_DUP_FIRST_CUBIC_CURVE_TO_NV
	case GL_DUP_FIRST_CUBIC_CURVE_TO_NV: return StrLit("DUP_FIRST_CUBIC_CURVE_TO_NV");
#endif
#if defined GL_DUP_LAST_CUBIC_CURVE_TO_NV
	case GL_DUP_LAST_CUBIC_CURVE_TO_NV: return StrLit("DUP_LAST_CUBIC_CURVE_TO_NV");
#endif
#if defined GL_RECT_NV
	case GL_RECT_NV: return StrLit("RECT_NV");
#endif
#if defined GL_CIRCULAR_CCW_ARC_TO_NV
	case GL_CIRCULAR_CCW_ARC_TO_NV: return StrLit("CIRCULAR_CCW_ARC_TO_NV");
#endif
#if defined GL_CIRCULAR_CW_ARC_TO_NV
	case GL_CIRCULAR_CW_ARC_TO_NV: return StrLit("CIRCULAR_CW_ARC_TO_NV");
#endif
#if defined GL_CIRCULAR_TANGENT_ARC_TO_NV
	case GL_CIRCULAR_TANGENT_ARC_TO_NV: return StrLit("CIRCULAR_TANGENT_ARC_TO_NV");
#endif
#if defined GL_ARC_TO_NV
	case GL_ARC_TO_NV: return StrLit("ARC_TO_NV");
#endif
#if defined GL_RELATIVE_ARC_TO_NV
	case GL_RELATIVE_ARC_TO_NV: return StrLit("RELATIVE_ARC_TO_NV");
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

