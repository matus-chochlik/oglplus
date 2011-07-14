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

namespace oglplus {

template <class Object>
class FriendOf
{
protected:
	static GLuint GetName(const Object& object)
	{
		return object._name;
	}
};

} // namespace oglplus

#endif // include guard
