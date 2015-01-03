//  File implement/oglplus/enums/error_code_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/error_code.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	ErrorCode*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_ERRORCODE)
#define OGLPLUS_IMPL_EVN_ERRORCODE
{
switch(value)
{
#if defined GL_NO_ERROR
	case GL_NO_ERROR: return CStrRef("NO_ERROR");
#endif
#if defined GL_OUT_OF_MEMORY
	case GL_OUT_OF_MEMORY: return CStrRef("OUT_OF_MEMORY");
#endif
#if defined GL_INVALID_ENUM
	case GL_INVALID_ENUM: return CStrRef("INVALID_ENUM");
#endif
#if defined GL_INVALID_VALUE
	case GL_INVALID_VALUE: return CStrRef("INVALID_VALUE");
#endif
#if defined GL_INVALID_OPERATION
	case GL_INVALID_OPERATION: return CStrRef("INVALID_OPERATION");
#endif
#if defined GL_INVALID_FRAMEBUFFER_OPERATION
	case GL_INVALID_FRAMEBUFFER_OPERATION: return CStrRef("INVALID_FRAMEBUFFER_OPERATION");
#endif
#if defined GL_STACK_OVERFLOW
	case GL_STACK_OVERFLOW: return CStrRef("STACK_OVERFLOW");
#endif
#if defined GL_STACK_UNDERFLOW
	case GL_STACK_UNDERFLOW: return CStrRef("STACK_UNDERFLOW");
#endif
#if defined GL_TABLE_TOO_LARGE
	case GL_TABLE_TOO_LARGE: return CStrRef("TABLE_TOO_LARGE");
#endif
#if defined GL_CONTEXT_LOST
	case GL_CONTEXT_LOST: return CStrRef("CONTEXT_LOST");
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

