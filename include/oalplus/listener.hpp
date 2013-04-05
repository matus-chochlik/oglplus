/**
 *  @file oalplus/listener.hpp
 *  @brief Wrapper for OpenAL listener object.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_LISTENER_1303201647_HPP
#define OALPLUS_LISTENER_1303201647_HPP

#include <oalplus/config.hpp>
#include <oalplus/fwd.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/error.hpp>
#include <oalplus/vector.hpp>

#include <cstring>
#include <cassert>

namespace oalplus {

/// An AL context-specific monostate object representing the listener
class Listener
{
public:
	void Position(const Vec3f& position)
	{
		OALPLUS_ALFUNC(al,Listener)(
			AL_POSITION,
			position.Data()
		);
		OALPLUS_VERIFY_AL(OALPLUS_ERROR_INFO(al,Listener));
	}
};

} // namespace oalplus

#endif // include guard
