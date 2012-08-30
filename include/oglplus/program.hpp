/**
 *  @file oglplus/program.hpp
 *  @brief Program wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PROGRAM_1107121519_HPP
#define OGLPLUS_PROGRAM_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/object.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/transform_feedback.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/link_error.hpp>
#include <oglplus/program_interface.hpp>
#include <oglplus/auxiliary/program.hpp>
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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
/// Information about a single active program resource
/**
 *  @see Program
 *  @see Program::ActiveResources()
 *  @see ProgramInterface
 *
 *  @code
 *  Program prog;
 *  ...
 *  ProgramInterface intf = ProgramInterface::ProgramInput;
 *  for(auto range=prog.ActiveResources(intf); !range.Empty(); range.Next())
 *  {
 *      auto res = range.Front();
 *      std::cout << res.Name() << std::endl;
 *      std::cout << EnumValueName(res.Type()) << std::endl;
 *      if(res.IsPerPatch())
 *          std::cout << "Per-patch" << std::endl;
 *      else std::cout << "Not per-patch << std::endl;
 *  }
 *  @endcode
 */
class ProgramResource
{
private:
	GLint _program;
	GLenum _interface;
	GLuint _index;
	String _name;

	GLint GetParams(
		GLenum property,
		GLsizei bufsize,
		GLsizei* written,
		GLint* params
	) const
	{
		OGLPLUS_GLFUNC(GetProgramResourceiv)(
			_program,
			_interface,
			_index,
			1, &property,
			bufsize,
			written,
			params
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetProgramResourceiv));
		return params[0];
	}

	GLint GetParam(GLenum property) const
	{
		GLint res;
		return GetParams(property, 1, nullptr, &res);
	}
