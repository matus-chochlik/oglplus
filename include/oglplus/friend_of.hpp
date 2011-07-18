/**
 *  @file oglplus/friend_of.hpp
 *  @brief Implementation of the FriendaOf helper base class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_FRIEND_OF_1107121519_HPP
#define OGLPLUS_FRIEND_OF_1107121519_HPP

#include <oglplus/auxiliary/named.hpp>

namespace oglplus {

template <class Object>
class FriendOf;

template <class ObjectOps>
class Managed;

template <>
class FriendOf<Named>
{
protected:
	static void SetName(Named& object, GLuint name)
	{
		object._name = name;
	}

	static GLuint GetName(const Named& object)
	{
		return object._name;
	}
};

template <class Object>
class FriendOf
 : public FriendOf<Named>
{
protected:
	static void SetName(Object& object, GLuint name)
	{
		FriendOf<Named>::SetName(object, name);
	}

	static GLuint GetName(const Object& object)
	{
		return FriendOf<Named>::GetName(object);
	}

	static GLuint GetIndex(const Object& object)
	{
		return object._index;
	}
};

} // namespace oglplus

#endif // include guard
