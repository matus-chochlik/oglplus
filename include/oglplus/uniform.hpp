/**
 *  @file oglplus/uniform.hpp
 *  @brief Uniform wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_UNIFORM_1107121519_HPP
#define OGLPLUS_UNIFORM_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/program.hpp>
#include <oglplus/matrix.hpp>
#include <oglplus/string.hpp>
#include <oglplus/auxiliary/shader_data.hpp>
#include <oglplus/auxiliary/tp_mat_vec.hpp>
#include <oglplus/auxiliary/uniform_init.hpp>

#include <vector>
#include <cassert>

namespace oglplus {
namespace aux {

class OptionalUniformInitOps
{
protected:
	typedef Nothing ParamType;

	OptionalUniformInitOps(Nothing)
	{ }

	GLint _init_location(GLuint program, const GLchar* identifier) const
	{
		return OGLPLUS_GLFUNC(GetUniformLocation)(
			program,
			identifier
		);
	}
};

class UniformInitOps
{
protected:
	typedef Nothing ParamType;

	UniformInitOps(Nothing)
	{ }

	GLint _do_init_location(GLuint program, const GLchar* identifier) const
	{
		return OGLPLUS_GLFUNC(GetUniformLocation)(
			program,
			identifier
		);
	}

	GLint _init_location(GLuint program, const GLchar* identifier) const
	{
		GLint location = _do_init_location(program, identifier);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetUniformLocation));
		if(OGLPLUS_IS_ERROR(location == GLint(-1)))
		{
			Error::PropertyMapInit props;
			Error::AddPropertyValue(
				props,
				"identifier",
				identifier
			);
			Error::AddPropertyValue(
				props,
				"program",
				aux::ObjectDescRegistry<ProgramOps>::
						_get_desc(program)
			);
			HandleError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive uniform",
				OGLPLUS_ERROR_INFO(GetUniformLocation),
				std::move(props)
			);
		}
		return location;
	}
};

typedef EagerUniformInitTpl<UniformInitOps>
	EagerUniformInit;

typedef LazyUniformInitTpl<UniformInitOps>
	LazyUniformInit;

typedef EagerUniformInitTpl<OptionalUniformInitOps>
	OptionalUniformInit;

class DirectUniformInit
 : public FriendOf<ProgramOps>
{
private:
	GLuint _program;
	GLint _location;
protected:
	DirectUniformInit(const ProgramOps& program, Nothing, GLint location)
	 : _program(FriendOf<ProgramOps>::GetName(program))
	 , _location(location)
	{ }

	DirectUniformInit(GLuint program, Nothing, GLint location)
	 : _program(program)
	 , _location(location)
	{ }

	GLuint _get_program(void) const
	{
		return _program;
	}

	GLint _get_location(void) const
	{
		return _location;
	}
};

} // namespace aux

// Helper class for Uniform
template <class Initializer>
class UniformOps
 : public Initializer
{
protected:
	template <class StrOrInt>
	UniformOps(const ProgramOps& program, StrOrInt&& name_or_idx)
	 : Initializer(program, Nothing(), std::forward<StrOrInt>(name_or_idx))
	{ }

	UniformOps(GLuint program, GLint location)
	 : Initializer(program, Nothing(), location)
	{ }
public:
};

namespace aux {

class UniformQueries
{
protected:
	static String _query_name(GLuint program, GLuint location)
	{
#if GL_VERSION_3_1 || GL_ARB_uniform_buffer_object
		GLsizei max_length = 255, real_length;
		GLchar buffer[256] = {GLchar(0)};
		OGLPLUS_GLFUNC(GetActiveUniformName)(
			program,
			location,
			max_length,
			&real_length,
			buffer
		);
		return String(buffer, real_length);
#else
		return String();
#endif
	}
};

class UniformSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(Uniform, Uniform)

	OGLPLUS_AUX_VARPARA_FNS(Uniform, ui, t, GLuint)
	OGLPLUS_AUX_VARPARA_FNS(Uniform, i, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS(Uniform, f, t, GLfloat)
#if GL_VERSION_3_3 || GL_ARB_gpu_shader_fp64
	OGLPLUS_AUX_VARPARA_FNS(Uniform, d, t, GLdouble)
#endif

	OGLPLUS_AUX_VARPARA_FNS(Uniform, iv, v, GLint)
	OGLPLUS_AUX_VARPARA_FNS(Uniform, fv, v, GLfloat)
#if GL_VERSION_3_3 || GL_ARB_gpu_shader_fp64
	OGLPLUS_AUX_VARPARA_FNS(Uniform, dv, v, GLdouble)
#endif
};

class UniformMatrixSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(UniformMatrix, Uniform)

	OGLPLUS_AUX_VARPARA_MAT_FNS(UniformMatrix, fv, v, GLfloat)
#if GL_VERSION_3_3 || GL_ARB_gpu_shader_fp64
	OGLPLUS_AUX_VARPARA_MAT_FNS(UniformMatrix, dv, v, GLdouble)
#endif
};


class ProgramUniformSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(ProgramUniform, ProgramUniform)

#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, ui, t, GLuint)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, i, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, f, t, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, d, t, GLdouble)

	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, iv, v, GLint)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, dv, v, GLdouble)
#elif GL_EXT_direct_state_access
	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, ui, EXT, t, GLuint)
	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, i, EXT, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, f, EXT, t, GLfloat)

	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, iv, EXT, v, GLint)
	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, fv, EXT, v, GLfloat)
#endif
};

class ProgramUniformMatrixSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(ProgramUniformMatrix, ProgramUniform)

#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects
	OGLPLUS_AUX_VARPARA_MAT_FNS(ProgramUniformMatrix, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_MAT_FNS(ProgramUniformMatrix, dv, v, GLdouble)
#elif GL_EXT_direct_state_access
	OGLPLUS_AUX_VARPARA_MAT_FNS_EXT(ProgramUniformMatrix,fv,EXT, v, GLfloat)
#endif
};


} // namespace aux

/// Base template for Uniform and ProgramUniform
/**
 *  @note Do not use this class directly use Uniform or ProgramUniform
 *  instead.
 */
