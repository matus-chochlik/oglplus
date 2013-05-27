/**
 *  @file oglplus/auxiliary/enum_class.hpp
 *  @brief Helper macros for declaring enumerations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_ENUM_CLASS_1207191556_HPP
#define OGLPLUS_AUX_ENUM_CLASS_1207191556_HPP

namespace oglplus {

// if we have native strongly typed enums
#if !OGLPLUS_NO_SCOPED_ENUMS

#define OGLPLUS_ENUM_CLASS_FWD(NAME, TYPE) \
namespace enums { \
enum class NAME : TYPE; \
} using enums::NAME;

#define OGLPLUS_ENUM_CLASS_FWD_EVT(NAME, TYPE) \
	OGLPLUS_ENUM_CLASS_FWD(NAME, TYPE)

#define OGLPLUS_ENUM_CLASS_BEGIN(NAME, TYPE) \
namespace enums { \
enum class NAME : TYPE {

#define OGLPLUS_ENUM_CLASS_VALUE(ITEM, VALUE) \
	ITEM = VALUE

#define OGLPLUS_CONST_ENUM_VALUE(ENUM_ITEM) \
	ENUM_ITEM

#define OGLPLUS_ENUM_CLASS_COMMA ,

#define OGLPLUS_ENUM_CLASS_END(NAME) \
}; } \
using enums::NAME;

namespace enums {

template <typename Enum>
struct EnumValueType
{
	typedef Enum Type;
};

template <typename Enum>
struct EnumBaseType;

} // namespace enums

// no native strongly typed enums
#else

#define OGLPLUS_ENUM_CLASS_FWD(NAME, TYPE) \
namespace enums { class NAME; }


#define OGLPLUS_ENUM_CLASS_FWD_EVT(NAME, TYPE) \
OGLPLUS_ENUM_CLASS_FWD(NAME, TYPE) \
namespace enums { \
template <> \
struct EnumValueType<NAME> \
{ \
	typedef TYPE Type; \
}; \
}

#define OGLPLUS_ENUM_CLASS_BEGIN(NAME, TYPE) \
class NAME { \
private:TYPE _value; \
	typedef NAME _self; \
public: typedef TYPE _value_type; \
	NAME(void):_value(0) { } \
	NAME(void (*init)(NAME&)){init(*this);} \
	explicit NAME(TYPE value):_value(value){ } \
	friend bool operator==(NAME a, NAME b){ return a._value==b._value; } \
	friend bool operator!=(NAME a, NAME b){ return a._value!=b._value; } \
	operator TYPE (void) const { return _value; }

#define OGLPLUS_ENUM_CLASS_VALUE(ITEM, VALUE) \
	enum { ITEM##_c = VALUE }; \
	static void ITEM(_self& inst){ inst._value = VALUE; }

#define OGLPLUS_CONST_ENUM_VALUE(ENUM_ITEM) \
	ENUM_ITEM##_c

#define OGLPLUS_ENUM_CLASS_COMMA

#define OGLPLUS_ENUM_CLASS_END(NAME) };

namespace enums {

template <typename Enum>
struct EnumValueType
{
	typedef typename Enum::_value_type Type;
};

template <typename Enum>
struct EnumBaseType
{
	typedef typename Enum::_value_type Type;
};

} // namespace enums

#endif

} // namespace oglplus

#endif // include guard
