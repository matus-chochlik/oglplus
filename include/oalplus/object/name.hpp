/**
 *  @file oalplus/object/name.hpp
 *  @brief Base class for OpenAL "named" objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_OBJECT_NAME_1107121519_HPP
#define OALPLUS_OBJECT_NAME_1107121519_HPP

#include <oalplus/fwd.hpp>
#include <oalplus/config.hpp>

#include <type_traits>
#include <utility>
#include <cassert>

namespace oalplus {

template <typename ObjTag>
ALuint GetALName(ObjectName<ObjTag>);

/// A common template for "named" OpenAL objects like sources, buffers, etc.
/** This is a common template for all OpenAL object wrappers which are
 *  identified by a (ALuint typed) name, i.e. object like Source, Buffer, etc.
 *  @c ObjectName adds static object type information and allows to distinguish
 *  between objects of different type with the same name value.
 *
 *  @note Do not use this class directly, it is used by the OpenAL object wrappers
 *  for basic initialization, error checking and access restriction.
 */
template <typename ObjTag>
class ObjectName
{
protected:
	friend ALuint GetALName<ObjTag>(ObjectName);
	ALuint _name;

	void _copy(const ObjectName& that)
	OALPLUS_NOEXCEPT(true)
	{
		_name = that._name;
	}

	void _adopt(ObjectName&& temp)
	OALPLUS_NOEXCEPT(true)
	{
		_name = temp._name;
		temp._name = 0;
	}
public:
	/// Constructs wrapper for name 0 (zero).
	ObjectName(void)
	OALPLUS_NOEXCEPT(true)
	 : _name(ALuint(0))
	{ }

	/// Constructs wrapper for the specified @p name.
	explicit ObjectName(ALuint name)
	OALPLUS_NOEXCEPT(true)
	 : _name(name)
	{ }

	ObjectName(const ObjectName& that)
	OALPLUS_NOEXCEPT(true)
	 : _name(that._name)
	{ }

	ObjectName(ObjectName&& temp)
	OALPLUS_NOEXCEPT(true)
	 : _name(temp._name)
	{
		temp._name = 0;
	}

	ObjectName& operator = (const ObjectName& that)
	OALPLUS_NOEXCEPT(true)
	{
		_copy(that);
		return *this;
	}

	ObjectName& operator = (ObjectName&& temp)
	OALPLUS_NOEXCEPT(true)
	{
		_adopt(std::move(temp));
		return *this;
	}

	/// Equality comparison
	friend bool operator == (ObjectName a, ObjectName b)
	{
		return a._name == b._name;
	}

	/// Inequality comparison
	friend bool operator != (ObjectName a, ObjectName b)
	{
		return a._name != b._name;
	}

	/// Ordering
	friend bool operator <  (ObjectName a, ObjectName b)
	{
		return a._name < b._name;
	}
};

/// Returns the ALuint OpenAL name assigned to @p named object
template <typename ObjTag>
inline ALuint GetALName(ObjectName<ObjTag> named)
{
	return named._name;
}

} // namespace oalplus

#endif // include guard
