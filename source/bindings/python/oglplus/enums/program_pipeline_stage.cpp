/*
 *  .file oglplus/enums/program_pipeline_stage.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/program_pipeline_stage.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/program_pipeline.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_program_pipeline_stage(void)
{
	boost::python::enum_<oglplus::ProgramPipelineStage>("ProgramPipelineStage")
#if defined GL_VERTEX_SHADER_BIT
# if defined VertexShader
#  pragma push_macro("VertexShader")
#  undef VertexShader
	.value("VertexShader", oglplus::ProgramPipelineStage::VertexShader)
#  pragma pop_macro("VertexShader")
# else
	.value("VertexShader", oglplus::ProgramPipelineStage::VertexShader)
# endif
#endif
#if defined GL_TESS_CONTROL_SHADER_BIT
# if defined TessControlShader
#  pragma push_macro("TessControlShader")
#  undef TessControlShader
	.value("TessControlShader", oglplus::ProgramPipelineStage::TessControlShader)
#  pragma pop_macro("TessControlShader")
# else
	.value("TessControlShader", oglplus::ProgramPipelineStage::TessControlShader)
# endif
#endif
#if defined GL_TESS_EVALUATION_SHADER_BIT
# if defined TessEvaluationShader
#  pragma push_macro("TessEvaluationShader")
#  undef TessEvaluationShader
	.value("TessEvaluationShader", oglplus::ProgramPipelineStage::TessEvaluationShader)
#  pragma pop_macro("TessEvaluationShader")
# else
	.value("TessEvaluationShader", oglplus::ProgramPipelineStage::TessEvaluationShader)
# endif
#endif
#if defined GL_GEOMETRY_SHADER_BIT
# if defined GeometryShader
#  pragma push_macro("GeometryShader")
#  undef GeometryShader
	.value("GeometryShader", oglplus::ProgramPipelineStage::GeometryShader)
#  pragma pop_macro("GeometryShader")
# else
	.value("GeometryShader", oglplus::ProgramPipelineStage::GeometryShader)
# endif
#endif
#if defined GL_FRAGMENT_SHADER_BIT
# if defined FragmentShader
#  pragma push_macro("FragmentShader")
#  undef FragmentShader
	.value("FragmentShader", oglplus::ProgramPipelineStage::FragmentShader)
#  pragma pop_macro("FragmentShader")
# else
	.value("FragmentShader", oglplus::ProgramPipelineStage::FragmentShader)
# endif
#endif
#if defined GL_COMPUTE_SHADER_BIT
# if defined ComputeShader
#  pragma push_macro("ComputeShader")
#  undef ComputeShader
	.value("ComputeShader", oglplus::ProgramPipelineStage::ComputeShader)
#  pragma pop_macro("ComputeShader")
# else
	.value("ComputeShader", oglplus::ProgramPipelineStage::ComputeShader)
# endif
#endif
#if defined GL_ALL_SHADER_BITS
# if defined AllShaders
#  pragma push_macro("AllShaders")
#  undef AllShaders
	.value("AllShaders", oglplus::ProgramPipelineStage::AllShaders)
#  pragma pop_macro("AllShaders")
# else
	.value("AllShaders", oglplus::ProgramPipelineStage::AllShaders)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::ProgramPipelineStage) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLbitfield*,
			oglplus::ProgramPipelineStage
		>
	>("aux_CastIterRange_ProgramPipelineStage");

	oglplus::aux::CastIterRange<
		const GLbitfield*,
		oglplus::ProgramPipelineStage
	> (*PEnumValueRange)(oglplus::ProgramPipelineStage) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
