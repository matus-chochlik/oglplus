/*
 *  .file oglplus/enums/compare_function_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/compare_function.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	CompareFunction*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_COMPAREFUNCTION)
#define OGLPLUS_IMPL_EVN_COMPAREFUNCTION
{
switch(value)
{
#if defined GL_LEQUAL
	case GL_LEQUAL: return StrLit("LEQUAL");
#endif
#if defined GL_GEQUAL
	case GL_GEQUAL: return StrLit("GEQUAL");
#endif
#if defined GL_LESS
	case GL_LESS: return StrLit("LESS");
#endif
#if defined GL_GREATER
	case GL_GREATER: return StrLit("GREATER");
#endif
#if defined GL_EQUAL
	case GL_EQUAL: return StrLit("EQUAL");
#endif
#if defined GL_NOTEQUAL
	case GL_NOTEQUAL: return StrLit("NOTEQUAL");
#endif
#if defined GL_ALWAYS
	case GL_ALWAYS: return StrLit("ALWAYS");
#endif
#if defined GL_NEVER
	case GL_NEVER: return StrLit("NEVER");
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

