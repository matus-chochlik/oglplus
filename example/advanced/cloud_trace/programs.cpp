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

RaytraceProg::RaytraceProg(RenderData& data)
 : Program(make())
 , ray_matrix(self(), "RayMatrix")
 , cloud_tex(self(), "CloudTex")
 , cloud_count(self(), "CloudCount")
{
	UniformBlock(self(), "CloudBlock").Binding(data.cloud_data_ub_idx);
	ProgramUniform<Vec3f>(self(), "LightPos").Set(
		data.light_x,
		data.light_y,
		data.light_z
	);
	ProgramUniform<GLfloat>(self(), "HighLight").Set(data.high_light);
	ProgramUniform<GLfloat>(self(), "AmbiLight").Set(data.ambi_light);

	ProgramUniform<GLfloat>(self(), "UnitOpacity").Set(data.unit_opacity);
	ProgramUniform<GLfloat>(self(), "UnitAttenuation").Set(data.unit_attenuation);
}

void RaytraceProg::SetCamera(
	const Vec3f& left,
	const Vec3f& up,
	const Vec3f& front,
	float near,
	float far
)
{
	ray_matrix.Set(Mat3f(
		CamMatrixf::PerspectiveX(RightAngle(), 1, near, far)*
		Mat4f(
			Vec4f(left, 0),
			Vec4f(up, 0),
			Vec4f(-front, 0),
			Vec4f::Unit(3)
		)
	));
}

} // namespace cloud_trace
} // namespace oglplus
