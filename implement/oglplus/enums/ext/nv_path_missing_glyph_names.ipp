/*
 *  .file oglplus/enums/ext/nv_path_missing_glyph_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_missing_glyph.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PathNVMissingGlyph*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVMISSINGGLYPH)
#define OGLPLUS_IMPL_EVN_PATHNVMISSINGGLYPH
{
switch(value)
{
#if defined GL_SKIP_MISSING_GLYPH_NV
	case GL_SKIP_MISSING_GLYPH_NV: return StrLit("SKIP_MISSING_GLYPH_NV");
#endif
#if defined GL_USE_MISSING_GLYPH_NV
	case GL_USE_MISSING_GLYPH_NV: return StrLit("USE_MISSING_GLYPH_NV");
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

