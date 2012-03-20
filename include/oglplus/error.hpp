/**
 *  @file oglplus/error.hpp
 *  @brief Declaration of OGLplus' exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_ERROR_1107121317_HPP
#define OGLPLUS_ERROR_1107121317_HPP

#include <oglplus/auxiliary/strings.hpp>
#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <stdexcept>
#include <cassert>
#include <list>
#include <map>

#if OGLPLUS_CUSTOM_ERROR_HANDLING
#include <stack>
#include <functional>
#endif

#define OGLPLUS_ERROR_INFO_CONTEXT(CONTEXT, CLASS) \
	static const char* _errinf_ctxt(void) \
	{ \
		return #CONTEXT; \
	} \
	static const char* _errinf_cls(void) \
	{ \
		return #CLASS; \
	}

#define OGLPLUS_ERROR_INFO_REUSE_CONTEXT(SOURCE) \
	using SOURCE::_errinf_ctxt; \
	using SOURCE::_errinf_cls;


// Define a macro that initializes the _glsym member of ErrorInfo
#if OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
#define OGLPLUS_ERROR_INFO_INIT_GLSYM(SYMBOL)
#else
#define OGLPLUS_ERROR_INFO_INIT_GLSYM(SYMBOL) , SYMBOL
#endif

// Define a macro that initializes the _file member of ErrorInfo
#if OGLPLUS_ERROR_INFO_NO_FILE
#define OGLPLUS_ERROR_INFO_INIT_FILE(FILEPATH)
#else
#define OGLPLUS_ERROR_INFO_INIT_FILE(FILEPATH) , FILEPATH
#endif

// Define a macro that initializes the _func member of ErrorInfo
#if OGLPLUS_ERROR_INFO_NO_FUNC
#define OGLPLUS_ERROR_INFO_INIT_FUNC(FUNC)
#else
#define OGLPLUS_ERROR_INFO_INIT_FUNC(FUNC) , FUNC
#endif

// Define a macro that initializes the _line member of ErrorInfo
#if OGLPLUS_ERROR_INFO_NO_LINE
#define OGLPLUS_ERROR_INFO_INIT_LINE(LINE)
#else
#define OGLPLUS_ERROR_INFO_INIT_LINE(LINE) , LINE
#endif

// Define a macro that initializes the _cls_name member of ErrorInfo
#if OGLPLUS_ERROR_INFO_NO_CLASS_NAME
#define OGLPLUS_ERROR_INFO_INIT_CLS_NAME(NAME)
#else
#define OGLPLUS_ERROR_INFO_INIT_CLS_NAME(NAME) , NAME
#endif

// Define a macro that initializes the _bind_tgt member of ErrorInfo
#if OGLPLUS_ERROR_INFO_NO_BIND_TARGET
#define OGLPLUS_ERROR_INFO_INIT_BIND_TGT(NAME)
#else
#define OGLPLUS_ERROR_INFO_INIT_BIND_TGT(NAME) , NAME
#endif

// Define a macro that initializes the description-related members of ErrorInfo
#if OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
#define OGLPLUS_ERROR_INFO_INIT_OBJ_DECS_FUNCS(GET, PURGE, NAME)
#else
#define OGLPLUS_ERROR_INFO_INIT_OBJ_DECS_FUNCS(GET, PURGE, NAME) \
	, GET, PURGE, GLuint(NAME)
#endif


#define OGLPLUS_ERROR_INFO(CONTEXT) \
oglplus::ErrorInfo(\
	sizeof(decltype(&gl ## CONTEXT)) \
	OGLPLUS_ERROR_INFO_INIT_GLSYM(#CONTEXT) \
	OGLPLUS_ERROR_INFO_INIT_FILE(__FILE__) \
	OGLPLUS_ERROR_INFO_INIT_FUNC(__FUNCTION__) \
	OGLPLUS_ERROR_INFO_INIT_LINE(__LINE__) \
	OGLPLUS_ERROR_INFO_INIT_CLS_NAME("") \
	OGLPLUS_ERROR_INFO_INIT_BIND_TGT("") \
	OGLPLUS_ERROR_INFO_INIT_OBJ_DECS_FUNCS(nullptr, nullptr, 0) \
)

#define OGLPLUS_LIMIT_ERROR_INFO(CONTEXT) \
oglplus::ErrorInfo(\
	sizeof(decltype(GL_ ## CONTEXT)) \
	OGLPLUS_ERROR_INFO_INIT_GLSYM(#CONTEXT) \
	OGLPLUS_ERROR_INFO_INIT_FILE(__FILE__) \
	OGLPLUS_ERROR_INFO_INIT_FUNC(__FUNCTION__) \
	OGLPLUS_ERROR_INFO_INIT_LINE(__LINE__) \
	OGLPLUS_ERROR_INFO_INIT_CLS_NAME("") \
	OGLPLUS_ERROR_INFO_INIT_BIND_TGT("") \
	OGLPLUS_ERROR_INFO_INIT_OBJ_DECS_FUNCS(nullptr, nullptr, 0) \
)

#define OGLPLUS_ERROR_INFO_AUTO_CTXT() \
oglplus::ErrorInfo(\
	0 \
	OGLPLUS_ERROR_INFO_INIT_GLSYM(_errinf_ctxt()) \
	OGLPLUS_ERROR_INFO_INIT_FILE(__FILE__) \
	OGLPLUS_ERROR_INFO_INIT_FUNC(__FUNCTION__) \
	OGLPLUS_ERROR_INFO_INIT_LINE(__LINE__) \
	OGLPLUS_ERROR_INFO_INIT_CLS_NAME(_errinf_cls())  \
	OGLPLUS_ERROR_INFO_INIT_BIND_TGT("") \
	OGLPLUS_ERROR_INFO_INIT_OBJ_DECS_FUNCS(nullptr, nullptr, 0) \
)

#define OGLPLUS_ERROR_INFO_STR(CONTEXT_STR) \
oglplus::ErrorInfo(\
	0 \
	OGLPLUS_ERROR_INFO_INIT_GLSYM(CONTEXT_STR) \
	OGLPLUS_ERROR_INFO_INIT_FILE(__FILE__) \
	OGLPLUS_ERROR_INFO_INIT_FUNC(__FUNCTION__) \
	OGLPLUS_ERROR_INFO_INIT_LINE(__LINE__) \
	OGLPLUS_ERROR_INFO_INIT_CLS_NAME("") \
	OGLPLUS_ERROR_INFO_INIT_BIND_TGT("") \
	OGLPLUS_ERROR_INFO_INIT_OBJ_DECS_FUNCS(nullptr, nullptr, 0) \
)

#define OGLPLUS_OBJECT_ERROR_INFO(CONTEXT, CLASS, TARGET_NAME, NAME) \
oglplus::ErrorInfo(\
	sizeof(decltype(&gl ## CONTEXT)) \
	OGLPLUS_ERROR_INFO_INIT_GLSYM(#CONTEXT) \
	OGLPLUS_ERROR_INFO_INIT_FILE(__FILE__) \
	OGLPLUS_ERROR_INFO_INIT_FUNC(__FUNCTION__) \
	OGLPLUS_ERROR_INFO_INIT_LINE(__LINE__) \
	OGLPLUS_ERROR_INFO_INIT_CLS_NAME(#CLASS) \
	OGLPLUS_ERROR_INFO_INIT_BIND_TGT(TARGET_NAME) \
	OGLPLUS_ERROR_INFO_INIT_OBJ_DECS_FUNCS( \
		&oglplus::aux::ObjectDescRegistry<CLASS##Ops>::_get_desc, \
		&oglplus::aux::ObjectDescRegistry<CLASS##Ops>::_purge_archive,\
		NAME \
	) \
)

namespace oglplus {

/** @defgroup error_handling Error handling
 *
 *  The exception classes listed below provide information about errors
 *  that occur during the excecution of the OpenGL function calls in the
 *  @OGLplus wrappers.
 */

