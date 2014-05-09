/**
 *  @file oglplus/vertex_attrib.hpp
 *  @brief VertexAttrib wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_VERTEX_ATTRIB_1107121519_HPP
#define OGLPLUS_VERTEX_ATTRIB_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/vertex_attrib_slot.hpp>
#include <oglplus/string/ref.hpp>
#include <oglplus/error/prog_var.hpp>
#include <oglplus/object/name.hpp>
#include <oglplus/object/sequence.hpp>
#include <oglplus/prog_var/location.hpp>
#include <oglplus/prog_var/varpara_fns.hpp>
#include <oglplus/prog_var/set_ops.hpp>

#include <type_traits>

namespace oglplus {

template <>
class ProgVarLocOps<tag::VertexAttrib>
{
private:
	static const char* _inactive_attr_message(void);
public:
	static void BindLocation(
		ProgramName program,
		VertexAttribSlot location,
		StrCRef identifier
	)
	{
		OGLPLUS_GLFUNC(BindAttribLocation)(
			GetGLName(program),
			GLuint(location),
			identifier.c_str()
		);
		OGLPLUS_CHECK(
			BindAttribLocation,
			ProgVarError,
			Program(program).
			Identifier(identifier).
			Index(GLuint(location))
		);
	}

	static GLint GetLocation(
		ProgramName program,
		StrCRef identifier
	)
	{
		GLint result = OGLPLUS_GLFUNC(GetAttribLocation)(
			GetGLName(program),
			identifier.c_str()
		);
		OGLPLUS_CHECK(
			GetAttribLocation,
			ProgVarError,
			Program(program).
			Identifier(identifier)
		);
		return result;
	}
	/// Bind the vertex attribute location
	/**
	 *  @see GetLocation
	 *  @see QueryLocation
	 *
	 *  @glsymbols
	 *  @glfunref{BindAttribLocation}
	 */

	/// Queries the vertex attribute location, returns false on failure
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	static bool QueryActiveLocation(
		ProgramName program,
		StrCRef identifier,
		VertexAttribSlot& location
	)
	{
		GLint result = GetLocation(program, identifier);
		if(result < 0) return false;
		location = VertexAttribSlot(result);
		return true;
	}

	/// Finds the vertex attribute location, throws on failure
	/** Finds the location of the input vertex attribute specified
	 *  by @p identifier in a @p program. Throws if no such attribute
	 *  exists or if it is not active. For a non-throwing version
	 *  see QueryActiveLocation().
	 *
	 *  @see GetCommonLocation
	 *  @see QueryActiveLocation
	 *  @see BindLocation
	 *
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	static VertexAttribSlot GetActiveLocation(
		ProgramName program,
		StrCRef identifier
	)
	{
		GLint result = GetLocation(program, identifier);
		OGLPLUS_HANDLE_ERROR_IF(
			result < 0,
			GL_INVALID_OPERATION,
			_inactive_attr_message(),
			ProgVarError,
			Program(program).
			Identifier(identifier)
		);
		return VertexAttribSlot(result);
	}

	/// Allows to query the vertex attribute @p location in multiple @p programs
	/** This function returns a temporary object that allows to query
	 *  the @p location of the specified @p identifier in several programs.
	 *  The returned object has two functions called @c In and @c And
	 *  which are equivalent and take a Program as the argument. Both
	 *  these functions return in turn a new instance of the temporary
	 *  which allows to check in another program, and so on.
	 *  The temporary is also convertible to @c bool indicating whether
	 *  a common location was found in all programs in the chain.
	 *
	 *  @code
	 *  VertexArray vao;
	 *  Buffer buf;
	 *  Program prog1, prog2, prog3, prog4;
	 *  // build the programs, load data into the buffer, ...
	 *  vao.Bind();
	 *  buffer.Bind(Buffer::Target::Array);
	 *  VertexAttribSlot location;
	 *  if(VertexAttrib::QueryCommonLocation(
	 *      MakeGroup(prog1, prog2, prog3),
	 *      "Position",
	 *      location
	 *  ))
	 *  {
	 *      VertexAttribArray attr(location);
	 *      attr.Setup(n_per_vertex, DataType::Float);
	 *      attr.Enable();
	 *  }
	 *  else
	 *  {
	 *      // handle the error or bind the locations manually
	 *  }
	 *  @endcode
	 *
	 *  @note Never store the resulting object in a named variable
	 *  nor use it after the call to this overload of QueryCommonLocation
	 *  has finished. Doing this causes undefined behavior.
	 *
	 *  @see GetLocation
	 *  @see GetCommonLocation
	 *  @see QueryLocation
	 *  @see BindLocation
	 *
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	static bool QueryCommonLocation(
		const Sequence<ProgramName>& programs,
		StrCRef identifier,
		VertexAttribSlot& location
	);

	/// Returns vertex attr. location in multiple programs if it's consistent
	/** Finds the location of the input vertex attribute specified
	 *  by @p identifier in every program in @p programs.
	 *  Throws Error if no such attribute exists or if it is not active
	 *  in some of the programs or if the attribute has different locations
	 *  in different programs. Otherwise returns the vertex attribute
	 *  position.
	 *
	 *  @code
	 *  VertexArray vao;
	 *  Buffer buf;
	 *  Program prog1, prog2, prog3;
	 *  // build the programs, load data into the buffer, ...
	 *  vao.Bind();
	 *  buffer.Bind(Buffer::Target::Array);
	 *  try
	 *  {
	 *      VertexAttribArray attr(
	 *          VertexAttribOps::GetCommonLocation(
	 *              MakeGroup(prog1, prog2, prog3),
	 *              "Position"
	 *          )
	 *      );
	 *      attr.Setup(n_per_vertex, DataType::Float);
	 *      attr.Enable();
	 *  }
	 *  catch(ProgVarError& error)
	 *  {
	 *      // handle the error or bind the locations manually
	 *  }
	 *
	 *  @endcode
	 *
	 *  @see GetLocation
	 *  @see GetCommonLocation
	 *  @see QueryLocation
	 *  @see BindLocation
	 *
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	static VertexAttribSlot GetCommonLocation(
		const Sequence<ProgramName>& programs,
		StrCRef identifier
	);
};

template <>
class ProgVarSetters<tag::ImplicitSel, tag::VertexAttrib, tag::NativeTypes>
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(VertexAttrib, VertexAttrib)

	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, f, t, GLfloat)
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, d, t, GLdouble)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, s, t, GLshort)

	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, i, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, ui, t, GLuint)
#endif

	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, fv, v, GLfloat)
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, dv, v, GLdouble)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, sv, v, GLshort)

	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, i, v, GLint)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, ui, v, GLuint)
#endif
};

template <>
class ProgVarCommonOps<tag::VertexAttrib>
 : public ProgVarLoc<tag::VertexAttrib>
 , public ProgVarLocOps<tag::VertexAttrib>
{
protected:
	ProgVarCommonOps(void) { }

	ProgVarCommonOps(ProgramName program, VertexAttribSlot location)
	 : ProgVarLoc<tag::VertexAttrib>(program, GLint(location))
	{ }

	ProgVarCommonOps(ProgramName program, StrCRef identifier)
	 : ProgVarLoc<tag::VertexAttrib>(
		program,
		GLint(this->GetLocation(program, identifier))
	){ }
public:
	void Bind(StrCRef identifier)
	{
		BindLocation(
			this->Program(),
			this->_location,
			identifier
		);
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
			_location,
			divisor
		);
		OGLPLUS_CHECK_SIMPLE(VertexAttribDivisor);
	}
#endif
};

/// Encapsulates vertex attribute value set functionality
/**
 *  @ingroup shader_variables
 */
