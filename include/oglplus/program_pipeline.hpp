/**
 *  @file oglplus/program_pipeline.hpp
 *  @brief ProgramPipeline object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROGRAM_PIPELINE_1107121519_HPP
#define OGLPLUS_PROGRAM_PIPELINE_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/program.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/bitfield.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/binding_query.hpp>
#include <oglplus/auxiliary/prog_pl_stages.hpp>

#include <cassert>

namespace oglplus {

// if program-pipeline is available
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects

/// Program pipeline stage enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(ProgramPipelineStage, GLbitfield)
#include <oglplus/enums/program_pipeline_stage.ipp>
OGLPLUS_ENUM_CLASS_END(ProgramPipelineStage)

OGLPLUS_MAKE_BITFIELD(ProgramPipelineStage)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/program_pipeline_stage_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/program_pipeline_stage_range.ipp>
#endif

/// ProgramPipeline operations wrapper class
/** This class implements OpenGL program pipeline operations.
 *  @note Do not use this class directly, use @c ProgramPipeline instead.
 *
 *  @see ProgramPipeline
 *
 *  @glvoereq{4,1,ARB,separate_shader_objects}
 *  @glsymbols
 *  @glfunref{GenProgramPipelines}
 *  @glfunref{DeleteProgramPipelines}
 *  @glfunref{IsProgramPipeline}
 */
class ProgramPipelineOps
 : public Named
 , public BaseObject<true>
 , public FriendOf<ProgramOps>
{
public:
	typedef Nothing Target;
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenProgramPipelines)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenProgramPipelines));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteProgramPipelines)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsProgramPipeline)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_PROGRAM_PIPELINE
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::ProgramPipeline;
	}
#endif

	static void _bind(GLuint _name, Nothing)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindProgramPipeline)(_name);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindProgramPipeline));
	}

	static GLenum _binding_query(Target);
	friend class BindingQuery<ProgramPipelineOps>;
	friend class FriendOf<ProgramPipelineOps>;
public:
	/// Types related to ProgramPipeline
	struct Properties
	{
		/// The stage of a ProgramPipeline
		typedef ProgramPipelineStage Stage;
	};

	GLint GetIntParam(GLenum query) const
	{
		GLint result;
		OGLPLUS_GLFUNC(GetProgramPipelineiv)(_name, query, &result);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramPipelineiv,
			ProgramPipeline,
			nullptr,
			_name
		));
		return result;
	}

	/// Bind this program pipeline
	/**
	 *  @glsymbols
	 *  @glfunref{BindProgramPipeline}
	 */
	void Bind(void) const
	{
		_bind(_name, Nothing());
	}

	/// Unbinds the current program pipeline object (if any)
	/**
	 *  @glsymbols
	 *  @glfunref{BindProgramPipeline}
	 */
	static void Unbind(void)
	{
		OGLPLUS_GLFUNC(BindProgramPipeline)(0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindProgramPipeline));
	}

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
	 *
	 *  @glsymbols
	 *  @glfunref{UseProgramStages}
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
	/**
	 *  @glsymbols
	 *  @glfunref{UseProgramStages}
	 */
	void UseStages(
		Bitfield<ProgramPipelineStage> stages,
		const ProgramOps& program
	) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(UseProgramStages)(
			_name,
			GLbitfield(stages),
			FriendOf<ProgramOps>::GetName(program)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(UseProgramStages));
	}

#if defined GL_ALL_SHADER_BITS
	/// Use all stages of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{UseProgramStages}
	 */
	void UseAllStages(const ProgramOps& program) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(UseProgramStages)(
			_name,
			GL_ALL_SHADER_BITS,
			FriendOf<ProgramOps>::GetName(program)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(UseProgramStages));
	}
#endif

	/// Returns the validation process output
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 *  @glfunref{GetProgramPipelineInfoLog}
	 */
	String GetInfoLog(void) const;

	/// Returns true if the pipeline is validated, false otherwise
	/**
	 *  @see Validate
	 *
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 */
	bool IsValid(void) const
	{
		return GetIntParam(GL_VALIDATE_STATUS) == GL_TRUE;
	}

	void HandleValidationError(void) const;

	/// Validates this program pipeline
	/**
	 *  @throws Error ValidationError
	 *  @see Link
	 *
	 *  @glsymbols
	 *  @glfunref{ValidateProgramPipeline}
	 */
	void Validate(void) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ValidateProgramPipeline)(_name);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			ValidateProgramPipeline,
			ProgramPipeline,
			nullptr,
			_name
		));
		if(OGLPLUS_IS_ERROR(!IsValid()))
			HandleValidationError();
	}

	/// Make the @p program active for this program pipeline
	/**
	 *  @glsymbols
	 *  @glfunref{ActiveShaderProgram}
	 */
	void ActiveShaderProgram(const ProgramOps& program) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ActiveShaderProgram)(
			_name,
			FriendOf<ProgramOps>::GetName(program)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ActiveShaderProgram));
	}

	/// Returns the current active shader program
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 *  @gldefref{ACTIVE_PROGRAM}
	 */
	Managed<ProgramOps> ActiveShaderProgram(void) const
	{
		return Managed<ProgramOps>(GetIntParam(GL_ACTIVE_PROGRAM));
	}

	/// Returns true if this pipeline contains a shader of a particular type
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 */
	bool HasShader(ShaderType shader_type) const
	{
		return GetIntParam(GLenum(shader_type)) != 0;
	}

	/// Returns the program from which the @p shader_type is used
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 */
	Managed<ProgramOps> ShaderProgram(ShaderType shader_type) const
	{
		return Managed<ProgramOps>(GetIntParam(GLenum(shader_type)));
	}
};

/// Class that can be used to unbind the currently bound ProgramPipeline
class NoProgramPipeline
{
public:
	/// Unbinds the current program pipeline object
	/**
	 *  @glsymbols
	 *  @glfunref{BindProgramPipeline}
	 */
	static void Bind(void)
	{
		OGLPLUS_GLFUNC(BindProgramPipeline)(0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindProgramPipeline));
	}
};


#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating  OpenGL program pipeline functionality
/**
 *  @ingroup oglplus_objects
 */
class ProgramPipeline
 : public ProgramPipelineOps
{ };
#else
typedef Object<ProgramPipelineOps> ProgramPipeline;
#endif

#endif // program pipeline

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/program_pipeline.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
