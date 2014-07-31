/*
 *  .file oglplus/enums/tess_gen_primitive_spacing_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/tess_gen_primitive_spacing.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	TessGenPrimitiveSpacing*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_TESSGENPRIMITIVESPACING)
#define OGLPLUS_IMPL_EVN_TESSGENPRIMITIVESPACING
{
switch(value)
{
#if defined GL_FRACTIONAL_EVEN
	case GL_FRACTIONAL_EVEN: return StrCRef("FRACTIONAL_EVEN");
#endif
#if defined GL_FRACTIONAL_ODD
	case GL_FRACTIONAL_ODD: return StrCRef("FRACTIONAL_ODD");
#endif
#if defined GL_EQUAL
	case GL_EQUAL: return StrCRef("EQUAL");
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