template <typename OpsTag, typename T>
class ProgVarGetSetOps<OpsTag, tag::VertexAttrib, T>
 : public ProgVarCommonOps<tag::VertexAttrib>
 , public ProgVarBaseSetOps<OpsTag, tag::VertexAttrib, tag::NativeTypes, T, 16>
{
protected:
	ProgVarGetSetOps(void) { }
public:
	/// Set the value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	void Set(T value)
	{
		this->_do_set(_program, _location, value);
	}
};

template <typename OpsTag, typename T, std::size_t N>
class ProgVarGetSetOps<OpsTag, tag::VertexAttrib, Vector<T, N>>
 : public ProgVarCommonOps<tag::VertexAttrib>
 , public ProgVarBaseSetOps<OpsTag, tag::VertexAttrib, tag::NativeTypes, T, 4>
{
protected:
	ProgVarGetSetOps(void) { }
public:
	void Set(const Vector<T, N>& value)
	{
		this->template _do_set<N>(_program, _location, Data(value));
	}
};

template <typename OpsTag, typename T, std::size_t R, std::size_t C>
class ProgVarGetSetOps<OpsTag, tag::VertexAttrib, Matrix<T, R, C>>
 : public ProgVarCommonOps<tag::VertexAttrib>
 , public ProgVarBaseSetOps<OpsTag, tag::VertexAttrib, tag::NativeTypes, T, 16>
{
protected:
	ProgVarGetSetOps(void) { }
public:
	void Set(const Matrix<T, R, C>& value)
	{
		this->template _do_set<R*C>(_program, _location, Data(value));
	}
};

