//  File implement/oglplus/enums/blend_function_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/blend_function.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	BlendFunction*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_BLENDFUNCTION)
#define OGLPLUS_IMPL_EVN_BLENDFUNCTION
{
switch(value)
{
#if defined GL_ZERO
	case GL_ZERO: return CStrRef("ZERO");
#endif
#if defined GL_ONE
	case GL_ONE: return CStrRef("ONE");
#endif
#if defined GL_SRC_COLOR
	case GL_SRC_COLOR: return CStrRef("SRC_COLOR");
#endif
#if defined GL_ONE_MINUS_SRC_COLOR
	case GL_ONE_MINUS_SRC_COLOR: return CStrRef("ONE_MINUS_SRC_COLOR");
#endif
#if defined GL_DST_COLOR
	case GL_DST_COLOR: return CStrRef("DST_COLOR");
#endif
#if defined GL_ONE_MINUS_DST_COLOR
	case GL_ONE_MINUS_DST_COLOR: return CStrRef("ONE_MINUS_DST_COLOR");
#endif
#if defined GL_SRC_ALPHA
	case GL_SRC_ALPHA: return CStrRef("SRC_ALPHA");
#endif
#if defined GL_ONE_MINUS_SRC_ALPHA
	case GL_ONE_MINUS_SRC_ALPHA: return CStrRef("ONE_MINUS_SRC_ALPHA");
#endif
#if defined GL_DST_ALPHA
	case GL_DST_ALPHA: return CStrRef("DST_ALPHA");
#endif
#if defined GL_ONE_MINUS_DST_ALPHA
	case GL_ONE_MINUS_DST_ALPHA: return CStrRef("ONE_MINUS_DST_ALPHA");
#endif
#if defined GL_CONSTANT_COLOR
	case GL_CONSTANT_COLOR: return CStrRef("CONSTANT_COLOR");
#endif
#if defined GL_ONE_MINUS_CONSTANT_COLOR
	case GL_ONE_MINUS_CONSTANT_COLOR: return CStrRef("ONE_MINUS_CONSTANT_COLOR");
#endif
#if defined GL_CONSTANT_ALPHA
	case GL_CONSTANT_ALPHA: return CStrRef("CONSTANT_ALPHA");
#endif
#if defined GL_ONE_MINUS_CONSTANT_ALPHA
	case GL_ONE_MINUS_CONSTANT_ALPHA: return CStrRef("ONE_MINUS_CONSTANT_ALPHA");
#endif
#if defined GL_SRC_ALPHA_SATURATE
	case GL_SRC_ALPHA_SATURATE: return CStrRef("SRC_ALPHA_SATURATE");
#endif
#if defined GL_SRC1_COLOR
	case GL_SRC1_COLOR: return CStrRef("SRC1_COLOR");
#endif
#if defined GL_ONE_MINUS_SRC1_COLOR
	case GL_ONE_MINUS_SRC1_COLOR: return CStrRef("ONE_MINUS_SRC1_COLOR");
#endif
#if defined GL_SRC1_ALPHA
	case GL_SRC1_ALPHA: return CStrRef("SRC1_ALPHA");
#endif
#if defined GL_ONE_MINUS_SRC1_ALPHA
	case GL_ONE_MINUS_SRC1_ALPHA: return CStrRef("ONE_MINUS_SRC1_ALPHA");
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