public:
	ProgramResource(
		aux::ProgramInterfaceContext& context,
		GLuint index
	): _program(context.Program())
	 , _interface(context.Interface())
	 , _index(index)
	{
		GLsizei bufsize = context.Buffer().size(), length = 0;
		OGLPLUS_GLFUNC(GetProgramResourceName)(
			_program,
			_interface,
			_index,
			bufsize,
			&length,
			context.Buffer().data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetProgramResourceName));
		_name.assign(context.Buffer().data(), length);
	}

	/// Returns the interface of the resource
	ProgramInterface Interface(void) const
	{
		return ProgramInterface(_interface);
	}

	/// Returns the name of the resource
	const String& Name(void) const
	{
		return _name;
	}

	/// Returns the index of the resource
	GLuint Index(void) const
	{
		return _index;
	}

	/// Returns the data type of the resource (if applicable)
	SLDataType Type(void) const
	{
		return SLDataType(GetParam(GL_TYPE));
	}

	/// Returns the array size of the resource (if applicable)
	GLint ArraySize(void) const
	{
		return GetParam(GL_ARRAY_SIZE);
	}

	/// Returns true if the resource is per-patch (if applicable)
	bool IsPerPatch(void) const
	{
		return GetParam(GL_IS_PER_PATCH) != 0;
	}

	// TODO: finish this
};
#endif

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
protected:
	static void _init(GLsizei _count, GLuint* _name, std::true_type)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_count == 1);
		assert(_name != nullptr);
		try{*_name = OGLPLUS_GLFUNC(CreateProgram)();}
		catch(...){ }
	}

	static void _init(GLsizei _count, GLuint* _name, std::false_type)
	{
		assert(_count == 1);
		assert(_name != nullptr);
		*_name = OGLPLUS_GLFUNC(CreateProgram)();
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CreateProgram));
	}

	static void _cleanup(GLsizei _count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
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
	void AttachShader(const ShaderOps& shader)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(AttachShader)(
			_name,
			FriendOf<ShaderOps>::GetName(shader)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			AttachShader,
			Program,
			nullptr,
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
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			DetachShader,
			Program,
			nullptr,
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
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			LinkProgram,
			Program,
			nullptr,
			_name
		));
		if(OGLPLUS_IS_ERROR(!IsLinked()))
			HandleBuildError<LinkError>(
				GetInfoLog(),
				OGLPLUS_OBJECT_ERROR_INFO(
					LinkProgram,
					Program,
					nullptr,
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
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			ValidateProgram,
			Program,
			nullptr,
			_name
		));
		if(OGLPLUS_IS_ERROR(!IsValid()))
			HandleBuildError<ValidationError>(
				GetInfoLog(),
				OGLPLUS_OBJECT_ERROR_INFO(
					ValidateProgram,
					Program,
					nullptr,
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
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			UseProgram,
			Program,
			nullptr,
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(UseProgram));
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Information about a single active vertex attribute or uniform
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

#if GL_VERSION_4_3
	typedef aux::BaseRange<
		aux::ProgramInterfaceContext,
		ProgramResource
	> ActiveResourceRange;
#endif

	typedef aux::BaseRange<
		aux::ProgramInterfaceContext,
		aux::ActiveAttribInfo
	> ActiveAttribRange;

	typedef aux::BaseRange<
		aux::ProgramInterfaceContext,
		aux::ActiveUniformInfo
	> ActiveUniformRange;

#if GL_VERSION_4_0 || GL_ARB_shader_subroutine
	typedef aux::BaseRange<
		aux::ProgramInterfaceContext,
		aux::ActiveSubroutineInfo
	> ActiveSubroutineRange;

	typedef aux::BaseRange<
		aux::ProgramInterfaceContext,
		aux::ActiveSubroutineUniformInfo
	> ActiveSubroutineUniformRange;
#endif
	typedef aux::BaseRange<
		aux::ProgramInterfaceContext,
		aux::TransformFeedbackVaryingInfo
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
			OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
				GetAttachedShaders,
				Program,
				nullptr,
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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
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
	ActiveResourceRange ActiveResources(ProgramInterface intf) const
	{
		// get the count of active attributes
		GLint count = 0;
		OGLPLUS_GLFUNC(GetProgramInterfaceiv)(
			_name,
			GLenum(intf),
			GL_ACTIVE_RESOURCES,
			&count
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetProgramInterfaceiv));

		// get the maximum string length of the longest identifier
		GLint length = 0;
		OGLPLUS_GLFUNC(GetProgramInterfaceiv)(
			_name,
			GLenum(intf),
			GL_ACTIVE_RESOURCES,
			&count
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetProgramInterfaceiv));

		return ActiveResourceRange(
			aux::ProgramInterfaceContext(
				_name,
				length,
				GLenum(intf)
			), 0, count
		);
	}
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
			aux::ProgramInterfaceContext(_name, length),
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
			aux::ProgramInterfaceContext(_name, length),
			0, count
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_shader_subroutine
	/// Returns a range allowing to do the traversal of subroutines
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,0,ARB,shader_subroutine}
	 */
	ActiveSubroutineRange ActiveSubroutines(ShaderType stage) const
	{
		// get the count of active subroutine uniforms
		GLint count = GetStageIntParam(
			GLenum(stage),
			GL_ACTIVE_SUBROUTINES
		);
		// get the maximum string length of the longest identifier
		GLint length = GetStageIntParam(
			GLenum(stage),
			GL_ACTIVE_SUBROUTINE_MAX_LENGTH
		);

		return ActiveSubroutineRange(
			aux::ProgramInterfaceContext(
				_name,
				length,
				GLenum(stage)
			),
			0, count
		);
	}

	/// Returns a range allowing to do the traversal of subroutine uniforms
	/** This instance of Program must be kept alive during the whole
	 *  lifetime of the returned range, i.e. the returned range must not
	 *  be used after the Program goes out of scope and is destroyed.
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,0,ARB,shader_subroutine}
	 */
	ActiveSubroutineUniformRange ActiveSubroutineUniforms(ShaderType stage) const
	{
		// get the count of active subroutine uniforms
		GLint count = GetStageIntParam(
			GLenum(stage),
			GL_ACTIVE_SUBROUTINE_UNIFORMS
		);
		// get the maximum string length of the longest identifier
		GLint length = GetStageIntParam(
			GLenum(stage),
			GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH
		);

		return ActiveSubroutineUniformRange(
			aux::ProgramInterfaceContext(
				_name,
				length,
				GLenum(stage)
			),
			0, count
		);
	}
#endif

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
			aux::ProgramInterfaceContext(_name, length),
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
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TransformFeedbackVaryings,
			Program,
			nullptr,
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
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TransformFeedbackVaryings,
			Program,
			nullptr,
			_name
		));
	}

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
	typedef aux::BaseRange<
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
			aux::ProgramInterfaceContext(_name, length),
			0, count
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects
	/// Makes this program separable
	/**
	 *  @glvoereq{4,1,ARB,separate_shader_objects}
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
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			ProgramParameteri,
			Program,
			nullptr,
			_name
		));
	}
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
	void MakeRetrievable(bool para = true) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ProgramParameteri)(
			_name,
			GL_PROGRAM_BINARY_RETRIEVABLE_HINT,
			para ? GL_TRUE : GL_FALSE
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			ProgramParameteri,
			Program,
			nullptr,
			_name
		));
	}

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
			OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
				GetProgramBinary,
				Program,
				nullptr,
				_name
			));
		}
	}

	/// Allows to specify to program code in binary form
	/**
	 *  @see MakeRetrievable
	 *  @see GetBinary
	 *
	 *  @glvoereq{4,1,ARB,get_program_binary}
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
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			ProgramBinary,
			Program,
			nullptr,
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

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating  OpenGL shading language program functionality
/**
 *  @ingroup objects
 */
