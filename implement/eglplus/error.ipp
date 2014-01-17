/**
 *  @file eglplus/error.ipp
 *  @brief Implementation of EGLplus' exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if EGLPLUS_CUSTOM_ERROR_HANDLING
#include <stack>
#endif

namespace eglplus {

#if EGLPLUS_CUSTOM_ERROR_HANDLING

namespace aux {

EGLPLUS_LIB_FUNC
std::stack<ErrorHandlerFunc>& _error_handlers(void)
{
	static std::stack<ErrorHandlerFunc> _handlers;
	return _handlers;
}

EGLPLUS_LIB_FUNC
bool _has_error_handler(void)
{
	return !_error_handlers().empty();
}

EGLPLUS_LIB_FUNC
ErrorHandlerFunc& _get_error_handler(void)
{
	assert(!_error_handlers().empty());
	return _error_handlers().top();
}

} // namespace aux

EGLPLUS_LIB_FUNC
LocalErrorHandler::LocalErrorHandler(ErrorHandlerFunc handler)
{
	aux::_error_handlers().push(handler);
	_installed = aux::_error_handlers().size();
}

EGLPLUS_LIB_FUNC
LocalErrorHandler::~LocalErrorHandler(void)
{
	if(_installed)
	{
		assert(aux::_error_handlers().size() == _installed);
		aux::_error_handlers().pop();
	}
}

#endif // EGLPLUS_CUSTOM_ERROR_HANDLING

EGLPLUS_LIB_FUNC
void HandleError(
	EGLint code,
	const char* msg,
	const ErrorInfo& info,
	bool assertion
)
{
#if EGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			code,
			msg,
			info,
			assertion,
			code == EGL_OUT_OF_MEMORY,
			false,
			false
		)
	)) return;
#endif // EGLPLUS_CUSTOM_ERROR_HANDLING
	throw Error(code, msg?msg:"Unknown error", info, assertion);
}

EGLPLUS_LIB_FUNC
void HandleEGLError(EGLint code, const ErrorInfo& info, bool assertion)
{
	const char* msg = nullptr;
	switch(code)
	{
		case EGL_NOT_INITIALIZED:
			msg =	"EGL is not initialized or could "
				"not be initialized";
			break;
		case EGL_BAD_ACCESS:
			msg =	"EGL cannot access a requested resource";
			break;
		case EGL_BAD_ALLOC:
			msg =	"EGL failed to allocate resources for "
				"the requested operation.";
			break;
		case EGL_BAD_ATTRIBUTE:
			msg =	"An unrecognized attribute or attribute "
				"value was passed in an attribute list";
			break;
		case EGL_BAD_CONTEXT:
			msg =	"Argument does not name a valid EGLContext";
			break;
		case EGL_BAD_CONFIG:
			msg =	"Argument does not name a valid EGLConfig";
			break;
		case EGL_BAD_CURRENT_SURFACE:
			msg =	"The current surface of the calling thread is "
				"a window, pbuffer, or pixmap that is no longer "
				"valid";
			break;
		case EGL_BAD_DISPLAY:
			msg = "Argument does not name a valid EGLDisplay";
			break;
		case EGL_BAD_SURFACE:
			msg =	"Argument does not name a valid surface (window, "
				"pbuffer, or pixmap) configured for rendering";
			break;
		case EGL_BAD_MATCH:
			msg =	"Arguments are inconsistent";
			break;
		case EGL_BAD_PARAMETER:
			msg =	"One or more argument values are invalid";
			break;
		case EGL_BAD_NATIVE_PIXMAP:
			msg =	"Argument does not refer to a valid native "
				"pixmap";
			break;
		case EGL_BAD_NATIVE_WINDOW:
			msg =	"argument does not refer to a valid native "
				"window";
			break;
		case EGL_CONTEXT_LOST:
			msg =	"A power management event has occurred, the "
				"previously current EGL context is lost";
			break;
		default:
			msg = "Unknown EGL error";
	}
	HandleError(code, msg, info, assertion);
}

} // namespace eglplus

