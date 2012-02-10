/*
 *  .file oglplus/enums/hint_target.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/hint_target.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// LINE_SMOOTH_HINT
LineSmooth,
/// POLYGON_SMOOTH_HINT
PolygonSmooth,
/// TEXTURE_COMPRESSION_HINT
TextureCompression,
/// FRAGMENT_SHADER_DERIVATIVE_HINT
FragmentShaderDerivative

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_LINE_SMOOTH_HINT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LineSmooth = GL_LINE_SMOOTH_HINT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_POLYGON_SMOOTH_HINT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
PolygonSmooth = GL_POLYGON_SMOOTH_HINT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TEXTURE_COMPRESSION_HINT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TextureCompression = GL_TEXTURE_COMPRESSION_HINT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAGMENT_SHADER_DERIVATIVE_HINT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
FragmentShaderDerivative = GL_FRAGMENT_SHADER_DERIVATIVE_HINT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

