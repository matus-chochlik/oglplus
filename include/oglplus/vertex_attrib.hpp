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
#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/program.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/limited_value.hpp>
#include <oglplus/auxiliary/shader_data.hpp>

#include <oglplus/string.hpp>

#include <type_traits>

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
	GLint _location;

	friend class FriendOf<VertexAttribOps>;

	VertexAttribOps(VertexAttribSlot i)
	 : _location(GLint(i))
	{ }

	static GLint _get_location(
		const ProgramOps& program,
		const GLchar* identifier
	)
	{
		return OGLPLUS_GLFUNC(GetAttribLocation)(
			FriendOf<ProgramOps>::GetName(program),
			identifier
		);
	}

	static void _handle_inactive(
		const ProgramOps& program,
		const GLchar* identifier,
		GLint result
	);

	static GLint _find_location(
		const ProgramOps& program,
		const GLchar* identifier
	)
	{
		GLint result = _get_location(program, identifier);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetAttribLocation));
		if(OGLPLUS_IS_ERROR(result == GLint(-1)))
		{
			_handle_inactive(program, identifier, result);
		}
		return result;
	}

	static bool _query_location(
		const ProgramOps& program,
		const String& identifier,
		VertexAttribSlot& location
	)
	{
		GLint result = _get_location(program, identifier.c_str());
		if(OGLPLUS_GLFUNC(GetError)() != GL_NO_ERROR)
			return false;
		if(result < 0) return false;
		location = result;
		return true;
	}

	template <typename Iterator>
	static bool _query_common_location(
		Iterator pprogram_begin,
		Iterator pprogram_end,
		const GLchar* identifier,
		VertexAttribSlot& location
	)
	{
		Iterator i=pprogram_begin, e=pprogram_end;
		if(i != e)
		{
			const ProgramOps* pprog = *i;
			assert(pprog);
			const ProgramOps& prog = *pprog;
			if(!_query_location(prog, identifier, location))
				return false;
			const VertexAttribSlot prev_loc(location);
			while(++i != e)
			{
				if(!_query_location(prog, identifier, location))
					return false;
				if(prev_loc != location)
					return false;
			}
			return true;
		}
		return false;
	}

	static void _handle_inconsistent_location(
		const GLchar* identifier,
		VertexAttribSlot location
	);

	template <typename Iterator>
	static VertexAttribSlot _get_common_location(
		Iterator pprogram_begin,
		Iterator pprogram_end,
		const GLchar* identifier
	)
	{
		VertexAttribSlot location;
		if(OGLPLUS_IS_ERROR(!_query_common_location(
			pprogram_begin,
			pprogram_end,
			identifier,
			location
		)))
		{
			_handle_inconsistent_location(identifier, location);
		}
		return location;
	}

	class _common_location_query
	{
	private:
		const GLchar* _identifier;
		VertexAttribSlot& _location;
		bool _first, _ok;

		_common_location_query(
			const GLchar* identifier,
			VertexAttribSlot& location,
			bool ok
		): _identifier(identifier)
		 , _location(location)
		 , _first(false)
		 , _ok(ok)
		{ }

	public:
		_common_location_query(
			const GLchar* identifier,
			VertexAttribSlot& location
		): _identifier(identifier)
		 , _location(location)
		 , _first(true)
		 , _ok(true)
		{ }

		_common_location_query In(const ProgramOps& prog) const
		{
			return _common_location_query(
				_identifier,
				_location,
				_ok && VertexAttribOps::_query_location(
					prog,
					_identifier,
					_location
				)
			);
		}

		_common_location_query And(const ProgramOps& prog) const
		{
			return In(prog);
		}

		operator bool (void) const
		{
			return !_first && _ok;
		}
	};

	// Functions for autodetection of values-per-vertex
	template <typename T>
	static GLint _get_values_per_vertex(T*)
	{
		return 1;
	}

	template <typename T, std::size_t N>
	static GLint _get_values_per_vertex(Vector<T, N>*)
	{
		return N;
	}

	template <typename T, std::size_t Rows, std::size_t Cols>
	static GLint _get_values_per_vertex(Matrix<T, Rows, Cols>*)
	{
		return Rows*Cols;
	}

	// Functions for autodetection of element type
	template <typename T>
	static T _get_element_type(T* p);

	template <typename T, std::size_t N>
	static T _get_element_type(Vector<T, N>*);

	template <typename T, std::size_t Rows, std::size_t Cols>
	static T _get_element_type(Matrix<T, Rows, Cols>*);

	VertexAttribOps(const ProgramOps& program, const GLchar* identifier)
	 : _location(_find_location(program, identifier))
	{ }
