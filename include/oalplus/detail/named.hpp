/**
 *  @file oalplus/detail/named.hpp
 *  @brief Base class for OpenAL "named" objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_AUX_NAMED_1107121519_HPP
#define OALPLUS_AUX_NAMED_1107121519_HPP

#include <oalplus/config.hpp>

#include <cassert>
#include <type_traits>

namespace oalplus {

template <class Object>
class FriendOf;

/// A common base class for "named" OpenAL objects like textures, buffers, etc.
/** This is a common base class for all OpenAL object wrappers which are
 *  identified by a (ALuint typed) name, i.e. object like Buffers, Sources,
 *  etc.
 *
 *  @note Do not use this class directly, it is used by the OpenAL object wrappers
 *  for basic initialization, error checking and access restriction.
 */
class Named
{
protected:
	ALuint _name;

	inline Named(void)
	 : _name(ALuint(0))
	{ }

	inline ~Named(void)
	{
		assert(_name == 0);
	}

	friend class FriendOf<Named>;

#if !OALPLUS_NO_DEFAULTED_FUNCTIONS
public:
	Named(const Named&) = default;

	Named(Named&&) = default;

	Named& operator = (const Named&) = default;

	Named& operator = (Named&&) = default;
#endif
};

} // namespace oalplus

#endif // include guard
