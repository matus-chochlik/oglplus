/**
 *  @file oglplus/program.hpp
 *  @brief Program wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROGRAM_1107121519_HPP
#define OGLPLUS_PROGRAM_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/object.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/transform_feedback_mode.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/link_error.hpp>
#include <oglplus/program_resource.hpp>
#include <oglplus/binding_query.hpp>
#include <oglplus/auxiliary/info_log.hpp>
#include <oglplus/auxiliary/base_range.hpp>
#include <oglplus/primitive_type.hpp>
#include <oglplus/face_mode.hpp>
#include <oglplus/string.hpp>

#include <vector>
#include <cassert>
#include <tuple>

namespace oglplus {

class VertexAttribOps;

/// Program operations wrapper helper class
/** This class implements OpenGL shading language program operations.
 *  @note Do not use this class directly, use @c Program instead.
 *
 *  @see Program
 *
 *  @glsymbols
 *  @glfunref{CreateProgram}
 *  @glfunref{DeleteProgram}
 *  @glfunref{IsProgram}
 */
class ProgramOps
 : public Named
 , public BaseObject<false>
 , public FriendOf<ShaderOps>
 , public FriendOf<VertexAttribOps>
{
public:
	typedef Nothing Target;
protected:
	static void _init(GLsizei _count, GLuint* _name)
	{
		OGLPLUS_FAKE_USE(_count);
		assert(_count == 1);
		assert(_name != nullptr);
		*_name = OGLPLUS_GLFUNC(CreateProgram)();
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CreateProgram));
	}

	static void _cleanup(GLsizei _count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		OGLPLUS_FAKE_USE(_count);
		assert(_count == 1);
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteProgram)(*_name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsProgram)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_PROGRAM
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::Program;
	}
#endif
	static GLenum _binding_query(Target);
	friend class BindingQuery<ProgramOps>;
	friend class FriendOf<ProgramOps>;

	GLint GetIntParam(GLenum query) const
	{
		GLint result;
		OGLPLUS_GLFUNC(GetProgramiv)(_name, query, &result);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramiv,
			Program,
			nullptr,
			_name
		));
		return result;
	}

#if GL_VERSION_4_0 || GL_ARB_shader_subroutine
	GLint GetStageIntParam(GLenum stage, GLenum query) const
	{
		GLint result;
		OGLPLUS_GLFUNC(GetProgramStageiv)(_name, stage, query, &result);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramStageiv,
			Program,
			nullptr,
			_name
		));
		return result;
	}
