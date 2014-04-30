/**
 *  @file oglplus/error.ipp
 *  @brief Implementation of Error / exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_CUSTOM_ERROR_HANDLING
#include <stack>
#endif

namespace oglplus {

OGLPLUS_LIB_FUNC
const char* ErrorGLSymbol(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
	return info._glsym;
#else
	return "";
#endif
}

OGLPLUS_LIB_FUNC
const char* ErrorFile(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_FILE
	return info._file;
#else
	OGLPLUS_FAKE_USE(info);
	return "";
#endif
}

OGLPLUS_LIB_FUNC
const char* ErrorFunc(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_FUNC
	return info._func;
#else
	OGLPLUS_FAKE_USE(info);
	return "";
#endif
}

OGLPLUS_LIB_FUNC
unsigned ErrorLine(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_LINE
	return info._line;
#else
	OGLPLUS_FAKE_USE(info);
	return 0;
#endif
}

OGLPLUS_LIB_FUNC
const char* ErrorClassName(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
	return (info._cls_name && *info._cls_name) ?
		info._cls_name :
		"UnknownClass";
#else
	OGLPLUS_FAKE_USE(info);
	return "UnknownClass";
#endif
}

OGLPLUS_LIB_FUNC
const char* ErrorBindTarget(const ErrorInfo& info)
{
	OGLPLUS_FAKE_USE(info);
	return
#if !OGLPLUS_ERROR_INFO_NO_BIND_TARGET
	(info._bind_tgt) ?
		info._bind_tgt.c_str() :
#endif
		"UnknownTarget";
}

OGLPLUS_LIB_FUNC
const String& ErrorObjectDescription(const ErrorInfo& info)
{
	OGLPLUS_FAKE_USE(info);
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
	if((info._get_obj_desc != 0) && (info._obj_name != 0))
		return info._get_obj_desc(info._obj_name);
#endif
	return EmptyString();
}

// -- Error --

OGLPLUS_LIB_FUNC
Error::Error(
	GLenum code,
	const char* desc,
	const ErrorInfo& info,
	bool assertion
): std::runtime_error(desc)
 , _code(code)
 , _info(info)
 , _assertion(assertion)
{ }

OGLPLUS_LIB_FUNC
Error::Error(
	GLenum code,
	const char* desc,
	const ErrorInfo& info,
	PropertyMapInit&& properties
): std::runtime_error(desc)
 , _code(code)
 , _info(info)
#if !OGLPLUS_ERROR_NO_PROPERTIES
 , _properties(std::move(properties))
#endif
 , _assertion(false)
{
#if OGLPLUS_ERROR_NO_PROPERTIES
	OGLPLUS_FAKE_USE(properties);
#endif
}

OGLPLUS_LIB_FUNC
void Error::SetPropertyValue(const String& key, const String& value)
{
#if !OGLPLUS_ERROR_NO_PROPERTIES
	_properties[key] = value;
#else
	OGLPLUS_FAKE_USE(key);
	OGLPLUS_FAKE_USE(value);
#endif
}

OGLPLUS_LIB_FUNC
void Error::Trace(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_NO_PROPAGATION_INFO
	_propagation.push_back(info);
#else
	OGLPLUS_FAKE_USE(info);
#endif
	throw;
}

OGLPLUS_LIB_FUNC
void Error::Cleanup(void) const
{
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
	if(_info._purge_archive != 0)
		_info._purge_archive();
	for(auto i=_propagation.begin(),e=_propagation.end();i!=e;++i)
	{
		if(i->_purge_archive != 0)
			i->_purge_archive();
	}
#endif
}


#if OGLPLUS_CUSTOM_ERROR_HANDLING

namespace aux {

OGLPLUS_LIB_FUNC
std::stack<ErrorHandlerFunc>& _error_handlers(void)
{
	static std::stack<ErrorHandlerFunc> _handlers;
	return _handlers;
}

OGLPLUS_LIB_FUNC
bool _has_error_handler(void)
{
	return !_error_handlers().empty();
}

OGLPLUS_LIB_FUNC
ErrorHandlerFunc& _get_error_handler(void)
{
	assert(!_error_handlers().empty());
	return _error_handlers().top();
}

} // namespace aux

OGLPLUS_LIB_FUNC
LocalErrorHandler::LocalErrorHandler(ErrorHandlerFunc handler)
{
	aux::_error_handlers().push(handler);
	_installed = aux::_error_handlers().size();
}

OGLPLUS_LIB_FUNC
LocalErrorHandler::~LocalErrorHandler(void)
{
	if(_installed)
	{
		assert(aux::_error_handlers().size() == _installed);
		aux::_error_handlers().pop();
	}
}

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