/// Basic information about exception's throw site and propagation trace points
/**
 *  @see ErrorGLSymbol
 *  @see ErrorFunc
 *  @see ErrorFile
 *  @see ErrorLine
 *  @see ErrorObjectDescription
 *
 *  @ingroup error_handling
 */
struct ErrorInfo
{
	// the data members of this structure are internal
	// implementation details which are subject to change
	// without any prior notice. Do not use directly.

	const size_t _dummy;

#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
	const char* _glsym;
#endif

#if !OGLPLUS_ERROR_INFO_NO_FILE
	const char* _file;
#endif

#if !OGLPLUS_ERROR_INFO_NO_FUNC
	const char* _func;
#endif

#if !OGLPLUS_ERROR_INFO_NO_LINE
	const unsigned _line;
#endif

#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
	const char* _cls_name;
#endif

#if !OGLPLUS_ERROR_INFO_NO_BIND_TARGET
	const char* _bind_tgt;
#endif

#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
	const String& (*_get_obj_desc)(GLuint);
	void (*_purge_archive)(void);
	GLuint _obj_name;
#endif

	inline ErrorInfo(
		const size_t dummy
#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
		, const char* glsym
#endif

#if !OGLPLUS_ERROR_INFO_NO_FILE
		, const char* file
#endif

#if !OGLPLUS_ERROR_INFO_NO_FUNC
		, const char* func
#endif

#if !OGLPLUS_ERROR_INFO_NO_LINE
		, const unsigned line
#endif

#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
		, const char* cls_name
#endif

#if !OGLPLUS_ERROR_INFO_NO_BIND_TARGET
		, const char* bind_tgt
#endif

#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
		, const String& (*get_obj_desc)(GLuint)
		, void (*purge_archive)(void)
		, GLuint obj_name
#endif
	): _dummy(dummy)

#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
	 , _glsym(glsym)
#endif

#if !OGLPLUS_ERROR_INFO_NO_FILE
	 , _file(file)
#endif

#if !OGLPLUS_ERROR_INFO_NO_FUNC
	 , _func(func)
#endif

#if !OGLPLUS_ERROR_INFO_NO_LINE
	 , _line(line)
#endif

#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
	 , _cls_name(cls_name)
#endif

#if !OGLPLUS_ERROR_INFO_NO_BIND_TARGET
	 , _bind_tgt(bind_tgt)
#endif

#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
	 , _get_obj_desc(get_obj_desc)
	 , _purge_archive(purge_archive)
	 , _obj_name(obj_name)
#endif
	{ }
};

