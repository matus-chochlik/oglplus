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
#include <oglplus/limited_value.hpp>
#include <oglplus/auxiliary/shader_data.hpp>

#include <string>

namespace oglplus {

#ifdef OGLPLUS_DOCUMENTATION_ONLY
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
 : public FriendOf<Program>
{
protected:
	GLint _index;

	friend class FriendOf<VertexAttribOps>;

	VertexAttribOps(VertexAttribSlot i)
	 : _index(GLint(i))
	{ }

	VertexAttribOps(const Program& program, const GLchar* identifier)
	 : _index(
		::glGetAttribLocation(
			FriendOf<Program>::GetName(program),
			identifier
		)
	)
	{
		ThrowOnError(OGLPLUS_ERROR_INFO(GetAttribLocation));
		if(_index == GLint(-1))
		{
			ThrowOnError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive vertex attrib",
				OGLPLUS_ERROR_INFO(GetAttribLocation),
				Error::PropertyMap({
					{"identifier", identifier},
					{"program", program.Description()}
				})
			);
		}
	}
public:
	void BindLocation(const Program& program, const GLchar* identifier) const
	{
		::glBindAttribLocation(
			FriendOf<Program>::GetName(program),
			_index,
			identifier
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(BindAttribLocation));
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
class VertexAttribSetters
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(VertexAttrib)

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
class VertexAttrib
 : public VertexAttribOps
 , public aux::ShaderDataSetOps<aux::VertexAttribSetters, 16>
{
private:
public:
	/// References the vertex attribute array at @p index
	VertexAttrib(VertexAttribSlot i)
	 : VertexAttribOps(i)
	{ }

	/// References the vertex attribute @p identifier of the @p program
	VertexAttrib(const Program& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	/// Set the value(s) of the vertex attribute
	template <typename ... T>
	void Set(T ... v) const
	{
		this->_do_set(_index, v...);
	}

	/// Set the value(s) of the vertex attribute
	template <size_t N, typename T>
	void Set(const T* v) const
	{
		this->_do_set<N>(_index, v);
	}
};

/// Encapsulates vertex attribute array functionality
class VertexAttribArray
 : public VertexAttribOps
{
public:
	/// References the vertex attribute array at @p index
	VertexAttribArray(VertexAttribSlot index)
	 : VertexAttribOps(index)
	{ }

	/// References the vertex attrib array @p identifier of the @p program
	VertexAttribArray(const Program& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	/// Setup the properties of this vertex attribute array
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
	void Enable(void) const
	{
		::glEnableVertexAttribArray(_index);
		AssertNoError(OGLPLUS_ERROR_INFO(EnableVertexAttribArray));
	}

	/// Disables this vertex attribute array
	void Disable(void) const
	{
		::glDisableVertexAttribArray(_index);
		AssertNoError(OGLPLUS_ERROR_INFO(DisableVertexAttribArray));
	}
};

} // namespace oglplus

#endif // include guard
