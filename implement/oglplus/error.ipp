/**
 *  @file oglplus/error.ipp
 *  @brief Implementation of Error / exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

#if OGLPLUS_CUSTOM_ERROR_HANDLING

namespace aux {

OGLPLUS_LIB_FUNC
std::stack<ErrorHandlerFunc>& _error_handlers(void)
{
	static std::stack<ErrorHandlerFunc> _handlers;
	return _handlers;
}

} // namespace aux

#endif // OGLPLUS_CUSTOM_ERROR_HANDLING

OGLPLUS_LIB_FUNC
void HandleShaderVariableError(
	GLenum code,
	GLint location,
	const GLchar* msg,
	const ErrorInfo& info,
	Error::PropertyMapInit&& properties
)
{
#if OGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			code,
			0u, 0u,
			msg,
			info,
			Error::PropertyMapInit(),
			false,
			false,
			false,
			false
		)
	)) return;
#endif // OGLPLUS_CUSTOM_ERROR_HANDLING
	throw ShaderVariableError(
		code,
		location,
		msg,
		info,
		std::move(properties)
	);
}

OGLPLUS_LIB_FUNC
void HandleLimitError(GLuint value, GLuint limit, const ErrorInfo& info)
{
	const GLchar* msg = "OpenGL limited value out of range";
#if OGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			GL_INVALID_VALUE,
			value, limit,
			msg,
			info,
			Error::PropertyMapInit(),
			false,
			false,
			false,
			true
		)
	)) return;
#endif // OGLPLUS_CUSTOM_ERROR_HANDLING
	throw LimitError(value, limit, msg, info);
}

#if !OGLPLUS_NO_VARIADIC_TEMPLATES && !OGLPLUS_NO_GLFUNC_CHECKS
OGLPLUS_LIB_FUNC
void HandleMissingFunction(const ErrorInfo& info)
{
	const GLenum code = GL_INVALID_VALUE;
	const char* msg = "Function called through an invalid pointer";
#if OGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			code,
			0u, 0u,
			msg,
			info,
			Error::PropertyMapInit(),
			true,
			true,
			false,
			false
		)
	)) return;
#endif // OGLPLUS_CUSTOM_ERROR_HANDLING
	throw MissingFunction(code, msg, info);
}
#endif // OGLPLUS_NO_VARIADIC_TEMPLATES || OGLPLUS_NO_GLFUNC_CHECKS

OGLPLUS_LIB_FUNC
void HandleError(
	GLenum code,
	const GLchar* msg,
	const ErrorInfo& info,
	Error::PropertyMapInit&& properties
)
{
#if OGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			code,
			0, 0,
			msg,
			info,
			std::move(properties),
			false,
			code == GL_OUT_OF_MEMORY,
			false,
			false
		)
	)) return;
#endif // OGLPLUS_CUSTOM_ERROR_HANDLING
	throw Error(
		code,
		msg,
		info,
		std::move(properties)
	);
}

OGLPLUS_LIB_FUNC
void HandleError(GLenum code, const ErrorInfo& info, bool assertion)
{
	const GLchar* msg = "Unknown error";
	switch(code)
	{
		case GL_OUT_OF_MEMORY:
			msg = "OpenGL out of memory";
			break;
		case GL_INVALID_ENUM:
			msg = "Invalid OpenGL enum argument";
			break;
		case GL_INVALID_VALUE:
			msg = "OpenGL numeric argument out of range";
			break;
		case GL_INVALID_OPERATION:
			msg = "Invalid OpenGL operation";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			msg = "Invalid OpenGL framebuffer operation";
			break;

#ifdef GL_STACK_OVERFLOW
		case GL_STACK_OVERFLOW:
			msg = "Stack overflow";
			break;
#endif

#ifdef GL_STACK_UNDERFLOW
		case GL_STACK_UNDERFLOW:
			msg = "Stack underflow";
			break;
#endif

#ifdef GL_TABLE_TOO_LARGE
		case GL_TABLE_TOO_LARGE:
			msg = "Table too large";
			break;
#endif
	}
#if OGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			code,
			0, 0,
			msg,
			info,
			Error::PropertyMapInit(),
			assertion,
			code == GL_OUT_OF_MEMORY,
			false,
			false
		)
	)) return;
#endif // OGLPLUS_CUSTOM_ERROR_HANDLING
	throw Error(code, msg, info, assertion);
}

} // namespace oglplus