#endif
public:
	/// Attaches the shader to this program
	/**
	 *  @glsymbols
	 *  @glfunref{AttachShader}
	 */
	ProgramOps& AttachShader(const ShaderOps& shader);

	/// Attaches a group of shaders to this program
	ProgramOps& AttachShaders(const Group<Shader>& shaders);

	/// Detaches the shader from this program
	/**
	 *  @glsymbols
	 *  @glfunref{DetachShader}
	 */
	ProgramOps& DetachShader(const ShaderOps& shader);

	/// Returns true if the program is already linked, false otherwise
	/**
	 *  @see Link
	 *  @see Validate
	 *
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{LINK_STATUS}
	 */
	bool IsLinked(void) const
	{
		return GetIntParam(GL_LINK_STATUS) == GL_TRUE;
	}

	/// Returns the linker output if the program is linked
	/**
	 *  @see IsLinked
	 *  @see Link
	 *
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @glfunref{GetProgramInfoLog}
	 */
	String GetInfoLog(void) const;

	void HandleLinkError(void) const;

	/// Links this shading language program
	/**
	 *  @post IsLinked()
	 *  @throws Error LinkError
	 *  @see IsLinked
	 *
	 *  @glsymbols
	 *  @glfunref{LinkProgram}
	 *  @glfunref{GetProgram}
	 *  @glfunref{GetProgramInfoLog}
	 */
	ProgramOps& Link(void);

	/// Returns true if the program is validated, false otherwise
	/**
	 *  @see Validate
	 *
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{VALIDATE_STATUS}
	 */
	bool IsValid(void) const
	{
		return GetIntParam(GL_VALIDATE_STATUS) == GL_TRUE;
	}

	/// Validates this shading language program
	/**
	 *  @post IsValid()
	 *  @throws Error ValidationError
	 *  @see Link
	 *
	 *  @glsymbols
	 *  @glfunref{ValidateProgram}
	 *  @glfunref{GetProgram}
	 *  @glfunref{GetProgramInfoLog}
	 */
	ProgramOps& Validate(void);

	/// Uses this shading language program
	/**
	 *  @note The program must be linked before it is used.
	 *  @pre IsLinked()
	 *  @pre IsValid()
	 *
	 *  @see IsLinked
	 *  @see Link
	 *
	 *  @glsymbols
	 *  @glfunref{UseProgram}
	 */
	const ProgramOps& Use(void) const
	{
		assert(_name != 0);
		assert(IsLinked());
		OGLPLUS_GLFUNC(UseProgram)(_name);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			UseProgram,
			Program,
			nullptr,
			_name
		));
		return *this;
	}

	/// Deactivates the currently active/used program (if any)
	/**
	 *  @glsymbols
	 *  @glfunref{UseProgram}
	 */
	static void UseNone(void)
	{
		OGLPLUS_GLFUNC(UseProgram)(0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(UseProgram));
	}

	/// Sets the variables that will be captured during transform feedback
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{TransformFeedbackVaryings}
	 */
	void TransformFeedbackVaryings(
		GLsizei count,
		const GLchar** varyings,
		TransformFeedbackMode mode
	);

	/// Sets the variable that will be captured during transform feedback
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{TransformFeedbackVaryings}
	 */
	void TransformFeedbackVarying(const GLchar* varying)
	{
		TransformFeedbackVaryings(
			1, &varying,
			TransformFeedbackMode::SeparateAttribs
		);
	}

	template <typename std::size_t N>
	void TransformFeedbackVaryings(
		const GLchar* (&varyings)[N],
		TransformFeedbackMode mode
	)
	{
		TransformFeedbackVaryings(N, varyings, mode);
	}

	/// Sets the variables that will be captured during transform feedback
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{TransformFeedbackVaryings}
	 */
	void TransformFeedbackVaryings(
		const std::vector<String>& varyings,
		TransformFeedbackMode mode
	) const;

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Information about a single active vertex attribute or uniform
	/** Note that the Program's functions documented as returning instances
	 *  of ActiveVariableInfo actually return types convertible to
	 *  ActiveVariableInfo.
	 */
	class ActiveVariableInfo
	{
	public:
		/// Returns the index of the attribute or uniform
		GLuint Index(void) const;

		/// Returns the name (identifier) of the attribute or uniform
		const String& Name(void) const;

		/// Returns the size in units of Type
		const GLint Size(void) const;

		/// Returns the data type of the variable
		const SLDataType Type(void) const;
	};

	/// Helper class for efficient iteration of Program interface items
	/** Instances of this class are created by a program for its specific
	 *  interfaces (uniform, vertex attributes, subroutines, etc.) or
	 *  stages (vertex, geometry, fragment, etc.). Instances of an interface
	 *  context can be used (mostly internally) for efficient iteration
	 *  of individual items of a particular interface (uniforms, subroutines,
	 *  etc.). Contexts for various programs and various interfaces are not
	 *  interchangeable.
	 *  The InterfaceContext type should be treated as opaque and only used
	 *  with appropriate functions.
	 */
	typedef Unspecified InterfaceContext;

	/// The type of the range for traversing program resource information
	typedef Range<ProgramResource> ActiveResourceRange;

	/// The type of the range for traversing active vertex attributes
	typedef Range<ActiveVariableInfo> ActiveAttribRange;
	/// The type of the range for traversing active uniforms
	typedef Range<ActiveVariableInfo> ActiveUniformRange;
	/// The type of the range for traversing active subroutine uniforms
	typedef Range<ActiveVariableInfo> ActiveSubroutineUniformRange;
	/// The type of the range for traversing transform feedback varyings
	typedef Range<ActiveVariableInfo> TransformFeedbackVaryingRange;
	/// The type of the range for traversing program's shaders
	typedef Range<Managed<Shader> > ShaderRange;
#else
	typedef aux::ActiveVariableInfo ActiveVariableInfo;
	typedef aux::ProgramInterfaceContext InterfaceContext;

