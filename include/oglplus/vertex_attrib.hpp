/**
 *  @file oglplus/vertex_attrib.hpp
 *  @brief VertexAttrib wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_VERTEX_ATTRIB_1107121519_HPP
#define OGLPLUS_VERTEX_ATTRIB_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/program.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/limited_value.hpp>
#include <oglplus/auxiliary/shader_data.hpp>

#include <oglplus/matrix.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/string.hpp>


namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY
/// Type for the vertex attribute slot (implementation-dependent limited) number
/**
 *  @see VertexAttrib
 *
 *  @ingroup shader_variables
 */
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

/// Helper class that encapsulates vertex attribute functionality
/**
 *  @note Do not use this class directly, use VertexAttrib instead.
 *
 *  @see VertexAttrib
 *
 *  @ingroup shader_variables
 */
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
		OGLPLUS_GLFUNC(GetAttribLocation)(
			FriendOf<ProgramOps>::GetName(program),
			identifier
		)
	)
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetAttribLocation));
		if(OGLPLUS_IS_ERROR(_index == GLint(-1)))
		{
			Error::PropertyMap props;
			props["identifier"] = identifier;
			props["program"] = DescriptionOf(program);
			HandleError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive vertex attrib",
				OGLPLUS_ERROR_INFO(GetAttribLocation),
				std::move(props)
			);
		}
	}
public:
	/// Bind the vertex attribute location
	/**
	 *  @glsymbols
	 *  @glfunref{BindAttribLocation}
	 */
	void BindLocation(
		const ProgramOps& program,
		const GLchar* identifier
	) const
	{
		OGLPLUS_GLFUNC(BindAttribLocation)(
			FriendOf<ProgramOps>::GetName(program),
			_index,
			identifier
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(BindAttribLocation));
	}

	/// Bind the vertex attribute location
	/**
	 *  @glsymbols
	 *  @glfunref{BindAttribLocation}
	 */
	void BindLocation(
		const ProgramOps& program,
		const String& identifier
	) const
	{
		OGLPLUS_GLFUNC(BindAttribLocation)(
			FriendOf<ProgramOps>::GetName(program),
			_index,
			identifier.c_str()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(BindAttribLocation));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_3
	/// Set the vertex attrib divisor
	/**
	 *  @glverreq{3,3}
	 *  @glsymbols
	 *  @glfunref{VertexAttribDivisor}
	 */
	void Divisor(GLuint divisor) const
	{
		OGLPLUS_GLFUNC(VertexAttribDivisor)(
			_index,
			divisor
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(VertexAttribDivisor));
	}
#endif
};

// Things from to Program related to vertex attributes
void ProgramOps::BindLocation(
	const VertexAttribOps& vertex_attrib,
	const GLchar* identifier
) const
{
	OGLPLUS_GLFUNC(BindAttribLocation)(
		_name,
		FriendOf<VertexAttribOps>::GetIndex(vertex_attrib),
		identifier
	);
	OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(BindAttribLocation));
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
		OGLPLUS_GLFUNC(GetActiveAttrib)(
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
template <typename T>
class VertexAttrib
 : public VertexAttribOps
#if OGLPLUS_DOCUMENTATION_ONLY
 , public Unspecified
#else
 , public aux::ShaderDataSetOps<
	aux::VertexAttribQueries,
	aux::VertexAttribSetters,
	aux::ActiveProgramCallOps<T>,
	16
>
#endif
{
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

	/// Set the value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	void Set(T value) const
	{
		this->_do_set(0, _index, value);
	}

	/// Set the value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	inline void operator = (T value) const
	{
		Set(value);
	}
};

template <typename T, size_t N>
class VertexAttrib<Vector<T, N> >
 : public VertexAttribOps
 , public aux::ShaderDataSetOps<
	aux::VertexAttribQueries,
	aux::VertexAttribSetters,
	aux::ActiveProgramCallOps<T>,
	4
>
{
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

	/// Set the vector value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	void Set(const Vector<T, N>& value) const
	{
		this->_do_set<N>(0, _index, Data(value));
	}

	/// Set the vector value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	inline void operator = (const Vector<T, N>& value) const
	{
		Set(value);
	}
};

template <typename T, size_t Rows, size_t Cols>
class VertexAttrib<Matrix<T, Rows, Cols> >
 : public VertexAttribOps
 , public aux::ShaderDataSetOps<
	aux::VertexAttribQueries,
	aux::VertexAttribSetters,
	aux::ActiveProgramCallOps<T>,
	16
>
{
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

	/// Set the matrix value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	void Set(const Matrix<T, Rows, Cols>& value) const
	{
		this->_do_set<Rows*Cols>(0, _index, Data(value));
	}

	/// Set the matrix value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	inline void operator = (const Matrix<T, Rows, Cols>& value) const
	{
		Set(value);
	}
};

/// Encapsulates vertex attribute array functionality
/**
 *  @ingroup shader_variables
 */
class VertexAttribArray
 : public VertexAttribOps
{
private:
	// Functions for autodetection of values-per-vertex
	template <typename T>
	static GLint _get_values_per_vertex(T*)
	{
		return 1;
	}

	template <typename T, size_t N>
	static GLint _get_values_per_vertex(Vector<T, N>*)
	{
		return N;
	}

	template <typename T, size_t Rows, size_t Cols>
	static GLint _get_values_per_vertex(Matrix<T, Rows, Cols>*)
	{
		return Rows*Cols;
	}

	// Functions for autodetection of data type
	template <typename T>
	static DataType _get_data_type(T* p)
	{
		return ::oglplus::GetDataType(p);
	}

	template <typename T, size_t N>
	static DataType _get_data_type(Vector<T, N>*)
	{
		return ::oglplus::GetDataType((T*)nullptr);
	}

	template <typename T, size_t Rows, size_t Cols>
	static DataType _get_data_type(Matrix<T, Rows, Cols>*)
	{
		return ::oglplus::GetDataType((T*)nullptr);
	}
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
		OGLPLUS_GLFUNC(VertexAttribPointer)(
			_index,
			values_per_vertex,
			GLenum(data_type),
			normalized ? GL_TRUE : GL_FALSE,
			stride,
			pointer
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(VertexAttribPointer));
	}

	/// Setup the properties of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttribPointer}
	 */
	template <typename T>
	void Setup(
		bool normalized = false,
		GLsizei stride = 0,
		void* pointer = nullptr
	) const
	{
		OGLPLUS_GLFUNC(VertexAttribPointer)(
			_index,
			_get_values_per_vertex((T*)nullptr),
			GLenum(_get_data_type((T*)nullptr)),
			normalized ? GL_TRUE : GL_FALSE,
			stride,
			pointer
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(VertexAttribPointer));
	}


	/// Enables this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{EnableVertexAttribArray}
	 */
	void Enable(void) const
	{
		OGLPLUS_GLFUNC(EnableVertexAttribArray)(_index);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(EnableVertexAttribArray));
	}

	/// Disables this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{DisableVertexAttribArray}
	 */
	void Disable(void) const
	{
		OGLPLUS_GLFUNC(DisableVertexAttribArray)(_index);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DisableVertexAttribArray));
	}
};

} // namespace oglplus

#endif // include guard
