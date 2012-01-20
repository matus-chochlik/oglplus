/*
 *  .file oglplus/enums/provoke_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/provoke_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// FIRST_VERTEX_CONVENTION: First vertex convention
FirstVertexConvention,
/// LAST_VERTEX_CONVENTION: Last vertex convention
LastVertexConvention

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_FIRST_VERTEX_CONVENTION
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
FirstVertexConvention = GL_FIRST_VERTEX_CONVENTION
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LAST_VERTEX_CONVENTION
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LastVertexConvention = GL_LAST_VERTEX_CONVENTION
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

