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

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/program.hpp>
#include <oglplus/limited_value.hpp>
#include <oglplus/auxiliary/shader_data.hpp>
#include <oglplus/string.hpp>


namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY
/// Type for the vertex attribute slot (implementation-dependent limited) number
class VertexAttribSlot
 : public LimitedCount
{
public:
	VertexAttribSlot(GLuint count);
};
#else
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	VertexAttribSlot,
	MAX_VERTEX_ATTRIBS
)
#endif

class VertexAttribOps
 : public FriendOf<ProgramOps>
{
protected:
	GLint _index;

	friend class FriendOf<VertexAttribOps>;

	VertexAttribOps(VertexAttribSlot i)
	 : _index(GLint(i))
	{ }

	VertexAttribOps(const ProgramOps& program, const GLchar* identifier)
	 : _index(
		::glGetAttribLocation(
			FriendOf<ProgramOps>::GetName(program),
			identifier
		)
	)
	{
		ThrowOnError(OGLPLUS_ERROR_INFO(GetAttribLocation));
		if(_index == GLint(-1))
		{
			Error::PropertyMap props;
			props["identifier"] = identifier;
			props["program"] = ObjectDescription(program);
			ThrowOnError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive vertex attrib",
				OGLPLUS_ERROR_INFO(GetAttribLocation),
				std::move(props)
			);
		}
	}
public:
	void BindLocation(
		const ProgramOps& program,
		const GLchar* identifier
	) const
	{
		::glBindAttribLocation(
			FriendOf<ProgramOps>::GetName(program),
			_index,
			identifier
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(BindAttribLocation));
	}

	void BindLocation(
		const ProgramOps& program,
		const String& identifier
	) const
	{
		::glBindAttribLocation(
			FriendOf<ProgramOps>::GetName(program),
			_index,
			identifier.c_str()
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(BindAttribLocation));
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
	ThrowOnError(OGLPLUS_ERROR_INFO(BindAttribLocation));
}

namespace aux {

class VertexAttribQueries
{
protected:
	static String _query_name(GLuint program, GLuint index)
	{
		GLsizei max_length = 255, real_length;
		GLchar buffer[256] = {GLchar(0)};
		GLint size;
		GLenum type;
		::glGetActiveAttrib(
			program,
			index,
			max_length,
			&real_length,
			&size,
			&type,
			buffer
		);
		return String(buffer, real_length);
	}
};

class VertexAttribSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(VertexAttrib, VertexAttrib)

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
};

} // namespace aux

/// Encapsulates vertex attribute functionality
/**
 *  @ingroup shader_variables
 */
class VertexAttrib
 : public VertexAttribOps
 , public aux::ShaderDataSetOps<
	aux::VertexAttribQueries,
	aux::VertexAttribSetters,
	aux::ActiveProgramCallOps,
	16
>
{
private:
public:
	/// References the vertex attribute array at @p index
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttrib(VertexAttribSlot i)
	 : VertexAttribOps(i)
	{ }

	/// References the vertex attribute @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttrib(const Program& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	/// References the vertex attribute @p identifier of the @p program
	VertexAttrib(const Program& program, const String& identifier)
	 : VertexAttribOps(program, identifier.c_str())
	{ }

	/// Set the value(s) of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	template <typename ... T>
	void Set(T ... v) const
	{
		this->_do_set(0, _index, v...);
	}

	/// Set the value(s) of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	template <size_t N, typename T>
	void Set(const T* v) const
	{
		this->_do_set<N>(0, _index, v);
	}
};

/// Encapsulates vertex attribute array functionality
/**
 *  @ingroup shader_variables
 */
class VertexAttribArray
 : public VertexAttribOps
{
public:
	/// References the vertex attribute array at @p index
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttribArray(VertexAttribSlot index)
	 : VertexAttribOps(index)
	{ }

	/// References the vertex attrib array @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttribArray(const Program& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	/// References the vertex attrib array @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttribArray(const Program& program, const String& identifier)
	 : VertexAttribOps(program, identifier.c_str())
	{ }

	/// Setup the properties of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttribPointer}
	 */
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
		ThrowOnError(OGLPLUS_ERROR_INFO(VertexAttribPointer));
	}

	/// Enables this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{EnableVertexAttribArray}
	 */
	void Enable(void) const
	{
		::glEnableVertexAttribArray(_index);
		AssertNoError(OGLPLUS_ERROR_INFO(EnableVertexAttribArray));
	}

	/// Disables this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{DisableVertexAttribArray}
	 */
	void Disable(void) const
	{
		::glDisableVertexAttribArray(_index);
		AssertNoError(OGLPLUS_ERROR_INFO(DisableVertexAttribArray));
	}
};

} // namespace oglplus

#endif // include guard
