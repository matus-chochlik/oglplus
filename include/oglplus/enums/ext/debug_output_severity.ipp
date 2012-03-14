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
Low

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_DEBUG_SEVERITY_HIGH_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
High = GL_DEBUG_SEVERITY_HIGH_ARB
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEBUG_SEVERITY_MEDIUM_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Medium = GL_DEBUG_SEVERITY_MEDIUM_ARB
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEBUG_SEVERITY_LOW_ARB
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Low = GL_DEBUG_SEVERITY_LOW_ARB
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