#if GL_VERSION_4_3
	typedef aux::ContextElementRange<
		aux::ProgramInterfaceContext,
		ProgramResource
	> ActiveResourceRange;
#endif

	typedef aux::ContextElementRange<
		aux::ProgramInterfaceContext,
		aux::ActiveAttribInfo
	> ActiveAttribRange;

	typedef aux::ContextElementRange<
		aux::ProgramInterfaceContext,
		aux::ActiveUniformInfo
	> ActiveUniformRange;

#if GL_VERSION_4_0 || GL_ARB_shader_subroutine
	typedef aux::ContextElementRange<
		aux::ProgramInterfaceContext,
		aux::ActiveSubroutineInfo
	> ActiveSubroutineRange;

	typedef aux::ContextElementRange<
		aux::ProgramInterfaceContext,
		aux::ActiveSubroutineUniformInfo
	> ActiveSubroutineUniformRange;
#endif
	typedef aux::ContextElementRange<
		aux::ProgramInterfaceContext,
		aux::TransformFeedbackVaryingInfo
	> TransformFeedbackVaryingRange;

	struct ShaderIterationContext
	{
		std::vector<GLuint> _shader_names;

		ShaderIterationContext(GLuint name, GLuint count);

		ShaderIterationContext(ShaderIterationContext&& temp)
		 : _shader_names(std::move(temp._shader_names))
		{ }
	};

	struct ManagedShader : Managed<ShaderOps>
	{
		typedef ShaderOps BaseOps;

		ManagedShader(
			const ShaderIterationContext& context,
			GLuint index
		): Managed<ShaderOps>(context._shader_names[index])
		{ }
	};

	typedef aux::ContextElementRange<
			ShaderIterationContext,
			ManagedShader
	> ShaderRange;
#endif // !OGLPLUS_DOCUMENTATION_ONLY

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
	/// Returns the context for traversal of Program's active resources
	/**
	 *  @see ActiveResources
	 */
	InterfaceContext ActiveResourceContext(ProgramInterface intf) const;

	/// Returns a range allowing to do the traversal of interface's resources
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @see ProgramInterface
	 *  @see ProgramResource
	 *
	 *  @throws Error
	 */
	ActiveResourceRange ActiveResources(ProgramInterface intf) const;
#endif

	/// Returns the context for traversal of Program's active vertex attributes
	/**
	 *  @see ActiveAttribs
	 */
	InterfaceContext ActiveAttribContext(void) const;

	/// Returns a range allowing to do the traversal of active attributes
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 */
	ActiveAttribRange ActiveAttribs(void) const;

	/// Returns the context for traversal of Program's active uniforms
	/**
	 *  @see ActiveUniforms
	 */
	InterfaceContext ActiveUniformContext(void) const;

	/// Returns a range allowing to do the traversal of active uniforms
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 */
	ActiveUniformRange ActiveUniforms(void) const;

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_shader_subroutine

	/// Returns the context for traversal of Program's active subroutines
	/**
	 *  @see ActiveSubroutines
	 */
	InterfaceContext ActiveSubroutineContext(ShaderType stage) const;

	/// Returns a range allowing to do the traversal of subroutines
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,0,ARB,shader_subroutine}
	 */
	ActiveSubroutineRange ActiveSubroutines(ShaderType stage) const;

	/// Returns the context for traversal of Program's active subr. uniforms
	/**
	 *  @see ActiveSubroutineUniforms
	 */
	InterfaceContext ActiveSubroutineUniformContext(ShaderType stage) const;

	/// Returns a range allowing to do the traversal of subroutine uniforms
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,0,ARB,shader_subroutine}
	 */
	ActiveSubroutineUniformRange ActiveSubroutineUniforms(ShaderType stage) const;
