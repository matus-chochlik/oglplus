/**
 *  @file advanced/cloud_trace/programs.cpp
 *  @brief Implementation of the program classes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include "programs.hpp"

#include <oglplus/angle.hpp>
#include <oglplus/glsl_source.hpp>
#include <oglplus/opt/resources.hpp>

namespace oglplus {
namespace cloud_trace {

Program RaytraceProg::make(void)
{
	Program prog;

	ResourceFile vs_source("glsl", "raytrace", ".vs.glsl");
	prog << VertexShader(GLSLSource::FromStream(vs_source));

	ResourceFile fs_source("glsl", "raytrace", ".fs.glsl");
	prog << FragmentShader(GLSLSource::FromStream(fs_source));

	prog.Link().Use();

	return std::move(prog);
}

Program& RaytraceProg::self(void)
{
	return *this;
}

RaytraceProg::RaytraceProg(AppData& app_data)
 : Program(make())
 , ray_matrix(self(), "RayMatrix")
 , cloud_tex(self(), "CloudTex")
 , cloud_count(self(), "CloudCount")
 , cloud_block(self(), "CloudBlock")
{
	ProgramUniform<Vec3f>(self(), "LightPos").Set(
		app_data.light_x,
		app_data.light_y,
		app_data.light_z
	);
	ProgramUniform<GLfloat>(self(), "HighLight").Set(app_data.high_light);
	ProgramUniform<GLfloat>(self(), "AmbiLight").Set(app_data.ambi_light);

	ProgramUniform<GLfloat>(self(), "UnitOpacity").Set(app_data.unit_opacity);
	ProgramUniform<GLfloat>(self(), "UnitAttenuation").Set(app_data.unit_attenuation);
}

void RaytraceProg::SetRayMatrix(const Mat4f& mat)
{
	ray_matrix.Set(Mat3f(mat));
}

Program RenderProg::make(AppData&)
{
	Program prog;

	ResourceFile vs_source("glsl", "render", ".vs.glsl");
	prog << VertexShader(GLSLSource::FromStream(vs_source));

	ResourceFile fs_source("glsl", "render", ".fs.glsl");
	prog << FragmentShader(GLSLSource::FromStream(fs_source));

	prog.Link().Use();

	return std::move(prog);
}

Program& RenderProg::self(void)
{
	return *this;
}

RenderProg::RenderProg(AppData& app_data)
 : Program(make(app_data))
 , raytrace_size(self(), "RaytraceSize")
 , raytrace_output(self(), "RaytraceOutput")
{
}

} // namespace cloud_trace
} // namespace oglplus
