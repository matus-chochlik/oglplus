/*
 *  .file oglplus/enums/ext/nv_path_cap_style.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_cap_style.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// FLAT
Flat,
/// SQUARE_NV
Square,
/// ROUND_NV
Round,
/// TRIANGULAR_NV
Triangular

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_FLAT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Flat)
#  pragma push_macro("Flat")
#  undef Flat
   OGLPLUS_ENUM_CLASS_VALUE(Flat, GL_FLAT)
#  pragma pop_macro("Flat")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Flat, GL_FLAT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SQUARE_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Square)
#  pragma push_macro("Square")
#  undef Square
   OGLPLUS_ENUM_CLASS_VALUE(Square, GL_SQUARE_NV)
#  pragma pop_macro("Square")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Square, GL_SQUARE_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ROUND_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Round)
#  pragma push_macro("Round")
#  undef Round
   OGLPLUS_ENUM_CLASS_VALUE(Round, GL_ROUND_NV)
#  pragma pop_macro("Round")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Round, GL_ROUND_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TRIANGULAR_NV
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Triangular)
#  pragma push_macro("Triangular")
#  undef Triangular
   OGLPLUS_ENUM_CLASS_VALUE(Triangular, GL_TRIANGULAR_NV)
#  pragma pop_macro("Triangular")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Triangular, GL_TRIANGULAR_NV)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