template <typename T, class IndexInit, class SpecOpsWrapper>
class UniformBase
 : public UniformOps<IndexInit>
 , public SpecOpsWrapper::type
{
protected:
	template <class StrOrInt>
	UniformBase(const Program& program, StrOrInt&& name_or_idx)
	 : UniformOps<IndexInit>(program, std::forward<StrOrInt>(name_or_idx))
	{ }

	UniformBase(GLuint program, GLint location)
	 : UniformOps<IndexInit>(program, location)
	{ }
public:

	/// Set the value of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(T value)
	{
		this->_do_set(
			this->_get_program(),
			this->_get_location(),
			value
		);
	}

	/// Set the multiple value(s) of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(GLsizei count, const T* v)
	{
		this->template _do_set_many<1>(
			this->_get_program(),
			this->_get_location(),
			count,
			v
		);
	}

	/// Set the value(s) of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(const std::vector<T>& v)
	{
		this->template _do_set_many<1>(
			this->_get_program(),
			this->_get_location(),
			v.size(),
			v.data()
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Set the multiple value(s) of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename ... P>
	void Set(T v, P ... p);
#endif

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <typename ... P>
	void Set(T v, P ... p)
	{
		const T tmp[] = {v, p...};
		this->template _do_set_many<1>(
			this->_get_program(),
			this->_get_location(),
			sizeof(tmp)/sizeof(tmp[0]),
			tmp
		);
	}
#else
	void Set(T v0, T v1)
	{
		const T tmp[] = {v0, v1};
		this->template _do_set_many<1>(
			this->_get_program(),
			this->_get_location(),
			2,
			tmp
		);
	}

	void Set(T v0, T v1, T v2)
	{
		const T tmp[] = {v0, v1, v2};
		this->template _do_set_many<1>(
			this->_get_program(),
			this->_get_location(),
			3,
			tmp
		);
	}

	void Set(T v0, T v1, T v2, T v3)
	{
		const T tmp[] = {v0, v1, v2, v3};
		this->template _do_set_many<1>(
			this->_get_program(),
			this->_get_location(),
			4,
			tmp
		);
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Set the vector value of the uniform variable
	/** This function can be used to set uniform variables
	 *  with 2, 3 or 4 -component vector types with the
	 *  same underlying type as is the template parameter
	 *  of the Uniform or ProgramUniform class. For example
	 *  Uniform<GLfloat>::SetVector() can be used to set the
	 *  values of GLSL uniforms with vec2, vec3 or vec4 type,
	 *  Uniform<GLint>::SetVector() can be used to set the
	 *  values of GLSL uniforms with ivec2, ivec3 or ivec4 type, etc.
	 *
	 *  @note Consider using Uniform<Vector<T,N>>::Set() instead
	 *  of Uniform<T>::SetVector<N>().
	 *
	 *  @note This function is @em not intended for setting
	 *  arrays of uniform variables.
	 *
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename ... P>
	void SetVector(T v, P ... p);
#endif

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <typename ... P>
	void SetVector(T v, P ... p)
	{
		this->_do_set(
			this->_get_program(),
			this->_get_location(),
			v, p...
		);
	}
#else
	void SetVector(T v0, T v1)
	{
		const T tmp[] = {v0, v1};
		this->template _do_set<2>(
			this->_get_program(),
			this->_get_location(),
			tmp
		);
	}

	void SetVector(T v0, T v1, T v2)
	{
		const T tmp[] = {v0, v1, v2};
		this->template _do_set<3>(
			this->_get_program(),
			this->_get_location(),
			tmp
		);
	}

	void SetVector(T v0, T v1, T v2, T v3)
	{
		const T tmp[] = {v0, v1, v2, v3};
		this->template _do_set<4>(
			this->_get_program(),
			this->_get_location(),
			tmp
		);
	}
#endif

	/// Set the vector value of the uniform variable
	/** This function can be used to set uniform variables
	 *  with 2, 3 or 4 -component vector types with the
	 *  same underlying type as is the template parameter
	 *  of the Uniform or ProgramUniform class.
	 *
	 *  For example
	 *  Uniform<GLfloat>::SetVector() can be used to set the
	 *  values of GLSL uniforms with vec2, vec3 or vec4 type,
	 *  Uniform<GLint>::SetVector() can be used to set the
	 *  values of GLSL uniforms with ivec2, ivec3 or ivec4 type, etc.
	 *
	 *  @note Consider using Uniform<Vector<T,N>>::Set() instead
	 *  of Uniform<T>::SetVector<N>().
	 *
	 *  @note This function is @em not intended for setting
	 *  arrays of uniform variables.
	 *
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <std::size_t Cols>
	void SetVector(const T* v)
	{
		this->template _do_set<Cols>(
			this->_get_program(),
			this->_get_location(),
			v
		);
	}

	/// Set multiple scalar or vector values of an uniform variable
	/** This function can be used to set multiple values of an
	 *  uniform array variable with scalar or vector type with
	 *  2, 3 or 4 -components with the same underlying type as is
	 *  the template parameter of the Uniform or ProgramUniform class.
	 *
	 *  For example
	 *  Uniform<GLfloat>::SetVector() can be used to set the
	 *  values of GLSL uniforms with vec2, vec3 or vec4 type,
	 *  Uniform<GLint>::SetVector() can be used to set the
	 *  values of GLSL uniforms with ivec2, ivec3 or ivec4 type, etc.
	 *
	 *  @note Consider using Uniform<T>::Set()
	 *  or Uniform<Vector<T,N>>::Set() instead of SetVectors.
	 *
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <std::size_t Cols>
	void SetVectors(GLsizei count, const T* v)
	{
		this->template _do_set_many<Cols>(
			this->_get_program(),
			this->_get_location(),
			count,
			v
		);
	}

	/// Set multiple scalar or vector values of an uniform variable
	/** This function can be used to set multiple values of an
	 *  uniform array variable with scalar or vector type with
	 *  2, 3 or 4 -components with the same underlying type as is
	 *  the template parameter of the Uniform or ProgramUniform class.
	 *
	 *  For example
	 *  Uniform<GLfloat>::SetVector() can be used to set the
	 *  values of GLSL uniforms with vec2, vec3 or vec4 type,
	 *  Uniform<GLint>::SetVector() can be used to set the
	 *  values of GLSL uniforms with ivec2, ivec3 or ivec4 type, etc.
	 *
	 *  @note Consider using Uniform<T>::Set()
	 *  or Uniform<Vector<T,N>>::Set() instead of SetVectors.
	 *
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <std::size_t Cols>
	void SetVectors(const std::vector<T>& v)
	{
		this->template _do_set_many<Cols>(
			this->_get_program(),
			this->_get_location(),
			v.size(),
			v.data()
		);
	}

	/// Set the matrix components of the uniform variable
	/**
	 *  @note Consider using @c Uniform<Matrix<T,M,N>> instead
	 *
	 *  @glsymbols
	 *  @glfunref{UniformMatrix}
	 *  @glfunref{ProgramUniformMatrix}
	 */
	template <std::size_t Cols, std::size_t Rows>
	void SetMatrix(std::size_t count, const T* v)
	{
		this->template _do_set_mat<Cols, Rows>(
			this->_get_program(),
			this->_get_location(),
			count,
			false,
			v
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Set the matrix components of the uniform variable
	/**
	 *  @note Consider using @c Uniform<Matrix<T,M,N>> instead
	 *
	 *  @glsymbols
	 *  @glfunref{UniformMatrix}
	 *  @glfunref{ProgramUniformMatrix}
	 */
	template <std::size_t Cols, typename ... P>
	void SetMatrix(T v, P ... p)
	{
		this->template _do_set_mat_p<Cols>(
			this->_get_program(),
			this->_get_location(),
			false,
			v, p...
		);
	}
#endif
};

/// Specialization of uniform operations for Vector types
template <typename T, std::size_t N, class IndexInit, class SpecOpsWrapper>
class UniformBase<Vector<T, N>, IndexInit, SpecOpsWrapper>
 : public UniformOps<IndexInit>
 , public SpecOpsWrapper::type
{
protected:
	template <class StrOrInt>
	UniformBase(const Program& program, StrOrInt&& name_or_idx)
	 : UniformOps<IndexInit>(program, std::forward<StrOrInt>(name_or_idx))
	{ }

	UniformBase(GLuint program, GLint location)
	 : UniformOps<IndexInit>(program, location)
	{ }
public:
	/// Set the vector value of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(const Vector<T, N>& vector)
	{
		this->template _do_set<N>(
			this->_get_program(),
			this->_get_location(),
			Data(vector)
		);
	}

	/// Set a third-party vector type value to the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(const ThirdPartyVector<T, N>& vector)
	{
		this->template _do_set<N>(
			this->_get_program(),
			this->_get_location(),
			vector.Data()
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Set the vector components of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename ... P>
	inline void Set(T v, P ... p)
	{
		this->Set(Vector<T, N>(v, p...));
	}
#else
	inline void Set(T v0, T v1)
	{
		this->Set(Vector<T, 2>(v0, v1));
	}

	inline void Set(T v0, T v1, T v2)
	{
		this->Set(Vector<T, 3>(v0, v1, v2));
	}

	inline void Set(T v0, T v1, T v2, T v3)
	{
		this->Set(Vector<T, 4>(v0, v1, v2, v3));
	}
#endif

	/// Set the vector value(s) of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename Alloc>
	void Set(const std::vector<Vector<T, N>, Alloc>& range)
	{
		// TODO: this could be optimized in situations
		// when the alignment is right and could work
		// without the temporary copy
		std::vector<T> temp;
		temp.reserve(range.size()*N);
		for(auto i=range.begin(), e=range.end(); i!=e; ++i)
			temp.insert(temp.end(), Data(*i), Data(*i)+N);
		this->template _do_set_many<N>(
			this->_get_program(),
			this->_get_location(),
			temp.size(),
			temp.data()
		);
	}

	/// Set the third-party vector type value to the uniform
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename Alloc>
	void Set(const std::vector<ThirdPartyVector<T, N>, Alloc>& range)
	{
		std::vector<T> temp;
		temp.reserve(range.size()*N);
		for(auto i=range.begin(), e=range.end(); i!=e; ++i)
			temp.insert(temp.end(), i->Data(), i->Data()+N);
		this->template _do_set_many<N>(
			this->_get_program(),
			this->_get_location(),
			temp.size(),
			temp.data()
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Set the vector value(s) of the shader variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <
		template <typename ... Params> class StdRange,
		typename ... P
	>
	void Set(const StdRange<Vector<T, N>, P...>& range)
	{
		// TODO: this could be optimized in situations
		// when the alignment is right and could work
		// without the temporary copy
		std::vector<T> temp;
		temp.reserve(range.size()*N);
		for(auto i=range.begin(), e=range.end(); i!=e; ++i)
			temp.insert(temp.end(), Data(*i), Data(*i)+N);
		this->template _do_set_many<N>(
			this->_get_program(),
			this->_get_location(),
			temp.size(),
			temp.data()
		);
	}
#endif
};

/// Specialization of uniform operations for Matrix types
template <
	typename T,
	std::size_t Rows,
	std::size_t Cols,
	class IndexInit,
	class SpecOpsWrapper
>
class UniformBase<Matrix<T, Rows, Cols>, IndexInit, SpecOpsWrapper>
 : public UniformOps<IndexInit>
 , public SpecOpsWrapper::type
{
protected:
	template <class StrOrInt>
	UniformBase(const Program& program, StrOrInt&& name_or_idx)
	 : UniformOps<IndexInit>(program, std::forward<StrOrInt>(name_or_idx))
	{ }

	UniformBase(GLuint program, GLint location)
	 : UniformOps<IndexInit>(program, location)
	{ }
public:
	/// Set the matrix components of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{UniformMatrix}
	 *  @glfunref{ProgramUniformMatrix}
	 */
	void Set(const Matrix<T, Rows, Cols>& matrix)
	{
		this->template _do_set_mat<Cols, Rows>(
			this->_get_program(),
			this->_get_location(),
			1,
			true,
			Data(matrix)
		);
	}

	/// Set a third-party matrix type value to the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{UniformMatrix}
	 *  @glfunref{ProgramUniformMatrix}
	 */
	void Set(const ThirdPartyMatrix<T, Rows, Cols>& matrix)
	{
		this->template _do_set_mat<Cols, Rows>(
			this->_get_program(),
			this->_get_location(),
			1,
			matrix.IsRowMajor(),
			matrix.Data()
		);
	}

	/// Set the matrix components of the uniform variable
	/**
	 *
	 *  @glsymbols
	 *  @glfunref{UniformMatrix}
	 *  @glfunref{ProgramUniformMatrix}
	 */
	template <typename Alloc>
	void Set(const std::vector<Matrix<T, Rows, Cols>, Alloc>& range)
	{
		// TODO: this could be optimized in situations
		// when the alignment is right and could work
		// without the temporary copy
		std::vector<T> temp;
		temp.reserve(range.size()*Rows*Cols);
		for(auto i=range.begin(), e=range.end(); i!=e; ++i)
			temp.insert(temp.end(), Data(*i), Data(*i)+Rows*Cols);
		this->template _do_set_mat<Cols, Rows>(
			this->_get_program(),
			this->_get_location(),
			range.size(),
			true,
			temp.data()
		);
	}

	/// Set a third-party matrix type values to the uniform variable
	/**
	 *
	 *  @glsymbols
	 *  @glfunref{UniformMatrix}
	 *  @glfunref{ProgramUniformMatrix}
	 */
	template <typename Alloc>
	void Set(const std::vector<ThirdPartyMatrix<T,Rows,Cols>, Alloc>& range)
	{
		std::vector<T> temp;
		temp.reserve(range.size()*Rows*Cols);
		auto i=range.begin(), e=range.end();
		if(i != e)
		{
			bool is_row_major = i->IsRowMajor();
			while(i != e)
			{
				temp.insert(
					temp.end(),
					i->Data(),
					i->Data()+i->Size()
				);
				++i;
			}
			this->template _do_set_mat<Cols, Rows>(
				this->_get_program(),
				this->_get_location(),
				range.size(),
				is_row_major,
				temp.data()
			);
		}
	}

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Set the matrix components of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename ... P>
	inline void Set(T v, P ... p)
	{
		this->Set(Matrix<T, Rows, Cols>(v, p...));
	}
#endif
};

namespace aux {

template <typename T>
class UniformAllSetOps
 : public aux::ShaderDataSetOps<
	aux::UniformQueries,
	aux::UniformSetters,
	aux::ActiveProgramCallOps<T>,
	4
>, public aux::ShaderMatrixSetOps<
	aux::UniformQueries,
	aux::UniformMatrixSetters,
	aux::ActiveProgramCallOps<T>
>
{ };

template <typename T>
struct UniformSetOps
{
	typedef UniformAllSetOps<T> type;
};

template <typename T, std::size_t N>
struct UniformSetOps<Vector<T, N> >
{
	typedef aux::ShaderDataSetOps<
		aux::UniformQueries,
		aux::UniformSetters,
		aux::ActiveProgramCallOps<T>,
		4
	> type;
};

template <typename T, std::size_t Rows, std::size_t Cols>
struct UniformSetOps<Matrix<T, Rows, Cols> >
{
	typedef aux::ShaderMatrixSetOps<
		aux::UniformQueries,
		aux::UniformMatrixSetters,
		aux::ActiveProgramCallOps<T>
	> type;
};

template <typename T>
class ProgramUniformAllSetOps
 : public aux::ShaderDataSetOps<
	aux::UniformQueries,
	aux::ProgramUniformSetters,
	aux::SpecificProgramCallOps<T>,
	4
>, public aux::ShaderMatrixSetOps<
	aux::UniformQueries,
	aux::ProgramUniformMatrixSetters,
	aux::SpecificProgramCallOps<T>
>
{ };

template <typename T>
struct ProgramUniformSetOps
{
	typedef ProgramUniformAllSetOps<T> type;
};

template <typename T, std::size_t N>
struct ProgramUniformSetOps<Vector<T, N> >
{
	typedef aux::ShaderDataSetOps<
		aux::UniformQueries,
		aux::ProgramUniformSetters,
		aux::SpecificProgramCallOps<T>,
		4
	> type;
};

template <typename T, std::size_t Rows, std::size_t Cols>
struct ProgramUniformSetOps<Matrix<T, Rows, Cols> >
{
	typedef aux::ShaderMatrixSetOps<
		aux::UniformQueries,
		aux::ProgramUniformMatrixSetters,
		aux::SpecificProgramCallOps<T>
	> type;
};

} // namespace aux

/// Template for Uniform, ProgramUniform, LazyUniform and LazyProgramUniform
/** @note Do not use directly, use Uniform, ProgramUniform, LazyUniform,
 *  LazyProgramUniform, OptionalUniform, OptionalProgramUniform,
 *  DirectUniform, DirectProgramUniform, etc. instead.
 *
 *  @ingroup shader_variables
 */
template <typename T, class IndexInit, class SetOps>
class UniformTpl
 : public UniformBase<T, IndexInit, SetOps>
{
private:
	typedef UniformBase<T, IndexInit, SetOps> _base;

	Program::ActiveVariableInfo _find_uniform_avi(
		GLuint prog_name,
		GLint location
	)
	{
		Managed<Program> program(prog_name);
		auto aur = program.ActiveUniforms();
		while(!aur.Empty())
		{
			GLint tmp_loc = OGLPLUS_GLFUNC(GetUniformLocation)(
				prog_name,
				aur.Front().Name().c_str()
			);
			OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetUniformLocation));
			if(tmp_loc == location) break;
			aur.Next();
		}
		assert(!aur.Empty());
		return aur.Front();
	}
public:
	UniformTpl(GLuint program, GLint location)
	 : _base(program, location)
	{ }

	/// Reference a uniform identified by @p identifier in the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformLocation}
	 */
	UniformTpl(const Program& program, const GLchar* identifier)
	 : _base(program, identifier)
	{ }

	/// Reference a uniform identified by @p identifier in the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformLocation}
	 */
	UniformTpl(const Program& program, const String& identifier)
	 : _base(program, identifier)
	{ }

	/// Reference a uniform identified by @p identifier in the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformLocation}
	 */
	UniformTpl(const Program& program, String&& identifier)
	 : _base(program, std::move(identifier))
	{ }

	/// Reference a uniform identified by @p location in the @p program
	/**
	 *  @glsymbols
	 */
	UniformTpl(const Program& program, GLint location)
	 : _base(program, location)
	{ }

	UniformTpl<T, aux::DirectUniformInit, SetOps>
	operator[](GLint offset)
	{
		return UniformTpl<T, aux::DirectUniformInit, SetOps>(
			this->_get_program(),
			this->_get_location()+offset
		);
	}

	/// Set the value of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{UniformMatrix}
	 */
	void operator = (const T& value)
	{
		this->Set(value);
	}

	/// Tests if this Uniform is initialized and can be used
	/**
	 *  For Uniform and ProgramUniform this function always
	 *  returns true as these cannot be in uninitialized state.
	 *  For LazyUniform and LazyProgramUniform this function
	 *  returns true if the uniform is active and can be referenced
	 *  and used for subsequent value-setting operations.
	 *  If this function returns false then trying to set a value
	 *  or any other operation on the uniform besides destruction
	 *  throws an exception.
	 */
	bool IsActive(void)
	{
		return this->_try_init_location();
	}

	/// Equivalent to IsActive()
	/**
	 *  @see IsActive
	 */
	operator bool (void)
	{
		return IsActive();
	}

	/// Equivalent to !IsActive()
	/**
	 *  @see IsActive
	 */
	bool operator ! (void)
	{
		return !IsActive();
	}

	/// Returns a Program::ActiveVariableInfo for this uniform
	/** Note that this is a rather inefficient operation.
	 */
	Program::ActiveVariableInfo Info(void)
	{
		return _find_uniform_avi(
			this->_get_program(),
			this->_get_location()
		);
	}

};

/// Class encapsulating Uniform shader variable functionality
/**
 *  The difference between Uniform and LazyUniform is, that Uniform
 *  tries to get the location (binding) of the GLSL uniform variable
 *  in a Program during construction and LazyUniform postpones this
 *  initialization until the value is actually needed at the cost
 *  of having to internally store the identifer in a String.
 *
 *  @see ProgramUniform
 *  @see LazyUniform
 *  @see DirectUniform
 *
 *  @ingroup shader_variables
 */
template <typename T>
class Uniform
#if OGLPLUS_DOCUMENTATION_ONLY
 : public UniformTpl<T, Unspecified, Unspecified>
#else
 : public UniformTpl<T, aux::EagerUniformInit, aux::UniformSetOps<T>>
#endif
{
protected:
	typedef UniformTpl<
		T,
		aux::EagerUniformInit,
		aux::UniformSetOps<T>
	> _base;
public:
#if OGLPLUS_DOCUMENTATION_ONLY
	/// Construction from a const reference to @p program and an identifier
	Uniform(const Program& program, String identifier);
#else
	template <typename _String>
	Uniform(const Program& program, _String&& identifier)
	 : _base(program, std::forward<_String>(identifier))
	{ }
#endif

	/// Set the value of the uniform variable
	inline void operator = (const T& value)
	{
		this->Set(value);
	}
};

/// Class encapsulating Uniform shader variable functionality
/**
 *  The difference between Uniform and LazyUniform is, that Uniform
 *  tries to get the location (binding) of the GLSL uniform variable
 *  in a Program during construction and LazyUniform postpones this
 *  initialization until the value is actually needed at the cost
 *  of having to internally store the identifer in a String.
 *
 *  @see ProgramUniform
 *  @see Uniform
 *
 *  @ingroup shader_variables
 */
template <typename T>
class LazyUniform
#if OGLPLUS_DOCUMENTATION_ONLY
 : public UniformTpl<T, Unspecified, Unspecified>
#else
 : public UniformTpl<T, aux::LazyUniformInit, aux::UniformSetOps<T>>
#endif
{
protected:
	typedef UniformTpl<
		T,
		aux::LazyUniformInit,
		aux::UniformSetOps<T>
	> _base;
public:
#if OGLPLUS_DOCUMENTATION_ONLY
	/// Construction from a const reference to @p program and an identifier
	LazyUniform(const Program& program, String identifier);
#else
	template <typename _String>
	LazyUniform(const Program& program, _String&& identifier)
	 : _base(program, std::forward<_String>(identifier))
	{ }
#endif

	/// Set the value of the uniform variable
	inline void operator = (const T& value)
	{
		this->Set(value);
	}
};

/// Class encapsulating Uniform shader variable functionality
/**
 *  The difference between Uniform and OptionalUniform is, that Uniform
 *  construction fails if the referenced uniform variable in the GLSL
 *  program is inactive. OptionalUniform always constructs, but may
 *  fail when used later.
 *
 *  @see ProgramUniform
 *  @see Uniform
 *
 *  @ingroup shader_variables
 */
template <typename T>
class OptionalUniform
#if OGLPLUS_DOCUMENTATION_ONLY
 : public UniformTpl<T, Unspecified, Unspecified>
#else
 : public UniformTpl<T, aux::OptionalUniformInit, aux::UniformSetOps<T>>
#endif
{
protected:
	typedef UniformTpl<
		T,
		aux::OptionalUniformInit,
		aux::UniformSetOps<T>
	> _base;
public:
#if OGLPLUS_DOCUMENTATION_ONLY
	/// Construction from a const reference to @p program and an identifier
	OptionalUniform(const Program& program, String identifier);
#else
	template <typename _String>
	OptionalUniform(const Program& program, _String&& identifier)
	 : _base(program, std::forward<_String>(identifier))
	{ }
#endif

	/// Set the value of the uniform variable
	inline void operator = (const T& value)
	{
		this->Set(value);
	}
};


/// Class encapsulating Uniform shader variable functionality
/**
 *  The difference between Uniform and DirectUniform is, that Uniform
 *  is initialized by the name of the uniform variable in the GLSL
 *  program. Direct uniform is initialized by the location (binding)
 *  of the variable in the program.
 *
 *  @see Uniform
 *  @see ProgramUniform
 *  @see LazyUniform
 *
 *  @ingroup shader_variables
 */
template <typename T>
class DirectUniform
#if OGLPLUS_DOCUMENTATION_ONLY
 : public UniformTpl<T, Unspecified, Unspecified>
#else
 : public UniformTpl<T, aux::DirectUniformInit, aux::UniformSetOps<T>>
#endif
{
protected:
	typedef UniformTpl<
		T,
		aux::DirectUniformInit,
		aux::UniformSetOps<T>
	> _base;
public:
	/// Construction from a const reference to @p program and a @p location
	DirectUniform(const Program& program, GLint location)
	 : _base(program, location)
	{ }

	DirectUniform(const _base& other)
	 : _base(other)
	{ }

	/// Set the value of the uniform variable
	inline void operator = (const T& value)
	{
		this->Set(value);
	}
};

/// Class that can be used to set sampler uniform variable values
/**
 *  @ingroup shader_variables
 */
typedef Uniform<GLint> UniformSampler;

/// Class that can be used to set sampler uniform variable values
/**
 *  @ingroup shader_variables
 */
typedef LazyUniform<GLint> LazyUniformSampler;

/// Finds and sets the value of the variable identified by @p identifier in program
/** This convenience function finds the uniform variable with the name
 *  @p identifier in the specified @p program and sets its @p value.
 *
 *  @note This function is not very efficient. If you need to set the value
 *  of this uniform variable repeatedly, consider declaring a Uniform variable
 *  and use it to set the @p value to avoid repetitive search for the reference
 *  to the shading program variable by its name.
 *
 *  @see Uniform
 *  @see LazyUniform
 *  @see ProgramUniform
 *  @see LazyProgramUniform
 *
 *  @ingroup shader_variables
 *
 *  @glsymbols
 *  @glfunref{Uniform}
 *  @glfunref{UniformMatrix}
 */
template <typename T>
inline void SetUniform(
	const Program& program,
	const GLchar* identifier,
	const T& value
)
{
	Uniform<T>(program, identifier).Set(value);
}

#if OGLPLUS_DOCUMENTATION_ONLY || \
	GL_VERSION_4_1 || \
	GL_ARB_separate_shader_objects || \
	GL_EXT_direct_state_access

/// Class encapsulating ProgramUniform shader variable functionality
/**
 *  The difference between ProgramUniform and LazyProgramUniform is, that
 *  ProgramUniform tries to get the location (binding) of the GLSL uniform
 *  variable in a Program during construction and LazyProgramUniform postpones
 *  this initialization until the value is actually needed at the cost
 *  of having to internally store the identifer in a String.
 *
 *  @see Uniform
 *  @see LazyProgramUniform
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{4,1,ARB,separate_shader_objects}
 */
template <typename T>
class ProgramUniform
#if OGLPLUS_DOCUMENTATION_ONLY
 : public UniformTpl<T, Unspecified, Unspecified>
#else
 : public UniformTpl<T, aux::EagerUniformInit, aux::ProgramUniformSetOps<T>>
#endif
{
private:
	typedef UniformTpl<
		T,
		aux::EagerUniformInit,
		aux::ProgramUniformSetOps<T>>
	_base;
public:
#if OGLPLUS_DOCUMENTATION_ONLY
	/// Construction from a const reference to @p program and an identifier
	ProgramUniform(const Program& program, String identifier);
#else
	template <typename _String>
	ProgramUniform(const Program& program, _String&& identifier)
	 : _base(program, std::forward<_String>(identifier))
	{ }
#endif

	/// Set the value of the uniform variable
	inline void operator = (const T& value)
	{
		this->Set(value);
	}
};

/// Class encapsulating ProgramUniform shader variable functionality
/**
 *  The difference between ProgramUniform and LazyProgramUniform is, that
 *  ProgramUniform tries to get the location (binding) of the GLSL uniform
 *  variable in a Program during construction and LazyProgramUniform postpones
 *  this initialization until the value is actually needed at the cost
 *  of having to internally store the identifer in a String.
 *
 *  @see Uniform
 *  @see LazyProgramUniform
 *
 *  @ingroup shader_variables
 */
template <typename T>
class LazyProgramUniform
#if OGLPLUS_DOCUMENTATION_ONLY
 : public UniformTpl<T, Unspecified, Unspecified>
#else
 : public UniformTpl<T, aux::LazyUniformInit, aux::ProgramUniformSetOps<T>>
#endif
{
private:
	typedef UniformTpl<
		T,
		aux::LazyUniformInit,
		aux::ProgramUniformSetOps<T>>
	_base;
public:
#if OGLPLUS_DOCUMENTATION_ONLY
	/// Construction from a const reference to @p program and an identifier
	LazyProgramUniform(const Program& program, String identifier);
#else
	template <typename _String>
	LazyProgramUniform(const Program& program, _String&& identifier)
	 : _base(program, std::forward<_String>(identifier))
	{ }
#endif

	/// Set the value of the uniform variable
	inline void operator = (const T& value)
	{
		this->Set(value);
	}
};

/// Class encapsulating ProgramUniform shader variable functionality
/**
 *  The difference between ProgramUniform and OptionalProgramUniform is,
 *  that ProgramUniform construction fails if the referenced uniform variable
 *  in the GLSL program is inactive. OptionalProgramUniform always constructs,
 *  but may fail when used later.
 *
 *  @see ProgramUniform
 *  @see Uniform
 *
 *  @ingroup shader_variables
 */
template <typename T>
class OptionalProgramUniform
#if OGLPLUS_DOCUMENTATION_ONLY
 : public UniformTpl<T, Unspecified, Unspecified>
#else
 : public UniformTpl<T, aux::OptionalUniformInit, aux::ProgramUniformSetOps<T>>
#endif
{
protected:
	typedef UniformTpl<
		T,
		aux::OptionalUniformInit,
		aux::ProgramUniformSetOps<T>
	> _base;
public:
#if OGLPLUS_DOCUMENTATION_ONLY
	/// Construction from a const reference to @p program and an identifier
	OptionalProgramUniform(const Program& program, String identifier);
#else
	template <typename _String>
	OptionalProgramUniform(const Program& program, _String&& identifier)
	 : _base(program, std::forward<_String>(identifier))
	{ }
#endif

	/// Set the value of the uniform variable
	inline void operator = (const T& value)
	{
		this->Set(value);
	}
};

/// Class encapsulating ProgramUniform shader variable functionality
/**
 *  The difference between ProgramUniform and DirectProgramUniform is,
 *  that Uniform is initialized by the name of the uniform variable in the GLSL
 *  program. Direct uniform is initialized by the location (binding)
 *  of the variable in the program.
 *
 *  @see Uniform
 *  @see ProgramUniform
 *  @see LazyProgramUniform
 *
 *  @ingroup shader_variables
 */
template <typename T>
class DirectProgramUniform
#if OGLPLUS_DOCUMENTATION_ONLY
 : public UniformTpl<T, Unspecified, Unspecified>
#else
 : public UniformTpl<T, aux::DirectUniformInit, aux::ProgramUniformSetOps<T>>
#endif
{
protected:
	typedef UniformTpl<
		T,
		aux::DirectUniformInit,
		aux::ProgramUniformSetOps<T>
	> _base;
public:
	/// Construction from a const reference to @p program and a @p location
	DirectProgramUniform(const Program& program, GLint location)
	 : _base(program, location)
	{ }

	DirectProgramUniform(const _base& other)
	 : _base(other)
	{ }

	/// Set the value of the uniform variable
	inline void operator = (const T& value)
	{
		this->Set(value);
	}
};

/// Class that can be used to set sampler uniform variable values
/**
 *  @ingroup shader_variables
 */
typedef ProgramUniform<GLint> ProgramUniformSampler;

/// Class that can be used to set sampler uniform variable values
/**
 *  @ingroup shader_variables
 */
typedef LazyProgramUniform<GLint> LazyProgramUniformSampler;

/// Finds and sets the value of the variable identified by @p identifier in program
/** This convenience function finds the uniform variable with the name
 *  @p identifier in the specified @p program and sets its @p value.
 *
 *  @note This function is not very efficient. If you need to set the value
 *  of this uniform variable repeatedly, consider declaring a ProgramUniform variable
 *  and use it to set the @p value to avoid repetitive search for the reference
 *  to the shading program variable by its name.
 *
 *  @see Uniform
 *  @see LazyUniform
 *  @see ProgramUniform
 *  @see LazyProgramUniform
 *
 *  @ingroup shader_variables
 *
 *  @glsymbols
 *  @glfunref{ProgramUniform}
 *  @glfunref{ProgramUniformMatrix}
 */
template <typename T>
inline void SetProgramUniform(
	const Program& program,
	const GLchar* identifier,
	const T& value
)
{
	ProgramUniform<T>(program, identifier).Set(value);
}

#endif

} // namespace oglplus

#endif // include guard
