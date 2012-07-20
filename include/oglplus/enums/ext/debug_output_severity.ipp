/*
 *  .file oglplus/enums/ext/debug_output_severity.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/debug_output_severity.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// DEBUG_SEVERITY_HIGH_ARB
High,
/// DEBUG_SEVERITY_MEDIUM_ARB
Medium,
/// DEBUG_SEVERITY_LOW_ARB
Low,
/// DONT_CARE
DontCare

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_DEBUG_SEVERITY_HIGH_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(High)
#  pragma push_macro("High")
#  undef High
   OGLPLUS_ENUM_CLASS_VALUE(High, GL_DEBUG_SEVERITY_HIGH_ARB)
#  pragma pop_macro("High")
# else
   OGLPLUS_ENUM_CLASS_VALUE(High, GL_DEBUG_SEVERITY_HIGH_ARB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEBUG_SEVERITY_MEDIUM_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Medium)
#  pragma push_macro("Medium")
#  undef Medium
   OGLPLUS_ENUM_CLASS_VALUE(Medium, GL_DEBUG_SEVERITY_MEDIUM_ARB)
#  pragma pop_macro("Medium")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Medium, GL_DEBUG_SEVERITY_MEDIUM_ARB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEBUG_SEVERITY_LOW_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Low)
#  pragma push_macro("Low")
#  undef Low
   OGLPLUS_ENUM_CLASS_VALUE(Low, GL_DEBUG_SEVERITY_LOW_ARB)
#  pragma pop_macro("Low")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Low, GL_DEBUG_SEVERITY_LOW_ARB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DONT_CARE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DontCare)
#  pragma push_macro("DontCare")
#  undef DontCare
   OGLPLUS_ENUM_CLASS_VALUE(DontCare, GL_DONT_CARE)
#  pragma pop_macro("DontCare")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DontCare, GL_DONT_CARE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

