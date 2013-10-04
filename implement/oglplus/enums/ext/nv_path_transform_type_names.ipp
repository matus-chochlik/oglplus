/*
 *  .file oglplus/enums/ext/nv_path_transform_type_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_transform_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PathNVTransformType*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVTRANSFORMTYPE)
#define OGLPLUS_IMPL_EVN_PATHNVTRANSFORMTYPE
{
switch(value)
{
#if defined GL_NONE
	case GL_NONE: return StrLit("NONE");
#endif
#if defined GL_TRANSLATE_X_NV
	case GL_TRANSLATE_X_NV: return StrLit("TRANSLATE_X_NV");
#endif
#if defined GL_TRANSLATE_Y_NV
	case GL_TRANSLATE_Y_NV: return StrLit("TRANSLATE_Y_NV");
#endif
#if defined GL_TRANSLATE_2D_NV
	case GL_TRANSLATE_2D_NV: return StrLit("TRANSLATE_2D_NV");
#endif
#if defined GL_TRANSLATE_3D_NV
	case GL_TRANSLATE_3D_NV: return StrLit("TRANSLATE_3D_NV");
#endif
#if defined GL_AFFINE_2D_NV
	case GL_AFFINE_2D_NV: return StrLit("AFFINE_2D_NV");
#endif
#if defined GL_AFFINE_3D_NV
	case GL_AFFINE_3D_NV: return StrLit("AFFINE_3D_NV");
#endif
#if defined GL_TRANSPOSE_AFFINE_2D_NV
	case GL_TRANSPOSE_AFFINE_2D_NV: return StrLit("TRANSPOSE_AFFINE_2D_NV");
#endif
#if defined GL_TRANSPOSE_AFFINE_3D_NV
	case GL_TRANSPOSE_AFFINE_3D_NV: return StrLit("TRANSPOSE_AFFINE_3D_NV");
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

