/**
 *  @file oglplus/auxiliary/named.hpp
 *  @brief Base class for OpenGL "named" objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_NAMED_1107121519_HPP
#define OGLPLUS_AUX_NAMED_1107121519_HPP

#include <oglplus/config.hpp>

#include <cassert>
#include <type_traits>

namespace oglplus {

template <class Object>
class FriendOf;

/// A common base class for "named" OpenGL objects like textures, buffers, etc.
/** This is a common base class for all OpenGL object wrappers which are
 *  identified by a (GLuint typed) name, i.e. object like Textures, Buffer, VAOs,
 *  Queries, etc. but also Shaders, Programs, and so on.
 *
 *  @note Do not use this class directly, it is used by the OpenGL object wrappers
 *  for basic initialization, error checking and access restriction.
 */
class Named
{
protected:
	typedef std::false_type _can_be_zero;

	GLuint _name;

	inline Named(void) OGLPLUS_NOEXCEPT_IF(GLuint(0))
	 : _name(GLuint(0))
	{ }

	inline ~Named(void) OGLPLUS_NOEXCEPT(true)
	{
		assert(_name == 0);
	}

	friend class FriendOf<Named>;

#if !OGLPLUS_NO_DEFAULTED_FUNCTIONS
public:
	Named(const Named&) = default;

	Named(Named&&) = default;

	Named& operator = (const Named&) = default;

	Named& operator = (Named&&) = default;
#endif
};

} // namespace oglplus

#endif // include guard
