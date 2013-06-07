/*
 *  .file oglplus/enums/shader_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/shader_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/shader.hpp>

#include <boost/python.hpp>

void oglplus_py_shader_type(void)
{
	boost::python::enum_<oglplus::ShaderType>("ShaderType")
#if defined GL_VERTEX_SHADER
# if defined Vertex
#  pragma push_macro("Vertex")
#  undef Vertex
	.value("Vertex", oglplus::ShaderType::Vertex)
#  pragma pop_macro("Vertex")
# else
	.value("Vertex", oglplus::ShaderType::Vertex)
# endif
#endif
#if defined GL_TESS_CONTROL_SHADER
# if defined TessControl
#  pragma push_macro("TessControl")
#  undef TessControl
	.value("TessControl", oglplus::ShaderType::TessControl)
#  pragma pop_macro("TessControl")
# else
	.value("TessControl", oglplus::ShaderType::TessControl)
# endif
#endif
#if defined GL_TESS_EVALUATION_SHADER
# if defined TessEvaluation
#  pragma push_macro("TessEvaluation")
#  undef TessEvaluation
	.value("TessEvaluation", oglplus::ShaderType::TessEvaluation)
#  pragma pop_macro("TessEvaluation")
# else
	.value("TessEvaluation", oglplus::ShaderType::TessEvaluation)
# endif
#endif
#if defined GL_GEOMETRY_SHADER
# if defined Geometry
#  pragma push_macro("Geometry")
#  undef Geometry
	.value("Geometry", oglplus::ShaderType::Geometry)
#  pragma pop_macro("Geometry")
# else
	.value("Geometry", oglplus::ShaderType::Geometry)
# endif
#endif
#if defined GL_FRAGMENT_SHADER
# if defined Fragment
#  pragma push_macro("Fragment")
#  undef Fragment
	.value("Fragment", oglplus::ShaderType::Fragment)
#  pragma pop_macro("Fragment")
# else
	.value("Fragment", oglplus::ShaderType::Fragment)
# endif
#endif
#if defined GL_COMPUTE_SHADER
# if defined Compute
#  pragma push_macro("Compute")
#  undef Compute
	.value("Compute", oglplus::ShaderType::Compute)
#  pragma pop_macro("Compute")
# else
	.value("Compute", oglplus::ShaderType::Compute)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::ShaderType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
