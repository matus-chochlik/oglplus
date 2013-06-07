/*
 *  .file oglplus/enums/error_code.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/error_code.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/context/errors.hpp>

#include <boost/python.hpp>

void oglplus_py_error_code(void)
{
	boost::python::enum_<oglplus::ErrorCode>("ErrorCode")
#if defined GL_NO_ERROR
# if defined NoError
#  pragma push_macro("NoError")
#  undef NoError
	.value("NoError", oglplus::ErrorCode::NoError)
#  pragma pop_macro("NoError")
# else
	.value("NoError", oglplus::ErrorCode::NoError)
# endif
#endif
#if defined GL_OUT_OF_MEMORY
# if defined OutOfMemory
#  pragma push_macro("OutOfMemory")
#  undef OutOfMemory
	.value("OutOfMemory", oglplus::ErrorCode::OutOfMemory)
#  pragma pop_macro("OutOfMemory")
# else
	.value("OutOfMemory", oglplus::ErrorCode::OutOfMemory)
# endif
#endif
#if defined GL_INVALID_ENUM
# if defined InvalidEnum
#  pragma push_macro("InvalidEnum")
#  undef InvalidEnum
	.value("InvalidEnum", oglplus::ErrorCode::InvalidEnum)
#  pragma pop_macro("InvalidEnum")
# else
	.value("InvalidEnum", oglplus::ErrorCode::InvalidEnum)
# endif
#endif
#if defined GL_INVALID_VALUE
# if defined InvalidValue
#  pragma push_macro("InvalidValue")
#  undef InvalidValue
	.value("InvalidValue", oglplus::ErrorCode::InvalidValue)
#  pragma pop_macro("InvalidValue")
# else
	.value("InvalidValue", oglplus::ErrorCode::InvalidValue)
# endif
#endif
#if defined GL_INVALID_OPERATION
# if defined InvalidOperation
#  pragma push_macro("InvalidOperation")
#  undef InvalidOperation
	.value("InvalidOperation", oglplus::ErrorCode::InvalidOperation)
#  pragma pop_macro("InvalidOperation")
# else
	.value("InvalidOperation", oglplus::ErrorCode::InvalidOperation)
# endif
#endif
#if defined GL_INVALID_FRAMEBUFFER_OPERATION
# if defined InvalidFramebufferOperation
#  pragma push_macro("InvalidFramebufferOperation")
#  undef InvalidFramebufferOperation
	.value("InvalidFramebufferOperation", oglplus::ErrorCode::InvalidFramebufferOperation)
#  pragma pop_macro("InvalidFramebufferOperation")
# else
	.value("InvalidFramebufferOperation", oglplus::ErrorCode::InvalidFramebufferOperation)
# endif
#endif
#if defined GL_STACK_OVERFLOW
# if defined StackOverflow
#  pragma push_macro("StackOverflow")
#  undef StackOverflow
	.value("StackOverflow", oglplus::ErrorCode::StackOverflow)
#  pragma pop_macro("StackOverflow")
# else
	.value("StackOverflow", oglplus::ErrorCode::StackOverflow)
# endif
#endif
#if defined GL_STACK_UNDERFLOW
# if defined StackUnderflow
#  pragma push_macro("StackUnderflow")
#  undef StackUnderflow
	.value("StackUnderflow", oglplus::ErrorCode::StackUnderflow)
#  pragma pop_macro("StackUnderflow")
# else
	.value("StackUnderflow", oglplus::ErrorCode::StackUnderflow)
# endif
#endif
#if defined GL_TABLE_TOO_LARGE
# if defined TableTooLarge
#  pragma push_macro("TableTooLarge")
#  undef TableTooLarge
	.value("TableTooLarge", oglplus::ErrorCode::TableTooLarge)
#  pragma pop_macro("TableTooLarge")
# else
	.value("TableTooLarge", oglplus::ErrorCode::TableTooLarge)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::ErrorCode) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
