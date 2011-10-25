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

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/program.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/auxiliary/bitfield.hpp>
#include <oglplus/auxiliary/prog_pl_stages.hpp>

#include <cassert>

namespace oglplus {

// if program-pipeline is available
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects

/// ProgramPipeline operations wrapper class
/** This class implements OpenGL program pipeline operations.
 *  @note Do not use this class directly, use @c ProgramPipeline instead.
 *
 *  @see ProgramPipeline
 */
class ProgramPipelineOps
 : public Named
 , public FriendOf<ProgramOps>
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
	GLint GetIntParam(GLenum query) const
	{
		GLint result;
		::glGetProgramPipelineiv(_name, query, &result);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramPipelineiv,
			ProgramPipeline,
			_name
		));
		return result;
	}

	/// Bind this program pipeline
	void Bind(void) const
	{
		assert(_name != 0);
		::glBindProgramPipeline(_name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindProgramPipeline));
	}

	/// Unbinds the current program pipeline object (if any)
	static void Unbind(void)
	{
		::glBindProgramPipeline(0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindProgramPipeline));
	}

	/// Program pipeline stage enumeration
	enum class Stage : GLbitfield {
#include <oglplus/enums/program_pipeline_stage.ipp>
	};

	/// Specifies program stages by calling functions of the returned object
	/** This function returns an object that allows to specify which stages
	 *  of @p program should by used when this pipeline is active by calling
	 *  the Vertex(), TessControl(), TessEvaluation(), Geometry(), Fragment()
	 *  and All() member functions of the object returned by UseStages.
	 *
	 *  example:
	 *  @code
	 *  Program prog;
	 *  ProgramPipeline pp;
	 *  ...
	 *  pp.UseStages(prog).Vertex();
	 *  pp.UseStages(prog).Vertex().Geometry();
	 *  pp.UseStages(prog).Vertex().TessControl().TessEvaluation().Geometry();
	 *  pp.UseStages(prog).Vertex().Geometry().Fragment();
	 *  pp.UseStages(prog).Geometry();
	 *  pp.UseStages(prog).All();
	 *  @endcode
	 *
	 *  @throws Error
	 */
	aux::ProgPLUseStages UseStages(const ProgramOps& program) const
	{
		assert(_name != 0);
		return aux::ProgPLUseStages(
			_name,
			FriendOf<ProgramOps>::GetName(program),
			0
		);
	}

	/// Use the specified @p stages of the @p program
	void UseStages(
		std::initializer_list<Stage> stages,
		const ProgramOps& program
	) const
	{
		assert(_name != 0);
		::glUseProgramStages(
			_name,
			aux::MakeBitfield(stages),
			FriendOf<ProgramOps>::GetName(program)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(UseProgramStages));
	}

#if defined GL_ALL_SHADER_BITS
	/// Use all stages of the @p program
	void UseAllStages(const ProgramOps& program) const
	{
		assert(_name != 0);
		::glUseProgramStages(
			_name,
			GL_ALL_SHADER_BITS,
			FriendOf<ProgramOps>::GetName(program)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(UseProgramStages));
	}
#endif

	/// Returns the validation process output
	/**
	 */
	String GetInfoLog(void) const
	{
		assert(_name != 0);
		return aux::GetInfoLog(
			_name, ::glGetProgramPipelineiv,
			::glGetProgramPipelineInfoLog,
			"GetProgramPipelineiv",
			"GetProgramPipelineInfoLog"
		);
	}

	/// Returns true if the pipeline is validated, false otherwise
	/**
	 *  @see Validate
	 */
	bool IsValid(void) const
	{
		return GetIntParam(GL_VALIDATE_STATUS) == GL_TRUE;
	}

	/// Validates this program pipeline
	/**
	 *  @throws Error ValidationError
	 *  @see Link
	 */
	void Validate(void) const
	{
		assert(_name != 0);
		::glValidateProgramPipeline(_name);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			ValidateProgramPipeline,
			ProgramPipeline,
			_name
		));
		if(!IsValid())
			throw ValidationError(
				GetInfoLog(),
				OGLPLUS_OBJECT_ERROR_INFO(
					ValidateProgramPipeline,
					ProgramPipeline,
					_name
				)
			);
	}

	/// Make the @p program active for this program pipeline
	void ActiveShaderProgram(const ProgramOps& program) const
	{
		assert(_name != 0);
		::glActiveShaderProgram(
			_name,
			FriendOf<ProgramOps>::GetName(program)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(ActiveShaderProgram));
	}

	/// Returns the current active shader program
	Managed<ProgramOps> ActiveShaderProgram(void) const
	{
		return Managed<ProgramOps>(GetIntParam(GL_ACTIVE_PROGRAM));
	}

	/// Returns true if this pipeline contains a shader of a particular kind
	bool HasShader(Shader::Kind shader_kind) const
	{
		return GetIntParam(GLenum(shader_kind)) != 0;
	}

	/// Returns the program from which the @p shader_kind is used
	Managed<ProgramOps> ShaderProgram(Shader::Kind shader_kind) const
	{
		return Managed<ProgramOps>(GetIntParam(GLenum(shader_kind)));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating  OpenGL shading language program functionality
/**
 *  @ingroup objects
 */
class ProgramPipeline
 : public ProgramPipelineOps
{ };
#else
typedef Object<ProgramPipelineOps, true> ProgramPipeline;
#endif

#endif // program pipeline

} // namespace oglplus

#endif // include guard
