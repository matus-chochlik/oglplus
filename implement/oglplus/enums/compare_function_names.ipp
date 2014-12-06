//  File implement/oglplus/enums/compare_function_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/compare_function.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	CompareFunction*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_COMPAREFUNCTION)
#define OGLPLUS_IMPL_EVN_COMPAREFUNCTION
{
switch(value)
{
#if defined GL_LEQUAL
	case GL_LEQUAL: return CStrRef("LEQUAL");
#endif
#if defined GL_GEQUAL
	case GL_GEQUAL: return CStrRef("GEQUAL");
#endif
#if defined GL_LESS
	case GL_LESS: return CStrRef("LESS");
#endif
#if defined GL_GREATER
	case GL_GREATER: return CStrRef("GREATER");
#endif
#if defined GL_EQUAL
	case GL_EQUAL: return CStrRef("EQUAL");
#endif
#if defined GL_NOTEQUAL
	case GL_NOTEQUAL: return CStrRef("NOTEQUAL");
#endif
#if defined GL_ALWAYS
	case GL_ALWAYS: return CStrRef("ALWAYS");
#endif
#if defined GL_NEVER
	case GL_NEVER: return CStrRef("NEVER");
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

