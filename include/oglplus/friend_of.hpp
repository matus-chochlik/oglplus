/**
 *  @file oglplus/friend_of.hpp
 *  @brief Implementation of the FriendOf helper class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FRIEND_OF_1107121519_HPP
#define OGLPLUS_FRIEND_OF_1107121519_HPP

#include <oglplus/auxiliary/named.hpp>
#include <oglplus/auxiliary/obj_desc.hpp>

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
public:
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

	static const String& GetDescription(const ObjectOps& object)
	{
		return aux::ObjectDescRegistry<ObjectOps>::_get_desc(
			GetName(object)
		);
	}
};

template <template <typename> class Wrapper, class ObjectOps>
class FriendOf<Wrapper<ObjectOps>>
 : public FriendOf<ObjectOps>
{ };

#endif

/// Exposes the raw GL name of an OGLplus object.
/** This function can be used to get the GLuint name of a wrapped GL object
 *  like Texture, Program, Buffer, TransformFeedback, etc.
 */
template <typename Object>
inline GLuint ExposeGLName(const Object& object)
{
	return FriendOf<Object>::GetName(object);
}

} // namespace oglplus

#endif // include guard
