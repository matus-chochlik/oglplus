/**
 *  @file oglplus/program.hpp
 *  @brief Program wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PROGRAM_1107121519_HPP
#define OGLPLUS_PROGRAM_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/transform_feedback.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/link_error.hpp>
#include <oglplus/auxiliary/info_log.hpp>
#include <oglplus/auxiliary/base_range.hpp>
#include <oglplus/string.hpp>

#include <vector>
#include <cassert>

namespace oglplus {
namespace aux {

class ProgramPartInfoContext
{
private:
	GLuint _name;
	GLuint _size;
	std::vector<GLchar> _buffer;
public:
	ProgramPartInfoContext(GLuint name, GLuint size)
	 : _name(name)
	 , _size(size)
	{ }

	ProgramPartInfoContext(ProgramPartInfoContext&& tmp)
	 : _name(tmp._name)
	 , _size(tmp._size)
	 , _buffer(std::move(tmp._buffer))
	{ }

	GLuint Program(void) const
	{
		return _name;
	}

	std::vector<GLchar>& Buffer(void)
	{
		if(_size && _buffer.empty())
			_buffer.resize(_size);
		return _buffer;
	}
};

} // namespace aux

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
 , public FriendOf<ShaderOps>
 , public FriendOf<VertexAttribOps>
{
protected:
	static void _init(GLsizei, GLuint& _name)
	{
		_name = OGLPLUS_GLFUNC(CreateProgram)();
		HandleIfError(OGLPLUS_ERROR_INFO(CreateProgram));
	}

	static void _cleanup(GLsizei, GLuint& _name)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(DeleteProgram)(_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsProgram)(_name);
	}

	friend class FriendOf<ProgramOps>;
public:
	GLint GetIntParam(GLenum query) const
	{
		GLint result;
		OGLPLUS_GLFUNC(GetProgramiv)(_name, query, &result);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramiv,
			Program,
			_name
		));
		return result;
	}

	/// Attaches the shader to this program
	/**
	 *  @glsymbols
	 *  @glfunref{AttachShader}
	 */
	void AttachShader(const ShaderOps& shader)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(AttachShader)(
			_name,
			FriendOf<ShaderOps>::GetName(shader)
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			AttachShader,
			Program,
			_name
		));
	}


	/// Detaches the shader to this program
	/**
	 *  @glsymbols
	 *  @glfunref{DetachShader}
	 */
	void DetachShader(const ShaderOps& shader)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(DetachShader)(
			_name,
			FriendOf<ShaderOps>::GetName(shader)
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			DetachShader,
			Program,
			_name
		));
	}

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
	String GetInfoLog(void) const
	{
		assert(_name != 0);
		return aux::GetInfoLog(
			_name, OGLPLUS_GLFUNC(GetProgramiv),
			OGLPLUS_GLFUNC(GetProgramInfoLog),
			"GetProgramiv",
			"GetProgramInfoLog"
		);
	}

	/// Links this shading language program
	/**
	 *  @throws Error LinkError
	 *  @see IsLinked
	 *
	 *  @glsymbols
	 *  @glfunref{LinkProgram}
	 *  @glfunref{GetProgram}
	 *  @glfunref{GetProgramInfoLog}
	 */
	void Link(void) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(LinkProgram)(_name);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			LinkProgram,
			Program,
			_name
		));
		if(!IsLinked())
			HandleBuildError<LinkError>(
				GetInfoLog(),
				OGLPLUS_OBJECT_ERROR_INFO(
					LinkProgram,
					Program,
					_name
				)
			);
	}

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
	 *  @throws Error ValidationError
	 *  @see Link
	 *
	 *  @glsymbols
	 *  @glfunref{ValidateProgram}
	 *  @glfunref{GetProgram}
	 *  @glfunref{GetProgramInfoLog}
	 */
	void Validate(void) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ValidateProgram)(_name);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			ValidateProgram,
			Program,
			_name
		));
		if(!IsValid())
			HandleBuildError<ValidationError>(
				GetInfoLog(),
				OGLPLUS_OBJECT_ERROR_INFO(
					ValidateProgram,
					Program,
					_name
				)
			);
	}

	/// Uses this shading language program
	/**
	 *  @note The program must be linked before it is used.
	 *
	 *  @see IsLinked
	 *  @see Link
	 *
	 *  @glsymbols
	 *  @glfunref{UseProgram}
	 */
	void Use(void) const
	{
		assert(_name != 0);
		assert(IsLinked());
		OGLPLUS_GLFUNC(UseProgram)(_name);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			UseProgram,
			Program,
			_name
		));
	}

	/// Deactivates the currently active/used program (if any)
	/**
	 *  @glsymbols
	 *  @glfunref{UseProgram}
	 */
	static void UseNone(void)
	{
		OGLPLUS_GLFUNC(UseProgram)(0);
		AssertNoError(OGLPLUS_ERROR_INFO(UseProgram));
	}

	/// Information about a single active vertex attribute or uniform
	class ActiveVariableInfo
	{
	private:
		GLuint _index;
		GLint _size;
		GLenum _type;
		String _name;
	protected:
		ActiveVariableInfo(
			aux::ProgramPartInfoContext& context,
			GLuint index,
			void (*GetActiveVariable)(
				GLuint /*program*/,
				GLuint /*index*/,
				GLsizei /*bufsize*/,
				GLsizei* /*length*/,
				GLint* /*size*/,
				GLenum* /*type*/,
				GLchar* /*name*/
			)
		): _index(index)
		 , _size(0)
		{
			GLsizei strlen = 0;
			GetActiveVariable(
				context.Program(),
				index,
				context.Buffer().size(),
				&strlen,
				&_size,
				&_type,
				context.Buffer().data()
			);
			_name = String(context.Buffer().data(), strlen);
		}

		// TODO: this is here only because GLEW defines
		// glGetTransformFeedbackVaryings this way
		ActiveVariableInfo(
			aux::ProgramPartInfoContext& context,
			GLuint index,
			void (*GetActiveVariable)(GLuint, GLuint, GLint*)
		): _index(index)
		 , _size(0)
		 , _type(0)
		 , _name(0)
		{
		}
	public:
		/// Returns the index of the attribute or uniform
		GLuint Index(void) const
		{
			return _index;
		}

		/// Returns the name (identifier) of the attribute or uniform
		const String& Name(void) const
		{
			return _name;
		}

		/// Returns the size in units of Type
		const GLint Size(void) const
		{
			return _size;
		}

		const SLDataType Type(void) const
		{
			return SLDataType(_type);
		}
	};

