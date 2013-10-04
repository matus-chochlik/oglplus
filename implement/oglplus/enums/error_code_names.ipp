/*
 *  .file oglplus/enums/error_code_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/error_code.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	ErrorCode*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_ERRORCODE)
#define OGLPLUS_IMPL_EVN_ERRORCODE
{
switch(value)
{
#if defined GL_NO_ERROR
	case GL_NO_ERROR: return StrLit("NO_ERROR");
#endif
#if defined GL_OUT_OF_MEMORY
	case GL_OUT_OF_MEMORY: return StrLit("OUT_OF_MEMORY");
#endif
#if defined GL_INVALID_ENUM
	case GL_INVALID_ENUM: return StrLit("INVALID_ENUM");
#endif
#if defined GL_INVALID_VALUE
	case GL_INVALID_VALUE: return StrLit("INVALID_VALUE");
#endif
#if defined GL_INVALID_OPERATION
	case GL_INVALID_OPERATION: return StrLit("INVALID_OPERATION");
#endif
#if defined GL_INVALID_FRAMEBUFFER_OPERATION
	case GL_INVALID_FRAMEBUFFER_OPERATION: return StrLit("INVALID_FRAMEBUFFER_OPERATION");
#endif
#if defined GL_STACK_OVERFLOW
	case GL_STACK_OVERFLOW: return StrLit("STACK_OVERFLOW");
#endif
#if defined GL_STACK_UNDERFLOW
	case GL_STACK_UNDERFLOW: return StrLit("STACK_UNDERFLOW");
#endif
#if defined GL_TABLE_TOO_LARGE
	case GL_TABLE_TOO_LARGE: return StrLit("TABLE_TOO_LARGE");
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

