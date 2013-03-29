/**
 *  @file oglplus/enumerations.hpp
 *  @brief Enumeration-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ENUMERATIONS_1107121519_HPP
#define OGLPLUS_ENUMERATIONS_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/string.hpp>
#include <oglplus/auxiliary/enum_class.hpp>
#include <oglplus/auxiliary/base_range.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY

/// Returns the name of the GL enumerated value for an OGLplus enum value
/** This function is overloaded for the enumerated types defined by @OGLplus
 *  and returns the GL constant name (without the 'GL_' prefix) as a c-string.
 *  @note The returned c-string is managed by the EnumValueName functions
 *  and should NOT be freed by the caller.
 *
 *  The result of this function is influenced by the #OGLPLUS_NO_ENUM_VALUE_NAMES
 *  preprocessor-symbol. If it is set to a nonzero value then EnumValueName(Enum)
 *  returns an empty string.
 *
 *  @ingroup enumerations
 *  @see OGLPLUS_NO_ENUM_VALUE_NAMES
 */
StrLit EnumValueName(Enum enum_value);

/// Returns a @c Range of values in an @p Enumeration
/** This template function is available for the enumerated types defined by
 *  @OGLplus and returns a Range that allows to traverse all values of
 *  a particular @p Enumeration type.
 *
 *  The result of this function is influenced by the #OGLPLUS_NO_ENUM_VALUE_RANGES
 *  preprocessor-symbol. If it is set to a nonzero value then EnumValueRange<E>()
 *  returns an empty range.
 *
 *  @ingroup enumerations
 *  @see OGLPLUS_NO_ENUM_VALUE_RANGES
 */
template <typename Enumeration>
Range<Enum> EnumValueRange(void);

#else

#if !OGLPLUS_NO_SCOPED_ENUMS
template <typename Enum>
struct EnumBaseType
{
	typedef GLenum Type;
};
#endif

template <typename EnumType>
inline StrLit EnumValueName(EnumType enum_value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
	typedef typename EnumBaseType<EnumType>::Type BaseType;
	return EnumValueName(
		(EnumType*)nullptr,
		BaseType(enum_value)
	);
#else
	OGLPLUS_FAKE_USE(enum_value);
	return StrLit();
#endif
}

template <typename EnumType>
inline aux::CastIterRange<
	const typename EnumBaseType<EnumType>::Type*,
	EnumType
> EnumValueRange(void)
{
#if !OGLPLUS_NO_ENUM_VALUE_RANGES
	return EnumValueRange((EnumType*)nullptr);
#else
	const typename EnumBaseType<EnumType>::Type* x = nullptr;
	return aux::CastIterRange<
		const typename EnumBaseType<EnumType>::Type*,
		EnumType
	>(x, x);

#endif
}

#endif // OGLPLUS_DOCUMENTATION_ONLY

} // namespace oglplus

#endif // include guard
