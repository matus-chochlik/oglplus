/*
 *  .file oglplus/enums/program_interface.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/program_interface.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/program_interface.hpp>

#include <boost/python.hpp>

void oglplus_py_program_interface(void)
{
	boost::python::enum_<oglplus::ProgramInterface>("ProgramInterface")
#if defined GL_UNIFORM
# if defined Uniform
#  pragma push_macro("Uniform")
#  undef Uniform
	.value("Uniform", oglplus::ProgramInterface::Uniform)
#  pragma pop_macro("Uniform")
# else
	.value("Uniform", oglplus::ProgramInterface::Uniform)
# endif
#endif
#if defined GL_UNIFORM_BLOCK
# if defined UniformBlock
#  pragma push_macro("UniformBlock")
#  undef UniformBlock
	.value("UniformBlock", oglplus::ProgramInterface::UniformBlock)
#  pragma pop_macro("UniformBlock")
# else
	.value("UniformBlock", oglplus::ProgramInterface::UniformBlock)
# endif
#endif
#if defined GL_ATOMIC_COUNTER_BUFFER
# if defined AtomicCounterBuffer
#  pragma push_macro("AtomicCounterBuffer")
#  undef AtomicCounterBuffer
	.value("AtomicCounterBuffer", oglplus::ProgramInterface::AtomicCounterBuffer)
#  pragma pop_macro("AtomicCounterBuffer")
# else
	.value("AtomicCounterBuffer", oglplus::ProgramInterface::AtomicCounterBuffer)
# endif
#endif
#if defined GL_PROGRAM_INPUT
# if defined ProgramInput
#  pragma push_macro("ProgramInput")
#  undef ProgramInput
	.value("ProgramInput", oglplus::ProgramInterface::ProgramInput)
#  pragma pop_macro("ProgramInput")
# else
	.value("ProgramInput", oglplus::ProgramInterface::ProgramInput)
# endif
#endif
#if defined GL_PROGRAM_OUTPUT
# if defined ProgramOutput
#  pragma push_macro("ProgramOutput")
#  undef ProgramOutput
	.value("ProgramOutput", oglplus::ProgramInterface::ProgramOutput)
#  pragma pop_macro("ProgramOutput")
# else
	.value("ProgramOutput", oglplus::ProgramInterface::ProgramOutput)
# endif
#endif
#if defined GL_VERTEX_SUBROUTINE
# if defined VertexSubroutine
#  pragma push_macro("VertexSubroutine")
#  undef VertexSubroutine
	.value("VertexSubroutine", oglplus::ProgramInterface::VertexSubroutine)
#  pragma pop_macro("VertexSubroutine")
# else
	.value("VertexSubroutine", oglplus::ProgramInterface::VertexSubroutine)
# endif
#endif
#if defined GL_TESS_CONTROL_SUBROUTINE
# if defined TessControlSubroutine
#  pragma push_macro("TessControlSubroutine")
#  undef TessControlSubroutine
	.value("TessControlSubroutine", oglplus::ProgramInterface::TessControlSubroutine)
#  pragma pop_macro("TessControlSubroutine")
# else
	.value("TessControlSubroutine", oglplus::ProgramInterface::TessControlSubroutine)
# endif
#endif
#if defined GL_TESS_EVALUATION_SUBROUTINE
# if defined TessEvaluationSubroutine
#  pragma push_macro("TessEvaluationSubroutine")
#  undef TessEvaluationSubroutine
	.value("TessEvaluationSubroutine", oglplus::ProgramInterface::TessEvaluationSubroutine)
#  pragma pop_macro("TessEvaluationSubroutine")
# else
	.value("TessEvaluationSubroutine", oglplus::ProgramInterface::TessEvaluationSubroutine)
# endif
#endif
#if defined GL_GEOMETRY_SUBROUTINE
# if defined GeometrySubroutine
#  pragma push_macro("GeometrySubroutine")
#  undef GeometrySubroutine
	.value("GeometrySubroutine", oglplus::ProgramInterface::GeometrySubroutine)
#  pragma pop_macro("GeometrySubroutine")
# else
	.value("GeometrySubroutine", oglplus::ProgramInterface::GeometrySubroutine)
# endif
#endif
#if defined GL_FRAGMENT_SUBROUTINE
# if defined FragmentSubroutine
#  pragma push_macro("FragmentSubroutine")
#  undef FragmentSubroutine
	.value("FragmentSubroutine", oglplus::ProgramInterface::FragmentSubroutine)
#  pragma pop_macro("FragmentSubroutine")
# else
	.value("FragmentSubroutine", oglplus::ProgramInterface::FragmentSubroutine)
# endif
#endif
#if defined GL_COMPUTE_SUBROUTINE
# if defined ComputeSubroutine
#  pragma push_macro("ComputeSubroutine")
#  undef ComputeSubroutine
	.value("ComputeSubroutine", oglplus::ProgramInterface::ComputeSubroutine)
#  pragma pop_macro("ComputeSubroutine")
# else
	.value("ComputeSubroutine", oglplus::ProgramInterface::ComputeSubroutine)
# endif
#endif
#if defined GL_VERTEX_SUBROUTINE_UNIFORM
# if defined VertexSubroutineUniform
#  pragma push_macro("VertexSubroutineUniform")
#  undef VertexSubroutineUniform
	.value("VertexSubroutineUniform", oglplus::ProgramInterface::VertexSubroutineUniform)
#  pragma pop_macro("VertexSubroutineUniform")
# else
	.value("VertexSubroutineUniform", oglplus::ProgramInterface::VertexSubroutineUniform)
# endif
#endif
#if defined GL_TESS_CONTROL_SUBROUTINE_UNIFORM
# if defined TessControlSubroutineUniform
#  pragma push_macro("TessControlSubroutineUniform")
#  undef TessControlSubroutineUniform
	.value("TessControlSubroutineUniform", oglplus::ProgramInterface::TessControlSubroutineUniform)
#  pragma pop_macro("TessControlSubroutineUniform")
# else
	.value("TessControlSubroutineUniform", oglplus::ProgramInterface::TessControlSubroutineUniform)
# endif
#endif
#if defined GL_TESS_EVALUATION_SUBROUTINE_UNIFORM
# if defined TessEvaluationSubroutineUniform
#  pragma push_macro("TessEvaluationSubroutineUniform")
#  undef TessEvaluationSubroutineUniform
	.value("TessEvaluationSubroutineUniform", oglplus::ProgramInterface::TessEvaluationSubroutineUniform)
#  pragma pop_macro("TessEvaluationSubroutineUniform")
# else
	.value("TessEvaluationSubroutineUniform", oglplus::ProgramInterface::TessEvaluationSubroutineUniform)
# endif
#endif
#if defined GL_GEOMETRY_SUBROUTINE_UNIFORM
# if defined GeometrySubroutineUniform
#  pragma push_macro("GeometrySubroutineUniform")
#  undef GeometrySubroutineUniform
	.value("GeometrySubroutineUniform", oglplus::ProgramInterface::GeometrySubroutineUniform)
#  pragma pop_macro("GeometrySubroutineUniform")
# else
	.value("GeometrySubroutineUniform", oglplus::ProgramInterface::GeometrySubroutineUniform)
# endif
#endif
#if defined GL_FRAGMENT_SUBROUTINE_UNIFORM
# if defined FragmentSubroutineUniform
#  pragma push_macro("FragmentSubroutineUniform")
#  undef FragmentSubroutineUniform
	.value("FragmentSubroutineUniform", oglplus::ProgramInterface::FragmentSubroutineUniform)
#  pragma pop_macro("FragmentSubroutineUniform")
# else
	.value("FragmentSubroutineUniform", oglplus::ProgramInterface::FragmentSubroutineUniform)
# endif
#endif
#if defined GL_COMPUTE_SUBROUTINE_UNIFORM
# if defined ComputeSubroutineUniform
#  pragma push_macro("ComputeSubroutineUniform")
#  undef ComputeSubroutineUniform
	.value("ComputeSubroutineUniform", oglplus::ProgramInterface::ComputeSubroutineUniform)
#  pragma pop_macro("ComputeSubroutineUniform")
# else
	.value("ComputeSubroutineUniform", oglplus::ProgramInterface::ComputeSubroutineUniform)
# endif
#endif
#if defined GL_TRANSFORM_FEEDEBACK_VARYING
# if defined TransformFeedebackVarying
#  pragma push_macro("TransformFeedebackVarying")
#  undef TransformFeedebackVarying
	.value("TransformFeedebackVarying", oglplus::ProgramInterface::TransformFeedebackVarying)
#  pragma pop_macro("TransformFeedebackVarying")
# else
	.value("TransformFeedebackVarying", oglplus::ProgramInterface::TransformFeedebackVarying)
# endif
#endif
#if defined GL_BUFFER_VARIABLE
# if defined BufferVariable
#  pragma push_macro("BufferVariable")
#  undef BufferVariable
	.value("BufferVariable", oglplus::ProgramInterface::BufferVariable)
#  pragma pop_macro("BufferVariable")
# else
	.value("BufferVariable", oglplus::ProgramInterface::BufferVariable)
# endif
#endif
#if defined GL_SHADER_STORAGE_BLOCK
# if defined ShaderStorageBlock
#  pragma push_macro("ShaderStorageBlock")
#  undef ShaderStorageBlock
	.value("ShaderStorageBlock", oglplus::ProgramInterface::ShaderStorageBlock)
#  pragma pop_macro("ShaderStorageBlock")
# else
	.value("ShaderStorageBlock", oglplus::ProgramInterface::ShaderStorageBlock)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::ProgramInterface) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
