/*
 *  .file oglplus/enums/program_pipeline_stage.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/program_pipeline_stage.txt' instead.
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// VERTEX_SHADER_BIT
VertexShader,
/// TESS_CONTROL_SHADER_BIT
TessControlShader,
/// TESS_EVALUATION_SHADER_BIT
TessEvaluationShader,
/// GEOMETRY_SHADER_BIT
GeometryShader,
/// FRAGMENT_SHADER_BIT
FragmentShader,
/// ALL_SHADER_BITS
AllShaders

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_VERTEX_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
VertexShader = GL_VERTEX_SHADER_BIT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TESS_CONTROL_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TessControlShader = GL_TESS_CONTROL_SHADER_BIT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TESS_EVALUATION_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TessEvaluationShader = GL_TESS_EVALUATION_SHADER_BIT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_GEOMETRY_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
GeometryShader = GL_GEOMETRY_SHADER_BIT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAGMENT_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
FragmentShader = GL_FRAGMENT_SHADER_BIT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ALL_SHADER_BITS
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
AllShaders = GL_ALL_SHADER_BITS
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

