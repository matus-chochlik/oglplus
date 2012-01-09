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
#include <oglplus/auxiliary/shader_data.hpp>
#include <oglplus/string.hpp>

#include <vector>

namespace oglplus {

// Helper class for Uniform
class UniformOps
 : public FriendOf<ProgramOps>
{
protected:
	GLuint _program;
	GLint _index;

	friend class FriendOf<UniformOps>;

	UniformOps(const ProgramOps& program, const GLchar* identifier)
	 : _program(FriendOf<ProgramOps>::GetName(program))
	 , _index(
		OGLPLUS_GLFUNC(GetUniformLocation)(
			FriendOf<ProgramOps>::GetName(program),
			identifier
		)
	)
	{
		HandleIfError(OGLPLUS_ERROR_INFO(GetUniformLocation));
		if(_index == GLint(-1))
		{
			Error::PropertyMap props;
			props["identifier"] = identifier;
			props["program"] = ObjectDescription(program);
			HandleError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive uniform",
				OGLPLUS_ERROR_INFO(GetUniformLocation),
				std::move(props)
			);
		}
	}
public:
};

namespace aux {

class UniformQueries
{
protected:
	static String _query_name(GLuint program, GLuint index)
	{
#if GL_VERSION_3_1 || GL_ARB_uniform_buffer_object
		GLsizei max_length = 255, real_length;
		GLchar buffer[256] = {GLchar(0)};
		OGLPLUS_GLFUNC(GetActiveUniformName)(
			program,
			index,
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

#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects

class ProgramUniformSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(ProgramUniform, ProgramUniform)

	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, ui, t, GLuint)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, i, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, f, t, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, d, t, GLdouble)

	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, iv, v, GLint)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, dv, v, GLdouble)
};

class ProgramUniformMatrixSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(ProgramUniformMatrix, ProgramUniform)

	OGLPLUS_AUX_VARPARA_MAT_FNS(ProgramUniformMatrix, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_MAT_FNS(ProgramUniformMatrix, dv, v, GLdouble)
};

#endif // separate shader objects

} // namespace aux

/// Base template for Uniform and ProgramUniform
/**
 *  @note Do not use this class directly use Uniform or ProgramUniform
 *  instead.
 */
