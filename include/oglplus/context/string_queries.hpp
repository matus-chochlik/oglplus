/**
 *  @file oglplus/context/string_queries.hpp
 *  @brief Wrappers for GL string queries
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_STRING_QUERIES_1202210920_HPP
#define OGLPLUS_CONTEXT_STRING_QUERIES_1202210920_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/string_query.hpp>

namespace oglplus {
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
		AssertNoError(OGLPLUS_ERROR_INFO(GetString));
		return result;
	}

	/// Queries the major version number
	/**
	 *  @throws Error
	 *
	 *  @see MinorVersion
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{MAJOR_VERSION}
	 */
	static GLint MajorVersion(void)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_MAJOR_VERSION, &result);
		AssertNoError(OGLPLUS_ERROR_INFO(GetIntegerv));
		return result;
	}

	/// Queries the minor version number
	/**
	 *  @throws Error
	 *
	 *  @see MajorVersion
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{MINOR_VERSION}
	 */
	static GLint MinorVersion(void)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_MINOR_VERSION, &result);
		AssertNoError(OGLPLUS_ERROR_INFO(GetIntegerv));
		return result;
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
		AssertNoError(OGLPLUS_ERROR_INFO(GetIntegerv));
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
		AssertNoError(OGLPLUS_ERROR_INFO(GetStringi));
		return result;
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