/// Returns the name of the symbol or constant related to the error
/** This function returns the name of the failed OpenGL function
 *  without the gl prefix in case of a function error or the name
 *  of the OpenGL constant (usually a implementation-dependent) limit
 *  which are related to the error.
 *
 *  The result of this function is also influenced by the
 *  #OGLPLUS_ERROR_INFO_NO_GL_SYMBOL preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns an empty C string.
 *
 *  @see ErrorInfo
 *  @see ErrorFunc()
 *  @see ErrorFile()
 *  @see ErrorLine()
 *  @see ErrorClassName()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline const char* ErrorGLSymbol(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
	return info._glsym;
#else
	return "";
#endif
}

/// Returns the path of the source file where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #OGLPLUS_ERROR_INFO_NO_FILE preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns an empty C string.
 *
 *  @see ErrorInfo
 *  @see ErrorGLSymbol()
 *  @see ErrorFunc()
 *  @see ErrorLine()
 *  @see ErrorClassName()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline const char* ErrorFile(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_FILE
	return info._file;
#else
	return "";
#endif
}

/// Returns the name of the function where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #OGLPLUS_ERROR_INFO_NO_FUNC preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns an empty C string.
 *
 *  @see ErrorInfo
 *  @see ErrorGLSymbol()
 *  @see ErrorFile()
 *  @see ErrorLine()
 *  @see ErrorClassName()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline const char* ErrorFunc(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_FUNC
	return info._func;
#else
	return "";
#endif
}

/// Returns the line in the source file where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #OGLPLUS_ERROR_INFO_NO_LINE preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns zero.
 *
 *  @see ErrorInfo
 *  @see ErrorGLSymbol()
 *  @see ErrorFile()
 *  @see ErrorFunc()
 *  @see ErrorClassName()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline unsigned ErrorLine(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_LINE
	return info._line;
#else
	return 0;
#endif
}

/// Returns the name of the class of the object where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #OGLPLUS_ERROR_INFO_NO_CLASS_NAME preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns the string "UnknownClass".
 *
 *  @see ErrorInfo
 *  @see ErrorGLSymbol()
 *  @see ErrorFile()
 *  @see ErrorFunc()
 *  @see ErrorLine()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline const char* ErrorClassName(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_CLASS_NAME
	return (info._cls_name && *info._cls_name) ?
		info._cls_name :
		"UnknownClass";
#else
	return "UnknownClass";
#endif
}

/// Returns the name of the binding point the object where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #OGLPLUS_ERROR_INFO_NO_BIND_TARGET preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns the string "UnknownTarget".
 *
 *  @see ErrorInfo
 *  @see ErrorGLSymbol()
 *  @see ErrorFile()
 *  @see ErrorFunc()
 *  @see ErrorLine()
 *  @see ErrorClassName()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline const char* ErrorBindTarget(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_BIND_TARGET
	return (info._bind_tgt && *info._bind_tgt) ?
		info._bind_tgt :
		"UnknownTarget";
#else
	return "UnknownTarget";
#endif
}

/// Returns the optional description of the object related to the error
/**
 *  The result of this function is also influenced by the
 *  #OGLPLUS_ERROR_INFO_NO_OBJECT_DESC preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns an empty string.
 *
 *  @see ErrorInfo
 *  @see ErrorGLSymbol()
 *  @see ErrorFile()
 *  @see ErrorFunc()
 *  @see ErrorLine()
 *  @see ErrorClassName()
 *  @see ErrorBindTarget()
 *
 *  @ingroup error_handling
 */
