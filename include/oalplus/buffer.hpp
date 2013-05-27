/**
 *  @file oalplus/buffer.hpp
 *  @brief Wrapper for OpenAL buffer object.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_BUFFER_1303201647_HPP
#define OALPLUS_BUFFER_1303201647_HPP

#include <oalplus/config.hpp>
#include <oalplus/fwd.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/error.hpp>
#include <oalplus/object.hpp>
#include <oalplus/data_format.hpp>

#include <cassert>

namespace oalplus {

/// Wrapper for OpenAL buffer operations
/**
 *  @note Do not use this class directly, use Buffer instead
 *
 *  @see Buffer
 */
class BufferOps
 : public Named
{
protected:
	friend class FriendOf<BufferOps>;

	static void _init(ALsizei count, ALuint* _name)
	{
		assert(_name != nullptr);
		OALPLUS_ALFUNC(al,GenBuffers)(count, _name);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,GenBuffers));
	}

	static void _cleanup(ALsizei count, ALuint* _name)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OALPLUS_ALFUNC(al,DeleteBuffers)(count, _name);}
		catch(...){ }
	}

	static ALboolean _is_x(ALuint _name)
	{
		assert(_name != 0);
		try{return OALPLUS_ALFUNC(al,IsBuffer)(_name);}
		catch(...){ }
		return AL_FALSE;
	}
public:
	void Data(
		DataFormat format,
		const ALvoid* data,
		ALsizei size,
		ALsizei frequency
	)
	{
		OALPLUS_ALFUNC(al,BufferData)(
			ALuint(this->_name),
			ALenum(format),
			data,
			size,
			frequency
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,BufferData));
	}

	ALsizei Frequency(void) const
	{
		ALint result = 0;
		OALPLUS_ALFUNC(al,GetBufferiv)(
			_name,
			AL_FREQUENCY,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetBufferiv));
		return ALsizei(result);
	}

	ALsizei Size(void) const
	{
		ALint result = 0;
		OALPLUS_ALFUNC(al,GetBufferiv)(
			_name,
			AL_SIZE,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetBufferiv));
		return ALsizei(result);
	}

	ALsizei Bits(void) const
	{
		ALint result = 0;
		OALPLUS_ALFUNC(al,GetBufferiv)(
			_name,
			AL_BITS,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetBufferiv));
		return ALsizei(result);
	}

	ALsizei Channels(void) const
	{
		ALint result = 0;
		OALPLUS_ALFUNC(al,GetBufferiv)(
			_name,
			AL_CHANNELS,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetBufferiv));
		return ALsizei(result);
	}

	ALfloat Duration(void) const
	{
		ALfloat s = Size();
		ALfloat f = Frequency();
		ALfloat b = Bits()/8.0f;
		ALfloat c = Channels();
		ALfloat bps = f*b*c;
		return bps>0.0f?ALfloat(s/bps):ALfloat(0);
	}
};

#if OALPLUS_DOCUMENTATION_ONLY
/// An @ref oalplus_object encapsulating the OpenAL buffer functionality
/**
 *  @ingroup oalplus_objects
 */
class Buffer
 : public BufferOps
{ };
#else
typedef Object<BufferOps> Buffer;
#endif

} // namespace oalplus

#endif // include guard
