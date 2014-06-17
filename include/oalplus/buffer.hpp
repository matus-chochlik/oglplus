/**
 *  @file oalplus/buffer.hpp
 *  @brief Wrapper for OpenAL buffer object.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_BUFFER_1303201647_HPP
#define OALPLUS_BUFFER_1303201647_HPP

#include <oalplus/config.hpp>
#include <oalplus/fwd.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/data_format.hpp>
#include <oalplus/error/object.hpp>
#include <oalplus/object/wrapper.hpp>

#include <cassert>

namespace oalplus {

/// Class wrapping AL buffer construction/destruction functions
/** @note Do not use this class directly, use Buffer instead.
 *
 *  @alsymbols
 *  @alfunref{GenBuffers}
 *  @alfunref{DeleteBuffers}
 *  @alfunref{IsBuffer}
 */
template <>
class ObjGenDelOps<tag::Buffer>
{
protected:
	static void Gen(ALsizei count, ALuint* names)
	{
		assert(names != nullptr);
		OALPLUS_ALFUNC(GenBuffers)(count, names);
		OALPLUS_CHECK_SIMPLE(GenBuffers);
	}

	static void Delete(ALsizei count, ALuint* names)
	{
		assert(names != nullptr);
		OALPLUS_ALFUNC(DeleteBuffers)(count, names);
		OALPLUS_VERIFY_SIMPLE(DeleteBuffers);
	}

	static ALboolean IsA(ALuint name)
	{
		assert(name != 0);
		ALboolean result = OALPLUS_ALFUNC(IsBuffer)(name);
		OALPLUS_VERIFY_SIMPLE(IsBuffer);
		return result;
	}
};

/// Wrapper for OpenAL buffer operations
/**
 *  @note Do not use this class directly, use Buffer instead
 *
 *  @see Buffer
 *
 */
template <>
class ObjectOps<tag::DirectState, tag::Buffer>
 : public ObjectName<tag::Buffer>
{
protected:
	ObjectOps(void) { }
public:
	/// Specifies the buffer data
	/**
	 *  @alsymbols
	 *  @alfunref{BufferData}
	 */
	void Data(
		DataFormat format,
		const ALvoid* data,
		ALsizei size,
		ALsizei frequency
	)
	{
		OALPLUS_ALFUNC(BufferData)(
			ALuint(this->_name),
			ALenum(format),
			data,
			size,
			frequency
		);
		OALPLUS_CHECK(
			BufferData,
			ObjectError,
			Object(*this)
		);
	}

	/// Returns the sampling frequency of the data stored in this buffer
	/**
	 *  @alsymbols
	 *  @alfunref{GetBuffer}
	 *  @aldefref{FREQUENCY}
	 */
	ALsizei Frequency(void) const
	{
		ALint result = 0;
		OALPLUS_ALFUNC(GetBufferiv)(
			_name,
			AL_FREQUENCY,
			&result
		);
		OALPLUS_VERIFY(
			GetBufferiv,
			ObjectError,
			Object(*this)
		);
		return ALsizei(result);
	}

	/// Returns the size of the data stored in this buffer
	/**
	 *  @alsymbols
	 *  @alfunref{GetBuffer}
	 *  @aldefref{SIZE}
	 */
	ALsizei Size(void) const
	{
		ALint result = 0;
		OALPLUS_ALFUNC(GetBufferiv)(
			_name,
			AL_SIZE,
			&result
		);
		OALPLUS_VERIFY(
			GetBufferiv,
			ObjectError,
			Object(*this)
		);
		return ALsizei(result);
	}

	/// Returns the number of bits of the data stored in this buffer
	/**
	 *  @alsymbols
	 *  @alfunref{GetBuffer}
	 *  @aldefref{BITS}
	 */
	ALsizei Bits(void) const
	{
		ALint result = 0;
		OALPLUS_ALFUNC(GetBufferiv)(
			_name,
			AL_BITS,
			&result
		);
		OALPLUS_VERIFY(
			GetBufferiv,
			ObjectError,
			Object(*this)
		);
		return ALsizei(result);
	}

	/// Returns the number of channels of the data stored in this buffer
	/**
	 *  @alsymbols
	 *  @alfunref{GetBuffer}
	 *  @aldefref{CHANNELS}
	 */
	ALsizei Channels(void) const
	{
		ALint result = 0;
		OALPLUS_ALFUNC(GetBufferiv)(
			_name,
			AL_CHANNELS,
			&result
		);
		OALPLUS_VERIFY(
			GetBufferiv,
			ObjectError,
			Object(*this)
		);
		return ALsizei(result);
	}

	/// Returns the duration of the sound stored in this buffer
	/**
	 *  @alsymbols
	 *  @alfunref{GetBuffer}
	 *  @aldefref{SIZE}
	 *  @aldefref{FREQUENCY}
	 *  @aldefref{BITS}
	 *  @aldefref{CHANNELS}
	 */
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

} // namespace oalplus
namespace oglplus {

template <>
class ObjGenDelOps<oalplus::tag::Buffer>
 : public oalplus::ObjGenDelOps<oalplus::tag::Buffer>
{ };

template <typename OpsTag>
class ObjectOps<OpsTag, oalplus::tag::Buffer>
 : public oalplus::ObjectOps<OpsTag, oalplus::tag::Buffer>
{ };

} // namespace oglplus
namespace oalplus {

typedef oglplus::ObjectOps<tag::DirectState, tag::Buffer> BufferOps;

/// An @ref oalplus_object encapsulating the OpenAL buffer functionality
/**
 *  @ingroup oalplus_objects
 */
typedef Object<BufferOps> Buffer;

} // namespace oalplus

#endif // include guard
