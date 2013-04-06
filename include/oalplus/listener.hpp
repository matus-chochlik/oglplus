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

	static Vec3f Position(void)
	{
		ALfloat result[3];
		OALPLUS_ALFUNC(al,GetListenerfv)(
			AL_POSITION,
			result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetListenerfv));
		return Vec3f(result);
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

	static Vec3f Velocity(void)
	{
		ALfloat result[3];
		OALPLUS_ALFUNC(al,GetListenerfv)(
			AL_VELOCITY,
			result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetListenerfv));
		return Vec3f(result);
	}

	static void Orientation(const Vec3f& at, const Vec3f& up)
	{
		ALfloat v[6] = {
			at[0], at[1], at[2],
			up[0], up[1], up[2],
		};
		OALPLUS_ALFUNC(al,Listenerfv)(AL_ORIENTATION, v);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listenerfv));
	}

	static void Orientation(
		ALfloat at_x,
		ALfloat at_y,
		ALfloat at_z,
		ALfloat up_x,
		ALfloat up_y,
		ALfloat up_z
	)
	{
		ALfloat v[6] = {at_x, at_y, at_z, up_x, up_y, up_z};
		OALPLUS_ALFUNC(al,Listenerfv)(AL_ORIENTATION, v);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listenerfv));
	}

	static Vec3f OrientationAt(void)
	{
		ALfloat v[6];
		OALPLUS_ALFUNC(al,GetListenerfv)(AL_ORIENTATION, v);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetListenerfv));
		return Vec3f(v, 3);
	}

	static void Gain(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Listenerf)(
			AL_GAIN,
			value
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Listenerf));
	}

	static ALfloat Gain(void)
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetListenerfv)(
			AL_VELOCITY,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetListenerfv));
		return result;
	}
};

} // namespace oalplus

#endif // include guard
