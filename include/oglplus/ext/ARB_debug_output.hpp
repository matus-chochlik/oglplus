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

#include <cassert>
#include <stack>
#include <functional>
#include <memory>

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

	/// Type of a callback functor processing debug output
	typedef std::function<void (
		DebugOutputSource source,
		DebugOutputType type,
		GLuint id,
		DebugOutputSeverity severity,
		GLsizei length,
		const GLchar* message
	)> Callback;

	/// Installs a custom callback processing the debug output
	/**
	 *  Instanes of this class install a new Callback function
	 *  processing the debug output messages in the constructor
	 *  and restoring the previous callback when destroyed.
	 */
	class LogSink
	{
	private:
		static void APIENTRY _gl_debug_proc(
			GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			GLvoid* user_param
		)
		{
			LogSink* self = static_cast<LogSink*>(user_param);
			assert(self);
			if(self->_callback)
			{
				self->_callback(
					DebugOutputSource(source),
					DebugOutputType(type),
					id,
					DebugOutputSeverity(severity),
					length,
					message
				);
			}
		}

		Callback _callback;
		GLDEBUGPROCARB _prev_callback;
		void* _prev_context;
		bool _initialized;
	public:
		/// Installs the @p callback and remembers the previous
		LogSink(Callback callback)
		 : _callback(callback)
		 , _prev_callback(nullptr)
		 , _prev_context(nullptr)
		{
			// get the previous callback
			void* _tmp_ptr = nullptr;
			OGLPLUS_GLFUNC(GetPointerv)(
				GL_DEBUG_CALLBACK_FUNCTION_ARB,
				&_tmp_ptr
			);
			AssertNoError(OGLPLUS_ERROR_INFO(GetPointerv));
			// TODO: this might be a problem
			_prev_callback = reinterpret_cast<GLDEBUGPROCARB>(_tmp_ptr);

			//get the previous context
			OGLPLUS_GLFUNC(GetPointerv)(
				GL_DEBUG_CALLBACK_USER_PARAM_ARB,
				&_prev_context
			);
			AssertNoError(OGLPLUS_ERROR_INFO(GetPointerv));

			OGLPLUS_GLFUNC(DebugMessageCallbackARB)(
				&LogSink::_gl_debug_proc,
				static_cast<void*>(this)
			);
			AssertNoError(
				OGLPLUS_ERROR_INFO(DebugMessageCallbackARB)
			);
			_initialized = true;
		}

		/// LogSinks are not copyable
		LogSink(const LogSink&) = delete;

		/// LogSinks are movable
		LogSink(LogSink&& temp)
		 : _callback(temp._callback)
		 , _prev_callback(temp._prev_callback)
		 , _prev_context(temp._prev_context)
		 , _initialized(temp._initialized)
		{
			temp._prev_callback = nullptr;
			temp._prev_context  = nullptr;
			temp._initialized = false;
		}

		/// Restores the previous callback and its context
		~LogSink(void)
		{
			if(_initialized)
			{
				OGLPLUS_GLFUNC(DebugMessageCallbackARB)(
					_prev_callback,
					_prev_context
				);
			}
		}
	};

	/// Installs a callback handling debug output
	static LogSink Install(Callback callback)
	{
		return std::move(LogSink(callback));
	}

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
