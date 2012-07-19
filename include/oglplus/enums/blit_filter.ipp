/*
 *  .file oglplus/enums/blit_filter.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/blit_filter.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// NEAREST
Nearest,
/// LINEAR
Linear

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_NEAREST
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(Nearest, GL_NEAREST)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINEAR
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(Linear, GL_LINEAR)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

