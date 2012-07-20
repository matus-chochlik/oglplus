/*
 *  .file oglplus/enums/program_pipeline_stage.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/program_pipeline_stage.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
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

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_VERTEX_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(VertexShader)
#  pragma push_macro("VertexShader")
#  undef VertexShader
   OGLPLUS_ENUM_CLASS_VALUE(VertexShader, GL_VERTEX_SHADER_BIT)
#  pragma pop_macro("VertexShader")
# else
   OGLPLUS_ENUM_CLASS_VALUE(VertexShader, GL_VERTEX_SHADER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TESS_CONTROL_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(TessControlShader)
#  pragma push_macro("TessControlShader")
#  undef TessControlShader
   OGLPLUS_ENUM_CLASS_VALUE(TessControlShader, GL_TESS_CONTROL_SHADER_BIT)
#  pragma pop_macro("TessControlShader")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TessControlShader, GL_TESS_CONTROL_SHADER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TESS_EVALUATION_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(TessEvaluationShader)
#  pragma push_macro("TessEvaluationShader")
#  undef TessEvaluationShader
   OGLPLUS_ENUM_CLASS_VALUE(TessEvaluationShader, GL_TESS_EVALUATION_SHADER_BIT)
#  pragma pop_macro("TessEvaluationShader")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TessEvaluationShader, GL_TESS_EVALUATION_SHADER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_GEOMETRY_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(GeometryShader)
#  pragma push_macro("GeometryShader")
#  undef GeometryShader
   OGLPLUS_ENUM_CLASS_VALUE(GeometryShader, GL_GEOMETRY_SHADER_BIT)
#  pragma pop_macro("GeometryShader")
# else
   OGLPLUS_ENUM_CLASS_VALUE(GeometryShader, GL_GEOMETRY_SHADER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAGMENT_SHADER_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FragmentShader)
#  pragma push_macro("FragmentShader")
#  undef FragmentShader
   OGLPLUS_ENUM_CLASS_VALUE(FragmentShader, GL_FRAGMENT_SHADER_BIT)
#  pragma pop_macro("FragmentShader")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FragmentShader, GL_FRAGMENT_SHADER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ALL_SHADER_BITS
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(AllShaders)
#  pragma push_macro("AllShaders")
#  undef AllShaders
   OGLPLUS_ENUM_CLASS_VALUE(AllShaders, GL_ALL_SHADER_BITS)
#  pragma pop_macro("AllShaders")
# else
   OGLPLUS_ENUM_CLASS_VALUE(AllShaders, GL_ALL_SHADER_BITS)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

