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

/// ProgramPipeline operations wrapper class
/** This class implements OpenGL program pipeline operations.
 *  @note Do not use this class directly, use @c ProgramPipeline instead.
 *
 *  @see ProgramPipeline
 */
class ProgramPipelineOps
 : public Named
 , public FriendOf<Program>
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenProgramPipelines(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(GenProgramPipelines));
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
	/// Bind this program pipeline
	void Bind(void) const
	{
		assert(_name != 0);
		::glBindProgramPipeline(_name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindProgramPipeline));
	}

	/// Program pipeline stage enumeration
	enum class Stage : GLbitfield {
		/// VERTEX_SHADER_BIT
		VertexShader = GL_VERTEX_SHADER_BIT,
		/// GEOMETRY_SHADER_BIT
		GeometryShader = GL_GEOMETRY_SHADER_BIT,
		/// FRAGMENT_SHADER_BIT
		FragmentShader = GL_FRAGMENT_SHADER_BIT,
		/// TESS_CONTROL_SHADER_BIT
		TessControlShader = GL_TESS_CONTROL_SHADER_BIT,
		/// TESS_EVALUATION_SHADER_BIT
		TessEvaluationShader = GL_TESS_EVALUATION_SHADER_BIT,
		/// ALL_SHADER_BITS
		All = GL_ALL_SHADER_BITS
	};

	/// Use the specified @p stages of the @p program
	void UseStages(
		const std::initializer_list<Stage>& stages,
		const Program& program
	) const
	{
		assert(_name != 0);
		::glUseProgramStages(
			_name,
			aux::MakeBitfield(stages),
			FriendOf<Program>::GetName(program)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(UseProgramStages));
	}

	/// Use all stages of the @p program
	void UseAllStages(const Program& program) const
	{
		assert(_name != 0);
		::glUseProgramStages(
			_name,
			GL_ALL_SHADER_BITS,
			FriendOf<Program>::GetName(program)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(UseProgramStages));
	}
};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating  OpenGL shading language program functionality
class ProgramPipeline
 : public ProgramPipelineOps
{ };
#else
typedef Object<ProgramPipelineOps, true> ProgramPipeline;
#endif

} // namespace oglplus

#endif // include guard
