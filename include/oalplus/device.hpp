/**
 *  @file oalplus/device.hpp
 *  @brief Wrapper around a OpenAL device
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_DEVICE_1303201647_HPP
#define OALPLUS_DEVICE_1303201647_HPP

#include <oalplus/config.hpp>
#include <oalplus/fwd.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/error/alc.hpp>

#include <cstring>
#include <cassert>

namespace oalplus {

/// A range for iteration through the device specifier strings
class DeviceSpecRange
{
private:
	friend class oalplus::DeviceOps;

	const ALchar* _ptr;

	DeviceSpecRange(const ALchar* ptr)
	 : _ptr(ptr)
	{ }
public:
	typedef const ALchar* ValueType;

	/// Returns true when the range is empty (at the end of traversal)
	bool Empty(void) const
	{
		return !_ptr || !(*_ptr);
	}

	/// Returns the specifier string at the front of the range
	const ALchar* Front(void) const
	{
		assert(!Empty());
		return _ptr;
	}

	/// Goes to the next specifier in the range
	void Next(void)
	{
		assert(!Empty());
		_ptr += std::strlen(_ptr)+1;
	}

	/// A synonym for Next
	void StepFront(void)
	{
		Next();
	}
};

/// Class implementing audio device-specific operations
/**
 *  @note Do not use this class directly, use Device instead.
 */
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
	/// Returns a range of specifier strings for available audio devices
	/**
	 *  @alsymbols
	 *  @alcfunref{GetString}
	 *  @alcdefref{DEVICE_SPECIFIER}
	 */
	static DeviceSpecRange Specifiers(void)
	{
		const ALchar* ptr = OALPLUS_ALCFUNC(GetString)(
			nullptr,
			ALC_DEVICE_SPECIFIER
		);
		return DeviceSpecRange(ptr);
	}

	/// Returns a range of specifier strings for available capture devices
	/**
	 *  @alsymbols
	 *  @alcfunref{GetString}
	 *  @alcdefref{CAPTURE_DEVICE_SPECIFIER}
	 */
	static DeviceSpecRange CaptureSpecifiers(void)
	{
		const ALchar* ptr = OALPLUS_ALCFUNC(GetString)(
			nullptr,
			ALC_CAPTURE_DEVICE_SPECIFIER
		);
		return DeviceSpecRange(ptr);
	}
};

/// A wrapper for audio device-related operations
class Device
 : public DeviceOps
{
private:
	Device(const Device&);
public:
	/// Constructs an object referencing the default audio device
	/**
	 *  @alsymbols
	 *  @alcfunref{OpenDevice}
	 */
	Device(void)
	 : DeviceOps(OALPLUS_ALCFUNC(OpenDevice)(nullptr))
	{
		OALPLUS_CHECK_SIMPLE_ALC(_device,OpenDevice);
	}

	/// Constructs an object referencing the specified audio device
	/**
	 *  @alsymbols
	 *  @alcfunref{OpenDevice}
	 */
	Device(const ALchar* dev_spec)
	 : DeviceOps(OALPLUS_ALCFUNC(OpenDevice)(dev_spec))
	{
		OALPLUS_CHECK_SIMPLE_ALC(_device,OpenDevice);
	}

	/// Device is movable
	Device(Device&& tmp)
	 : DeviceOps(tmp._device)
	{
		tmp._device = nullptr;
	}

	/// Closes this device
	/**
	 *  @alsymbols
	 *  @alcfunref{CloseDevice}
	 */
	~Device(void)
	{
		if(_device)
		{
			OALPLUS_ALCFUNC(CloseDevice)(_device);
		}
	}
};

} // namespace oalplus

#endif // include guard