class Program
 : public ProgramOps
{ };
#else
typedef Object<ProgramOps> Program;
#endif

Program& operator << (Program& program, const Shader& shader)
{
	program.AttachShader(shader);
	return program;
}

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
	void _do_initialize(bool separable)
	{
#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects
		if(separable) MakeSeparable();
#endif
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

	template <typename Tuple>
	void _initialize_tuple(bool separable, const Tuple& tuple)
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

	template <typename ... Shaders>
	void _initialize(bool separable, const Shaders& ... shaders)
	{
		_attach(shaders...);
		_do_initialize(separable);
	}
#endif

public:
#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Build a optionally separable program using the specified @c shaders
	template <typename ... Shaders>
	QuickProgram(
		bool separable,
		const Shader& shader,
		const Shaders& ... shaders
	): Program()
	{
		_initialize(separable, shader, shaders...);
	}

	/// Build a program with @c description using the specified @c shaders
	template <typename ... Shaders>
	QuickProgram(
		ObjectDesc&& description,
		bool separable,
		const Shader& shader,
		const Shaders& ... shaders
	): Program(std::move(description))
	{
		_initialize(separable, shader, shaders...);
	}

	/// Build a optionally separable program using the specified @c shaders
	template <typename ... Shaders>
	QuickProgram(
		bool separable,
		const std::tuple<Shaders...>& shaders
	): Program()
	{
		_initialize_tuple(separable, shaders);
	}

	/// Build a program with @c description using the specified @c shaders
	template <typename ... Shaders>
	QuickProgram(
		ObjectDesc&& description,
		bool separable,
		const std::tuple<Shaders...>& shaders
	): Program(std::move(description))
	{
		_initialize_tuple(separable, shaders);
	}
#else
	template <typename StdTuple>
	QuickProgram(
		ObjectDesc&& description,
		bool separable,
		const StdTuple& shaders
	): Program(std::move(description))
	{
		_initialize_tuple(separable, shaders);
	}

	QuickProgram(bool separable, const Shader& s0)
	 : Program()
	{
		this->AttachShader(s0);
		_do_initialize(separable);
	}

	QuickProgram(bool separable, const Shader& s0, const Shader& s1)
	 : Program()
	{
		this->AttachShader(s0);
		this->AttachShader(s1);
		_do_initialize(separable);
	}

	QuickProgram(bool separable, const Shader& s0, const Shader& s1, const Shader& s2)
	 : Program()
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
	 : QuickProgram(false, _single_shader((Shaders*)0)...)
	{ }

	/// Create an instance of the hardwired program with a @c description
	HardwiredProgram(ObjectDesc&& description)
	 : QuickProgram(
		std::move(description),
		false,
		_single_shader((Shaders*)0)...
	)
	{ }

	/// Create an instance of the hardwired program, possibly @c separable
	HardwiredProgram(bool separable)
	 : QuickProgram(separable, _single_shader((Shaders*)0)...)
	{ }

	/// Create an instance of the hardwired program with a @c description
	HardwiredProgram(ObjectDesc&& description, bool separable)
	 : QuickProgram(
		std::move(description),
		separable,
		_single_shader((Shaders*)0)...
	)
	{ }
};

#endif // NO_VARIADIC_TEMPLATES

template <class StdTuple>
class HardwiredTupleProgram;

/// A Program that has its shaders statically hardcoded via a std::tuple
#if !OGLPLUS_NO_VARIADIC_TEMPLATES
template <class ... Shaders>
class HardwiredTupleProgram<std::tuple<Shaders...> >
 : protected std::tuple<Shaders...>
#else
template <class StdTuple>
class HardwiredTupleProgram
 : protected StdTuple
#endif
 , public QuickProgram
{
private:
#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	typedef std::tuple<Shaders...> StdTuple;
#endif
	const StdTuple& _base_shaders(void) const
	{
		return *((StdTuple*)this);
	}
public:
	/// Create an instance of the hardwired program, possibly @c separable
	HardwiredTupleProgram(bool separable)
	 : QuickProgram(ObjectDesc(), separable, _base_shaders())
	{ }

	/// Create an instance of the hardwired program with a @c description
	HardwiredTupleProgram(
		ObjectDesc&& description,
		bool separable
	): QuickProgram(std::move(description), separable, _base_shaders())
	{ }
};


} // namespace oglplus

#endif // include guard