#endif

	/// Returns the context for traversal of Program's active TFB varyings
	/**
	 *  @see TransformFeedbackVaryings
	 */
	InterfaceContext TransformFeedbackVaryingContext(void) const;

	/// Returns a range allowing to do the traversal of feedback varyings
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 */
	TransformFeedbackVaryingRange TransformFeedbackVaryings(void) const;

	/// Returns a range allowing to traverse shaders attached to this program
	ShaderRange AttachedShaders(void) const;

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Information about a active uniform block
	/** Do not instantiate this class directly, instances are returned
	 *  by the ActiveUniformBlocks() function.
	 *
	 *  @see ActiveUniformBlocks
	 */
	class ActiveUniformBlockInfo
	{
		/// Returns the index of the attribute or uniform
		GLuint Index(void) const;

		/// Returns the name (identifier) of the named uniform block
		const String& Name(void) const;

		// TODO: active uniform indices, etc.
	};

	/// The type of the range for traversing active uniform blocks
	typedef Range<ActiveUniformBlockInfo> ActiveUniformRange;
#else
	typedef aux::ContextElementRange<
		aux::ProgramInterfaceContext,
		aux::ActiveUniformBlockInfo
	> ActiveUniformBlockRange;
#endif

	/// Returns a range allowing to do the traversal of active attributes
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 */
	ActiveUniformBlockRange ActiveUniformBlocks(void) const;

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects
	/// Makes this program separable
	/**
	 *  @glvoereq{4,1,ARB,separate_shader_objects}
	 *  @glsymbols
	 *  @glfunref{ProgramParameter}
	 */
	ProgramOps& MakeSeparable(bool para = true);
#endif // separate shader objects

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_get_program_binary
	/// Makes this program retrievable in binary form
	/**
	 *  @see GetBinary
	 *
	 *  @glvoereq{4,1,ARB,get_program_binary}
	 *  @glsymbols
	 *  @glfunref{ProgramParameter}
	 */
	ProgramOps& MakeRetrievable(bool para = true);

	/// Returns this programs binary representation
	/**
	 *  @see MakeRetrievable
	 *  @see Binary
	 *
	 *  @glvoereq{4,1,ARB,get_program_binary}
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @glfunref{GetProgramBinary}
	 *  @gldefref{PROGRAM_BINARY_LENGTH}
	 */
	void GetBinary(std::vector<GLubyte>& binary, GLenum& format) const;

	/// Allows to specify to program code in binary form
	/**
	 *  @see MakeRetrievable
	 *  @see GetBinary
	 *
	 *  @glvoereq{4,1,ARB,get_program_binary}
	 *  @glsymbols
	 *  @glfunref{ProgramBinary}
	 */
	void Binary(const std::vector<GLubyte>& binary, GLenum format);
