/**
 *  @file oalplus/friend_of.hpp
 *  @brief Implementation of the FriendaOf helper base class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_FRIEND_OF_1107121519_HPP
#define OALPLUS_FRIEND_OF_1107121519_HPP

#include <oalplus/auxiliary/named.hpp>

namespace oalplus {

template <class Object>
class FriendOf;

#if !OALPLUS_DOXYGEN_PARSE
template <>
class FriendOf<Named>
{
protected:
	static void SetName(Named& object, ALuint name)
	{
		object._name = name;
	}

	static ALuint GetName(const Named& object)
	{
		return object._name;
	}
};

template <class ObjectOps>
class FriendOf
 : public FriendOf<Named>
{
protected:
	static void SetName(ObjectOps& object, ALuint name)
	{
		FriendOf<Named>::SetName(object, name);
	}

	static ALuint GetName(const ObjectOps& object)
	{
		return FriendOf<Named>::GetName(object);
	}
};
#endif

} // namespace oalplus

#endif // include guard
