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

namespace oalplus {

/// An AL context-specific monostate object representing the listener
class Listener
{
public:
	static void Position(const Vec3f& position)
	{
		OALPLUS_ALFUNC(al,Listenerfv)(
			AL_POSITION,
			position.Data()
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listenerfv));
	}

	static void Position(ALfloat x, ALfloat y, ALfloat z)
	{
		OALPLUS_ALFUNC(al,Listener3f)(
			AL_POSITION,
			x, y, z
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listener3f));
	}

	static void Velocity(const Vec3f& velocity)
	{
		OALPLUS_ALFUNC(al,Listenerfv)(
			AL_VELOCITY,
			velocity.Data()
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listenerfv));
	}

	static void Velocity(ALfloat x, ALfloat y, ALfloat z)
	{
		OALPLUS_ALFUNC(al,Listener3f)(
			AL_VELOCITY,
			x, y, z
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listener3f));
	}

	static void Orientation(const Vec3f& forward, const Vec3f& up)
	{
		ALfloat v[6] = {
			forward[0], forward[1], forward[2],
			up[0], up[1], up[2],
		};
		OALPLUS_ALFUNC(al,Listenerfv)(AL_ORIENTATION, v);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listenerfv));
	}

	static void Orientation(
		ALfloat fw_x,
		ALfloat fw_y,
		ALfloat fw_z,
		ALfloat up_x,
		ALfloat up_y,
		ALfloat up_z
	)
	{
		ALfloat v[6] = {fw_x, fw_y, fw_z, up_x, up_y, up_z};
		OALPLUS_ALFUNC(al,Listenerfv)(AL_ORIENTATION, v);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listenerfv));
	}

	static void Gain(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Listenerf)(
			AL_GAIN,
			value
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listenerf));
	}
};

} // namespace oalplus

#endif // include guard
