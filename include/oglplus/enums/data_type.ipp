/*
 *  .file oglplus/enums/data_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/data_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// BYTE
Byte,
/// SHORT
Short,
/// INT
Int,
/// FIXED
Fixed,
/// FLOAT
Float,
/// HALF_FLOAT
HalfFloat,
/// DOUBLE
Double,
/// UNSIGNED_BYTE
UnsignedByte,
/// UNSIGNED_SHORT
UnsignedShort,
/// UNSIGNED_INT
UnsignedInt

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_BYTE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Byte = GL_BYTE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SHORT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Short = GL_SHORT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Int = GL_INT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FIXED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Fixed = GL_FIXED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Float = GL_FLOAT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_HALF_FLOAT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
HalfFloat = GL_HALF_FLOAT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Double = GL_DOUBLE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_BYTE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
UnsignedByte = GL_UNSIGNED_BYTE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_SHORT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
UnsignedShort = GL_UNSIGNED_SHORT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
UnsignedInt = GL_UNSIGNED_INT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

