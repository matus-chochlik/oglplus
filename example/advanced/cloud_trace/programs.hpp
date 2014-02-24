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

#include "render_data.hpp"

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

	RaytraceProg(RenderData& data);

	void SetCamera(
		const Vec3f& left,
		const Vec3f& up,
		const Vec3f& front,
		float near,
		float far
	);
};

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
