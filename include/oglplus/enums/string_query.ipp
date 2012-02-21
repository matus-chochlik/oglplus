/*
 *  .file oglplus/enums/string_query.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/string_query.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// RENDERER
Renderer,
/// VENDOR
Vendor,
/// VERSION
Version,
/// SHADING_LANGUAGE_VERSION
ShadingLanguageVersion

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_RENDERER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Renderer = GL_RENDERER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_VENDOR
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Vendor = GL_VENDOR
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_VERSION
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Version = GL_VERSION
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SHADING_LANGUAGE_VERSION
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
ShadingLanguageVersion = GL_SHADING_LANGUAGE_VERSION
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

