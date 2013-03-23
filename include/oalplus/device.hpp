/**
 *  @file oalplus/device.hpp
 *  @brief Wrapper around a OpenAL device
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_DEVICE_1303201647_HPP
#define OALPLUS_DEVICE_1303201647_HPP

#include <oalplus/config.hpp>
#include <oalplus/fwd.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/error.hpp>

#include <cstring>
#include <cassert>

namespace oalplus {
namespace aux {

class DeviceSpecRange
{
private:
	friend class oalplus::DeviceOps;

	const ALchar* _ptr;

	DeviceSpecRange(const ALchar* ptr)
	 : _ptr(ptr)
	{ }
public:
	bool Empty(void) const
	{
		return !_ptr || !(*_ptr);
	}

	const ALchar* Front(void) const
	{
		assert(!Empty());
		return _ptr;
	}

	void Next(void)
	{
		assert(!Empty());
		_ptr += std::strlen(_ptr)+1;
	}

	void StepFront(void)
	{
		Next();
	}
};

} // namespace aux

class DeviceOps
{
protected:
	friend class ContextOps;
	friend class Context;

	::ALCdevice* _device;

	DeviceOps(::ALCdevice* device)
	 : _device(device)
	{
		assert(_device);
	}
public:
	static aux::DeviceSpecRange Specifiers(void)
	{
		const ALchar* ptr = OALPLUS_ALFUNC(alc,GetString)(
			nullptr,
			ALC_DEVICE_SPECIFIER
		);
		return aux::DeviceSpecRange(ptr);
	}

	static aux::DeviceSpecRange CaptureSpecifiers(void)
	{
		const ALchar* ptr = OALPLUS_ALFUNC(alc,GetString)(
			nullptr,
			ALC_CAPTURE_DEVICE_SPECIFIER
		);
		return aux::DeviceSpecRange(ptr);
	}
};

class Device
 : public DeviceOps
{
private:
	Device(const Device&);
public:
	Device(void)
	 : DeviceOps(OALPLUS_ALFUNC(alc,OpenDevice)(nullptr))
	{
		OALPLUS_CHECK_ALC(
			OALPLUS_ERROR_INFO(alc,OpenDevice),
			_device
		);
	}

	Device(const ALchar* dev_spec)
	 : DeviceOps(OALPLUS_ALFUNC(alc,OpenDevice)(dev_spec))
	{
		OALPLUS_CHECK_ALC(
			OALPLUS_ERROR_INFO(alc,OpenDevice),
			_device
		);
	}

	Device(Device&& tmp)
	 : DeviceOps(tmp._device)
	{
		tmp._device = nullptr;
	}

	~Device(void)
	{
		if(_device)
		{
			OALPLUS_ALFUNC(alc,CloseDevice)(_device);
		}
	}
};

} // namespace oalplus

#endif // include guard
