/**
 *  @file oglplus/uniform.hpp
 *  @brief Uniform wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
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
		::glGetUniformLocation(
			FriendOf<ProgramOps>::GetName(program),
			identifier
		)
	)
	{
		ThrowOnError(OGLPLUS_ERROR_INFO(GetUniformLocation));
		if(_index == GLint(-1))
		{
			ThrowOnError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive uniform",
				OGLPLUS_ERROR_INFO(GetUniformLocation),
				Error::PropertyMap({
					{"identifier", identifier},
					{"program", ObjectDescription(program)}
				})
			);
		}
	}
public:
};

namespace aux {

class UniformSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(Uniform)

	OGLPLUS_AUX_VARPARA_FNS(Uniform, ui, t, GLuint)
	OGLPLUS_AUX_VARPARA_FNS(Uniform, i, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS(Uniform, f, t, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(Uniform, d, t, GLdouble)

	OGLPLUS_AUX_VARPARA_FNS(Uniform, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(Uniform, dv, v, GLdouble)
};

class UniformMatrixSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(UniformMatrix)

	OGLPLUS_AUX_VARPARA_MAT_FNS(UniformMatrix, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_MAT_FNS(UniformMatrix, dv, v, GLdouble)
};

class ProgramUniformSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(ProgramUniform)

	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, ui, t, GLuint)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, i, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, f, t, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, d, t, GLdouble)

	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, dv, v, GLdouble)
};

class ProgramUniformMatrixSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(ProgramUniformMatrix)

	OGLPLUS_AUX_VARPARA_MAT_FNS(ProgramUniformMatrix, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_MAT_FNS(ProgramUniformMatrix, dv, v, GLdouble)
};

} // namespace aux

/// Base template for Uniform and ProgramUniform
/**
 *  @note Do not use this class directly use Uniform or ProgramUniform
 *  instead.
 */
template <class SetOps, class MatrixSetOps>
class UniformBase
 : public UniformOps
 , public SetOps
 , public MatrixSetOps
{
public:
	/// Reference a uniform identified by @p identifier in the @p program
	UniformBase(const Program& program, const GLchar* identifier)
	 : UniformOps(program, identifier)
	{ }

	/// Reference a uniform identified by @p identifier in the @p program
	UniformBase(const Program& program, const String& identifier)
	 : UniformOps(program, identifier.c_str())
	{ }

	/// Set the value(s) of the uniform
	template <typename ... T>
	void Set(T ... v) const
	{
		this->_do_set(
			this->_program,
			this->_index,
			v...
		);
	}

	/// Set the value(s) of the uniform
	template <size_t Cols, typename T>
	void Set(const T* v) const
	{
		this->template _do_set<Cols>(
			this->_program,
			this->_index,
			v
		);
	}

	/// Set the value(s) of the uniform
	template <size_t Cols, typename T>
	void Set(GLsizei count, const T* v) const
	{
		this->template _do_set_many<Cols>(
			this->_program,
			this->_index,
			count,
			v
		);
	}

	/// Set the value(s) of the uniform
	template <size_t Cols, typename T>
	void Set(const std::vector<T>& v) const
	{
		this->template _do_set_many<Cols>(
			this->_program,
			this->_index,
			v.size(),
			v.data()
		);
	}

	/// Set the value(s) of the uniform
	template <typename T, size_t N>
	void Set(const Vector<T, N>& vector) const
	{
		this->template _do_set<N>(
			this->_program,
			this->_index,
			Data(vector)
		);
	}

	/// Set the value(s) of the shader variable
	template <typename T, size_t N>
	void Set(const std::vector<Vector<T, N> >& v) const
	{
		// TODO: this could be optimized in situations
		// when the alignment is right and could work
		// without the temporary copy
		std::vector<T> t;
		t.reserve(v.size()*N);
		for(auto i=v.begin(), e=v.end(); i!=e; ++i)
			t.insert(t.end(), Data(*i), Data(*i)+N);
		this->template _do_set_many<N>(
			this->_program,
			this->_index,
			t.size(),
			t.data()
		);
	}

	/// Set the matrix components of the uniform
	template <size_t Cols, size_t Rows, typename T>
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

	/// Set the matrix components of the uniform
	template <typename T, size_t Rows, size_t Cols>
	void SetMatrix(const Matrix<T, Rows, Cols>& matrix) const
	{
		this->template _do_set_mat<Cols, Rows>(
			this->_program,
			this->_index,
			1,
			true,
			Data(matrix)
		);
	}

	/// Set the matrix components of the uniform
	template <typename T, size_t Rows, size_t Cols>
	void SetMatrix(const std::vector<Matrix<T, Rows, Cols> >& m) const
	{
		// TODO: this could be optimized in situations
		// when the alignment is right and could work
		// without the temporary copy
		std::vector<T> t;
		t.reserve(m.size() * Rows * Cols);
		for(auto i=m.begin(), e=m.end(); i!=e; ++i)
			t.insert(t.end(), Data(*i), Data(*i)+Rows*Cols);
		this->template _do_set_mat<Cols, Rows>(
			this->_program,
			this->_index,
			m.size(),
			true,
			t.data()
		);
	}

	/// Set the matrix components of the uniform
	template <size_t Cols, typename ... T>
	void SetMatrix(T ... v) const
	{
		this->template _do_set_mat_p<Cols>(
			this->_program,
			this->_index,
			false,
			v...
		);
	}
};

/// Class encapsulating Uniform shader variable functionality
/**
 *  @ingroup shader_variables
 */
typedef UniformBase<
	aux::ShaderDataSetOps<
		aux::UniformSetters,
		aux::ActiveProgramCallOps,
		4
	>,
	aux::ShaderMatrixSetOps<
		aux::UniformMatrixSetters,
		aux::ActiveProgramCallOps
	>
> Uniform;

/// Class encapsulating ProgramUniform shader variable functionality
/**
 *  @ingroup shader_variables
 */
typedef UniformBase<
	aux::ShaderDataSetOps<
		aux::ProgramUniformSetters,
		aux::SpecificProgramCallOps,
		4
	>,
	aux::ShaderMatrixSetOps<
		aux::ProgramUniformMatrixSetters,
		aux::SpecificProgramCallOps
	>
> ProgramUniform;

} // namespace oglplus

#endif // include guard