template <typename T>
class VertexAttrib
 : public ProgVarGetSetOps<tag::ImplicitSel, tag::VertexAttrib, T>
{
public:
	VertexAttrib(ProgramName program, VertexAttribSlot location)
	{
		this->Init(program, location);
	}

	VertexAttrib(ProgramName program, StrCRef identifier)
	{
		this->Init(
			program,
			GLint(this->GetActiveLocation(program, identifier))
		);
	}

	void TrySet(const T& value)
	{
		if(this->IsActive())
		{
			this->Set(value);
		}
	}
};

/// Encapsulates vertex attribute array functionality
/**
 *  @ingroup shader_variables
 */
class VertexAttribArray
 : public ProgVarCommonOps<tag::VertexAttrib>
{
private:
	// Functions for autodetection of values-per-vertex
	template <typename T>
	static GLint _get_vpv(T*)
	{
		return 1;
	}

	template <typename T, std::size_t N>
	static GLint _get_vpv(Vector<T, N>*)
	{
		return N;
	}

	template <typename T, std::size_t Rows, std::size_t Cols>
	static GLint _get_vpv(Matrix<T, Rows, Cols>*)
	{
		return Rows*Cols;
	}

	// Functions for autodetection of element type
	template <typename T>
	static T _get_et(T* p);

	template <typename T, std::size_t N>
	static T _get_et(Vector<T, N>*);

	template <typename T, std::size_t Rows, std::size_t Cols>
	static T _get_et(Matrix<T, Rows, Cols>*);
public:
	/// References the vertex attribute array at @p location
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttribArray(ProgramName program, VertexAttribSlot location)
	 : ProgVarCommonOps<tag::VertexAttrib>(program, location)
	{ }

	/// References the vertex attrib array @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttribArray(ProgramName program, StrCRef identifier)
	 : ProgVarCommonOps<tag::VertexAttrib>(program, identifier)
	{ }

	/// Setup the properties of this vertex attribute array
	/** Equivalent to
	 *  @code
	 *  Pointer(valuer_per_vertex, data_type, false, 0, NULL)
	 *  @endcode
	 *  if @p data_type is DataType::Float or to
	 *  @code
	 *  LPointer(valuer_per_vertex, data_type, 0, NULL)
	 *  @endcode
	 *  if @p data_type is DataType::Double or to
	 *  @code
	 *  IPointer(valuer_per_vertex, data_type, 0, NULL)
	 *  @endcode
	 *  otherwise.
	 *
	 *  @note Consider using the templated version of Setup(), because
	 *  it is more portable. For example instead of:
	 *  @code
	 *  attr.Setup(3, DataType::Float);
	 *  @endcode
	 *  use
	 *  @code
	 *  attr.Setup<Vec3f>();
	 *  @endcode
	 *  or
	 *  @code
	 *  attr.Setup<GLfloat>(3);
	 *  @endcode
	 *
	 *  @see Pointer
	 *  @see IPointer
	 *  @see LPointer
	 *
	 *  @glsymbols
	 *  @glfunref{VertexAttribPointer}
	 */
	const VertexAttribArray& Setup(
		GLint values_per_vertex,
		DataType data_type
	) const
	{
		if(data_type == DataType::Float)
		{
			Pointer(
				values_per_vertex,
				data_type,
				false,
				0,
				nullptr
			);
		}
#ifdef GL_DOUBLE
		else if(data_type == DataType::Double)
		{
			LPointer(
				values_per_vertex,
				data_type,
				0,
				nullptr
			);
		}
#endif
		else
		{
			IPointer(
				values_per_vertex,
				data_type,
				0,
				nullptr
			);
		}
		return *this;
	}

	const VertexAttribArray& Setup(
		GLint values_per_vertex,
		std::integral_constant<
			typename enums::EnumValueType<DataType>::Type,
			OGLPLUS_CONST_ENUM_VALUE(DataType::Float)
		>
	) const
	{
		return Pointer(
			values_per_vertex,
			DataType::Float,
			false,
			0,
			nullptr
		);
	}

#ifdef GL_DOUBLE
	const VertexAttribArray& Setup(
		GLint values_per_vertex,
		std::integral_constant<
			typename enums::EnumValueType<DataType>::Type,
			OGLPLUS_CONST_ENUM_VALUE(DataType::Double)
		>
	) const
	{
		return LPointer(
			values_per_vertex,
			DataType::Double,
			0,
			nullptr
		);
	}
#endif

	template <
		typename enums::EnumValueType<DataType>::Type DataTypeValue
	>
	const VertexAttribArray& Setup(
		GLint values_per_vertex,
		std::integral_constant<
			typename enums::EnumValueType<DataType>::Type,
			DataTypeValue
		>
	) const
	{
		return IPointer(
			values_per_vertex,
			DataTypeValue,
			0,
			nullptr
		);
	}

	/// Setup the properties of this vertex attribute array
	/**
	 *  @see Pointer
	 *  @see IPointer
	 *  @see LPointer
	 *
	 *  @glsymbols
	 *  @glfunref{VertexAttribPointer}
	 */
	template <typename T>
	const VertexAttribArray& Setup(GLuint n = 1) const
	{
		typedef decltype(_get_et((T*)nullptr)) elem_type;

		return Setup(
			_get_vpv((T*)nullptr)*n,
			typename DataTypeCT<elem_type>::type()
		);
	}

	/// Setup the properties of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttribPointer}
	 */
	const VertexAttribArray& Pointer(
		GLint values_per_vertex,
		DataType data_type,
		bool normalized,
		GLsizei stride,
		const void* pointer
	) const
	{
		OGLPLUS_GLFUNC(VertexAttribPointer)(
			_location,
			values_per_vertex,
			GLenum(data_type),
			normalized ? GL_TRUE : GL_FALSE,
			stride,
			pointer
		);
		OGLPLUS_CHECK(
			VertexAttribPointer,
			Error,
			EnumParam(data_type).
			Index(_location)
		);
		return *this;
	}

	/// Setup the properties of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttribPointer}
	 */
	const VertexAttribArray& IPointer(
		GLuint values_per_vertex,
		DataType data_type,
		GLsizei stride,
		const void* pointer
	) const
	{
		OGLPLUS_GLFUNC(VertexAttribIPointer)(
			_location,
			values_per_vertex,
			GLenum(data_type),
			stride,
			pointer
		);
		OGLPLUS_CHECK(
			VertexAttribIPointer,
			Error,
			EnumParam(data_type).
			Index(_location)
		);
		return *this;
	}


#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2 || GL_ARB_vertex_attrib_64bit
	/// Setup the properties of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttribPointer}
	 */
	const VertexAttribArray& LPointer(
		GLuint values_per_vertex,
		DataType data_type,
		GLsizei stride,
		const void* pointer
	) const
	{
		OGLPLUS_GLFUNC(VertexAttribLPointer)(
			_location,
			values_per_vertex,
			GLenum(data_type),
			stride,
			pointer
		);
		OGLPLUS_CHECK(VertexAttribLPointer,
			Error,
			EnumParam(data_type).
			Index(_location)
		);
		return *this;
	}
#else
	const VertexAttribArray& LPointer(
		GLuint,
		DataType,
		GLsizei,
		const void*
	) const
	{
		assert(!
		"The glVertexAttribLPointer function is "
		"required but not available! Double-precision "
		"vertex attribute values are not supported."
		);
		return *this;
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_vertex_attrib_binding
	/// Setup the format of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttribFormat}
	 */
	const VertexAttribArray& Format(
		GLint values_per_vertex,
		DataType data_type,
		bool normalized,
		GLuint relative_offset
	) const
	{
		OGLPLUS_GLFUNC(VertexAttribFormat)(
			_location,
			values_per_vertex,
			GLenum(data_type),
			normalized ? GL_TRUE : GL_FALSE,
			relative_offset
		);
		OGLPLUS_CHECK(
			VertexAttribFormat,
			Error,
			EnumParam(data_type).
			Index(_location)
		);
		return *this;
	}

	/// Setup the format of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttribIFormat}
	 */
	const VertexAttribArray& IFormat(
		GLint values_per_vertex,
		DataType data_type,
		GLuint relative_offset
	) const
	{
		OGLPLUS_GLFUNC(VertexAttribIFormat)(
			_location,
			values_per_vertex,
			GLenum(data_type),
			relative_offset
		);
		OGLPLUS_CHECK(
			VertexAttribIFormat,
			Error,
			EnumParam(data_type).
			Index(_location)
		);
		return *this;
	}

	/// Setup the format of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttribLFormat}
	 */
	const VertexAttribArray& LFormat(
		GLint values_per_vertex,
		DataType data_type,
		GLuint relative_offset
	) const
	{
		OGLPLUS_GLFUNC(VertexAttribLFormat)(
			_location,
			values_per_vertex,
			GLenum(data_type),
			relative_offset
		);
		OGLPLUS_CHECK(
			VertexAttribLFormat,
			Error,
			EnumParam(data_type).
			Index(_location)
		);
		return *this;
	}
#endif

	/// Enables this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{EnableVertexAttribArray}
	 */
	const VertexAttribArray& Enable(void) const
	{
		OGLPLUS_GLFUNC(EnableVertexAttribArray)(_location);
		OGLPLUS_VERIFY(
			EnableVertexAttribArray,
			Error,
			Index(_location)
		);
		return *this;
	}

	/// Disables this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{DisableVertexAttribArray}
	 */
	const VertexAttribArray& Disable(void) const
	{
		OGLPLUS_GLFUNC(DisableVertexAttribArray)(_location);
		OGLPLUS_VERIFY(
			DisableVertexAttribArray,
			Error,
			Index(_location)
		);
		return *this;
	}
};

/// Syntax sugar for construction of a VertexAttribArray object
/** Constructs an instance of VertexAttribArray for a vertex attribute
 *  identified by @p identifier in a @p program.
 *
 *  @see VertexAttribArray
 */
template <std::size_t N>
inline VertexAttribArray operator | (
	ProgramName program,
	const GLchar (&identifier)[N]
)
{
	return VertexAttribArray(program, identifier);
}

/// Syntax sugar for construction of a VertexAttribArray object
/** Constructs an instance of VertexAttribArray for a vertex attribute
 *  at the specified @p location in a @p program.
 *
 *  @see VertexAttribArray
 */
inline VertexAttribArray operator | (
	ProgramName program,
	GLuint location
)
{
	return VertexAttribArray(program, VertexAttribSlot(location));
}

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/vertex_attrib.ipp>
#endif

#endif // include guard
