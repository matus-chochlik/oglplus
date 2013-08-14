/*
 *  .file oglplus/shader.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/shader.hpp>

#include <boost/python.hpp>


void oglplus_py_Shader(void)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	bpy::return_internal_reference<1> bpy_rvp;

	bpy::class_<ShaderOps>("ShaderOps", bpy::no_init)
		.def("Type", &ShaderOps::Type)
		.def("Source", (
			const ShaderOps& (ShaderOps::*)(const String&) const)
			&ShaderOps::Source,
			bpy_rvp
		)
		.def("IsCompiled", &ShaderOps::IsCompiled)
		.def("GetInfoLog", &ShaderOps::GetInfoLog)
		.def("Compile", &ShaderOps::Compile, bpy_rvp)
	;

	bpy::class_<
		Shader,
		bpy::bases<ShaderOps>,
		boost::noncopyable
	>("Shader", bpy::init<ShaderType>())
	;

	bpy::class_<
		VertexShader,
		bpy::bases<Shader>,
		boost::noncopyable
	>("VertexShader", bpy::init<>());

#ifdef GL_TESS_CONTROL_SHADER
	bpy::class_<
		TessControlShader,
		bpy::bases<Shader>,
		boost::noncopyable
	>("TessControlShader", bpy::init<>());
#endif

#ifdef GL_TESS_EVALUATION_SHADER
	bpy::class_<
		TessEvaluationShader,
		bpy::bases<Shader>,
		boost::noncopyable
	>("TessEvaluationShader", bpy::init<>());
#endif

	bpy::class_<
		GeometryShader,
		bpy::bases<Shader>,
		boost::noncopyable
	>("GeometryShader", bpy::init<>());

	bpy::class_<
		FragmentShader,
		bpy::bases<Shader>,
		boost::noncopyable
	>("FragmentShader", bpy::init<>());

#ifdef GL_COMPUTE_SHADER
	bpy::class_<
		ComputeShader,
		bpy::bases<Shader>,
		boost::noncopyable
	>("ComputeShader", bpy::init<>());
#endif
}

