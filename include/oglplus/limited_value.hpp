/**
 *  @file oglplus/limited_value.hpp
 *  @brief Generic OpenGL implementation-dependend limited value wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_LIMITED_VALUE_1107121519_HPP
#define OGLPLUS_LIMITED_VALUE_1107121519_HPP

#include <oglplus/error.hpp>
#include <cassert>

namespace oglplus {

/// Base class for limited implementation-dependent numeric values
/** This class checks if the given unsigned int value is in the
 *  implementation-dependent range of allowed valued and throws
 *  an @c LimitError exception if it is not.
 */
class LimitedCount
{
private:
	GLuint _value;
protected:
	/**
	 *  @throws Error
	 *  @throws LimitError
	 */
	LimitedCount(
		GLuint value,
		GLuint query,
		const ErrorInfo& info
	): _value(value)
	{
		GLint limit = -1;
		::glGetIntegerv(query, &limit);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetIntegerv));
		assert(limit >= 0);
		if(_value >= GLuint(limit))
			throw LimitError(info, value, limit);
	}
public:
	/// Returns the value
	template <typename Type>
	explicit operator Type(void) const
	{
		return Type(_value);
	}
};

#define OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(NAME, QUERY) \
class NAME \
 : public LimitedCount \
{ \
public: \
	NAME(GLuint value) \
	 : LimitedCount(value, GL_##QUERY, OGLPLUS_LIMIT_ERROR_INFO(QUERY)) \
	{ } \
};

} // namespace oglplus

#endif // include guard
