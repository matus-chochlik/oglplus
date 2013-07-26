/**
 *  @file oglplus/ext/ARB_debug_output.hpp
 *  @brief Wrapper for the ARB_debug_output extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_ARB_DEBUG_OUTPUT_1203031902_HPP
#define OGLPLUS_EXT_ARB_DEBUG_OUTPUT_1203031902_HPP

#include <oglplus/config.hpp>
#include <oglplus/extension.hpp>
#include <oglplus/string.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/enumerations.hpp>

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
OGLPLUS_ENUM_CLASS_BEGIN(DebugOutputARBSeverity, GLenum)
#include <oglplus/enums/ext/debug_output_severity.ipp>
OGLPLUS_ENUM_CLASS_END(DebugOutputARBSeverity)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/debug_output_severity_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/debug_output_severity_range.ipp>
#endif


/// Debug output source enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{ARB,debug_output}
 */
OGLPLUS_ENUM_CLASS_BEGIN(DebugOutputARBSource, GLenum)
#include <oglplus/enums/ext/debug_output_source.ipp>
OGLPLUS_ENUM_CLASS_END(DebugOutputARBSource)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/debug_output_source_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/debug_output_source_range.ipp>
#endif


/// Debug output type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{ARB,debug_output}
 */
OGLPLUS_ENUM_CLASS_BEGIN(DebugOutputARBType, GLenum)
#include <oglplus/enums/ext/debug_output_type.ipp>
OGLPLUS_ENUM_CLASS_END(DebugOutputARBType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/debug_output_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/debug_output_type_range.ipp>
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_debug_output


/// Wrapper for the ARB_debug_output extension
/**
 *  @glsymbols
 *  @glextref{ARB,debug_output}
 *
 *  @ingroup gl_extensions
 */
class ARB_debug_output
{
public:
	OGLPLUS_EXTENSION_CLASS(ARB, debug_output)

	/// Enables/disables messages with specific parameters
	static void Control(
		DebugOutputARBSource source,
		DebugOutputARBType type,
		DebugOutputARBSeverity severity,
		bool enable
	)
	{
		OGLPLUS_GLFUNC(DebugMessageControlARB)(
			GLenum(source),
			GLenum(type),
			GLenum(severity),
			0, nullptr,
			enable ? GL_TRUE : GL_FALSE
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DebugMessageControlARB));
	}

	/// Structure containing data passed to Callback functor
	struct CallbackData
	{
		DebugOutputARBSource source;
		DebugOutputARBType type;
		GLuint id;
		DebugOutputARBSeverity severity;
		GLsizei length;
		const GLchar* message;
	};

	/// Type of a callback functor processing debug output
	typedef std::function<void (const CallbackData&)> Callback;

	/// Installs a custom callback processing the debug output
	/**
	 *  Instances of this class install a new Callback function
	 *  processing the debug output messages in the constructor
	 *  and restoring the previous callback when destroyed.
	 */
	class LogSink
	{
	private:
		static void GLAPIENTRY _gl_debug_proc(
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
				CallbackData data;
				data.source = DebugOutputARBSource(source);
				data.type = DebugOutputARBType(type);
				data.id = id;
				data.severity = DebugOutputARBSeverity(severity);
				data.length = length;
				data.message = message;
				self->_callback(data);
			}
		}

		Callback _callback;
		GLDEBUGPROCARB _prev_callback;
		void* _prev_context;
	public:
		/// Installs the @p callback and remembers the previous
		LogSink(Callback callback)
		 : _callback(callback)
		 , _prev_callback(nullptr)
		 , _prev_context(nullptr)
		{
			// get the previous callback
			GLDEBUGPROCARB _tmp_callback = nullptr;
			void** _tmp_ptr=reinterpret_cast<void**>(&_tmp_callback);
			OGLPLUS_GLFUNC(GetPointerv)(
				GL_DEBUG_CALLBACK_FUNCTION_ARB,
				_tmp_ptr
			);
			OGLPLUS_IGNORE(OGLPLUS_ERROR_INFO(GetPointerv));
			_prev_callback = _tmp_callback;

			//get the previous context
			OGLPLUS_GLFUNC(GetPointerv)(
				GL_DEBUG_CALLBACK_USER_PARAM_ARB,
				&_prev_context
			);
			OGLPLUS_IGNORE(OGLPLUS_ERROR_INFO(GetPointerv));

			OGLPLUS_GLFUNC(DebugMessageCallbackARB)(
				&LogSink::_gl_debug_proc,
				static_cast<void*>(this)
			);
			OGLPLUS_VERIFY(
				OGLPLUS_ERROR_INFO(DebugMessageCallbackARB)
			);
		}

#if !OGLPLUS_NO_DELETED_FUNCTIONS
		/// LogSinks are not copyable
		LogSink(const LogSink&) = delete;
#else
	private:
		LogSink(const LogSink&);
	public:
#endif

		/// Restores the previous callback and its context
		~LogSink(void)
		{
			if(_prev_callback)
			{
				OGLPLUS_GLFUNC(DebugMessageCallbackARB)(
					_prev_callback,
					_prev_context
				);
			}
		}
	};

	/// Enables or disables synchronous debug output
	static void Synchronous(bool enable)
	{
		if(enable)
		{
			OGLPLUS_GLFUNC(Enable)(
				GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB
			);
			OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Enable));
		}
		else
		{
			OGLPLUS_GLFUNC(Disable)(
				GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB
			);
			OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Disable));
		}
	}

	/// Inserts a new message into the debug output
	static void InsertMessage(
		DebugOutputARBSource source,
		DebugOutputARBType type,
		GLuint id,
		DebugOutputARBSeverity severity,
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DebugMessageInsertARB));
	}

	/// Inserts a new message into the debug output
	static void InsertMessage(
		DebugOutputARBSource source,
		DebugOutputARBType type,
		GLuint id,
		DebugOutputARBSeverity severity,
		const String& message
	)
	{
		OGLPLUS_GLFUNC(DebugMessageInsertARB)(
			GLenum(source),
			GLenum(type),
			id,
			GLenum(severity),
			message.size(),
			message.c_str()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DebugMessageInsertARB));
	}
};
#endif

} // namespace oglplus

#endif // include guard
