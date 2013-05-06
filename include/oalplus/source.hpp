/**
 *  @file oalplus/source.hpp
 *  @brief Wrapper for OpenAL source object.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_SOURCE_1303201647_HPP
#define OALPLUS_SOURCE_1303201647_HPP

#include <oalplus/config.hpp>
#include <oalplus/fwd.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/error.hpp>
#include <oalplus/angle.hpp>
#include <oalplus/vector.hpp>
#include <oalplus/object.hpp>
#include <oalplus/array.hpp>
#include <oalplus/buffer.hpp>
#include <oalplus/friend_of.hpp>
#include <oalplus/source_state.hpp>
#include <oalplus/source_type.hpp>

#include <cassert>

namespace oalplus {

/// Wrapper for OpenAL source operations
/**
 *  @note Do not use this class directly, use Source instead
 *
 *  @see Source
 */
class SourceOps
 : public Named
 , public FriendOf<BufferOps>
 , public FriendOf<Array<Buffer> >
{
protected:
	friend class FriendOf<SourceOps>;

	static void _init(ALsizei count, ALuint* _name)
	{
		assert(_name != nullptr);
		OALPLUS_ALFUNC(al,GenSources)(count, _name);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,GenSources));
	}

	static void _cleanup(ALsizei count, ALuint* _name)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OALPLUS_ALFUNC(al,DeleteSources)(count, _name);}
		catch(...){ }
	}

	static ALboolean _is_x(ALuint _name)
	{
		assert(_name != 0);
		try{return OALPLUS_ALFUNC(al,IsSource)(_name);}
		catch(...){ }
		return AL_FALSE;
	}
