/**
 *  @file oglplus/context/string_queries.hpp
 *  @brief Wrappers for GL string queries
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_STRING_QUERIES_1202210920_HPP
#define OGLPLUS_CONTEXT_STRING_QUERIES_1202210920_HPP

#include <oglplus/config_compiler.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/string_query.hpp>

#include <cassert>

namespace oglplus {
namespace aux {

class ExtStrRange
{
private:
	GLuint _index, _count;
public:
	typedef String ValueType;

	ExtStrRange(GLuint n)
	 : _index(0)
	 , _count(n)
	{ }

	bool Empty(void) const
	{
		assert(_index <= _count);
		return _index == _count;
	}

	String Front(void) const
	{
		assert(!Empty());
		const GLubyte* result = OGLPLUS_GLFUNC(GetStringi)(
			GL_EXTENSIONS,
			_index
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetStringi));
		return String((const GLchar*)result);
	}

	void Next(void)
	{
		assert(!Empty());
		++_index;
	}
};

} // namespace aux

namespace context {

/// Wrapper for the GL string-query-related operations
/**
 *  @ingroup ogl_context
 */
class StringQueries
{
public:
	/// Queries a string describing GL properties
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{GetString}
	 */
	static const GLubyte* GetString(StringQuery query)
	{
		const GLubyte* result = OGLPLUS_GLFUNC(GetString)(GLenum(query));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetString));
		return result;
	}

	/// Returns the vendor name
	/**
	 *  @glsymbols
	 *  @glfunref{GetString}
	 *  @gldefref{VENDOR}
	 */
	static const char* Vendor(void)
	{
		return (const char*)GetString(StringQuery::Vendor);
	}

	/// Returns the version string
	/**
	 *  @glsymbols
	 *  @glfunref{GetString}
	 *  @gldefref{VERSION}
	 */
	static const char* Version(void)
	{
		return (const char*)GetString(StringQuery::Version);
	}

	/// Returns the shading language version string
	/**
	 *  @glsymbols
	 *  @glfunref{GetString}
	 *  @gldefref{SHADING_LANGUAGE_VERSION}
	 */
	static const char* ShadingLanguageVersion(void)
	{
		return (const char*)GetString(StringQuery::ShadingLanguageVersion);
	}

	/// Returns the renderer name
	/**
	 *  @glsymbols
	 *  @glfunref{GetString}
	 *  @gldefref{RENDERER}
	 */
	static const char* Renderer(void)
	{
		return (const char*)GetString(StringQuery::Renderer);
	}

	/// Queries the number of extension strings
	/**
	 *  @throws Error
	 *
	 *  @see GetExtension
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{NUM_EXTENSIONS}
	 */
	static GLuint NumExtensions(void)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_NUM_EXTENSIONS, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return GLuint(result);
	}


	/// Returns the name of the @p index -th extension
	/**
	 *  @throws Error
	 *
	 *  @see NumExtensions
	 *
	 *  @glsymbols
	 *  @glfunref{GetStringi}
	 *  @gldefref{EXTENSIONS}
	 */
	static const GLubyte* Extensions(GLuint index)
	{
		const GLubyte* result = OGLPLUS_GLFUNC(GetStringi)(
			GL_EXTENSIONS,
			index
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetStringi));
		return result;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Returns a range of extension strings
	/**
	 *  @glsymbols
	 *  @glfunref{GetString}
	 *  @gldefref{EXTENSIONS}
	 */
	static Range<String> Extensions(void);
#else
	static aux::ExtStrRange Extensions(void)
	{
		return aux::ExtStrRange(NumExtensions());
	}
#endif
};

} // namespace context
} // namespace oglplus

#endif // include guard
