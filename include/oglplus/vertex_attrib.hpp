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

class VertexAttrib
 : public FriendOf<Program>
{
private:
	GLuint _index;

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
	 : _index(i)
	{ }

	VertexAttrib(const Program& program, const GLchar* name)
	 : _index(
		::glGetAttribLocation(
			FriendOf<Program>::GetName(program),
			name
		)
	)
	{
		ThrowOnError();
	}

	template <typename ... T>
	void Set(T ... v) const
	{
		static_assert(
			(sizeof...(T) > 0) && (sizeof...(T)<=4),
			"Set requires 1, 2, 3 or 4 arguments"
		);
		std::get<sizeof...(T) - 1>(_fns_t(&v...))(_index, v...);
		AssertNoError();
	}

	template <size_t N, typename T>
	void Set(const T* v) const
	{
		static_assert(
			(N > 0) && (N <= 4),
			"Set requires 1, 2, 3 or 4 elements"
		);
		std::get<N - 1>(_fns_v(v))(_index, v);
		AssertNoError();
	}
};

class VertexAttribArray
 : public FriendOf<Program>
{
private:
	GLuint _index;
public:
	VertexAttribArray(GLuint i)
	 : _index(i)
	{ }

	VertexAttribArray(const Program& program, const GLchar* name)
	 : _index(
		::glGetAttribLocation(
			FriendOf<Program>::GetName(program),
			name
		)
	)
	{
		ThrowOnError();
	}

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
		ThrowOnError();
	}

	void Enable(void) const
	{
		::glEnableVertexAttribArray(_index);
		AssertNoError();
	}

	void Disable(void) const
	{
		::glDisableVertexAttribArray(_index);
		AssertNoError();
	}
};

} // namespace oglplus

#endif // include guard