inline const String& ErrorObjectDescription(const ErrorInfo& info)
{
#if !OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
	if((info._get_obj_desc != 0) && (info._obj_name != 0))
		return info._get_obj_desc(info._obj_name);
#endif
	return aux::EmptyString();
}

/// Exception class for general OpenGL errors
/** Instances of this exception class are throws whenever an error is detected
 *  during the execution of OpenGL API calls in the @OGLplus code. There are several
 *  other classes derived for more specific error types, like GL shading language
 *  compilation and linking errors, out-of-memory errors, etc.
 *  This class is derived from the standard runtime_error exception and thus
 *  the basic error message can be obtained by calling its @c what() member function.
 *
 *  @ingroup error_handling
 */
class Error
 : public std::runtime_error
{
public:
	typedef std::map<String, String> PropertyMap;
	typedef std::list<ErrorInfo> PropagationInfoList;
private:
	GLenum _code;
	ErrorInfo _info;
	PropertyMap _properties;
	PropagationInfoList  _propagation;
public:
	Error(GLenum code, const char* desc, const ErrorInfo& info)
	 : std::runtime_error(desc)
	 , _code(code)
	 , _info(info)
	{ }

	Error(
		GLenum code,
		const char* desc,
		const ErrorInfo& info,
		PropertyMap&& properties
	): std::runtime_error(desc)
	 , _code(code)
	 , _info(info)
	 , _properties(std::move(properties))
	{ }

	inline ~Error(void) throw()
	{ }

	/// Returns the OpenGL error code
	/** This is basically the value of error code returned by the glGetError
	 *  functions.
	 *
	 *  @see ThrowInfo
	 *  @see File
	 *  @see Func
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	GLenum Code(void) const
	{
		return _code;
	}

	/// Returns information about the throw site of the exception
	/**
	 *  @see GLSymbol
	 *  @see Code
	 *  @see File
	 *  @see Func
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const ErrorInfo& ThrowInfo(void) const
	{
		return _info;
	}

	/// Returns the name of the symbol or constant related to the error
	/** This function returns the name of the failed OpenGL function
	 *  without the gl prefix in case of a function error or the name
	 *  of the OpenGL constant (usually a implementation-dependent) limit
	 *  which are related to the error.
	 *
	 *  @see ThrowInfo
	 *  @see Code
	 *  @see Func
	 *  @see File
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const char* GLSymbol(void) const
	{
		return ::oglplus::ErrorGLSymbol(_info);
	}

	/// Returns the path of the source file where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see GLSymbol
	 *  @see Code
	 *  @see Func
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const char* File(void) const
	{
		return ::oglplus::ErrorFile(_info);
	}

	/// Returns the name of the function where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see GLSymbol
	 *  @see Code
	 *  @see File
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const char* Func(void) const
	{
		return ::oglplus::ErrorFunc(_info);
	}

	/// Returns the line in the source file where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see GLSymbol
	 *  @see Code
	 *  @see File
	 *  @see Func
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	unsigned Line(void) const
	{
		return ::oglplus::ErrorLine(_info);
	}

	/// Returns the class name of the object that caused the exception
	const char* ClassName(void) const
	{
		return ::oglplus::ErrorClassName(_info);
	}

	/// Returns the name of the binding point that caused the exception
	const char* BindTarget(void) const
	{
		return ::oglplus::ErrorBindTarget(_info);
	}

	/// Returns the description of the object that caused the exception
	const String& ObjectDescription(void) const
	{
		return ::oglplus::ErrorObjectDescription(_info);
	}

	/// Returns the properties of the exception
	const PropertyMap& Properties(void) const
	{
		return _properties;
	}

	/// Set a property key/value to the exception
	void SetPropertyValue(const String& key, const String& value)
	{
		_properties[key] = value;
	}

	const PropagationInfoList& PropagationInfo(void) const
	{
		return _propagation;
	}

	Error& Trace(const ErrorInfo& info)
	{
		_propagation.push_back(info);
		throw;
	}

	void Cleanup(void) const
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
};

/// Exception class for out-of-memory OpenGL errors
/** Out-of-memory is a very serious error and applications generally should not
 *  try to recover from such errors, but terminate gracefully if possible.
 *
 *  @ingroup error_handling
 */
class OutOfMemory
 : public Error
{
public:
	OutOfMemory(GLenum code, const char* desc, const ErrorInfo& info)
	 : Error(code, desc, info)
	{ }
};

/// Exception for exceeding implementation-defined limits
/** Instances of this class are thrown if an instance of a (usually unsigned
 *  integer) type is assigned a value that it is outside of a implementation
 *  dependent range. This includes things like limits on the number of texture
 *  units of the GPU, the maximum texture dimensions, maximum number of draw
 *  buffers, vertex attributes, etc.
 *
 *  @ingroup error_handling
 */
class LimitError
 : public Error
{
private:
	GLuint _value;
	GLuint _limit;
public:
	LimitError(GLuint value, GLuint limit, const ErrorInfo& info)
	 : Error(
		GL_INVALID_VALUE,
		"OpenGL limited value out of range",
		info
	), _value(value)
	 , _limit(limit)
	{ }

	/// The value assigned to the limited-type variable
	GLuint Value(void) const
	{
		return _value;
	}

	/// The allowed limit of the limited-type
	GLuint Limit(void) const
	{
		return _limit;
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY || OGLPLUS_CUSTOM_ERROR_HANDLING

/// Structure containing all error-related data; Used in custom error handlers
/**
 *  Available only if the #OGLPLUS_CUSTOM_ERROR_HANDLING compile-time switch
 *  is set to a nonzero value.
 *
 *  @ingroup error_handling
 */
struct ErrorData
{
private:
	GLenum _error_code;
	GLuint _value;
	GLuint _limit;
	const char* _message;
	ErrorInfo _info;
	Error::PropertyMap _properties;
	bool _assertion;
	bool _fatal_error;
	bool _build_error;
	bool _limit_error;
public:
	/// The OpenGL error code
	inline GLenum ErrorCode(void) const
	{
		return _error_code;
	}

	/// The invalid value that caused a limit error
	inline GLuint Value(void) const
	{
		return _value;
	}

	/// The limited value limit
	inline GLuint Limit(void) const
	{
		return _limit;
	}

	/// The error message
	/** The returned pointer should not be used when its ErrorData instance
	 *  goes out of scope. If this is necessary the string should be copied.
	 */
	inline const char* Message(void) const
	{
		return _message;
	}

	/// Additional error info
	inline const ErrorInfo& Info(void) const
	{
		return _info;
	}

	/// Additional error property (key/values)
	inline const Error::PropertyMap& Properties(void) const
	{
		return _properties;
	}

	/// Indicates that an assertion has failed
	inline bool Assertion(void) const
	{
		return _assertion;
	}

	/// Indicates a fatal (very severe) error like (out of memory)
	inline bool FatalError(void) const
	{
		return _fatal_error;
	}

	/// Indicates a build error
	inline bool BuildError(void) const
	{
		return _build_error;
	}

	/// Indicates a limited value error
	inline bool LimitError(void) const
	{
		return _limit_error;
	}

	inline ErrorData(
		GLenum error_code,
		GLuint value,
		GLuint limit,
		const char* message,
		const ErrorInfo& info,
		Error::PropertyMap&& properties,
		bool assertion,
		bool fatal_error,
		bool build_error,
		bool limit_error
	): _error_code(error_code)
	 , _value(value)
	 , _limit(limit)
	 , _message(message)
	 , _info(info)
	 , _properties(properties)
	 , _assertion(assertion)
	 , _fatal_error(fatal_error)
	 , _build_error(build_error)
	 , _limit_error(limit_error)
	{ }
};

/// Type of installable custom error handler functor
/**
 *  Available only if the #OGLPLUS_CUSTOM_ERROR_HANDLING compile-time switch
 *  is set to a nonzero value.
 *
 *  @ingroup error_handling
 */
typedef std::function<bool (const ErrorData&)> ErrorHandlerFunc;

namespace aux {

inline std::stack<ErrorHandlerFunc>& _error_handlers(void)
{
	static std::stack<ErrorHandlerFunc> _handlers;
	return _handlers;
}

inline bool _has_error_handler(void)
{
	return !_error_handlers().empty();
}

inline ErrorHandlerFunc& _get_error_handler(void)
{
	assert(!_error_handlers().empty());
	return _error_handlers().top();
}

} // namespace aux

/// A RAII class installing a temporary custom error handler
/**
 *  Available only if the #OGLPLUS_CUSTOM_ERROR_HANDLING compile-time switch
 *  is set to a nonzero value.
 *
 *  @ingroup error_handling
 */
class LocalErrorHandler
{
private:
	size_t _installed;
public:
	/// Installs the specified error @p handler
	LocalErrorHandler(ErrorHandlerFunc handler)
	{
		aux::_error_handlers().push(handler);
		_installed = aux::_error_handlers().size();
	}

	/// This class is non-copyable
	LocalErrorHandler(const LocalErrorHandler&) = delete;

	/// Uninstalls the previously installed handler
	~LocalErrorHandler(void)
	{
		if(_installed)
		{
			assert(aux::_error_handlers().size() == _installed);
			aux::_error_handlers().pop();
		}
	}
};

#endif // OGLPLUS_CUSTOM_ERROR_HANDLING

template <class Exception>
inline void HandleBuildError(const String& msg, const ErrorInfo& info)
{
#if OGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			GL_INVALID_OPERATION,
			0, 0,
			msg.c_str(),
			info,
			Error::PropertyMap(),
			false,
			false,
			true,
			false
		)
	)) return;
#endif // OGLPLUS_CUSTOM_ERROR_HANDLING
	throw Exception(msg, info);
}

