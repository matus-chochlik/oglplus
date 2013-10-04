/*
 *  .file oglplus/enums/blend_function_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/blend_function.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	BlendFunction*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_BLENDFUNCTION)
#define OGLPLUS_IMPL_EVN_BLENDFUNCTION
{
switch(value)
{
#if defined GL_ZERO
	case GL_ZERO: return StrLit("ZERO");
#endif
#if defined GL_ONE
	case GL_ONE: return StrLit("ONE");
#endif
#if defined GL_SRC_COLOR
	case GL_SRC_COLOR: return StrLit("SRC_COLOR");
#endif
#if defined GL_ONE_MINUS_SRC_COLOR
	case GL_ONE_MINUS_SRC_COLOR: return StrLit("ONE_MINUS_SRC_COLOR");
#endif
#if defined GL_DST_COLOR
	case GL_DST_COLOR: return StrLit("DST_COLOR");
#endif
#if defined GL_ONE_MINUS_DST_COLOR
	case GL_ONE_MINUS_DST_COLOR: return StrLit("ONE_MINUS_DST_COLOR");
#endif
#if defined GL_SRC_ALPHA
	case GL_SRC_ALPHA: return StrLit("SRC_ALPHA");
#endif
#if defined GL_ONE_MINUS_SRC_ALPHA
	case GL_ONE_MINUS_SRC_ALPHA: return StrLit("ONE_MINUS_SRC_ALPHA");
#endif
#if defined GL_DST_ALPHA
	case GL_DST_ALPHA: return StrLit("DST_ALPHA");
#endif
#if defined GL_ONE_MINUS_DST_ALPHA
	case GL_ONE_MINUS_DST_ALPHA: return StrLit("ONE_MINUS_DST_ALPHA");
#endif
#if defined GL_CONSTANT_COLOR
	case GL_CONSTANT_COLOR: return StrLit("CONSTANT_COLOR");
#endif
#if defined GL_ONE_MINUS_CONSTANT_COLOR
	case GL_ONE_MINUS_CONSTANT_COLOR: return StrLit("ONE_MINUS_CONSTANT_COLOR");
#endif
#if defined GL_CONSTANT_ALPHA
	case GL_CONSTANT_ALPHA: return StrLit("CONSTANT_ALPHA");
#endif
#if defined GL_ONE_MINUS_CONSTANT_ALPHA
	case GL_ONE_MINUS_CONSTANT_ALPHA: return StrLit("ONE_MINUS_CONSTANT_ALPHA");
#endif
#if defined GL_SRC_ALPHA_SATURATE
	case GL_SRC_ALPHA_SATURATE: return StrLit("SRC_ALPHA_SATURATE");
#endif
#if defined GL_SRC1_COLOR
	case GL_SRC1_COLOR: return StrLit("SRC1_COLOR");
#endif
#if defined GL_ONE_MINUS_SRC1_COLOR
	case GL_ONE_MINUS_SRC1_COLOR: return StrLit("ONE_MINUS_SRC1_COLOR");
#endif
#if defined GL_SRC1_ALPHA
	case GL_SRC1_ALPHA: return StrLit("SRC1_ALPHA");
#endif
#if defined GL_ONE_MINUS_SRC1_ALPHA
	case GL_ONE_MINUS_SRC1_ALPHA: return StrLit("ONE_MINUS_SRC1_ALPHA");
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

