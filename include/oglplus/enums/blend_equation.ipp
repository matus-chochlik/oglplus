/*
 *  .file oglplus/enums/blend_equation.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/blend_equation.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// FUNC_ADD
Add,
/// FUNC_SUBTRACT
Subtract,
/// FUNC_REVERSE_SUBTRACT
ReverseSubtract,
/// MIN
Min,
/// MAX
Max

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_FUNC_ADD
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Add)
#  pragma push_macro("Add")
#  undef Add
   OGLPLUS_ENUM_CLASS_VALUE(Add, GL_FUNC_ADD)
#  pragma pop_macro("Add")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Add, GL_FUNC_ADD)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FUNC_SUBTRACT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Subtract)
#  pragma push_macro("Subtract")
#  undef Subtract
   OGLPLUS_ENUM_CLASS_VALUE(Subtract, GL_FUNC_SUBTRACT)
#  pragma pop_macro("Subtract")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Subtract, GL_FUNC_SUBTRACT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FUNC_REVERSE_SUBTRACT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ReverseSubtract)
#  pragma push_macro("ReverseSubtract")
#  undef ReverseSubtract
   OGLPLUS_ENUM_CLASS_VALUE(ReverseSubtract, GL_FUNC_REVERSE_SUBTRACT)
#  pragma pop_macro("ReverseSubtract")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ReverseSubtract, GL_FUNC_REVERSE_SUBTRACT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MIN
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Min)
#  pragma push_macro("Min")
#  undef Min
   OGLPLUS_ENUM_CLASS_VALUE(Min, GL_MIN)
#  pragma pop_macro("Min")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Min, GL_MIN)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MAX
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Max)
#  pragma push_macro("Max")
#  undef Max
   OGLPLUS_ENUM_CLASS_VALUE(Max, GL_MAX)
#  pragma pop_macro("Max")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Max, GL_MAX)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

