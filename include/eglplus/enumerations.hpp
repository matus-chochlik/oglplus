/**
 *  @file eglplus/enumerations.hpp
 *  @brief Enumeration-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_ENUMERATIONS_1303201759_HPP
#define EGLPLUS_ENUMERATIONS_1303201759_HPP

#include <eglplus/config.hpp>
#include <eglplus/string.hpp>
#include <eglplus/detail/enum_class.hpp>
#include <eglplus/detail/base_range.hpp>

namespace eglplus {
namespace enums {

#if !OGLPLUS_NO_SCOPED_ENUMS
template <typename Enum>
struct EnumBaseType
{
	typedef EGLenum Type;
};
#else
// No scoped enums -> no enum value names/ranges
#ifdef EGLPLUS_NO_ENUM_VALUE_NAMES
#undef EGLPLUS_NO_ENUM_VALUE_NAMES
#endif
#define EGLPLUS_NO_ENUM_VALUE_NAMES  1

#ifdef EGLPLUS_NO_ENUM_VALUE_RANGES
#undef EGLPLUS_NO_ENUM_VALUE_RANGES
#endif
#define EGLPLUS_NO_ENUM_VALUE_RANGES 1
using oglplus::EnumBaseType;
#endif

template <typename EnumType>
inline StrLit EnumValueName(EnumType enum_value)
{
#if !EGLPLUS_NO_ENUM_VALUE_NAMES
	typedef typename EnumBaseType<EnumType>::Type BaseType;
	return ValueName_(
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
#if !EGLPLUS_NO_ENUM_VALUE_RANGES
	return ValueRange_((EnumType*)nullptr);
#else
	const typename EnumBaseType<EnumType>::Type* x = nullptr;
	return aux::CastIterRange<
		const typename EnumBaseType<EnumType>::Type*,
		EnumType
	>(x, x);

#endif
}

} // namespace enums

using enums::EnumValueName;
using enums::EnumValueRange;

} // namespace eglplus

#endif // include guard
