/**
 *  .file oglplus/auxiliary/named.hpp
 *  .brief Base class for OpenGL "named" objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_NAMED_1107121519_HPP
#define OGLPLUS_AUX_NAMED_1107121519_HPP

#include <cassert>

namespace oglplus {

template <class Object>
class FriendOf;

class Named
{
protected:
	GLuint _name;

	inline Named(void)
	 : _name(GLuint(0))
	{ }

	inline ~Named(void)
	{
		assert(_name == 0);
	}

	friend class FriendOf<Named>;
};

} // namespace oglplus

#endif // include guard
