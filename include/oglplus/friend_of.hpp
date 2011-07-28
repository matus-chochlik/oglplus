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

template <class ObjectOps>
class FriendOf
 : public FriendOf<Named>
{
private:
	static void SetName(ObjectOps& object, GLuint name)
	{
		FriendOf<Named>::SetName(object, name);
	}

	friend class Managed<ObjectOps>;
	friend class Managed<Object<ObjectOps, true> >;
	friend class Managed<Object<ObjectOps, false> >;
protected:
	static GLuint GetName(const ObjectOps& object)
	{
		return FriendOf<Named>::GetName(object);
	}

	static GLuint GetIndex(const ObjectOps& object)
	{
		return object._index;
	}
};

template <class ObjectOps, bool MultiObject>
class Object;

template <class ObjectOps, bool MultiObject>
class FriendOf<Object<ObjectOps, MultiObject> >
 : public FriendOf<ObjectOps>
{
protected:
	static GLuint GetName(const Object<ObjectOps, MultiObject>& object)
	{
		return FriendOf<ObjectOps>::GetName(object);
	}
};

} // namespace oglplus

#endif // include guard
