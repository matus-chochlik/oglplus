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

#include <oglplus/error.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/link_error.hpp>
#include <oglplus/auxiliary/info_log.hpp>
#include <oglplus/auxiliary/base_range.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace oglplus {
namespace aux {

// helper class used to store
class _ProgramVarInfoContext
{
private:
	GLuint _name;
	GLuint _size;
	std::vector<GLchar> _buffer;
public:
	_ProgramVarInfoContext(GLuint name, GLuint size)
	 : _name(name)
	 , _size(size)
	{ }

	_ProgramVarInfoContext(_ProgramVarInfoContext&& tmp)
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
 , public FriendOf<Shader>
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
	/// Attaches the shader to this program
	void AttachShader(const Shader& shader)
	{
		assert(_name != 0);
		::glAttachShader(_name, FriendOf<Shader>::GetName(shader));
		ThrowOnError(OGLPLUS_ERROR_INFO(AttachShader));
	}


	/// Detaches the shader to this program
	void DetachShader(const Shader& shader)
	{
		assert(_name != 0);
		::glDetachShader(_name, FriendOf<Shader>::GetName(shader));
		ThrowOnError(OGLPLUS_ERROR_INFO(DetachShader));
	}

	/// Returns true if the program is already linked,, false otherwise
	/**
	 *  @see Link
	 */
	bool IsLinked(void) const
	{
		int status;
		::glGetProgramiv(_name, GL_LINK_STATUS, &status);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));
		return status == GL_TRUE;
	}

	/// Returns the linker output if the program is linked
	/**
	 *  @see IsLinked
	 *  @see Link
	 */
	std::string GetInfoLog(void) const
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
	 *  @see Link
	 */
	void Link(void) const
	{
		assert(_name != 0);
		::glLinkProgram(_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(LinkProgram));
		if(!IsLinked())
			throw LinkError(
				GetInfoLog(),
				OGLPLUS_ERROR_INFO(LinkProgram)
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
		AssertNoError(OGLPLUS_ERROR_INFO(UseProgram));
	}

	/// Information about a single active vertex attribute or uniform
	class ActiveVariableInfo
	{
	private:
		GLuint _index;
		GLint _size;
		GLenum _type;
		std::string _name;
	protected:
		ActiveVariableInfo(
			aux::_ProgramVarInfoContext& context,
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
			_name = std::string(context.Buffer().data(), strlen);
		}
	public:
		/// Returns the index of the attribute or uniform
		GLuint Index(void) const
		{
			return _index;
		}

		/// Returns the name (identifier) of the attribute or uniform
		const std::string& Name(void) const
		{
			return _name;
		}

		/// Returns the size in units of Type
		const GLint Size(void) const
		{
			return _size;
		}

		// TODO: Type()
	};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
	/// The type of the range for traversing active vertex attributes
	typedef BaseRange<ActiveVariableInfo> ActiveAttribRange;
	/// The type of the range for traversing active uniforms
	typedef BaseRange<ActiveVariableInfo> ActiveUniformRange;
#else

	struct ActiveAttribInfo : ActiveVariableInfo
	{
		ActiveAttribInfo(
			aux::_ProgramVarInfoContext& context,
			GLuint index
		): ActiveVariableInfo(context, index, &::glGetActiveAttrib)
		{
			ThrowOnError(OGLPLUS_ERROR_INFO(GetActiveAttrib));
		}
	};
	typedef aux::BaseRange<
		aux::_ProgramVarInfoContext,
		ActiveAttribInfo
	> ActiveAttribRange;

	struct ActiveUniformInfo : ActiveVariableInfo
	{
		ActiveUniformInfo(
			aux::_ProgramVarInfoContext& context,
			GLuint index
		): ActiveVariableInfo(context, index, &::glGetActiveUniform)
		{
			ThrowOnError(OGLPLUS_ERROR_INFO(GetActiveUniform));
		}
	};
	typedef aux::BaseRange<
		aux::_ProgramVarInfoContext,
		ActiveUniformInfo
	> ActiveUniformRange;
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
		GLint count = 0, length = 0;
		// get the count of active attributes
		::glGetProgramiv(_name, GL_ACTIVE_ATTRIBUTES, &count);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));
		// get the maximum string length of the longest identifier
		::glGetProgramiv(_name, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));

		return ActiveAttribRange(
			aux::_ProgramVarInfoContext(_name, length),
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
		GLint count = 0, length = 0;
		// get the count of active uniforms
		::glGetProgramiv(_name, GL_ACTIVE_UNIFORMS, &count);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));
		// get the maximum string length of the longest identifier
		::glGetProgramiv(_name, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));

		return ActiveUniformRange(
			aux::_ProgramVarInfoContext(_name, length),
			0, count
		);
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
		std::string _name;
	public:
		ActiveUniformBlockInfo(
			aux::_ProgramVarInfoContext& context,
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
			ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));
			GLsizei strlen = 0;
			::glGetActiveUniformBlockName(
				context.Program(),
				index,
				context.Buffer().size(),
				&strlen,
				context.Buffer().data()
			);
			ThrowOnError(
				OGLPLUS_ERROR_INFO(GetActiveUniformBlockName)
			);
			_name = std::string(context.Buffer().data(), strlen);
		}

		/// Returns the index of the attribute or uniform
		GLuint Index(void) const
		{
			return _index;
		}

		/// Returns the name (identifier) of the named uniform block
		const std::string& Name(void) const
		{
			return _name;
		}

		// TODO: active uniform indices, etc.
	};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
	/// The type of the range for traversing active uniform blocks
	typedef BaseRange<ActiveUniformBlockInfo> ActiveUniformRange;
#else
	typedef aux::BaseRange<
		aux::_ProgramVarInfoContext,
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
		GLint count = 0, length = 0;
		// get the count of active uniform blocks
		::glGetProgramiv(_name, GL_ACTIVE_UNIFORM_BLOCKS, &count);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));
		if(count != 0)
		{
			// get the string length of the first identifier
			::glGetProgramiv(
				_name,
				GL_UNIFORM_BLOCK_NAME_LENGTH,
				&length
			);
			ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));
		}
		return ActiveUniformBlockRange(
			aux::_ProgramVarInfoContext(_name, length),
			0, count
		);
	}

	void MakeSeparable(bool para = true) const
	{
		assert(_name != 0);
		glProgramParameteri(
			_name,
			GL_PROGRAM_SEPARABLE,
			para ? GL_TRUE : GL_FALSE
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(ProgramParameteri));
	}

	void MakeRetrievable(bool para = true) const
	{
		assert(_name != 0);
		glProgramParameteri(
			_name,
			GL_PROGRAM_BINARY_RETRIEVABLE_HINT,
			para ? GL_TRUE : GL_FALSE
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(ProgramParameteri));
	}

	void GetBinary(std::vector<GLubyte>& binary, GLenum& format) const
	{
		assert(_name != 0);
		GLint size = 0;
		::glGetProgramiv(
			_name,
			GL_PROGRAM_BINARY_LENGTH,
			&size
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));
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
			ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramBinary));
		}
	}

	void Binary(const std::vector<GLubyte>& binary, GLenum format) const
	{
		assert(_name != 0);
		::glProgramBinary(
			_name,
			format,
			binary.data(),
			binary.size()
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(ProgramBinary));
	}

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

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// Encapsulates OpenGL shading language-related program functionality
class Program
 : public ProgramOps
{ };
#else
typedef Object<ProgramOps, false> Program;
#endif

} // namespace oglplus

#endif // include guard
