/*
 *  .file oglplus/enums/tess_gen_primitive_spacing.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/tess_gen_primitive_spacing.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// FRACTIONAL_EVEN
FractionalEven,
/// FRACTIONAL_ODD
FractionalOdd,
/// EQUAL
Equal

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_FRACTIONAL_EVEN
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FractionalEven)
#  pragma push_macro("FractionalEven")
#  undef FractionalEven
   OGLPLUS_ENUM_CLASS_VALUE(FractionalEven, GL_FRACTIONAL_EVEN)
#  pragma pop_macro("FractionalEven")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FractionalEven, GL_FRACTIONAL_EVEN)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRACTIONAL_ODD
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FractionalOdd)
#  pragma push_macro("FractionalOdd")
#  undef FractionalOdd
   OGLPLUS_ENUM_CLASS_VALUE(FractionalOdd, GL_FRACTIONAL_ODD)
#  pragma pop_macro("FractionalOdd")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FractionalOdd, GL_FRACTIONAL_ODD)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_EQUAL
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Equal)
#  pragma push_macro("Equal")
#  undef Equal
   OGLPLUS_ENUM_CLASS_VALUE(Equal, GL_EQUAL)
#  pragma pop_macro("Equal")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Equal, GL_EQUAL)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