template <class Exception>
inline void HandleLimitError(GLuint value, GLuint limit, const ErrorInfo& info)
{
#if OGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			GL_INVALID_VALUE,
			value, limit,
			"OpenGL limited value out of range",
			info,
			Error::PropertyMap(),
			false,
			false,
			false,
			true
		)
	)) return;
#endif // OGLPLUS_CUSTOM_ERROR_HANDLING
	throw Exception(value, limit, info);
}

inline void HandleError(
	GLenum code,
	const GLchar* msg,
	const ErrorInfo& info,
	Error::PropertyMap&& properties
)
{
#if OGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			GL_INVALID_OPERATION,
			0, 0,
			msg,
			info,
			std::forward<Error::PropertyMap>(properties),
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
		std::forward<Error::PropertyMap>(properties)
	);
}

inline void HandleError(GLenum code, const ErrorInfo& info, bool assertion)
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

#ifdef GL_STACK_OVERFLOW
		case GL_STACK_OVERFLOW:
			msg = "Stack overflow";
#endif

#ifdef GL_STACK_UNDERFLOW
		case GL_STACK_UNDERFLOW:
			msg = "Stack underflow";
#endif

#ifdef GL_TABLE_TOO_LARGE
		case GL_TABLE_TOO_LARGE:
			msg = "Table too large";
