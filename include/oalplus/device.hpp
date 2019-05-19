/**
 *  @file oalplus/device.hpp
 *  @brief Wrapper around a OpenAL device
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_DEVICE_1303201647_HPP
#define OALPLUS_DEVICE_1303201647_HPP

#include <oalplus/config.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/data_format.hpp>
#include <oalplus/error/alc.hpp>
#include <oalplus/fwd.hpp>

#include <oalplus/detail/sep_str_range.hpp>

#include <cassert>
#include <cstring>

namespace oalplus {

/// A range for iteration through the device specifier strings
class DeviceSpecRange {
private:
    const ALchar* _ptr;

public:
    DeviceSpecRange(const ALchar* ptr)
      : _ptr(ptr) {
    }

    typedef const ALchar* ValueType;

    /// Returns true when the range is empty (at the end of traversal)
    bool Empty() const {
        return !_ptr || !(*_ptr);
    }

    /// Returns the specifier string at the front of the range
    StrCRef Front() const {
        assert(!Empty());
        return StrCRef(_ptr);
    }

    /// Goes to the next specifier in the range
    void Next() {
        assert(!Empty());
        _ptr += std::strlen(_ptr) + 1;
    }

    /// A synonym for Next
    void StepFront() {
        Next();
    }
};

class DevCommonOps {
protected:
    friend class ContextOps;
    friend class Context;

    ::ALCdevice* _device;

    DevCommonOps(::ALCdevice* device)
      : _device(device) {
        assert(_device);
    }

public:
    /// Device is movable
    DevCommonOps(DevCommonOps&& tmp)
      : _device(tmp._device) {
        tmp._device = nullptr;
    }

#if OALPLUS_DOCUMENTATION_ONLY
    /// Returns a range of ALC extension strings
    /**
     *  @alsymbols
     *  @alfunref{GetString}
     *  @aldefref{EXTENSIONS}
     */
    static Range<String> Extensions();
#else
    static aux::SepStrRange Extensions() {
        const ALchar* str = OALPLUS_ALCFUNC(GetString)(nullptr, ALC_EXTENSIONS);
        OALPLUS_CHECK_SIMPLE_ALC(nullptr, GetString);

        return aux::SepStrRange(reinterpret_cast<const char*>(str));
    }
#endif
};

/// Class implementing audio playback device-specific operations
/**
 *  @note Do not use this class directly, use Device instead.
 */
template <>
class DeviceOps<tag::Playback> : public DevCommonOps {
protected:
    friend class ContextOps;

    DeviceOps(::ALCdevice* device)
      : DevCommonOps(device) {
    }

public:
    /// Returns the device specifier string
    /**
     *  @alsymbols
     *  @alcfunref{GetString}
     *  @alcdefref{DEVICE_SPECIFIER}
     */
    StrCRef Specifier() const {
        const ALchar* str =
          OALPLUS_ALCFUNC(GetString)(_device, ALC_DEVICE_SPECIFIER);
        OALPLUS_CHECK_SIMPLE_ALC(_device, GetString);
        return StrCRef(str);
    }

    /// Returns a range of specifier strings for available audio devices
    /**
     *  @alsymbols
     *  @alcfunref{GetString}
     *  @alcdefref{DEVICE_SPECIFIER}
     */
    static DeviceSpecRange Specifiers() {
        const ALchar* ptr =
          OALPLUS_ALCFUNC(GetString)(nullptr, ALC_DEVICE_SPECIFIER);
        OALPLUS_CHECK_SIMPLE_ALC(nullptr, GetString);
        return DeviceSpecRange(ptr);
    }
};

/// Class implementing audio capture device-specific operations
/**
 *  @note Do not use this class directly, use Device instead.
 */
template <>
class DeviceOps<tag::Capture> : public DevCommonOps {
protected:
    DeviceOps(::ALCdevice* device)
      : DevCommonOps(device) {
    }

public:
    /// Returns the capture device specifier string
    /**
     *  @alsymbols
     *  @alcfunref{GetString}
     *  @alcdefref{CAPTURE_DEVICE_SPECIFIER}
     */
    StrCRef Specifier() const {
        const ALchar* str =
          OALPLUS_ALCFUNC(GetString)(_device, ALC_CAPTURE_DEVICE_SPECIFIER);
        OALPLUS_CHECK_SIMPLE_ALC(_device, GetString);
        return StrCRef(str);
    }

