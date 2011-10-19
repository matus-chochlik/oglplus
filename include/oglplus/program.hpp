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
 */
class ProgramOps
 : public Named
 , public FriendOf<ShaderOps>
 , public FriendOf<VertexAttribOps>
{
protected:
	static void _init(GLsizei, GLuint& _name)
	{
		_name = ::glCreateProgram();
		ThrowOnError(OGLPLUS_ERROR_INFO(CreateProgram));
	}

	static void _cleanup(GLsizei, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteProgram(_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsProgram(_name);
	}

	friend class FriendOf<ProgramOps>;
public:
	GLint GetIntParam(GLenum query) const
	{
		GLint result;
		::glGetProgramiv(_name, query, &result);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramiv,
			Program,
			_name
		));
		return result;
	}

	/// Attaches the shader to this program
	void AttachShader(const ShaderOps& shader)
	{
		assert(_name != 0);
		::glAttachShader(_name, FriendOf<ShaderOps>::GetName(shader));
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			AttachShader,
			Program,
			_name
		));
	}


	/// Detaches the shader to this program
	void DetachShader(const ShaderOps& shader)
	{
		assert(_name != 0);
		::glDetachShader(_name, FriendOf<ShaderOps>::GetName(shader));
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			DetachShader,
			Program,
			_name
		));
	}

	/// Returns true if the program is already linked, false otherwise
	/**
	 *  @see Link
	 *  @see Validate
	 */
	bool IsLinked(void) const
	{
		return GetIntParam(GL_LINK_STATUS) == GL_TRUE;
	}

	/// Returns the linker output if the program is linked
	/**
	 *  @see IsLinked
	 *  @see Link
	 */
	String GetInfoLog(void) const
	{
		assert(_name != 0);
		return aux::GetInfoLog(
			_name, ::glGetProgramiv,
			::glGetProgramInfoLog,
			"GetProgramiv",
			"GetProgramInfoLog"
		);
	}

	/// Links this shading language program
	/**
	 *  @throws Error LinkError
	 *  @see IsLinked
	 */
	void Link(void) const
	{
		assert(_name != 0);
		::glLinkProgram(_name);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			LinkProgram,
			Program,
			_name
		));
		if(!IsLinked())
			throw LinkError(
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
	 */
	bool IsValid(void) const
	{
		return GetIntParam(GL_VALIDATE_STATUS) == GL_TRUE;
	}

	/// Validates this shading language program
	/**
	 *  @throws Error ValidationError
	 *  @see Link
	 */
	void Validate(void) const
	{
		assert(_name != 0);
		::glValidateProgram(_name);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			ValidateProgram,
			Program,
			_name
		));
		if(!IsValid())
			throw ValidationError(
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
	 */
	void Use(void) const
	{
		assert(_name != 0);
		assert(IsLinked());
		::glUseProgram(_name);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			UseProgram,
			Program,
			_name
		));
	}

	/// Deactivates the currently active/used program (if any)
	static void UseNone(void)
	{
		::glUseProgram(0);
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
			::glGetActiveAttrib
		)
		{
			ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
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
			::glGetActiveUniform
		)
		{
			ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
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
			::glGetTransformFeedbackVarying
		)
		{
			ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
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
			::glGetAttachedShaders(
				name,
				_shader_names.size(),
				nullptr,
				_shader_names.data()
			);
			ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
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
	 */
	void TransformFeedbackVaryings(
		GLsizei count,
		const GLchar** varyings,
		TransformFeedbackMode mode
	) const
	{
		::glTransformFeedbackVaryings(
			_name,
			count,
			varyings,
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			TransformFeedbackVaryings,
			Program,
			_name
		));
	}

	/// Sets the variables that will be captured during transform feedback
	/**
	 *  @throws Error
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
		::glTransformFeedbackVaryings(
			_name,
			GLsizei(tmp.size()),
			tmp.data(),
			GLenum(mode)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
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
			::glGetProgramiv(
				context.Program(),
				GL_UNIFORM_BLOCK_NAME_LENGTH,
				&length
			);
			if(context.Buffer().size() < size_t(length))
				context.Buffer().resize(length);
			ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
				GetProgramiv,
				Program,
				context.Program()
			));
			GLsizei strlen = 0;
			::glGetActiveUniformBlockName(
				context.Program(),
				index,
				context.Buffer().size(),
				&strlen,
				context.Buffer().data()
			);
			ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
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
	void MakeSeparable(bool para = true) const
	{
		assert(_name != 0);
		glProgramParameteri(
			_name,
			GL_PROGRAM_SEPARABLE,
			para ? GL_TRUE : GL_FALSE
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
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
	 */
	void MakeRetrievable(bool para = true) const
	{
		assert(_name != 0);
		glProgramParameteri(
			_name,
			GL_PROGRAM_BINARY_RETRIEVABLE_HINT,
			para ? GL_TRUE : GL_FALSE
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			ProgramParameteri,
			Program,
			_name
		));
	}

	/// Returns this programs binary representation
	/**
	 *  @see MakeRetrievable
	 *  @see Binary
	 */
	void GetBinary(std::vector<GLubyte>& binary, GLenum& format) const
	{
		assert(_name != 0);
		GLint size = GetIntParam(GL_PROGRAM_BINARY_LENGTH);
		if(size > 0)
		{
			GLsizei len = 0;
			binary.resize(size);
			::glGetProgramBinary(
				_name,
				size,
				&len,
				&format,
				binary.data()
			);
			ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
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
	 */
	void Binary(const std::vector<GLubyte>& binary, GLenum format) const
	{
		assert(_name != 0);
		::glProgramBinary(
			_name,
			format,
			binary.data(),
			binary.size()
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			ProgramBinary,
			Program,
			_name
		));
	}
#endif // get program binary

	/// Returns the transform feedback buffer mode
	TransformFeedbackMode TransformFeedbackBufferMode(void) const
	{
		return TransformFeedbackMode(
			GetIntParam(GL_TRANSFORM_FEEDBACK_BUFFER_MODE)
		);
	}

	/// Returns the number of vertices that the geometry shader will output
	GLint GeometryVerticesOut(void) const
	{
		return GetIntParam(GL_GEOMETRY_VERTICES_OUT);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_gpu_shader5

	/// Returns the number of invocations of geometry shader per primitive
	GLint GeometryShaderInvocations(void) const
	{
		return GetIntParam(GL_GEOMETRY_SHADER_INVOCATIONS);
	}
#endif // gpu shader 5

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2

	/// Returns the geometry shader input primitive type
	PrimitiveType GeometryInputType(void) const
	{
		return PrimitiveType(GetIntParam(GL_GEOMETRY_INPUT_TYPE));
	}

	/// Returns the geometry shader output primitive type
	PrimitiveType GeometryOutputType(void) const
	{
		return PrimitiveType(GetIntParam(GL_GEOMETRY_OUTPUT_TYPE));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_tessellation_shader

	/// Returns the vertex order in tesselation evaluation shader
	FaceOrientation TessGenVertexOrder(void) const
	{
		return FaceOrientation(GetIntParam(GL_TESS_GEN_VERTEX_ORDER));
	}

	/// Returns the tesselation generator output primitive type
	TessGenPrimitiveType TessGenMode(void) const
	{
		return TessGenPrimitiveType(GetIntParam(GL_TESS_GEN_MODE));
	}

	/// Returns the tesselation generator primitive spacing mode
	TessGenPrimitiveSpacing TessGenSpacing(void) const
	{
		return TessGenPrimitiveSpacing(GetIntParam(GL_TESS_GEN_SPACING));
	}

	/// Returns true if point mode is enabled in tesslation eval. shader
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

} // namespace oglplus

#endif // include guard