#endif
			break;
	}
#if OGLPLUS_CUSTOM_ERROR_HANDLING
	if(aux::_has_error_handler() && aux::_get_error_handler()(
		ErrorData(
			GL_INVALID_OPERATION,
			0, 0,
			msg,
			info,
			Error::PropertyMap(),
			assertion,
			code == GL_OUT_OF_MEMORY,
			false,
			false
		)
	)) return;
#endif // OGLPLUS_CUSTOM_ERROR_HANDLING
	throw Error(code, msg, info);
}

#ifndef OGLPLUS_IS_ERROR
/// This macro decides if error handling should be done
/** The @p EXPRESSION parameter is a boolean expression
 *  and true values indicate an error condition. If this
 *  macro returns a false expression any error handling
 *  is skipped.
 */
#define OGLPLUS_IS_ERROR(EXPRESSION) (EXPRESSION)
#endif

inline void HandleIfError(const ErrorInfo& info)
{
	GLenum code = OGLPLUS_GLFUNC(GetError)();
	if(code != GL_NO_ERROR)
		HandleError(code, info, false);
}

#ifndef OGLPLUS_CHECK
/// Macro checking and possibly handling run-time errors in previous call to GL
/** This macro is called immediatelly after calls to GL functions
 *  that may fail due to invalid values of run-time parameters.
 */
#define OGLPLUS_CHECK(PARAM) HandleIfError(PARAM)
#endif

inline void AssertNoError(const ErrorInfo& info)
{
	GLenum code = OGLPLUS_GLFUNC(GetError)();
	if(code != GL_NO_ERROR)
		HandleError(code, info, true);
}

#ifndef OGLPLUS_VERIFY
/// Macro asserting that no errors occured in prevous call to GL
/** This macro is called immediatelly after calls to GL functions
 *  that "should not" fail and if they do fail it indicates
 *  a program logic error that is not dependent on run-time parameters.
 */
#define OGLPLUS_VERIFY(PARAM) AssertNoError(PARAM)
#endif

} // namespace oglplus

#endif // include guard
