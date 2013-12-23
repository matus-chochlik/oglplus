/**
 *  @file oglplus/auxiliary/uniform_typecheck.hpp
 *  @brief Helper base class templates used for uniform variable initialization
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_UNIFORM_TYPECHECK_1107121519_HPP
#define OGLPLUS_AUX_UNIFORM_TYPECHECK_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>

#include <vector>
#include <cstring>
#include <cassert>

namespace oglplus {

OGLPLUS_ENUM_CLASS_FWD_EVT(SLDataType, GLenum)

template <typename enums::EnumValueType<oglplus::enums::SLDataType>::Type>
struct SLtoCpp;

namespace aux {

class NoUniformTypecheck
{
public:
	inline NoUniformTypecheck(void)
	OGLPLUS_NOEXCEPT(true)
	{ }

	template <typename T>
	inline NoUniformTypecheck(T* /*selector*/)
	OGLPLUS_NOEXCEPT(true)
	{ }

	inline bool operator()(
		GLuint /*_program*/,
		GLint /*location*/,
		const GLchar* /*identifier*/
	) const
	OGLPLUS_NOEXCEPT(true)
	{
		return true;
	}
};

#if !OGLPLUS_NO_UNIFORM_TYPECHECK

class UniformTypecheckBase
{
protected:
	static GLenum _query_uniform_type(
		GLuint program,
		GLint /*location*/,
		const GLchar* identifier
	);

	bool (*_uniform_type_match)(GLenum);
public:
	UniformTypecheckBase(bool (*uniform_type_match)(GLenum))
	 : _uniform_type_match(uniform_type_match)
	{ }

	bool operator()(
		GLuint program,
		GLint location,
		const GLchar* identifier
	) const
	{
		assert(_uniform_type_match);
		return _uniform_type_match(
			_query_uniform_type(
				program,
				location,
				identifier
			)
		);
	}
};

template <typename T>
struct DefaultGLSLtoCppTypeMatcher
{
	static bool _matches(GLenum /*sl_type*/)
	{
		return false;
	}
};

template <typename enums::EnumValueType<oglplus::enums::SLDataType>::Type SLType>
struct DefaultGLSLtoCppTypeMatcher<oglplus::SLtoCpp<SLType> >
{
	static bool _matches(GLenum sl_type)
	{
		return sl_type == GLenum(SLType);
	}
};

template <>
struct DefaultGLSLtoCppTypeMatcher<bool>
{
	static bool _matches(GLenum sl_type)
	{
		return sl_type == GL_BOOL;
	}
};

template <>
struct DefaultGLSLtoCppTypeMatcher<GLint>
{
	static bool _matches(GLenum sl_type);
};

template <>
struct DefaultGLSLtoCppTypeMatcher<GLuint>
{
	static bool _matches(GLenum sl_type);
};

template <>
struct DefaultGLSLtoCppTypeMatcher<GLfloat>
{
	static bool _matches(GLenum sl_type)
	{
		return sl_type == GL_FLOAT;
	}
};

#if defined(GL_DOUBLE)
template <>
struct DefaultGLSLtoCppTypeMatcher<GLdouble>
{
	static bool _matches(GLenum sl_type)
	{
		return sl_type == GL_DOUBLE;
	}
};
#endif

#if defined(GL_UNSIGNED_INT64_ARB)
template <>
struct DefaultGLSLtoCppTypeMatcher<GLuint64>
{
	static bool _matches(GLenum sl_type)
	{
		return sl_type == GL_UNSIGNED_INT64_ARB;
	}
};
#endif

struct DefaultGLSLtoCppTypeMatcher_Vec
{
	static std::size_t _type_idx(bool*) { return 0; }
	static std::size_t _type_idx(GLint*) { return 1; }
	static std::size_t _type_idx(GLuint*) { return 2; }
	static std::size_t _type_idx(GLfloat*) { return 3; }
#if defined(GL_DOUBLE)
	static std::size_t _type_idx(GLdouble*) { return 4; }
#endif

	static bool _does_match(
		GLenum sl_type,
		std::size_t type_idx,
		std::size_t dim
	);
};

template <typename T, std::size_t N>
struct DefaultGLSLtoCppTypeMatcher<oglplus::Vector<T, N> >
 : public DefaultGLSLtoCppTypeMatcher_Vec
{
	static_assert(N <= 4, "Invalid vector size");

	static T* _type_sel(void) { return nullptr; }

	static bool _matches(GLenum sl_type)
	{
		return DefaultGLSLtoCppTypeMatcher_Vec::_does_match(
			sl_type,
			DefaultGLSLtoCppTypeMatcher_Vec::_type_idx(_type_sel()),
			N
		);
	}
};

struct DefaultGLSLtoCppTypeMatcher_Mat
{
	static std::size_t _type_idx(GLfloat*) { return 0; }
#ifdef GL_DOUBLE
	static std::size_t _type_idx(GLdouble*) { return 1; }
#endif

	static bool _does_match(
		GLenum sl_type,
		std::size_t type_idx,
		std::size_t rows,
		std::size_t cols
	);
};

template <typename T, std::size_t Rows, std::size_t Cols>
struct DefaultGLSLtoCppTypeMatcher<oglplus::Matrix<T, Rows, Cols> >
 : public DefaultGLSLtoCppTypeMatcher_Mat
{
	static_assert(Rows >= 2, "Invalid matrix size");
	static_assert(Cols >= 2, "Invalid matrix size");

	static_assert(Rows <= 4, "Invalid matrix size");
	static_assert(Cols <= 4, "Invalid matrix size");

	static T* _type_sel(void) { return nullptr; }

	static bool _matches(GLenum sl_type)
	{
		return DefaultGLSLtoCppTypeMatcher_Mat::_does_match(
			sl_type,
			DefaultGLSLtoCppTypeMatcher_Mat::_type_idx(_type_sel()),
			Rows,
			Cols
		);
	}
};

class DefaultUniformTypecheck
 : public UniformTypecheckBase
{
public:
	template <typename TypeSel>
	DefaultUniformTypecheck(TypeSel* /*type_sel*/)
	 : UniformTypecheckBase(&DefaultGLSLtoCppTypeMatcher<TypeSel>::_matches)
	{ }
};
#endif // !OGLPLUS_NO_UNIFORM_TYPECHECK

class UniformInitTypecheckUtils
{
private:
	static void _handle_error(
		GLuint program,
		GLint location,
		const GLchar* identifier
	);
protected:
	template <typename Typechecker>
	GLint _typecheck(
		Typechecker& type_ok,
		GLuint program,
		GLint location,
		const GLchar* identifier
	)
	{
		if(!type_ok(program, location, identifier))
			_handle_error(program, location, identifier);

		return location;
	}
};

} // namespace aux

typedef aux::NoUniformTypecheck NoTypecheck;

#if !OGLPLUS_NO_UNIFORM_TYPECHECK
typedef aux::DefaultUniformTypecheck DefaultTypecheck;
#else
typedef aux::NoUniformTypecheck DefaultTypecheck;
#endif

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/auxiliary/uniform_typecheck.ipp>
#endif // OGLPLUS_LINK_LIB

#endif // include guard
