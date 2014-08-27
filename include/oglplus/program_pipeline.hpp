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

#include <oglplus/glfunc.hpp>
#include <oglplus/shader_type.hpp>
#include <oglplus/program_pipeline_stage.hpp>
#include <oglplus/object/wrapper.hpp>
#include <oglplus/error/program.hpp>
#include <oglplus/detail/prog_pl_stages.hpp>

#include <cassert>

namespace oglplus {

// if program-pipeline is available
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects

/// Class wrapping program pipeline construction/destruction functions
/** @note Do not use this class directly, use ProgramPipeline instead.
 *
 *  @glvoereq{4,1,ARB,separate_shader_objects}
 *  @glsymbols
 *  @glfunref{GenProgramPipelines}
 *  @glfunref{DeleteProgramPipelines}
 *  @glfunref{IsProgramPipeline}
 */
template <>
class ObjGenDelOps<tag::ProgramPipeline>
{
protected:
	static void Gen(tag::Generate, GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(GenProgramPipelines)(count, names);
		OGLPLUS_CHECK_SIMPLE(GenProgramPipelines);
	}

#if GL_VERSION_4_5 || GL_ARB_direct_state_access
	static void Gen(tag::Create, GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(CreateProgramPipelines)(count, names);
		OGLPLUS_CHECK_SIMPLE(CreateProgramPipelines);
	}
#endif

	static void Delete(GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(DeleteProgramPipelines)(count, names);
		OGLPLUS_VERIFY_SIMPLE(DeleteProgramPipelines);
	}

	static GLboolean IsA(GLuint name)
	{
		assert(name != 0);
		GLboolean result = OGLPLUS_GLFUNC(IsProgramPipeline)(name);
		OGLPLUS_VERIFY_SIMPLE(IsProgramPipeline);
		return result;
	}
};

/// Program pipeline binding operations
template <>
class ObjBindingOps<tag::ProgramPipeline>
{
protected:
	static GLuint _binding(void)
	{
		GLint name = 0;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_PROGRAM_PIPELINE_BINDING, &name);
		OGLPLUS_VERIFY(
			GetIntegerv,
			Error,
			EnumParam(GLenum(GL_PROGRAM_PIPELINE_BINDING))
		);
		return name;
	}
public:
	/// Returns the currently bound ProgramPipeline
	/**
	 *  @glsymbols
	 *  @glfunref{GetIntegerv}
	 */
	static ProgramPipelineName Binding(void)
	{
		return ProgramPipelineName(_binding());
	}

	/// Binds the specified @p vertex_array object
	/**
	 *  @glsymbols
	 *  @glfunref{BindProgramPipeline}
	 */
	static void Bind(ProgramPipelineName pipeline)
	{
		OGLPLUS_GLFUNC(BindProgramPipeline)(GetGLName(pipeline));
		OGLPLUS_VERIFY(
			BindProgramPipeline,
			ObjectError,
			Object(pipeline)
		);
	}
};

/// Common program pipeline operations
/** @note Do not use this class directly, use ProgramPipeline
 *  or NoProgramPipeline instead.
 */
template <>
class ObjCommonOps<tag::ProgramPipeline>
 : public ProgramPipelineName
 , public ObjBindingOps<tag::ProgramPipeline>
{
protected:
	ObjCommonOps(void){ }
public:
	using ObjBindingOps<tag::ProgramPipeline>::Bind;

	/// Binds this program pipeline object
	/**
	 *  @glsymbols
	 *  @glfunref{BindProgramPipeline}
	 */
	void Bind(void) const
	{
		Bind(*this);
	}
};

/// Class wrapping program pipeline functions (with direct state access)
/** @note Do not use this class directly, use ProgramPipeline instead.
 */
template <>
class ObjectOps<tag::DirectState, tag::ProgramPipeline>
 : public ObjZeroOps<tag::DirectState, tag::ProgramPipeline>
{
protected:
	ObjectOps(void){ }
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
		OGLPLUS_VERIFY(
			GetProgramPipelineiv,
			ObjectError,
			Object(*this).
			EnumParam(query)
		);
		return result;
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
	ProgPLUseStages UseStages(ProgramName program) const
	{
		assert(_name != 0);
		return ProgPLUseStages(
			_name,
			GetGLName(program),
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
		ProgramName program
	) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(UseProgramStages)(
			_name,
			GLbitfield(stages),
			GetGLName(program)
		);
		OGLPLUS_CHECK(
			UseProgramStages,
			ObjectError,
			Object(*this)
		);
	}

#if defined GL_ALL_SHADER_BITS
	/// Use all stages of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{UseProgramStages}
	 */
	void UseAllStages(ProgramName program) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(UseProgramStages)(
			_name,
			GL_ALL_SHADER_BITS,
			GetGLName(program)
		);
		OGLPLUS_VERIFY(
			UseProgramStages,
			ObjectError,
			Object(*this)
		);
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

	/// Validates this program pipeline
	/**
	 *  @throws Error ValidationError
	 *  @see Link
	 *
	 *  @glsymbols
	 *  @glfunref{ValidateProgramPipeline}
	 */
	void Validate(void) const;

	/// Make the @p program active for this program pipeline
	/**
	 *  @glsymbols
	 *  @glfunref{ActiveShaderProgram}
	 */
	void ActiveShaderProgram(ProgramName program) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ActiveShaderProgram)(
			_name,
			GetGLName(program)
		);
		OGLPLUS_CHECK(
			ActiveShaderProgram,
			ObjectError,
			Object(*this)
		);
	}

	/// Returns the current active shader program
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 *  @gldefref{ACTIVE_PROGRAM}
	 */
	ProgramName ActiveShaderProgram(void) const
	{
		return ProgramName(GetIntParam(GL_ACTIVE_PROGRAM));
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
	ProgramName ShaderProgram(ShaderType shader_type) const
	{
		return ProgramName(GetIntParam(GLenum(shader_type)));
	}
};

/// Program pipeline operations with direct state access
typedef ObjectOps<tag::DirectState, tag::ProgramPipeline>
	ProgramPipelineOps;

/// Class that can be used to unbind the currently bound program pipeline
/**
 *  @ingroup oglplus_objects
 */
typedef ObjectZero<ObjZeroOps<tag::DirectState, tag::ProgramPipeline>>
	NoProgramPipeline;

/// An @ref oglplus_object encapsulating the OpenGL program pipeline functionality
/**
 *  @ingroup oglplus_objects
 */
typedef Object<ProgramPipelineOps> ProgramPipeline;

#endif // program pipeline

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/program_pipeline.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
