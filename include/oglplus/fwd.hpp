/**
 *  @file oglplus/fwd.hpp
 *  @brief Forward declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_FWD_1107121519_HPP
#define OGLPLUS_FWD_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/string.hpp>

namespace oglplus {

struct None { typedef int _value_type; };

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

#else

template <typename Enum>
struct EnumBaseType;

template <typename EnumType>
inline StrLit EnumValueName(EnumType enum_value)
{
	typedef typename EnumBaseType<EnumType>::Type BaseType;
	return EnumValueName(
		(EnumType*)nullptr,
		BaseType(enum_value)
	);
}
#endif

template <typename ObjectOps>
struct ObjectTypeId;

} // namespace oglplus

#endif // include guard
