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
#include <oglplus/program.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/auxiliary/bitfield.hpp>

#include <cassert>

namespace oglplus {

class ProgramPipelineOps
 : public Named
 , public FriendOf<Program>
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenProgramPipelines(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteProgramPipelines(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsProgramPipeline(_name);
	}

	friend class FriendOf<ProgramPipelineOps>;
public:
	void Bind(void) const
	{
		assert(_name != 0);
		::glBindProgramPipeline(_name);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	enum class Stage : GLbitfield {
		VertexShader = GL_VERTEX_SHADER_BIT,
		GeometryShader = GL_GEOMETRY_SHADER_BIT,
		FragmentShader = GL_FRAGMENT_SHADER_BIT,
		TessControlShader = GL_TESS_CONTROL_SHADER_BIT,
		TessEvaluationShader = GL_TESS_EVALUATION_SHADER_BIT,
		All = GL_ALL_SHADER_BITS
	};

	void UseStages(
		const std::initializer_list<Stage>& stages,
		const Program& prog
	) const
	{
		assert(_name != 0);
		::glUseProgramStages(
			_name,
			aux::MakeBitfield(stages),
			FriendOf<Program>::GetName(prog)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	void UseAllStages(const Program& prog) const
	{
		assert(_name != 0);
		::glUseProgramStages(
			_name,
			GL_ALL_SHADER_BITS,
			FriendOf<Program>::GetName(prog)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}
};

typedef Object<ProgramPipelineOps, true> ProgramPipeline;

} // namespace oglplus

#endif // include guard
