/*
 *  .file oglplus/enums/polygon_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/polygon_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// POINT
Point,
/// LINE
Line,
/// FILL
Fill

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_POINT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Point)
#  pragma push_macro("Point")
#  undef Point
   OGLPLUS_ENUM_CLASS_VALUE(Point, GL_POINT)
#  pragma pop_macro("Point")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Point, GL_POINT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Line)
#  pragma push_macro("Line")
#  undef Line
   OGLPLUS_ENUM_CLASS_VALUE(Line, GL_LINE)
#  pragma pop_macro("Line")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Line, GL_LINE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FILL
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Fill)
#  pragma push_macro("Fill")
#  undef Fill
   OGLPLUS_ENUM_CLASS_VALUE(Fill, GL_FILL)
#  pragma pop_macro("Fill")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Fill, GL_FILL)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