#if OGLPLUS_DOCUMENTATION_ONLY
	/// The type of the range for traversing active vertex attributes
	typedef Range<ActiveVariableInfo> ActiveAttribRange;
	/// The type of the range for traversing active uniforms
	typedef Range<ActiveVariableInfo> ActiveUniformRange;
	/// The type of the range for traversing transform feedback varyings
	typedef Range<ActiveVariableInfo> TransformFeedbackVaryingRange;
	/// The type of the range for traversing program's shaders
	typedef Range<Managed<Shader> > ShaderRange;
#else

	struct ActiveAttribInfo : ActiveVariableInfo
	{
		ActiveAttribInfo(
			aux::ProgramPartInfoContext& context,
			GLuint index
		): ActiveVariableInfo(
			context,
			index,
			OGLPLUS_GLFUNC(GetActiveAttrib)
		)
		{
			HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
				GetActiveAttrib,
				Program,
				context.Program()
			));
		}
	};
	typedef aux::BaseRange<
		aux::ProgramPartInfoContext,
		ActiveAttribInfo
	> ActiveAttribRange;

	struct ActiveUniformInfo : ActiveVariableInfo
	{
		ActiveUniformInfo(
			aux::ProgramPartInfoContext& context,
			GLuint index
		): ActiveVariableInfo(
			context,
			index,
			OGLPLUS_GLFUNC(GetActiveUniform)
		)
		{
			HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
				GetActiveUniform,
				Program,
				context.Program()
			));
		}
	};
	typedef aux::BaseRange<
		aux::ProgramPartInfoContext,
		ActiveUniformInfo
	> ActiveUniformRange;

	struct TransformFeedbackVaryingInfo : ActiveVariableInfo
	{
		TransformFeedbackVaryingInfo(
			aux::ProgramPartInfoContext& context,
			GLuint index
		): ActiveVariableInfo(
			context,
			index,
			OGLPLUS_GLFUNC(GetTransformFeedbackVarying)
		)
		{
			HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
				GetTransformFeedbackVarying,
				Program,
				context.Program()
			));
		}
	};
	typedef aux::BaseRange<
		aux::ProgramPartInfoContext,
		TransformFeedbackVaryingInfo
	> TransformFeedbackVaryingRange;

	struct ShaderIterationContext
	{
		std::vector<GLuint> _shader_names;

		ShaderIterationContext(GLuint name, GLuint count)
		 : _shader_names(count)
		{
			OGLPLUS_GLFUNC(GetAttachedShaders)(
				name,
				_shader_names.size(),
				nullptr,
				_shader_names.data()
			);
			HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
				GetAttachedShaders,
				Program,
				name
			));
		};

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

	typedef aux::BaseRange<
			ShaderIterationContext,
			ManagedShader
	> ShaderRange;
