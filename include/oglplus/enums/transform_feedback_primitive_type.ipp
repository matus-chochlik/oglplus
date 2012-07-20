/*
 *  .file oglplus/enums/transform_feedback_primitive_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/transform_feedback_primitive_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// TRIANGLES
Triangles,
/// LINES
Lines,
/// POINTS
Points

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_TRIANGLES
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Triangles)
#  pragma push_macro("Triangles")
#  undef Triangles
   OGLPLUS_ENUM_CLASS_VALUE(Triangles, GL_TRIANGLES)
#  pragma pop_macro("Triangles")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Triangles, GL_TRIANGLES)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINES
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Lines)
#  pragma push_macro("Lines")
#  undef Lines
   OGLPLUS_ENUM_CLASS_VALUE(Lines, GL_LINES)
#  pragma pop_macro("Lines")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Lines, GL_LINES)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_POINTS
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Points)
#  pragma push_macro("Points")
#  undef Points
   OGLPLUS_ENUM_CLASS_VALUE(Points, GL_POINTS)
#  pragma pop_macro("Points")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Points, GL_POINTS)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