public:
	void Play(void)
	{
		OALPLUS_ALFUNC(al,SourcePlay)(_name);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,SourcePlay));
	}

	void Pause(void)
	{
		OALPLUS_ALFUNC(al,SourcePause)(_name);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,SourcePause));
	}

	void Stop(void)
	{
		OALPLUS_ALFUNC(al,SourceStop)(_name);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,SourceStop));
	}

	void Rewind(void)
	{
		OALPLUS_ALFUNC(al,SourceRewind)(_name);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,SourceRewind));
	}

	SourceState State(void) const
	{
		ALint result = 0;
		OALPLUS_ALFUNC(al,GetSourceiv)(
			_name,
			AL_SOURCE_STATE,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourceiv));
		return SourceState(result);
	}

	void Relative(bool value)
	{
		OALPLUS_ALFUNC(al,Sourcei)(
			_name,
			AL_SOURCE_RELATIVE,
			value?AL_TRUE:AL_FALSE
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Sourcei));
	}

	bool Relative(void) const
	{
		ALint result;
		OALPLUS_ALFUNC(al,GetSourceiv)(
			_name,
			AL_SOURCE_RELATIVE,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourceiv));
		return result == AL_TRUE;
	}

	void Type(SourceType type)
	{
		OALPLUS_ALFUNC(al,Sourcei)(
			_name,
			AL_SOURCE_TYPE,
			ALenum(type)
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Sourcei));
	}

	SourceType Type(void) const
	{
		ALint result;
		OALPLUS_ALFUNC(al,GetSourceiv)(
			_name,
			AL_SOURCE_TYPE,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourceiv));
		return SourceType(ALenum(result));
	}

	void Looping(bool value)
	{
		OALPLUS_ALFUNC(al,Sourcei)(
			_name,
			AL_LOOPING,
			value?AL_TRUE:AL_FALSE
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Sourcei));
	}

	bool Looping(void) const
	{
		ALint result;
		OALPLUS_ALFUNC(al,GetSourceiv)(
			_name,
			AL_LOOPING,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourceiv));
		return result == AL_TRUE;
	}

	void Buffer(const BufferOps& buffer)
	{
		OALPLUS_ALFUNC(al,Sourcei)(
			_name,
			AL_BUFFER,
			FriendOf<BufferOps>::GetName(buffer)
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Sourcei));
	}

	void DetachBuffers(void)
	{
		OALPLUS_ALFUNC(al,Sourcei)(
			_name,
			AL_BUFFER,
			0
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,Sourcei));
	}

	void QueueBuffers(const Array<oalplus::Buffer>& buffers)
	{
		OALPLUS_ALFUNC(al,SourceQueueBuffers)(
			_name,
			FriendOf<Array<oalplus::Buffer> >::GetSize(buffers),
			const_cast<ALuint*>(
			FriendOf<Array<oalplus::Buffer> >::GetNames(buffers)
			)
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,SourceQueueBuffers));
	}

	void UnqueueBuffers(const Array<oalplus::Buffer>& buffers)
	{
		OALPLUS_ALFUNC(al,SourceUnqueueBuffers)(
			_name,
			FriendOf<Array<oalplus::Buffer> >::GetSize(buffers),
			const_cast<ALuint*>(
			FriendOf<Array<oalplus::Buffer> >::GetNames(buffers)
			)
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,SourceUnqueueBuffers));
	}

	void Gain(ALfloat value) const
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_GAIN,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	ALfloat Gain(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_GAIN,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return result;
	}

	void MinGain(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_MIN_GAIN,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	ALfloat MinGain(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_MIN_GAIN,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return result;
	}

	void MaxGain(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_MAX_GAIN,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	ALfloat MaxGain(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_MAX_GAIN,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return result;
	}

	void ReferenceDistance(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_REFERENCE_DISTANCE,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	ALfloat ReferenceDisntace(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_REFERENCE_DISTANCE,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return result;
	}

	void RolloffFactor(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_ROLLOFF_FACTOR,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	ALfloat RolloffFactor(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_ROLLOFF_FACTOR,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return result;
	}

	void MaxDistance(ALfloat value) const
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_MAX_DISTANCE,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	ALfloat MaxDistance(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_MAX_DISTANCE,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return result;
	}

	void Pitch(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_PITCH,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	ALfloat Pitch(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_PITCH,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return result;
	}

	void Position(const Vec3f& dir)
	{
		OALPLUS_ALFUNC(al,Sourcefv)(
			_name,
			AL_POSITION,
			dir.Data()
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcefv));
	}

	void Position(ALfloat x, ALfloat y, ALfloat z)
	{
		OALPLUS_ALFUNC(al,Source3f)(
			_name,
			AL_POSITION,
			x, y, z
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Source3f));
	}

	Vec3f Position(void) const
	{
		ALfloat result[3];
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_POSITION,
			result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return Vec3f(result);
	}

	void Velocity(const Vec3f& dir)
	{
		OALPLUS_ALFUNC(al,Sourcefv)(
			_name,
			AL_VELOCITY,
			dir.Data()
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcefv));
	}

	void Velocity(ALfloat x, ALfloat y, ALfloat z)
	{
		OALPLUS_ALFUNC(al,Source3f)(
			_name,
			AL_VELOCITY,
			x, y, z
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Source3f));
	}

	Vec3f Velocity(void) const
	{
		ALfloat result[3];
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_VELOCITY,
			result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return Vec3f(result);
	}

	void Direction(const Vec3f& dir)
	{
		OALPLUS_ALFUNC(al,Sourcefv)(
			_name,
			AL_DIRECTION,
			dir.Data()
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcefv));
	}

	void Direction(ALfloat x, ALfloat y, ALfloat z)
	{
		OALPLUS_ALFUNC(al,Source3f)(
			_name,
			AL_DIRECTION,
			x, y, z
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Source3f));
	}

	Vec3f Direction(void) const
	{
		ALfloat result[3];
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_DIRECTION,
			result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return Vec3f(result);
	}

	void ConeInnerAngle(Anglef angle)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_CONE_INNER_ANGLE,
			angle.ValueInDegrees()
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	Anglef ConeInnerAngle(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_CONE_INNER_ANGLE,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return Anglef::Degrees(result);
	}

	void ConeOuterAngle(Anglef angle)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_CONE_OUTER_ANGLE,
			angle.ValueInDegrees()
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	Anglef ConeOuterAngle(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_CONE_OUTER_ANGLE,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return Anglef::Degrees(result);
	}

	void ConeOuterGain(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_CONE_OUTER_GAIN,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	ALfloat ConeOuterGain(void) const
	{
		ALfloat result;
		OALPLUS_ALFUNC(al,GetSourcefv)(
			_name,
			AL_CONE_OUTER_GAIN,
			&result
		);
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetSourcefv));
		return result;
	}

	void SecOffset(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_SEC_OFFSET,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	void SampleOffset(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_SAMPLE_OFFSET,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

	void ByteOffset(ALfloat value)
	{
		OALPLUS_ALFUNC(al,Sourcef)(
			_name,
			AL_BYTE_OFFSET,
			value
		);
		OALPLUS_CHECK(OALPLUS_ERROR_INFO(al,Sourcef));
	}

};

#if OALPLUS_DOCUMENTATION_ONLY
/// An @ref oalplus_object encapsulating the OpenAL source functionality
/**
 *  @ingroup oalplus_objects
 */
class Source
 : public SourceOps
{ };
#else
typedef Object<SourceOps> Source;
#endif

} // namespace oalplus

#endif // include guard
