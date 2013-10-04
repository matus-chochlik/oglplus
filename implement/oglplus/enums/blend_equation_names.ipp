/*
 *  .file oglplus/enums/blend_equation_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/blend_equation.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	BlendEquation*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_BLENDEQUATION)
#define OGLPLUS_IMPL_EVN_BLENDEQUATION
{
switch(value)
{
#if defined GL_FUNC_ADD
	case GL_FUNC_ADD: return StrLit("FUNC_ADD");
#endif
#if defined GL_FUNC_SUBTRACT
	case GL_FUNC_SUBTRACT: return StrLit("FUNC_SUBTRACT");
#endif
#if defined GL_FUNC_REVERSE_SUBTRACT
	case GL_FUNC_REVERSE_SUBTRACT: return StrLit("FUNC_REVERSE_SUBTRACT");
#endif
#if defined GL_MIN
	case GL_MIN: return StrLit("MIN");
#endif
#if defined GL_MAX
	case GL_MAX: return StrLit("MAX");
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

