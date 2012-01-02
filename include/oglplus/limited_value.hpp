/**
 *  @file oglplus/limited_value.hpp
 *  @brief Generic OpenGL implementation-dependend limited value wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_LIMITED_VALUE_1107121519_HPP
#define OGLPLUS_LIMITED_VALUE_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <cassert>

namespace oglplus {

/// Base class for limited implementation-dependent numeric values
/** This class checks if the given unsigned int value is in the
 *  implementation-dependent range of allowed valued and throws
 *  an @c LimitError exception if it is not.
 *
 *  @note Do not use this templates directly, use the derived types
 *  or the typedefs of instantiations instead.
 *
 *  @ingroup utility_classes
 */
template <GLenum Query>
class LimitedCount
{
private:
	GLuint _value;

	static GLuint _query_limit(void)
	{
		GLint limit = -1;
		OGLPLUS_GLFUNC(GetIntegerv)(Query, &limit);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetIntegerv));
		assert(limit >= 0);
		return GLuint(limit);
	}

	static GLuint _limit(void)
	{
		static GLuint limit = _query_limit();
		return limit;
	}
protected:
	/**
	 *  @throws Error
	 *  @throws LimitError
	 */
	LimitedCount(GLuint value, const ErrorInfo& info)
	 : _value(value)
	{
		if(_value >= _limit())
			throw LimitError(info, value, _limit());
	}
public:
	/// Returns the value
	template <typename Type>
	explicit operator Type(void) const
	{
		return Type(_value);
	}

	friend GLuint Max(const LimitedCount& count)
	{
		return _limit();
	}
};

#define OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(NAME, QUERY) \
class NAME \
 : public LimitedCount<GL_ ## QUERY> \
{ \
public: \
	NAME(GLuint value) \
	 : LimitedCount<GL_ ## QUERY>( \
		value, \
		OGLPLUS_LIMIT_ERROR_INFO(QUERY) \
	) \
	{ } \
};

} // namespace oglplus

#endif // include guard
