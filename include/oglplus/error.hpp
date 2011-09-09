/**
 *  @file oglplus/error.hpp
 *  @brief Declaration of OGLplus' exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_ERROR_1107121317_HPP
#define OGLPLUS_ERROR_1107121317_HPP

#include <oglplus/auxiliary/strings.hpp>
#include <stdexcept>
#include <list>
#include <map>

#define OGLPLUS_ERROR_INFO_CONTEXT(CONTEXT) \
	static const char* _errinf_ctxt(void) \
	{ \
		return #CONTEXT; \
	}

#ifdef _NDEBUG
#define OGLPLUS_ERROR_INFO(CONTEXT) \
	{#CONTEXT, __FILE__, __FUNCTION__, __LINE__, 0, 0, 0, 0}

#define OGLPLUS_LIMIT_ERROR_INFO(CONTEXT) \
	{#CONTEXT, __FILE__, __FUNCTION__, __LINE__, 0, 0, 0, 0}

#define OGLPLUS_ERROR_INFO_AUTO_CTXT() \
	{errinf_ctxt(), __FILE__, __FUNCTION__, __LINE__, 0, 0, 0, 0}

#define OGLPLUS_ERROR_INFO_STR(CONTEXT_STR) \
	{CONTEXT_STR, __FILE__, __FUNCTION__, __LINE__, 0, 0, 0, 0}

#define OGLPLUS_OBJECT_ERROR_INFO(CONTEXT, OBJECT, NAME) \
	{#CONTEXT, __FILE__, __FUNCTION__, __LINE__, \
	#OBJECT, \
	&oglplus::aux::ObjectDescRegistry<OBJECT##Ops>::_get_desc, \
	&oglplus::aux::ObjectDescRegistry<OBJECT##Ops>::_purge_archive, \
	NAME }

#else
#define OGLPLUS_ERROR_INFO(CONTEXT) \
	{#CONTEXT, __FILE__, __FUNCTION__, __LINE__, 0, 0, 0, 0, \
	sizeof(decltype(&gl ## CONTEXT))}

#define OGLPLUS_LIMIT_ERROR_INFO(CONTEXT) \
	{#CONTEXT, __FILE__, __FUNCTION__, __LINE__, 0, 0, 0, 0, \
	sizeof(decltype(GL_ ## CONTEXT))}

#define OGLPLUS_ERROR_INFO_AUTO_CTXT(CONTEXT_STR) \
	{_errinf_ctxt(), __FILE__, __FUNCTION__, __LINE__, 0, 0, 0, 0, 0}

#define OGLPLUS_ERROR_INFO_STR(CONTEXT_STR) \
	{CONTEXT_STR, __FILE__, __FUNCTION__, __LINE__, 0, 0, 0, 0, 0}

#define OGLPLUS_OBJECT_ERROR_INFO(CONTEXT, OBJECT, NAME) \
	{#CONTEXT, __FILE__, __FUNCTION__, __LINE__, \
	#OBJECT, \
	&oglplus::aux::ObjectDescRegistry<OBJECT##Ops>::_get_desc, \
	&oglplus::aux::ObjectDescRegistry<OBJECT##Ops>::_purge_archive, \
	NAME, sizeof(decltype(&gl ## CONTEXT)) }

#endif


namespace oglplus {

/// Basic information about exception's throw site and propagation trace points
/**
 *  @see ErrorGLSymbol
 *  @see ErrorCode
 *  @see ErrorFunc
 *  @see ErrorFile
 *  @see ErrorLine
 *  @see ErrorObjectDescription
 */
struct ErrorInfo
{
	// the data members of this structure are internal
	// implementation details which are subject to change
	// without any prior notice. Do not use directly.
	const char* glsym;
	const char* file;
	const char* func;
	const unsigned line;

	const char* _cls_name;
	const std::string& (*_get_obj_desc)(GLuint);
	void (*_purge_archive)(void);
	GLuint _obj_name;
#ifndef _NDEBUG
	const size_t _dummy;
#endif
};

/// Returns the name of the symbol or constant related to the error
/** This function returns the name of the failed OpenGL function
 *  without the gl prefix in case of a function error or the name
 *  of the OpenGL constant (usually a implementation-dependent) limit
 *  which are related to the error.
 *
 *  @see ErrorInfo
 *  @see ErrorCode
 *  @see ErrorFunc
 *  @see ErrorFile
 *  @see ErrorLine
 *  @see ErrorClassName
 *  @see ErrorObjectDescription
 */
inline const char* ErrorGLSymbol(const ErrorInfo& info)
{
	return info.glsym;
}

/// Returns the path of the source file where the exception originated
/**
 *  @see ErrorInfo
 *  @see ErrorGLSymbol
 *  @see ErrorCode
 *  @see ErrorFunc
 *  @see ErrorLine
 *  @see ErrorClassName
 *  @see ErrorObjectDescription
 */
inline const char* ErrorFile(const ErrorInfo& info)
{
	return info.file;
}

/// Returns the name of the function where the exception originated
/**
 *  @see ErrorInfo
 *  @see ErrorGLSymbol
 *  @see ErrorCode
 *  @see ErrorName
 *  @see ErrorLine
 *  @see ErrorClassName
 *  @see ErrorObjectDescription
 */
