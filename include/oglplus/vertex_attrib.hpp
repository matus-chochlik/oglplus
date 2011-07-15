/**
 *  @file oglplus/vertex_attrib.hpp
 *  @brief VertexAttrib wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_VERTEX_ATTRIB_1107121519_HPP
#define OGLPLUS_VERTEX_ATTRIB_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/program.hpp>
#include <oglplus/auxiliary/varpara_fns.hpp>

#include <tuple>

namespace oglplus {

class VertexAttribOps
 : public FriendOf<Program>
{
protected:
	GLuint _index;

	VertexAttribOps(GLuint i)
	 : _index(i)
	{ }

	VertexAttribOps(const Program& program, const GLchar* identifier)
	 : _index(
		::glGetAttribLocation(
			FriendOf<Program>::GetName(program),
			identifier
		)
	)
	{
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}
public:
	void BindLocation(const Program& program, const GLchar* identifier) const
	{
		::glBindAttribLocation(
			FriendOf<Program>::GetName(program),
			_index,
			identifier
		);
	}
};

class VertexAttrib
 : public VertexAttribOps
{
private:

	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, f, t, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, d, t, GLdouble)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, s, t, GLshort)

	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, i, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, ui, t, GLuint)

	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, dv, v, GLdouble)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, sv, v, GLshort)

	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, i, v, GLint)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, ui, v, GLuint)
public:
	VertexAttrib(GLuint i)
	 : VertexAttribOps(i)
	{ }

	VertexAttrib(const Program& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	template <typename ... T>
	void Set(T ... v) const
	{
		static_assert(
			(sizeof...(T) > 0) && (sizeof...(T)<=4),
			"Set requires 1, 2, 3 or 4 arguments"
		);
		std::get<sizeof...(T) - 1>(_fns_t(&v...))(_index, v...);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	template <size_t N, typename T>
	void Set(const T* v) const
	{
		static_assert(
			(N > 0) && (N <= 4),
			"Set requires 1, 2, 3 or 4 elements"
		);
		std::get<N - 1>(_fns_v(v))(_index, v);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}
};

class VertexAttribArray
 : public VertexAttribOps
{
public:
	VertexAttribArray(GLuint i)
	 : VertexAttribOps(i)
	{ }

	VertexAttribArray(const Program& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	void Setup(
		GLint values_per_vertex,
		DataType data_type,
		bool normalized = false,
		GLsizei stride = 0,
		void* pointer = nullptr
	) const
	{
		::glVertexAttribPointer(
			_index,
			values_per_vertex,
			GLenum(data_type),
			normalized ? GL_TRUE : GL_FALSE,
			stride,
			pointer
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	void Enable(void) const
	{
		::glEnableVertexAttribArray(_index);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	void Disable(void) const
	{
		::glDisableVertexAttribArray(_index);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}
};

} // namespace oglplus

#endif // include guard
