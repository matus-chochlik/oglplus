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
#include <oglplus/friend_of.hpp>
#include <oglplus/program.hpp>
#include <oglplus/auxiliary/varpara_fns.hpp>

#include <string>
#include <type_traits>

namespace oglplus {

class VertexAttribOps
 : public FriendOf<Program>
{
protected:
	GLuint _index;

	friend class FriendOf<VertexAttribOps>;

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
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	void BindLocation(
		const Program& program,
		const std::string& identifier
	) const
	{
		::glBindAttribLocation(
			FriendOf<Program>::GetName(program),
			_index,
			identifier.c_str()
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}
};

// Things from to Program related to vertex attributes
void ProgramOps::BindLocation(
	const VertexAttribOps& vertex_attrib,
	const GLchar* identifier
) const
{
	::glBindAttribLocation(
		_name,
		FriendOf<VertexAttribOps>::GetIndex(vertex_attrib),
		identifier
	);
	ThrowOnError(OGLPLUS_ERROR_INFO());
}

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

	typedef std::false_type _set_done;
	typedef std::true_type  _set_cont;

	template <size_t N>
	static std::integral_constant<bool,  (N > 4)> _set_mode(void)
	{
		return std::integral_constant<bool, (N > 4)>();
	}

	template <size_t N, typename T>
	static void _do_set_v(_set_cont, GLuint index, const T* v)
	{
		::std::get<3>(_fns_v(v))(index, v);
		AssertNoError(OGLPLUS_ERROR_INFO());
		_do_set_v<N - 4, T>(_set_mode<N - 4>(), index+1, v+4);
	}

	template <size_t N, typename T>
	static void _do_set_v(_set_done, GLuint index, const T* v)
	{
		::std::get<N-1>(_fns_v(v))(index, v);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	template <typename S, typename ... T>
	static void _do_set_t(
		_set_cont,
		GLuint index,
		 S v0, S v1, S v2, S v3,
		T ... v
	)
	{
		std::get<3>(_fns_t(&v0))(index, v0, v1, v2, v3);
		AssertNoError(OGLPLUS_ERROR_INFO());
		_do_set_t(_set_mode<sizeof...(T)>(), index+1, v...);
	}

	template <typename ... T>
	static void _do_set_t(
		_set_done,
		GLuint index,
		T ... v
	)
	{
		std::get<sizeof...(T) - 1>(_fns_t(&v...))(index, v...);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}
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
			(sizeof...(T) > 0) && (sizeof...(T) <= 16),
			"Set requires 1 to 16 arguments"
		);
		_do_set_t(
			_set_mode<sizeof...(T)>(),
			_index,
			v...
		);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	template <size_t N, typename T>
	void Set(const T* v) const
	{
		static_assert(
			(N > 0) && (N <= 16),
			"The number of elements must be between 1 and 16"
		);
		_do_set_v<N, T>(_set_mode<N>(), _index, v);
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