#endif

	/// Returns a range allowing to do the traversal of active attributes
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 */
	ActiveAttribRange ActiveAttribs(void) const
	{
		// get the count of active attributes
		GLint count = GetIntParam(GL_ACTIVE_ATTRIBUTES);
		// get the maximum string length of the longest identifier
		GLint length = GetIntParam(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);

		return ActiveAttribRange(
			aux::ProgramPartInfoContext(_name, length),
			0, count
		);
	}

	/// Returns a range allowing to do the traversal of active uniforms
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 */
	ActiveUniformRange ActiveUniforms(void) const
	{
		// get the count of active uniforms
		GLint count  = GetIntParam(GL_ACTIVE_UNIFORMS);
		// get the maximum string length of the longest identifier
		GLint length = GetIntParam(GL_ACTIVE_UNIFORM_MAX_LENGTH);

		return ActiveUniformRange(
			aux::ProgramPartInfoContext(_name, length),
			0, count
		);
	}

	/// Returns a range allowing to do the traversal of feedback varyings
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 */
	TransformFeedbackVaryingRange TransformFeedbackVaryings(void) const
	{
		// get the count of transform feedback varyings
		GLint count = GetIntParam(GL_TRANSFORM_FEEDBACK_VARYINGS);
		GLint length = GetIntParam(
			GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH
		);

		return TransformFeedbackVaryingRange(
			aux::ProgramPartInfoContext(_name, length),
			0, count
		);
	}

	/// Returns a range allowing to traverse shaders attached to this program
	ShaderRange AttachedShaders(void) const
	{
		GLint count = GetIntParam(GL_ATTACHED_SHADERS);
		return ShaderRange(
			ShaderIterationContext(_name, count),
			0, count
		);
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
	) const
	{
		OGLPLUS_GLFUNC(TransformFeedbackVaryings)(
			_name,
			count,
			varyings,
			GLenum(mode)
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			TransformFeedbackVaryings,
			Program,
			_name
		));
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
	) const
	{
		std::vector<const GLchar*> tmp(varyings.size());
		auto i = varyings.begin(), e = varyings.end();
		auto t = tmp.begin();
		while(i != e)
		{
			assert(t != tmp.end());
			*t = i->c_str();
			++i;
			++t;
		}
		OGLPLUS_GLFUNC(TransformFeedbackVaryings)(
			_name,
			GLsizei(tmp.size()),
			tmp.data(),
			GLenum(mode)
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			TransformFeedbackVaryings,
			Program,
			_name
		));
	}

	/// Information about a active uniform block
	/** Do not instantiate this class directly, instances are returned
	 *  by the ActiveUniformBlocks() function.
	 *
	 *  @see ActiveUniformBlocks
	 */
	class ActiveUniformBlockInfo
	{
	private:
		GLuint _index;
		String _name;
	public:
		ActiveUniformBlockInfo(
			aux::ProgramPartInfoContext& context,
			GLuint index
		): _index(0)
		{
			GLint length = 0;
			OGLPLUS_GLFUNC(GetProgramiv)(
				context.Program(),
				GL_UNIFORM_BLOCK_NAME_LENGTH,
				&length
			);
			if(context.Buffer().size() < size_t(length))
				context.Buffer().resize(length);
			HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
				GetProgramiv,
				Program,
				context.Program()
			));
			GLsizei strlen = 0;
			OGLPLUS_GLFUNC(GetActiveUniformBlockName)(
				context.Program(),
				index,
				context.Buffer().size(),
				&strlen,
				context.Buffer().data()
			);
			HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
				GetActiveUniformBlockName,
				Program,
				context.Program()
			));
			_name = String(context.Buffer().data(), strlen);
		}

		/// Returns the index of the attribute or uniform
		GLuint Index(void) const
		{
			return _index;
		}

		/// Returns the name (identifier) of the named uniform block
		const String& Name(void) const
		{
			return _name;
		}

		// TODO: active uniform indices, etc.
	};

