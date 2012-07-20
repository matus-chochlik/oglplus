/*
 *  .file oglplus/enums/ext/amd_perf_monitor_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/amd_perf_monitor_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// UNSIGNED_INT
UnsignedInt,
/// FLOAT
Float,
/// UNSIGNED_INT64_AMD
UnsignedInt64,
/// PERCENTAGE_AMD
Percentage

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_UNSIGNED_INT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedInt)
#  pragma push_macro("UnsignedInt")
#  undef UnsignedInt
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedInt, GL_UNSIGNED_INT)
#  pragma pop_macro("UnsignedInt")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedInt, GL_UNSIGNED_INT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Float)
#  pragma push_macro("Float")
#  undef Float
   OGLPLUS_ENUM_CLASS_VALUE(Float, GL_FLOAT)
#  pragma pop_macro("Float")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Float, GL_FLOAT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT64_AMD
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedInt64)
#  pragma push_macro("UnsignedInt64")
#  undef UnsignedInt64
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedInt64, GL_UNSIGNED_INT64_AMD)
#  pragma pop_macro("UnsignedInt64")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedInt64, GL_UNSIGNED_INT64_AMD)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PERCENTAGE_AMD
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Percentage)
#  pragma push_macro("Percentage")
#  undef Percentage
   OGLPLUS_ENUM_CLASS_VALUE(Percentage, GL_PERCENTAGE_AMD)
#  pragma pop_macro("Percentage")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Percentage, GL_PERCENTAGE_AMD)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

