/**
 *  @file advanced/cloud_trace/programs.hpp
 *  @brief Declaration of the shading program classes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_ADVANCED_CLOUD_TRACE_PROGRAMS_1119071146_HPP
#define OGLPLUS_ADVANCED_CLOUD_TRACE_PROGRAMS_1119071146_HPP

#include "app_data.hpp"

#include <oglplus/gl.hpp>
#include <oglplus/fix_gl_version.hpp>
#include <oglplus/program.hpp>
#include <oglplus/uniform.hpp>
#include <oglplus/uniform_block.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/matrix.hpp>

namespace oglplus {
namespace cloud_trace {

class RaytraceProg : public Program
{
private:
	static Program make(void);

	Program& self(void);

	ProgramUniform<Mat3f> ray_matrix;
public:
	ProgramUniformSampler cloud_tex;
	ProgramUniform<GLint> cloud_count;
	UniformBlock cloud_block;

	RaytraceProg(const AppData&);

	void SetRayMatrix(const AppData&, unsigned face);
};

class RenderProg : public Program
{
private:
	static Program make(const AppData&);

	Program& self(void);

	OptionalUniform<GLint> cube_face;
	OptionalUniform<Mat3f> ray_matrix;
public:
	ProgramUniform<Vec2f> raytrace_size;
	ProgramUniformSampler raytrace_output;

	RenderProg(const AppData&);

	void SetRayMatrix(const AppData&, unsigned face);
};

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