#if OGLPLUS_DOCUMENTATION_ONLY
	/// The type of the range for traversing active uniform blocks
	typedef Range<ActiveUniformBlockInfo> ActiveUniformRange;
#else
	typedef aux::BaseRange<
		aux::ProgramPartInfoContext,
		ActiveUniformBlockInfo
	> ActiveUniformBlockRange;
#endif

	/// Returns a range allowing to do the traversal of active attributes
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 */
	ActiveUniformBlockRange ActiveUniformBlocks(void) const
	{
		// get the count of active uniform blocks
		GLint count = GetIntParam(GL_ACTIVE_UNIFORM_BLOCKS);
		GLint length = 0;
		if(count != 0)
		{
			// get the string length of the first identifier
			length = GetIntParam(GL_UNIFORM_BLOCK_NAME_LENGTH);
		}
		return ActiveUniformBlockRange(
			aux::ProgramPartInfoContext(_name, length),
			0, count
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects
	/// Makes this program separable
	/**
	 *  @glsymbols
	 *  @glfunref{ProgramParameter}
	 */
	void MakeSeparable(bool para = true) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ProgramParameteri)(
			_name,
			GL_PROGRAM_SEPARABLE,
			para ? GL_TRUE : GL_FALSE
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			ProgramParameteri,
			Program,
			_name
		));
	}
#endif // separate shader objects

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_get_program_binary
	/// Makes this program retrievable in binary form
	/**
	 *  @see GetBinary
	 *
	 *  @glsymbols
	 *  @glfunref{ProgramParameter}
	 */
	void MakeRetrievable(bool para = true) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ProgramParameteri)(
			_name,
			GL_PROGRAM_BINARY_RETRIEVABLE_HINT,
			para ? GL_TRUE : GL_FALSE
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			ProgramParameteri,
			Program,
			_name
		));
	}

	/// Returns this programs binary representation
	/**
	 *  @see MakeRetrievable
	 *  @see Binary
	 *
	 *  @glsymbols
	 *  @glfunref{GetProgram}
	 *  @glfunref{GetProgramBinary}
	 *  @gldefref{PROGRAM_BINARY_LENGTH}
	 */
	void GetBinary(std::vector<GLubyte>& binary, GLenum& format) const
	{
		assert(_name != 0);
		GLint size = GetIntParam(GL_PROGRAM_BINARY_LENGTH);
		if(size > 0)
		{
			GLsizei len = 0;
			binary.resize(size);
			OGLPLUS_GLFUNC(GetProgramBinary)(
				_name,
				size,
				&len,
				&format,
				binary.data()
			);
			HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
				GetProgramBinary,
				Program,
				_name
			));
		}
	}

	/// Allows to specify to program code in binary form
	/**
	 *  @see MakeRetrievable
	 *  @see GetBinary
	 *
	 *  @glsymbols
	 *  @glfunref{ProgramBinary}
	 */
	void Binary(const std::vector<GLubyte>& binary, GLenum format) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ProgramBinary)(
			_name,
			format,
			binary.data(),
			binary.size()
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			ProgramBinary,
			Program,
			_name
		));
	}
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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_gpu_shader5

	/// Returns the number of invocations of geometry shader per primitive
	/**
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

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating  OpenGL shading language program functionality
/**
 *  @ingroup objects
 */
class Program
 : public ProgramOps
{ };
#else
typedef Object<ProgramOps, false> Program;
#endif

// TODO: docs
class QuickProgram
 : public Program
{
private:
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

	template <typename ... Shaders>
	void _initialize(const Shaders& ... shaders)
	{
		_attach(shaders...);
		Link();
		Use();
	}
public:
	template <typename ... Shaders>
	QuickProgram(const Shaders& ... shaders)
	 : Program()
	{
		_initialize(shaders...);
	}

	template <typename ... Shaders>
	QuickProgram(const GLchar* description, const Shaders& ... shaders)
	 : Program(description)
	{
		_initialize(shaders...);
	}

	template <typename ... Shaders>
	QuickProgram(const String& description, const Shaders& ... shaders)
	 : Program(description)
	{
		_initialize(shaders...);
	}
};

} // namespace oglplus

#endif // include guard
