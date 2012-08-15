/**
 *  @file oglplus/one_of.hpp
 *  @brief Variant helper class used mostly with enums
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_ONE_OF_1107121519_HPP
#define OGLPLUS_ONE_OF_1107121519_HPP

#include <oglplus/config.hpp>

#include <type_traits>

namespace oglplus {
namespace aux {

template <typename Common, typename T>
class OneOfBase
{
protected:
	static inline Common Accept(T value)
	{
		return Common(value);
	}
};

} // namespace aux

/// Stores a value having one of the listed types in a common representation.
/**
 *  Applications rarely need to use this class directly. Instantiations of this
 *  template are used as types for parameters in functions taking values with
 *  variant types.
 *  When constructing a one-of value the application simply passes a value
 *  whose type must be one of the types listed in the @c Variants template
 *  parameter pack, otherwise the construction will fail.
 *
 *  @code
 *  Context gl;
 *  ...
 *  gl.DrawBuffer(ColorBuffer::FrontLeft);
 *  ...
 *  gl.DrawBuffer(FramebufferColorAttachment::_0);
 *  @endcode
 */
template <typename Common, typename ... Variants>
class OneOf
 : public aux::OneOfBase<Common, Variants>...
{
private:
	Common _value;

	template <typename T>
	struct is_one_of
	 : std::is_convertible<
		OneOf,
		aux::OneOfBase<Common, T>
	>
	{ };
public:
	template <typename T>
	OneOf(T value, typename std::enable_if<is_one_of<T>::value>::type* = 0)
	 : _value(aux::OneOfBase<Common, T>::Accept(value))
	{ }

#if !OGLPLUS_NO_EXPLICIT_CONVERSION_OPERATORS
	explicit operator Common (void) const
#else
	operator Common (void) const
#endif
	OGLPLUS_NOEXCEPT(true)
	{
		return _value;
	}
};

} // namespace oglplus

#endif // include guard
