/*
 *  .file oglplus/enums/shader_type_ese.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/shader_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if defined GL_VERTEX_SHADER
# if defined Vertex
#  pragma push_macro("Vertex")
#  undef Vertex
   OGLPLUS_ENUM_CLASS_VALUE(Vertex, GL_VERTEX_SHADER)
#  pragma pop_macro("Vertex")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Vertex, GL_VERTEX_SHADER)
# endif
#endif
#if defined GL_TESS_CONTROL_SHADER
# if defined TessControl
#  pragma push_macro("TessControl")
#  undef TessControl
   OGLPLUS_ENUM_CLASS_VALUE(TessControl, GL_TESS_CONTROL_SHADER)
#  pragma pop_macro("TessControl")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TessControl, GL_TESS_CONTROL_SHADER)
# endif
#endif
#if defined GL_TESS_EVALUATION_SHADER
# if defined TessEvaluation
#  pragma push_macro("TessEvaluation")
#  undef TessEvaluation
   OGLPLUS_ENUM_CLASS_VALUE(TessEvaluation, GL_TESS_EVALUATION_SHADER)
#  pragma pop_macro("TessEvaluation")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TessEvaluation, GL_TESS_EVALUATION_SHADER)
# endif
#endif
#if defined GL_GEOMETRY_SHADER
# if defined Geometry
#  pragma push_macro("Geometry")
#  undef Geometry
   OGLPLUS_ENUM_CLASS_VALUE(Geometry, GL_GEOMETRY_SHADER)
#  pragma pop_macro("Geometry")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Geometry, GL_GEOMETRY_SHADER)
# endif
#endif
#if defined GL_FRAGMENT_SHADER
# if defined Fragment
#  pragma push_macro("Fragment")
#  undef Fragment
   OGLPLUS_ENUM_CLASS_VALUE(Fragment, GL_FRAGMENT_SHADER)
#  pragma pop_macro("Fragment")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Fragment, GL_FRAGMENT_SHADER)
# endif
#endif
#if defined GL_COMPUTE_SHADER
# if defined Compute
#  pragma push_macro("Compute")
#  undef Compute
   OGLPLUS_ENUM_CLASS_VALUE(Compute, GL_COMPUTE_SHADER)
#  pragma pop_macro("Compute")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Compute, GL_COMPUTE_SHADER)
# endif
#endif
