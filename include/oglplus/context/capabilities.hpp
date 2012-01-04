/**
 *  @file oglplus/context/capabilities.hpp
 *  @brief Wrappers for OpenGL capability-related functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_CAPABILITIES_1201040722_HPP
#define OGLPLUS_CONTEXT_CAPABILITIES_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/capability.hpp>

namespace oglplus {
namespace context {

/// Wrapper for the capability-related commands
/**
 *  @ingroup ogl_context
 */
class Capabilities
{
public:
	/// Enable a @p capability
	/**
	 *  @glsymbols
	 *  @glfunref{Enable}
	 */
	static void Enable(Capability capability)
	{
		OGLPLUS_GLFUNC(Enable)(GLenum(capability));
		AssertNoError(OGLPLUS_ERROR_INFO(Enable));
	}

	/// Enable a @p functionality
	/**
	 *  @glsymbols
	 *  @glfunref{Enable}
	 */
	static void Enable(Functionality functionality, GLuint offset)
	{
		OGLPLUS_GLFUNC(Enable)(GLenum(functionality)+offset);
		AssertNoError(OGLPLUS_ERROR_INFO(Enable));
	}

	/// Disable a @p capability
	/**
	 *  @glsymbols
	 *  @glfunref{Disable}
	 */
	static void Disable(Capability capability)
	{
		OGLPLUS_GLFUNC(Disable)(GLenum(capability));
		AssertNoError(OGLPLUS_ERROR_INFO(Disable));
	}

	/// Disable a @p functionality
	/**
	 *  @glsymbols
	 *  @glfunref{Disable}
	 */
	static void Disable(Functionality functionality, GLuint offset)
	{
		OGLPLUS_GLFUNC(Disable)(GLenum(functionality)+offset);
		AssertNoError(OGLPLUS_ERROR_INFO(Disable));
	}

	/// Checks if a @p capability is enabled
	/**
	 *  @glsymbols
	 *  @glfunref{IsEnabled}
	 */
	static bool IsEnabled(Capability capability)
	{
		GLboolean result = OGLPLUS_GLFUNC(IsEnabled)(GLenum(capability));
		AssertNoError(OGLPLUS_ERROR_INFO(IsEnabled));
		return result == GL_TRUE;
	}

	/// Checks if a @p functionality is enabled
	/**
	 *  @glsymbols
	 *  @glfunref{IsEnabled}
	 */
	static bool IsEnabled(Functionality functionality, GLuint offset)
	{
		GLboolean result = OGLPLUS_GLFUNC(IsEnabled)(
			GLenum(functionality)+
			offset
		);
		AssertNoError(OGLPLUS_ERROR_INFO(IsEnabled));
		return result == GL_TRUE;
	}

	/// Enable a @p capability for an indexed target
	/**
	 *  @glsymbols
	 *  @glfunref{Enablei}
	 */
	static void Enable(Capability capability, GLuint index)
	{
		OGLPLUS_GLFUNC(Enablei)(GLenum(capability), index);
		AssertNoError(OGLPLUS_ERROR_INFO(Enablei));
	}

	/// Disable a @p capability for an indexed target
	/**
	 *  @glsymbols
	 *  @glfunref{Disablei}
	 */
	static void Disable(Capability capability, GLuint index)
	{
		OGLPLUS_GLFUNC(Disablei)(GLenum(capability), index);
		AssertNoError(OGLPLUS_ERROR_INFO(Disablei));
	}

	/// Check if a @p capability is enabled for indexed target
	/**
	 *  @glsymbols
	 *  @glfunref{IsEnabledi}
	 */
	static bool IsEnabled(Capability capability, GLuint index)
	{
		GLboolean result = OGLPLUS_GLFUNC(IsEnabledi)(
			GLenum(capability),
			index
		);
		AssertNoError(OGLPLUS_ERROR_INFO(IsEnabledi));
		return result == GL_TRUE;
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