public:
	/// Returns the location of this vertex attribute in a program
	/**
	 *
	 *  @see GetLocation
	 *  @see GetCommonLocation
	 *  @see QueryLocation
	 *  @see BindLocation
	 *
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttribSlot Location(void) const
	{
		return VertexAttribSlot(_location);
	}


	static VertexAttribSlot GetLocation(
		const ProgramOps& program,
		const GLchar* identifier
	)
	{
		return VertexAttribSlot(_find_location(
			program,
			identifier
		));
	}

	/// Finds the vertex attribute location, throws on failure
	/** Finds the location of the input vertex attribute specified
	 *  by @p identifier in a @p program. Throws if no such attribute
	 *  exists or if it is not active. For a non-throwing version
	 *  see QueryLocation().
	 *
	 *  @see GetCommonLocation
	 *  @see QueryLocation
	 *  @see BindLocation
	 *
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	static VertexAttribSlot GetLocation(
		const ProgramOps& program,
		const String& identifier
	)
	{
		return VertexAttribSlot(_find_location(
			program,
			identifier.c_str()
		));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
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
	 *              "Position",
	 *              prog1,
	 *              prog2,
	 *              prog3
	 &          )
	 *      );
	 *      attr.Setup(n_per_vertex, DataType::Float);
	 *      attr.Enable();
	 *  }
	 *  catch(Error& error)
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
	template <typename ... ProgramOps_>
	static VertexAttribSlot GetCommonLocation(
		const GLchar* identifier,
		const ProgramOps & program,
		const ProgramOps_& ... programs
	)
	{
		const ProgramOps* pprogs[] = {
			&program,
			&programs...
		};
		return _get_common_location(
			pprogs,
			pprogs+1+sizeof...(programs),
			identifier
		);
	}
#else
	static VertexAttribSlot GetCommonLocation(
		const GLchar* identifier,
		const ProgramOps& program1,
		const ProgramOps& program2
	)
	{
		const ProgramOps* pprogs[] = {
			&program1,
			&program2
		};
		return _get_common_location(
			pprogs,
			pprogs+2,
			identifier
		);
	}

	static VertexAttribSlot GetCommonLocation(
		const GLchar* identifier,
		const ProgramOps& program1,
		const ProgramOps& program2,
		const ProgramOps& program3
	)
	{
		const ProgramOps* pprogs[] = {
			&program1,
			&program2,
			&program3
		};
		return _get_common_location(
			pprogs,
			pprogs+3,
			identifier
		);
	}
#endif

	static bool QueryLocation(
		const ProgramOps& program,
		const GLchar* identifier,
		VertexAttribSlot& location
	)
	{
		return _query_location(program, identifier, location);
	}

	/// Queries the vertex attribute @p location in a program
	/** Finds the @p location of the input vertex attribute specified
	 *  by @p identifier in a @p program. Returns false if no such attribute
	 *  exists or if it is not active, otherwise stores the vertex attribute
	 *  position in @p location and returns true.
	 *  For a throwing version see GetLocation().
	 *
	 *  @see GetLocation
	 *  @see GetCommonLocation
	 *  @see QueryCommonLocation
	 *  @see BindLocation
	 *
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	static bool QueryLocation(
		const ProgramOps& program,
		const String& identifier,
		VertexAttribSlot& location
	)
	{
		return _query_location(program, identifier.c_str(), location);
	}


	static _common_location_query QueryCommonLocation(
		const GLchar* identifier,
		VertexAttribSlot& location
	)
	{
		return _common_location_query(identifier, location);
	}

	/// Allows to query the vertex attribute @p location in multiple programs
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
	 *  VertexAttribSlot loc;
	 *  if(VertexAttribOps::QueryCommonLocation("Pos", loc)
	 *	.In(prog1).In(prog2).In(prog3).And(prog4)
	 *  )
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
	static _common_location_query QueryCommonLocation(
		const String& identifier,
		VertexAttribSlot& location
	)
	{
		return _common_location_query(identifier.c_str(), location);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Queries the vertex attribute @p location in multiple programs
	/** Finds the @p location of the input vertex attribute specified
	 *  by @p identifier in every program in @p programs.
	 *  Returns false if no such attribute exists or if it is not active
	 *  in some of the programs or if the attribute has different locations
	 *  in different programs. Otherwise stores the vertex attribute
	 *  position in @p location and returns true.
	 *
	 *  @see GetLocation
	 *  @see GetCommonLocation
	 *  @see QueryLocation
	 *  @see BindLocation
	 *
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	template <typename ... ProgramOps_>
	static bool QueryCommonLocation(
		const GLchar* identifier,
		VertexAttribSlot& location,
		const ProgramOps & program,
		const ProgramOps_& ... programs
	)
	{
		const ProgramOps* pprogs[] = {
			&program,
			&programs...
		};
		return _query_common_location(
			pprogs,
			pprogs+1+sizeof...(programs),
			identifier,
			location
		);
	}
#else
	static bool QueryCommonLocation(
		const GLchar* identifier,
		VertexAttribSlot& location,
		const ProgramOps& program1,
		const ProgramOps& program2
	)
	{
		const ProgramOps* pprogs[] = {
			&program1,
			&program2
		};
		return _query_common_location(
			pprogs,
			pprogs+2,
			identifier,
			location
		);
	}

	static bool QueryCommonLocation(
		const GLchar* identifier,
		VertexAttribSlot& location,
		const ProgramOps& program1,
		const ProgramOps& program2,
		const ProgramOps& program3
	)
	{
		const ProgramOps* pprogs[] = {
			&program1,
			&program2,
			&program3
		};
		return _query_common_location(
			pprogs,
			pprogs+3,
			identifier,
			location
		);
	}
#endif

	void BindLocation(
		const ProgramOps& program,
		const GLchar* identifier
	) const
	{
		OGLPLUS_GLFUNC(BindAttribLocation)(
			FriendOf<ProgramOps>::GetName(program),
			_location,
			identifier
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(BindAttribLocation));
	}

	/// Bind the vertex attribute location
	/**
	 *  @see GetLocation
	 *  @see QueryLocation
	 *
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
			_location,
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
			_location,
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
		FriendOf<VertexAttribOps>::GetLocation(vertex_attrib),
		identifier
	);
	OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(BindAttribLocation));
}

namespace aux {

class VertexAttribSetters
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
	aux::VertexAttribSetters,
	aux::ActiveProgramCallOps<T>,
	16
>
#endif
{
public:
	/// References the vertex attribute array at @p location
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttrib(VertexAttribSlot location)
	 : VertexAttribOps(location)
	{ }

	/// References the vertex attribute @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttrib(const ProgramOps& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	/// References the vertex attribute @p identifier of the @p program
	VertexAttrib(const ProgramOps& program, const String& identifier)
	 : VertexAttribOps(program, identifier.c_str())
	{ }

	/// Set the value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	void Set(T value) const
	{
		this->_do_set(0, _location, value);
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

template <typename T, std::size_t N>
class VertexAttrib<Vector<T, N> >
 : public VertexAttribOps
 , public aux::ShaderDataSetOps<
	aux::VertexAttribSetters,
	aux::ActiveProgramCallOps<T>,
	4
>
{
public:
	/// References the vertex attribute array at @p location
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttrib(VertexAttribSlot location)
	 : VertexAttribOps(location)
	{ }

	/// References the vertex attribute @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttrib(const ProgramOps& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	/// References the vertex attribute @p identifier of the @p program
	VertexAttrib(const ProgramOps& program, const String& identifier)
	 : VertexAttribOps(program, identifier.c_str())
	{ }

	/// Set the vector value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	void Set(const Vector<T, N>& value) const
	{
		this->template _do_set<N>(0, _location, Data(value));
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

template <typename T, std::size_t Rows, std::size_t Cols>
class VertexAttrib<Matrix<T, Rows, Cols> >
 : public VertexAttribOps
 , public aux::ShaderDataSetOps<
	aux::VertexAttribSetters,
	aux::ActiveProgramCallOps<T>,
	16
>
{
public:
	/// References the vertex attribute array at @p location
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttrib(VertexAttribSlot location)
	 : VertexAttribOps(location)
	{ }

	/// References the vertex attribute @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttrib(const ProgramOps& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	/// References the vertex attribute @p identifier of the @p program
	VertexAttrib(const ProgramOps& program, const String& identifier)
	 : VertexAttribOps(program, identifier.c_str())
	{ }

	/// Set the matrix value of the vertex attribute
	/**
	 *  @glsymbols
	 *  @glfunref{VertexAttrib}
	 */
	void Set(const Matrix<T, Rows, Cols>& value) const
	{
		this->template _do_set<Rows*Cols>(0, _location, Data(value));
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
public:
	/// References the vertex attribute array at @p location
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttribArray(VertexAttribSlot location)
	 : VertexAttribOps(location)
	{ }

	/// References the vertex attrib array @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttribArray(const ProgramOps& program, const GLchar* identifier)
	 : VertexAttribOps(program, identifier)
	{ }

	/// References the vertex attrib array @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	VertexAttribArray(const ProgramOps& program, const String& identifier)
	 : VertexAttribOps(program, identifier.c_str())
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
		typedef decltype(_get_element_type((T*)nullptr)) elem_type;

		return Setup(
			_get_values_per_vertex((T*)nullptr)*n,
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(VertexAttribPointer));
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(VertexAttribIPointer));
		return *this;
	}


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
#if GL_VERSION_4_2 || GL_ARB_vertex_attrib_64bit
		OGLPLUS_GLFUNC(VertexAttribLPointer)(
			_location,
			values_per_vertex,
			GLenum(data_type),
			stride,
			pointer
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(VertexAttribLPointer));
#else
		OGLPLUS_FAKE_USE(values_per_vertex);
		OGLPLUS_FAKE_USE(data_type);
		OGLPLUS_FAKE_USE(stride);
		OGLPLUS_FAKE_USE(pointer);
		assert(!
			"The glVertexAttribLPointer function is "
			"required but not available! Double-precision "
			"vertex attribute values are not supported."
		);
#endif
		return *this;
	}

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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(VertexAttribFormat));
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(VertexAttribIFormat));
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
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(VertexAttribLFormat));
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(EnableVertexAttribArray));
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DisableVertexAttribArray));
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
	const ProgramOps& program,
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
	const ProgramOps& program,
	GLuint location
)
{
	OGLPLUS_FAKE_USE(program);
	return VertexAttribArray(VertexAttribSlot(location));
}

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/vertex_attrib.ipp>
#endif

#endif // include guard
