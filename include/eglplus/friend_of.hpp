/**
 *  @file eglplus/friend_of.hpp
 *  @brief Implements friend access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_FRIEND_OF_1305291005_HPP
#define EGLPLUS_FRIEND_OF_1305291005_HPP

#include <eglplus/config.hpp>

namespace eglplus {

template <typename T>
class FriendOf
{
protected:
	static auto GetHandle(const T& x) ->
		decltype(x._handle)
	{
		return x._handle;
	}
};

} // namespace eglplus

#endif // include guard
