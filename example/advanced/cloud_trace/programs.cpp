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
#include "ray_matrix.hpp"

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

	ResourceFile fs_rs_source("glsl", "raysample", ".fs.glsl");
	prog << FragmentShader(GLSLSource::FromStream(fs_rs_source));

	ResourceFile fs_rt_source("glsl", "raytrace", ".fs.glsl");
	prog << FragmentShader(GLSLSource::FromStream(fs_rt_source));

	prog.Link().Use();

	return std::move(prog);
}

Program& RaytraceProg::self(void)
{
	return *this;
}

RaytraceProg::RaytraceProg(const AppData& app_data)
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

void RaytraceProg::SetRayMatrix(const AppData& app_data, unsigned face)
{
	ray_matrix.Set(Mat3f(RayMatrix(app_data, face)));
}

Program RenderProg::make(const AppData& app_data)
{
	Program prog;

	ResourceFile vs_source("glsl", "render", ".vs.glsl");
	prog << VertexShader(GLSLSource::FromStream(vs_source));

	std::string fs_name("render-");
	fs_name.append(app_data.finish_shader);
	ResourceFile fs_source("glsl", fs_name, ".fs.glsl");
	prog << FragmentShader(GLSLSource::FromStream(fs_source));

	prog.Link().Use();

	OptionalUniform<GLfloat>(prog, "Near").TrySet(app_data.cam_near);
	OptionalUniform<GLfloat>(prog, "Far").TrySet(app_data.cam_far);

	OptionalUniform<GLfloat>(prog, "LightX").TrySet(app_data.light_x);
	OptionalUniform<GLfloat>(prog, "LightY").TrySet(app_data.light_y);
	OptionalUniform<GLfloat>(prog, "LightZ").TrySet(app_data.light_z);
	OptionalUniform<GLfloat>(prog, "HighLight").TrySet(app_data.high_light);
	OptionalUniform<GLfloat>(prog, "AmbiLight").TrySet(app_data.ambi_light);

	OptionalUniform<GLfloat>(prog, "PlanetRadius").TrySet(app_data.planet_radius);
	OptionalUniform<GLfloat>(prog, "AtmThickness").TrySet(app_data.atm_thickness);

	return std::move(prog);
}

Program& RenderProg::self(void)
{
	return *this;
}

RenderProg::RenderProg(const AppData& app_data)
 : Program(make(app_data))
 , cube_face(self(), "CubeFace")
 , ray_matrix(self(), "RayMatrix")
 , raytrace_size(self(), "RaytraceSize")
 , raytrace_output(self(), "RaytraceOutput")
{
}

void RenderProg::SetRayMatrix(const AppData& app_data, unsigned face)
{
	cube_face.TrySet(face);
	if(ray_matrix)
	{
		ray_matrix.Set(Mat3f(RayMatrix(app_data, face)));
	}
}

} // namespace cloud_trace
} // namespace oglplus