    /// Returns a range of specifier strings for available capture devices
    /**
     *  @alsymbols
     *  @alcfunref{GetString}
     *  @alcdefref{CAPTURE_DEVICE_SPECIFIER}
     */
    static DeviceSpecRange Specifiers() {
        const ALchar* ptr =
          OALPLUS_ALCFUNC(GetString)(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);
        OALPLUS_CHECK_SIMPLE_ALC(nullptr, GetString);
        return DeviceSpecRange(ptr);
    }

    /// Starts audio capture on this device
    /**
     *  @alsymbols
     *  @alcfunref{CaptureStart}
     */
    void Start() {
        OALPLUS_ALCFUNC(CaptureStart)(_device);
        OALPLUS_CHECK_SIMPLE_ALC(_device, CaptureStart);
    }

    /// Stop audio capture on this device
    /**
     *  @alsymbols
     *  @alcfunref{CaptureStop}
     */
    void Stop() {
        OALPLUS_ALCFUNC(CaptureStop)(_device);
        OALPLUS_CHECK_SIMPLE_ALC(_device, CaptureStop);
    }

    /// Gets the number of samples captured on this device
    /**
     *  @alsymbols
     *  @alcfunref{GetInteger}
     *  @alcdefref{CAPTURE_SAMPLES}
     */
    ALCsizei Samples() const {
        ALCint result = 0;
        OALPLUS_ALCFUNC(GetIntegerv)(_device, ALC_CAPTURE_SAMPLES, 1, &result);
        OALPLUS_CHECK_SIMPLE_ALC(_device, GetIntegerv);
        return ALCsizei(result);
    }

    /// Gets the samples captured on this device
    /**
     *  @alsymbols
     *  @alcfunref{CaptureSamples}
     */
    void Samples(ALCvoid* buffer, ALCsizei samples) const {
        OALPLUS_ALCFUNC(CaptureSamples)(_device, buffer, samples);
        OALPLUS_CHECK_SIMPLE_ALC(_device, CaptureSamples);
    }
};

/// Audio playback device
class Device : public DeviceOps<tag::Playback> {
private:
    typedef DeviceOps<tag::Playback> Base;

public:
    /// Constructs an object referencing the default audio device
    /**
     *  @alsymbols
     *  @alcfunref{OpenDevice}
     */
    Device()
      : Base(OALPLUS_ALCFUNC(OpenDevice)(nullptr)) {
        OALPLUS_CHECK_SIMPLE_ALC(_device, OpenDevice);
    }

    /// Constructs an object referencing the specified audio device
    /**
     *  @alsymbols
     *  @alcfunref{OpenDevice}
     */
    Device(const StrCRef& dev_spec)
      : Base(OALPLUS_ALCFUNC(OpenDevice)(dev_spec.c_str())) {
        OALPLUS_CHECK_SIMPLE_ALC(_device, OpenDevice);
    }

    /// Closes this device
    /**
     *  @alsymbols
     *  @alcfunref{CloseDevice}
     */
    ~Device() {
        if(_device) {
            OALPLUS_ALCFUNC(CloseDevice)(_device);
        }
    }
};

/// Audio capture device
class CaptureDevice : public DeviceOps<tag::Capture> {
private:
    typedef DeviceOps<tag::Capture> Base;

public:
    /// Constructs an object referencing the default audio device
    /**
     *  @alsymbols
     *  @alcfunref{OpenDevice}
     */
    CaptureDevice(ALCuint frequency, DataFormat format, ALCsizei bufsize)
      : Base(OALPLUS_ALCFUNC(CaptureOpenDevice)(
          nullptr, frequency, ALCenum(format), bufsize)) {
        OALPLUS_CHECK_SIMPLE_ALC(_device, CaptureOpenDevice);
    }

    /// Constructs an object referencing the specified audio device
    /**
     *  @alsymbols
     *  @alcfunref{OpenDevice}
     */
    CaptureDevice(
      const StrCRef& dev_spec,
      ALCuint frequency,
      DataFormat format,
      ALCsizei bufsize)
      : Base(OALPLUS_ALCFUNC(CaptureOpenDevice)(
          dev_spec.c_str(), frequency, ALCenum(format), bufsize)) {
        OALPLUS_CHECK_SIMPLE_ALC(_device, CaptureOpenDevice);
    }

    /// Closes this device
    /**
     *  @alsymbols
     *  @alcfunref{CloseDevice}
     */
    ~CaptureDevice() {
        if(_device) {
            OALPLUS_ALCFUNC(CaptureCloseDevice)(_device);
        }
    }
};

} // namespace oalplus

#endif // include guard
