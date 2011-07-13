/**
 *  @file oglplus/program_pipeline.hpp
 *  @brief ProgramPipeline object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PROGRAM_PIPELINE_1107121519_HPP
#define OGLPLUS_PROGRAM_PIPELINE_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

class ProgramPipelineOps
{
protected:
	GLuint _name;

	ProgramPipelineOps(void)
	{ }

	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenProgramPipelines(count, &_name);
		ThrowOnError();
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteProgramPipelines(count, &_name);
	}
public:
	ProgramPipelineOps(GLuint _n)
	 : _name(_n)
	{ }

	void Bind(GLuint pipeline) const
	{
		::glBindProgramPipeline(pipeline);
	}
};

typedef Object<ProgramPipelineOps> ProgramPipeline;

} // namespace oglplus

#endif // include guard
