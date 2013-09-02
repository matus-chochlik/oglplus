/*
 *  .file oglplus/enums/access_specifier_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/access_specifier.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_READ_ONLY
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined ReadOnly
#  pragma push_macro("ReadOnly")
#  undef ReadOnly
   OGLPLUS_ENUM_CLASS_VALUE(ReadOnly, GL_READ_ONLY)
#  pragma pop_macro("ReadOnly")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ReadOnly, GL_READ_ONLY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_WRITE_ONLY
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined WriteOnly
#  pragma push_macro("WriteOnly")
#  undef WriteOnly
   OGLPLUS_ENUM_CLASS_VALUE(WriteOnly, GL_WRITE_ONLY)
#  pragma pop_macro("WriteOnly")
# else
   OGLPLUS_ENUM_CLASS_VALUE(WriteOnly, GL_WRITE_ONLY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_READ_WRITE
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined ReadWrite
#  pragma push_macro("ReadWrite")
#  undef ReadWrite
   OGLPLUS_ENUM_CLASS_VALUE(ReadWrite, GL_READ_WRITE)
#  pragma pop_macro("ReadWrite")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ReadWrite, GL_READ_WRITE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

