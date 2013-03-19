/**
 *  @file oglplus/friend_of.hpp
 *  @brief Implementation of the FriendaOf helper base class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FRIEND_OF_1107121519_HPP
#define OGLPLUS_FRIEND_OF_1107121519_HPP

#include <oglplus/auxiliary/named.hpp>
#include <oglplus/auxiliary/strings.hpp>

namespace oglplus {

template <class Object>
class FriendOf;

#if !OGLPLUS_DOXYGEN_PARSE
template <>
class FriendOf<Named>
{
protected:
	static void SetName(Named& object, GLuint name)
	OGLPLUS_NOEXCEPT(true)
	{
		object._name = name;
	}

	static GLuint GetName(const Named& object)
	OGLPLUS_NOEXCEPT(true)
	{
		return object._name;
	}
};

template <class ObjectOps>
class FriendOf
 : public FriendOf<Named>
{
protected:
	static void SetName(ObjectOps& object, GLuint name)
	OGLPLUS_NOEXCEPT(true)
	{
		FriendOf<Named>::SetName(object, name);
	}

	static GLuint GetName(const ObjectOps& object)
	OGLPLUS_NOEXCEPT(true)
	{
		return FriendOf<Named>::GetName(object);
	}

	static GLuint GetLocation(const ObjectOps& object)
	OGLPLUS_NOEXCEPT(true)
	{
		return object._location;
	}
public:
	static const String& GetDescription(const ObjectOps& object)
	{
		return aux::ObjectDescRegistry<ObjectOps>::_get_desc(
			GetName(object)
		);
	}
};
#endif

} // namespace oglplus

#endif // include guard
