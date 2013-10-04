/*
 *  .file oglplus/enums/patch_parameter_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/patch_parameter.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PatchParameter*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATCHPARAMETER)
#define OGLPLUS_IMPL_EVN_PATCHPARAMETER
{
switch(value)
{
#if defined GL_PATCH_VERTICES
	case GL_PATCH_VERTICES: return StrLit("PATCH_VERTICES");
#endif
#if defined GL_PATCH_DEFAULT_OUTER_LEVEL
	case GL_PATCH_DEFAULT_OUTER_LEVEL: return StrLit("PATCH_DEFAULT_OUTER_LEVEL");
#endif
#if defined GL_PATCH_DEFAULT_INNER_LEVEL
	case GL_PATCH_DEFAULT_INNER_LEVEL: return StrLit("PATCH_DEFAULT_INNER_LEVEL");
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