template <typename T, class SpecOpsWrapper>
class UniformBase
 : public UniformOps
 , public SpecOpsWrapper::type
{
protected:
	UniformBase(const Program& program, const GLchar* identifier)
	 : UniformOps(program, identifier)
	{ }

	UniformBase(const Program& program, const String& identifier)
	 : UniformOps(program, identifier.c_str())
	{ }
public:

	/// Set the value of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(T value) const
	{
		this->_do_set(
			this->_program,
			this->_index,
			value
		);
	}

	/// Set the multiple value(s) of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(GLsizei count, const T* v) const
	{
		this->template _do_set_many<1>(
			this->_program,
			this->_index,
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
	void Set(const std::vector<T>& v) const
	{
		this->template _do_set_many<1>(
			this->_program,
			this->_index,
			v.size(),
			v.data()
		);
	}

	/// Set the multiple value(s) of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename ... P>
	void Set(T v, P ... p) const
	{
		const T tmp[] = {v, p...};
		this->template _do_set_many<1>(
			this->_program,
			this->_index,
			sizeof(tmp)/sizeof(tmp[0]),
			tmp
		);
	}

	/// Set the vector value of the uniform variable
	/**
	 *  @note Consider using @c Uniform<Vector<T,N>> instead
	 *
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename ... P>
	void SetVector(T v, P ... p) const
	{
		this->_do_set(
			this->_program,
			this->_index,
			v, p...
		);
	}

	/// Set the vector value of the uniform variable
	/**
	 *  @note Consider using @c Uniform<Vector<T,N>> instead
	 *
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <size_t Cols>
	void SetVector(const T* v) const
	{
		this->template _do_set<Cols>(
			this->_program,
			this->_index,
			v
		);
	}

	/// Set the vector value(s) of the uniform variable
	/**
	 *  @note Consider using @c Uniform<Vector<T,N>> instead
	 *
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <size_t Cols>
	void SetVectors(GLsizei count, const T* v) const
	{
		this->template _do_set_many<Cols>(
			this->_program,
			this->_index,
			count,
			v
		);
	}

	/// Set the vector value(s) of the uniform variable
	/**
	 *  @note Consider using @c Uniform<Vector<T,N>> instead
	 *
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <size_t Cols>
	void SetVectors(const std::vector<T>& v) const
	{
		this->template _do_set_many<Cols>(
			this->_program,
			this->_index,
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
	template <size_t Cols, size_t Rows>
	void SetMatrix(size_t count, const T* v) const
	{
		this->template _do_set_mat<Cols, Rows>(
			this->_program,
			this->_index,
			count,
			false,
			v
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
	template <size_t Cols, typename ... P>
	void SetMatrix(T v, P ... p) const
	{
		this->template _do_set_mat_p<Cols>(
			this->_program,
			this->_index,
			false,
			v, p...
		);
	}
};

/// Specialization of uniform operations for Vector types
template <typename T, size_t N, class SpecOpsWrapper>
class UniformBase<Vector<T, N>, SpecOpsWrapper>
 : public UniformOps
 , public SpecOpsWrapper::type
{
protected:
	UniformBase(const Program& program, const GLchar* identifier)
	 : UniformOps(program, identifier)
	{ }

	UniformBase(const Program& program, const String& identifier)
	 : UniformOps(program, identifier.c_str())
	{ }
public:
	/// Set the vector value of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(const Vector<T, N>& vector) const
	{
		this->template _do_set<N>(
			this->_program,
			this->_index,
			Data(vector)
		);
	}

	/// Set the vector components of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename ... P>
	inline void Set(T v, P ... p) const
	{
		this->Set(Vector<T, N>(v, p...));
	}

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
	void Set(const StdRange<Vector<T, N>, P...>& range) const
	{
		// TODO: this could be optimized in situations
		// when the alignment is right and could work
		// without the temporary copy
		std::vector<T> temp;
		temp.reserve(range.size()*N);
		for(auto i=range.begin(), e=range.end(); i!=e; ++i)
			temp.insert(temp.end(), Data(*i), Data(*i)+N);
		this->template _do_set_many<N>(
			this->_program,
			this->_index,
			temp.size(),
			temp.data()
		);
	}
};

/// Specialization of uniform operations for Matrix types
template <typename T, size_t Rows, size_t Cols, class SpecOpsWrapper>
class UniformBase<Matrix<T, Rows, Cols>, SpecOpsWrapper>
 : public UniformOps
 , public SpecOpsWrapper::type
{
protected:
	UniformBase(const Program& program, const GLchar* identifier)
	 : UniformOps(program, identifier)
	{ }

	UniformBase(const Program& program, const String& identifier)
	 : UniformOps(program, identifier.c_str())
	{ }
public:
	/// Set the matrix components of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{UniformMatrix}
	 *  @glfunref{ProgramUniformMatrix}
	 */
	void Set(const Matrix<T, Rows, Cols>& matrix) const
	{
		this->template _do_set_mat<Cols, Rows>(
			this->_program,
			this->_index,
			1,
			true,
			Data(matrix)
		);
	}

	/// Set the matrix components of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	template <typename ... P>
	inline void Set(T v, P ... p) const
	{
		this->Set(Matrix<T, Rows, Cols>(v, p...));
	}

	/// Set the matrix components of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{UniformMatrix}
	 *  @glfunref{ProgramUniformMatrix}
	 */
	template <
		template <typename ... Params> class StdRange,
		typename ... P
	>
	void Set(const StdRange<Matrix<T, Rows, Cols>, P...>& range) const
	{
		// TODO: this could be optimized in situations
		// when the alignment is right and could work
		// without the temporary copy
		std::vector<T> temp;
		temp.reserve(range.size()*Rows*Cols);
		for(auto i=range.begin(), e=range.end(); i!=e; ++i)
			temp.insert(temp.end(), Data(*i), Data(*i)+Rows*Cols);
		this->template _do_set_mat<Cols, Rows>(
			this->_program,
			this->_index,
			range.size(),
			temp.size(),
			temp.data()
		);
	}
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
struct UniformOps
{
	typedef UniformAllSetOps<T> type;
};

template <typename T, size_t N>
struct UniformOps<Vector<T, N> >
{
	typedef aux::ShaderDataSetOps<
		aux::UniformQueries,
		aux::UniformSetters,
		aux::ActiveProgramCallOps<T>,
		4
	> type;
};

template <typename T, size_t Rows, size_t Cols>
struct UniformOps<Matrix<T, Rows, Cols> >
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
struct ProgramUniformOps
{
	typedef ProgramUniformAllSetOps<T> type;
};

template <typename T, size_t N>
struct ProgramUniformOps<Vector<T, N> >
{
	typedef aux::ShaderDataSetOps<
		aux::UniformQueries,
		aux::ProgramUniformSetters,
		aux::SpecificProgramCallOps<T>,
		4
	> type;
};

template <typename T, size_t Rows, size_t Cols>
struct ProgramUniformOps<Matrix<T, Rows, Cols> >
{
	typedef aux::ShaderMatrixSetOps<
		aux::UniformQueries,
		aux::ProgramUniformMatrixSetters,
		aux::SpecificProgramCallOps<T>
	> type;
};

} // namespace aux

/// Class encapsulating Uniform shader variable functionality
/**
 *  @ingroup shader_variables
 */
template <typename T>
class Uniform
 : public UniformBase<T, aux::UniformOps<T>>
{
private:
	typedef UniformBase<T, aux::UniformOps<T>> _base;
public:
	/// Reference a uniform identified by @p identifier in the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformLocation}
	 */
	Uniform(const Program& program, const GLchar* identifier)
	 : _base(program, identifier)
	{ }

	/// Reference a uniform identified by @p identifier in the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformLocation}
	 */
	Uniform(const Program& program, const String& identifier)
	 : _base(program, identifier.c_str())
	{ }

	/// Set the value of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{UniformMatrix}
	 */
	inline void operator = (const T& value) const
	{
		this->Set(value);
	}
};

/// Class that can be used to set sampler uniform variable values
/**
 *  @ingroup shader_variables
 */
typedef Uniform<GLint> UniformSampler;

/// Finds and sets the value of the variable identified by @p identifier in program
/** This convenience function finds the uniform variable with the name
 *  @p identifier in the specified @p program and sets its @p value.
 *
 *  @note This function is not very efficient, if you need to set the value
 *  of this uniform variable repeatedly, consider declaring a Uniform variable
 *  and use it to set the @p value to avoid repetitive search for the reference
 *  to the shading program variable by its name.
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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects

/// Class encapsulating ProgramUniform shader variable functionality
/**
 *  @ingroup shader_variables
 */
template <typename T>
class ProgramUniform
 : public UniformBase<T, aux::ProgramUniformOps<T>>
{
private:
	typedef UniformBase<T, aux::ProgramUniformOps<T>> _base;
public:
	/// Reference a uniform identified by @p identifier in the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformLocation}
	 */
	ProgramUniform(const Program& program, const GLchar* identifier)
	 : _base(program, identifier)
	{ }

	/// Reference a uniform identified by @p identifier in the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformLocation}
	 */
	ProgramUniform(const Program& program, const String& identifier)
	 : _base(program, identifier.c_str())
	{ }

	/// Set the value of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{ProgramUniform}
	 *  @glfunref{ProgramUniformMatrix}
	 */
	inline void operator = (const T& value) const
	{
		this->Set(value);
	}
};

/// Class that can be used to set sampler uniform variable values
/**
 *  @ingroup shader_variables
 */
typedef ProgramUniform<GLint> ProgramUniformSampler;

/// Finds and sets the value of the variable identified by @p identifier in program
/** This convenience function finds the uniform variable with the name
 *  @p identifier in the specified @p program and sets its @p value.
 *
 *  @note This function is not very efficient, if you need to set the value
 *  of this uniform variable repeatedly, consider declaring a ProgramUniform variable
 *  and use it to set the @p value to avoid repetitive search for the reference
 *  to the shading program variable by its name.
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

#endif // separate shader objects

} // namespace oglplus

#endif // include guard