#endif // get program binary

	/// Returns the transform feedback buffer mode
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{TRANSFORM_FEEDBACK_BUFFER_MODE}
	 */
	TransformFeedbackMode TransformFeedbackBufferMode(void) const
	{
		return TransformFeedbackMode(
			GetIntParam(GL_TRANSFORM_FEEDBACK_BUFFER_MODE)
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2
	/// Returns the number of vertices that the geometry shader will output
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{GEOMETRY_VERTICES_OUT}
	 */
	GLint GeometryVerticesOut(void) const
	{
		return GetIntParam(GL_GEOMETRY_VERTICES_OUT);
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_gpu_shader5

	/// Returns the number of invocations of geometry shader per primitive
	/**
	 *  @glvoereq{4,1,ARB,gpu_shader5}
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{GEOMETRY_SHADER_INVOCATIONS}
	 */
	GLint GeometryShaderInvocations(void) const
	{
		return GetIntParam(GL_GEOMETRY_SHADER_INVOCATIONS);
	}
#endif // gpu shader 5

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2

	/// Returns the geometry shader input primitive type
	/**
	 *  @glverreq{3,2}
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{GEOMETRY_INPUT_TYPE}
	 */
	PrimitiveType GeometryInputType(void) const
	{
		return PrimitiveType(GetIntParam(GL_GEOMETRY_INPUT_TYPE));
	}

	/// Returns the geometry shader output primitive type
	/**
	 *  @glverreq{3,2}
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{GEOMETRY_OUTPUT_TYPE}
	 */
	PrimitiveType GeometryOutputType(void) const
	{
		return PrimitiveType(GetIntParam(GL_GEOMETRY_OUTPUT_TYPE));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_tessellation_shader

	/// Returns the vertex order in tesselation evaluation shader
	/**
	 *  @glvoereq{4,0,ARB,tessellation_shader}
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{TESS_GEN_VERTEX_ORDER}
	 */
	FaceOrientation TessGenVertexOrder(void) const
	{
		return FaceOrientation(GetIntParam(GL_TESS_GEN_VERTEX_ORDER));
	}

	/// Returns the tesselation generator output primitive type
	/**
	 *  @glvoereq{4,0,ARB,tessellation_shader}
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{TESS_GEN_MODE}
	 */
	TessGenPrimitiveType TessGenMode(void) const
	{
		return TessGenPrimitiveType(GetIntParam(GL_TESS_GEN_MODE));
	}

	/// Returns the tesselation generator primitive spacing mode
	/**
	 *  @glvoereq{4,0,ARB,tessellation_shader}
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{TESS_GEN_SPACING}
	 */
	TessGenPrimitiveSpacing TessGenSpacing(void) const
	{
		return TessGenPrimitiveSpacing(GetIntParam(GL_TESS_GEN_SPACING));
	}

	/// Returns true if point mode is enabled in tesslation eval. shader
	/**
	 *  @glvoereq{4,0,ARB,tessellation_shader}
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @gldefref{TESS_GEN_POINT_MODE}
	 */
	bool TessGenPointMode(void) const
	{
		return GetIntParam(GL_TESS_GEN_POINT_MODE) == GL_TRUE;
	}
#endif // tessellation shader

	// Implemented in vertex_attrib.hpp
	/// Binds the location of a SL variable to the vertex_attrib
	/** This function binds the location of the vertex attribute
	 *  @c vertex_attrib to the shader variable identified by
	 *  @c identifier.
	 */
	inline void BindLocation(
		const VertexAttribOps& vertex_attrib,
		const GLchar* identifier
	) const;

};

/// Class that can be used to unbind the currently used program
class NoProgram
{
public:
	/// Deactivates the currently active/used program (if any)
	/**
	 *  @glsymbols
	 *  @glfunref{UseProgram}
	 */
	static void Use(void)
	{
		OGLPLUS_GLFUNC(UseProgram)(0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(UseProgram));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating  OpenGL shading language program functionality
/**
 *  @ingroup oglplus_objects
 */
class Program
 : public ProgramOps
{ };
#else
typedef Object<ProgramOps> Program;
#endif

// syntax-sugar operators

inline ProgramOps& operator << (
	ProgramOps& program,
	const Shader& shader
)
{
	program.AttachShader(shader);
	return program;
}

struct ProgAndXFBMode
{
	ProgramOps& prog;
	TransformFeedbackMode mode;

	ProgAndXFBMode(ProgramOps& p, TransformFeedbackMode m)
	 : prog(p)
	 , mode(m)
	{ }
};

inline ProgAndXFBMode operator << (
	ProgramOps& prog,
	TransformFeedbackMode mode
)
{
	return ProgAndXFBMode(prog, mode);
}

template <std::size_t N>
inline ProgramOps& operator << (
	ProgAndXFBMode pam,
	const GLchar* (&varyings)[N]
)
{
	pam.prog.TransformFeedbackVaryings(varyings, pam.mode);
	return pam.prog;
}

struct ProgXFBModeAndNames
{
	ProgramOps& prog;
	TransformFeedbackMode mode;
	std::vector<const GLchar*> names;

	ProgXFBModeAndNames(ProgAndXFBMode pam, const GLchar* name)
	 : prog(pam.prog)
	 , mode(pam.mode)
	{
		names.reserve(8);
		names.push_back(name);
	}

	ProgXFBModeAndNames(ProgXFBModeAndNames&& pman, const GLchar* name)
	 : prog(pman.prog)
	 , mode(pman.mode)
	 , names(std::move(pman.names))
	{
		names.push_back(name);
	}

	ProgXFBModeAndNames(ProgXFBModeAndNames&& tmp)
	 : prog(tmp.prog)
	 , mode(tmp.mode)
	 , names(std::move(tmp.names))
	{ }


#if !OGLPLUS_NO_DELETED_FUNCTIONS
	ProgXFBModeAndNames(const ProgXFBModeAndNames&) = delete;
#else
private:
	ProgXFBModeAndNames(const ProgXFBModeAndNames&);
public:
#endif

	~ProgXFBModeAndNames(void)
	{
		if(!names.empty())
		{
			prog.TransformFeedbackVaryings(
				names.size(),
				names.data(),
				mode
			);
		}
	}
};

inline ProgXFBModeAndNames operator << (
	ProgAndXFBMode pam,
	const GLchar* name
)
{
	return ProgXFBModeAndNames(pam, name);
}

inline ProgXFBModeAndNames operator << (
	ProgXFBModeAndNames&& pman,
	const GLchar* name
)
{
	return ProgXFBModeAndNames(std::move(pman), name);
}


#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects
/// A standalone program with a single shader of a specified type from GLSL source
/**
 *  @glsymbols
 *  @glfunref{CreateShaderProgram}
 *
 *  @see Program
 */
class ShaderProgram
 : public Program
{
private:
	static GLuint _make(
		ShaderType shader_type,
		GLsizei count,
		const GLchar** strings
	);

	void _check(void);
public:
	/// Creates a program with a single shader with specified type and source
	/**
	 *  @throws ValidationError
	 */
	ShaderProgram(
		ShaderType shader_type,
		const GLchar* source
	): Program(
		Program::ExternalName_(),
		_make(shader_type, 1, &source)
	)
	{ _check(); }

	/// Creates a program with a single shader with specified type and source
	/**
	 *  @throws ValidationError
	 */
	ShaderProgram(
		ShaderType shader_type,
		const GLchar* source,
		ObjectDesc&& object_desc
	): Program(
		Program::ExternalName_(),
		_make(shader_type, 1, &source),
		std::move(object_desc)
	)
	{ _check(); }

	/// Creates a program with a single shader with specified type and source
	/**
	 *  @throws ValidationError
	 */
	ShaderProgram(
		ShaderType shader_type,
		const GLSLSource& glsl_source
	): Program(
		Program::ExternalName_(),
		_make(shader_type, glsl_source.Count(), glsl_source.Parts())
	)
	{ _check(); }

	/// Creates a single shader program with specified type, source and desc.
	/**
	 *  @throws ValidationError
	 */
	ShaderProgram(
		ShaderType shader_type,
		const GLSLSource& glsl_source,
		ObjectDesc&& object_desc
	): Program(
		Program::ExternalName_(),
		_make(shader_type, glsl_source.Count(), glsl_source.Parts()),
		std::move(object_desc)
	)
	{ _check(); }
};
#endif

/// A Program that allows to attach shaders and links itself during construction
/** This specialization of Program allows to build a whole shading language
 *  program (i.e. to attach its shaders, optionally make the program separable,
 *  link and use it during construction.
 *
 *  @see Program
 */
class QuickProgram
 : public Program
{
private:
	void _do_make_separable(std::true_type)
	{
#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects
		MakeSeparable();
#endif
	}

	static void _do_make_separable(std::false_type) { }

	template <bool Separable>
	void _do_initialize(std::integral_constant<bool, Separable> separable)
	{
		_do_make_separable(separable);
		Link();
		Use();
	}

	template <typename Tuple, size_t N>
	void _attach_tuple(
		const Tuple& /*tuple*/,
		std::integral_constant<size_t, N>,
		std::integral_constant<size_t, N>
	){ }

	template <typename Tuple, size_t I, size_t N>
	void _attach_tuple(
		const Tuple& tuple,
		std::integral_constant<size_t, I>,
		std::integral_constant<size_t, N>
	)
	{
		this->AttachShader(std::get<I>(tuple));
		_attach_tuple(
			tuple,
			std::integral_constant<size_t, I+1>(),
			std::integral_constant<size_t, N>()
		);
	}

	template <bool Separable, typename Tuple>
	void _initialize_tuple(
		std::integral_constant<bool, Separable> separable,
		const Tuple& tuple
	)
	{
		std::integral_constant<size_t, 0> i;
		std::integral_constant<size_t, std::tuple_size<Tuple>::value> n;
		_attach_tuple(tuple, i, n);
		_do_initialize(separable);
	}

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	void _attach(const Shader& shader)
	{
		this->AttachShader(shader);
	}

	template <typename ... Shaders>
	void _attach(const Shader& shader, const Shaders& ... shaders)
	{
		this->AttachShader(shader);
		_attach(shaders...);
	}

	template <bool Separable, typename ... Shaders>
	void _initialize(
		std::integral_constant<bool, Separable> separable,
		const Shaders& ... shaders
	)
	{
		_attach(shaders...);
		_do_initialize(separable);
	}
#endif

public:
#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Build a optionally separable program using the specified @c shaders
	template <bool Separable, typename ... Shaders>
	QuickProgram(
		std::integral_constant<bool, Separable> separable,
		const Shader& shader,
		const Shaders& ... shaders
	): Program()
	{
		_initialize(separable, shader, shaders...);
	}

	/// Build a program with @c description using the specified @c shaders
	template <bool Separable, typename ... Shaders>
	QuickProgram(
		ObjectDesc&& description,
		std::integral_constant<bool, Separable> separable,
		const Shader& shader,
		const Shaders& ... shaders
	): Program(std::move(description))
	{
		_initialize(separable, shader, shaders...);
	}

	/// Build a optionally separable program using the specified @c shaders
	template <bool Separable, typename ... Shaders>
	QuickProgram(
		std::integral_constant<bool, Separable> separable,
		const std::tuple<Shaders...>& shaders
	): Program()
	{
		_initialize_tuple(separable, shaders);
	}

	/// Build a program with @c description using the specified @c shaders
	template <bool Separable, typename ... Shaders>
	QuickProgram(
		ObjectDesc&& description,
		std::integral_constant<bool, Separable> separable,
		const std::tuple<Shaders...>& shaders
	): Program(std::move(description))
	{
		_initialize_tuple(separable, shaders);
	}
#else
	template <bool Separable, typename StdTuple>
	QuickProgram(
		ObjectDesc&& description,
		std::integral_constant<bool, Separable> separable,
		const StdTuple& shaders
	): Program(std::move(description))
	{
		_initialize_tuple(separable, shaders);
	}

	template <bool Separable>
	QuickProgram(
		std::integral_constant<bool, Separable> separable,
		const Shader& s0
	): Program()
	{
		this->AttachShader(s0);
		_do_initialize(separable);
	}

	template <bool Separable>
	QuickProgram(
		std::integral_constant<bool, Separable> separable,
		const Shader& s0,
		const Shader& s1
	): Program()
	{
		this->AttachShader(s0);
		this->AttachShader(s1);
		_do_initialize(separable);
	}

	template <bool Separable>
	QuickProgram(
		std::integral_constant<bool, Separable> separable,
		const Shader& s0,
		const Shader& s1,
		const Shader& s2
	): Program()
	{
		this->AttachShader(s0);
		this->AttachShader(s1);
		this->AttachShader(s2);
		_do_initialize(separable);
	}
#endif // NO_VARIADIC_TEMPLATES
};

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
/// A Program that has its shaders statically hardcoded
template <class ... Shaders>
class HardwiredProgram
 : protected Shaders ...
 , public QuickProgram
{
private:
	template <class SingleShader>
	const Shader& _single_shader(SingleShader*) const
	{
		return *((SingleShader*)this);
	}
public:
	/// Create an instance of the hardwired program
	HardwiredProgram(void)
	 : QuickProgram(std::false_type(), _single_shader((Shaders*)0)...)
	{ }

	/// Create an instance of the hardwired program with a @c description
	HardwiredProgram(ObjectDesc&& description)
	 : QuickProgram(
		std::move(description),
		std::false_type(),
		_single_shader((Shaders*)0)...
	)
	{ }

	/// Create an instance of the hardwired program, possibly @c separable
	template <bool Separable>
	HardwiredProgram(std::integral_constant<bool, Separable> separable)
	 : QuickProgram(separable, _single_shader((Shaders*)0)...)
	{ }

	/// Create an instance of the hardwired program with a @c description
	template <bool Separable>
	HardwiredProgram(
		ObjectDesc&& description,
		std::integral_constant<bool, Separable> separable
	): QuickProgram(
		std::move(description),
		separable,
		_single_shader((Shaders*)0)...
	)
	{ }
};

#endif // NO_VARIADIC_TEMPLATES

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/program.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
