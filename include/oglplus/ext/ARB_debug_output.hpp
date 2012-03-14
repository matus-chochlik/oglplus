/**
 *  @file oglplus/ext/ARB_debug_output.hpp
 *  @brief Wrapper for the ARB_debug_output extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXT_ARB_DEBUG_OUTPUT_1203031902_HPP
#define OGLPLUS_EXT_ARB_DEBUG_OUTPUT_1203031902_HPP

#include <oglplus/extension.hpp>

#include <stack>
#include <functional>

namespace oglplus {

/// Debug output severity enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{ARB,debug_output}
 */
enum class DebugOutputSeverity : GLenum
{
#include <oglplus/enums/ext/debug_output_severity.ipp>
};

/// A shorter name for DebugOutputSeverity
typedef DebugOutputSeverity DebugSeverity;

inline const GLchar* EnumValueName(DebugOutputSeverity value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/debug_output_severity.ipp>
#endif
	return "";
}


/// Debug output source enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{ARB,debug_output}
 */
enum class DebugOutputSource : GLenum
{
#include <oglplus/enums/ext/debug_output_source.ipp>
};

/// A shorter name for DebugOutputSource
typedef DebugOutputSource DebugSource;

inline const GLchar* EnumValueName(DebugOutputSource value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/debug_output_source.ipp>
#endif
	return "";
}


/// Debug output type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{ARB,debug_output}
 */
enum class DebugOutputType : GLenum
{
#include <oglplus/enums/ext/debug_output_type.ipp>
};

/// A shorter name for DebugOutputType
typedef DebugOutputType DebugType;

inline const GLchar* EnumValueName(DebugOutputType value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/debug_output_type.ipp>
#endif
	return "";
}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_debug_output
/// Wrapper for the ARB_debug_output extension
/**
 *  @glsymbols
 *  @glextref{ARB,debug_output}
 *
 *  @ingroup extensions
 */
class ARB_debug_output
{
public:
	OGLPLUS_EXTENSION_CLASS(ARB, debug_output)

	typedef std::functional<void (
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message
	)> Callback;

private:
	static void APIENTRY _gl_debug_proc(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		GLvoid* userParam
	)
	{
	}
public:
	/// Enables or disables synchronous debug output
	static void Synchronous(bool enable)
	{
		if(enable)
		{
			OGLPLUS_GLFUNC(Enable)(
				GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB
			);
			AssertNoError(OGLPLUS_ERROR_INFO(Enable));
		}
		else
		{
			OGLPLUS_GLFUNC(Disable)(
				GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB
			);
			AssertNoError(OGLPLUS_ERROR_INFO(Disable));
		}
	}

	/// Inserts a new message into the debug output
	static void InsertMessage(
		DebugOutputSource source,
		DebugOutputType type,
		GLuint id,
		DebugOutputSeverity severity,
		const GLchar* buffer,
		GLint length = -1
	)
	{
		OGLPLUS_GLFUNC(DebugMessageInsertARB)(
			GLenum(source),
			GLenum(type),
			id,
			GLenum(severity),
			length,
			buffer
		);
		AssertNoError(OGLPLUS_ERROR_INFO(DebugMessageInsertARB));
	}
};
#endif

} // namespace oglplus

#endif // include guard