inline const char* ErrorFunc(const ErrorInfo& info)
{
	return info.func;
}

/// Returns the line in the source file where the exception originated
/**
 *  @see ErrorInfo
 *  @see ErrorGLSymbol
 *  @see ErrorCode
 *  @see ErrorName
 *  @see ErrorFunc
 *  @see ErrorClassName
 *  @see ErrorObjectDescription
 */
inline unsigned ErrorLine(const ErrorInfo& info)
{
	return info.line;
}

/// Returns the name of the class of the object where the exception originated
/**
 *  @see ErrorInfo
 *  @see ErrorGLSymbol
 *  @see ErrorCode
 *  @see ErrorName
 *  @see ErrorFunc
 *  @see ErrorLine
 *  @see ErrorObjectDescription
 */
inline const char* ErrorClassName(const ErrorInfo& info)
{
	return info._cls_name ? info._cls_name : "UnknownClass";
}

/// Returns the optional description of the object related to the error
/**
 *  @see ErrorInfo
 *  @see ErrorGLSymbol
 *  @see ErrorCode
 *  @see ErrorName
 *  @see ErrorFunc
 *  @see ErrorLine
 *  @see ErrorClassName
 */
inline const std::string& ErrorObjectDescription(const ErrorInfo& info)
{
	if((info._get_obj_desc != 0) && (info._obj_name != 0))
		return info._get_obj_desc(info._obj_name);
	return aux::EmptyString();
}

/// Exception class for general OpenGL errors
/** Instances of this exception class are throws whenever an error is detected
 *  during the execution of OpenGL API calls in the OGLplus code. There are several
 *  other classes derived for more specific error types, like GL shading language
 *  compilation and linking errors, out-of-memory errors, etc.
 *  This class is derived from the standard runtime_error exception and thus
 *  the basic error message can be obtained by calling its @c what() member function.
 */
class Error
 : public std::runtime_error
{
public:
	typedef std::map<std::string, std::string> PropertyMap;
	typedef std::list<ErrorInfo> PropagationInfoList;
private:
	GLenum _code;
	ErrorInfo _info;
	PropertyMap _properties;
	PropagationInfoList  _propagation;
protected:
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

	friend void ThrowOnError(
		GLenum code,
		const GLchar* msg,
		const ErrorInfo& info,
		PropertyMap&& properties
	);
	friend void ThrowOnError(const ErrorInfo& info);
public:
	/// Returns the OpenGL error code
	/** This is basically the value of error code returned by the glGetError
	 *  functions.
	 *
	 *  @see ThrowInfo
	 *  @see File
	 *  @see Func
	 *  @see Line
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
	 *  @see Name
	 *  @see Line
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
	 *  @see Name
	 *  @see Func
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

	/// Returns the description of the object that caused the exception
	const std::string& ObjectDescription(void) const
	{
		return ::oglplus::ErrorObjectDescription(_info);
	}

	/// Returns the properties of the exception
	const PropertyMap& Properties(void) const
	{
		return _properties;
	}

	/// Set a property key/value to the exception
	void SetPropertyValue(const std::string& key, const std::string& value)
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
		if(_info._purge_archive != 0)
			_info._purge_archive();
		for(auto i=_propagation.begin(),e=_propagation.end();i!=e;++i)
		{
			if(i->_purge_archive != 0)
				i->_purge_archive();
		}
	}
};

/// Exception class for out-of-memory OpenGL errors
/** Out-of-memory is a very serious error and applications generally should not
 *  try to recover from such errors, but terminate gracefully if possible.
 */
class OutOfMemory
 : public Error
{
public:
	OutOfMemory(GLenum code, const char* desc, const ErrorInfo& info)
	 : Error(code, desc, info)
	{ }
};

inline void ThrowOnError(
	GLenum code,
	const GLchar* msg,
	const ErrorInfo& info,
	Error::PropertyMap&& properties
)
{
	throw Error(
		code,
		msg,
		info,
		std::forward<Error::PropertyMap>(properties)
	);
}

inline void ThrowOnError(const ErrorInfo& info)
{
	GLenum code = ::glGetError();
	if(code != GL_NO_ERROR)
	{
		const GLchar* msg = "Unknown error";
		switch(code)
		{
			case GL_OUT_OF_MEMORY:
				msg = "OpenGL out of memory";
				throw OutOfMemory(code, msg, info);
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
		}
		throw Error(code, msg, info);
	}
}

inline void AssertNoError(const ErrorInfo& info)
{
	//TODO make this compile-time configurable
	ThrowOnError(info);
}


// Exception for exceeding implementation-defined limits
class LimitError
 : public Error
{
private:
	GLuint _value;
	GLuint _limit;
public:
	LimitError(const ErrorInfo& info, GLuint value, GLuint limit)
	 : Error(
		GL_INVALID_VALUE,
		"OpenGL limited value out of range",
		info
	), _value(value)
	 , _limit(limit)
	{ }

	GLuint Value(void) const
	{
		return _value;
	}

	GLuint Limit(void) const
	{
		return _limit;
	}
};

} // namespace oglplus

#endif // include guard
