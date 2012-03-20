/*
 *  .file oglplus/enums/error_code.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/error_code.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// NO_ERROR
NoError,
/// OUT_OF_MEMORY
OutOfMemory,
/// INVALID_ENUM
InvalidEnum,
/// INVALID_VALUE
InvalidValue,
/// INVALID_OPERATION
InvalidOperation,
/// INVALID_FRAMEBUFFER_OPERATION
InvalidFramebufferOperation,
/// STACK_OVERFLOW
StackOverflow,
/// STACK_UNDERFLOW
StackUnderflow,
/// TABLE_TOO_LARGE
TableTooLarge

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_NO_ERROR
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
NoError = GL_NO_ERROR
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_OUT_OF_MEMORY
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
OutOfMemory = GL_OUT_OF_MEMORY
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INVALID_ENUM
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
InvalidEnum = GL_INVALID_ENUM
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INVALID_VALUE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
InvalidValue = GL_INVALID_VALUE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INVALID_OPERATION
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
InvalidOperation = GL_INVALID_OPERATION
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INVALID_FRAMEBUFFER_OPERATION
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STACK_OVERFLOW
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
StackOverflow = GL_STACK_OVERFLOW
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STACK_UNDERFLOW
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
StackUnderflow = GL_STACK_UNDERFLOW
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TABLE_TOO_LARGE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TableTooLarge = GL_TABLE_TOO_LARGE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

