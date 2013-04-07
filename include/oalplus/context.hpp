/**
 *  @file oalplus/context.hpp
 *  @brief Wrapper around a OpenAL context
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_CONTEXT_1303201648_HPP
#define OALPLUS_CONTEXT_1303201648_HPP

#include <oalplus/config.hpp>
#include <oalplus/device.hpp>
#include <oalplus/error.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/distance_model.hpp>

namespace oalplus {

class ContextOps
{
protected:
	::ALCdevice* _device;
	::ALCcontext* _context;

	ContextOps(
		::ALCdevice* device,
		::ALCcontext* context
	): _device(device)
	 , _context(context)
	{
		assert(_device);
		assert(_context);
	}
public:
	static ContextOps Current(void)
	{
		::ALCcontext* context =
			OALPLUS_ALFUNC(alc,GetCurrentContext)();
		if(!context) HandleALCError(
			ALC_INVALID_CONTEXT,
			OALPLUS_ERROR_INFO(alc,GetCurrentContext),
			true
		);
		::ALCdevice* device =
			OALPLUS_ALFUNC(alc,GetContextsDevice)(context);
		if(!device) HandleALCError(
			ALC_INVALID_DEVICE,
			OALPLUS_ERROR_INFO(alc,GetContextsDevice),
			true
		);
		return ContextOps(device, context);
	}

	DeviceOps ContextsDevice(void) const
	{
		return DeviceOps(_device);
	}

	bool MakeCurrent(void)
	{
		bool result = OALPLUS_ALFUNC(alc,MakeContextCurrent)(_context);
		OALPLUS_VERIFY_ALC(
			OALPLUS_ERROR_INFO(alc,MakeContextCurrent),
			_device
		);
		return result;
	}

	void Process(void)
	{
		OALPLUS_ALFUNC(alc,ProcessContext)(_context);
		OALPLUS_VERIFY_ALC(
			OALPLUS_ERROR_INFO(alc,ProcessContext),
			_device
		);
	}

	void Suspend(void)
	{
		OALPLUS_ALFUNC(alc,SuspendContext)(_context);
		OALPLUS_VERIFY_ALC(
			OALPLUS_ERROR_INFO(alc,SuspendContext),
			_device
		);
	}

	static void DistanceModel(oalplus::DistanceModel dist_model)
	{
		OALPLUS_ALFUNC(al,DistanceModel(ALenum(dist_model)));
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,DistanceModel));
	}

	static oalplus::DistanceModel DistanceModel(void)
	{
		ALint result;
		OALPLUS_ALFUNC(al,GetIntegerv(
			AL_DISTANCE_MODEL,
			&result
		));
		OALPLUS_VERIFY(OALPLUS_ERROR_INFO(al,GetIntegerv));
		return oalplus::DistanceModel(result);
	}
};

class Context
 : public ContextOps
{
private:
	Context(const Context&);
public:
	Context(const DeviceOps& device)
	 : ContextOps(
		device._device,
		OALPLUS_ALFUNC(alc,CreateContext)(device._device, nullptr)
	)
	{
		OALPLUS_CHECK_ALC(
			OALPLUS_ERROR_INFO(alc,CreateContext),
			_device
		);
	}

	// TODO creation with attributes

	Context(Context&& tmp)
	 : ContextOps(tmp._device, tmp._context)
	{
		tmp._context = nullptr;
	}

	~Context(void)
	{
		if(_context)
		{
			OALPLUS_ALFUNC(alc,MakeContextCurrent)(nullptr);
			OALPLUS_ALFUNC(alc,DestroyContext)(_context);
		}
	}
};

// A context that is made current right after construction
class CurrentContext
 : public Context
{
public:
	CurrentContext(const DeviceOps& device)
	 : Context(device)
	{
		MakeCurrent();
	}

	CurrentContext(CurrentContext&& tmp)
	 : Context(static_cast<Context&&>(tmp))
	{
		if(_context) MakeCurrent();
	}
};

} // namespace oalplus

#endif // include guard
