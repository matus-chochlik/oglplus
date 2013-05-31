/**
 *  @file eglplus/configs.hpp
 *  @brief EGL configurations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_CONFIGS_1303292057_HPP
#define EGLPLUS_CONFIGS_1303292057_HPP

#include <eglplus/bitfield.hpp>
#include <eglplus/config_attrib.hpp>
#include <eglplus/color_buffer_type.hpp>
#include <eglplus/transparent_type.hpp>
#include <eglplus/config_caveat.hpp>
#include <eglplus/renderable_type.hpp>
#include <eglplus/surface_type.hpp>

namespace eglplus {

/// A wrapper for EGL configuration
class Config
 : public FriendOf<Display>
{
private:
	Display _display;
	::EGLConfig _handle;

	friend class FriendOf<Config>;
public:
	Config(const Display& display, ::EGLConfig handle)
	 : _display(display)
	 , _handle(handle)
	{ }

	/// Get the value of a specified attribute
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 */
	EGLint GetAttrib(ConfigAttrib attrib) const
	{
		EGLint result = 0;
		EGLPLUS_EGLFUNC(GetConfigAttrib)(
			FriendOf<Display>::GetHandle(_display),
			this->_handle,
			EGLint(attrib),
			&result
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(GetConfigAttrib));
		return result;
	}

	/// Get the unique configuration identifier
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{CONFIG_ID}
	 */
	EGLint ConfigId(void) const
	{
		return GetAttrib(ConfigAttrib::ConfigId);
	}

	/// Return the total component bits of the color buffer
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{BUFFER_SIZE}
	 */
	EGLint BufferSize(void) const
	{
		return GetAttrib(ConfigAttrib::BufferSize);
	}

	/// Returns the number of bits of the red color component
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{RED_SIZE}
	 */
	EGLint RedSize(void) const
	{
		return GetAttrib(ConfigAttrib::RedSize);
	}

	/// Returns the number of bits of the green color component
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{GREEN_SIZE}
	 */
	EGLint GreenSize(void) const
	{
		return GetAttrib(ConfigAttrib::GreenSize);
	}

	/// Returns the number of bits of the blue color component
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{BLUE_SIZE}
	 */
	EGLint BlueSize(void) const
	{
		return GetAttrib(ConfigAttrib::BlueSize);
	}

	/// Returns the number of bits of the luminance component
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{LUMINANCE_SIZE}
	 */
	EGLint LuminanceSize(void) const
	{
		return GetAttrib(ConfigAttrib::LuminanceSize);
	}

	/// Returns the number of bits of the alpha component
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{ALPHA_SIZE}
	 */
	EGLint AlphaSize(void) const
	{
		return GetAttrib(ConfigAttrib::AlphaSize);
	}

	/// Returns the number of bits of the depth component
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{DEPTH_SIZE}
	 */
	EGLint DepthSize(void) const
	{
		return GetAttrib(ConfigAttrib::DepthSize);
	}

	/// Returns the maximum width of PBuffers in pixels
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{MAX_PBUFFER_WIDTH}
	 */
	EGLint MaxPBufferWidth(void) const
	{
		return GetAttrib(ConfigAttrib::MaxPBufferWidth);
	}

	/// Returns the maximum height of PBuffers in pixels
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{MAX_PBUFFER_HEIGHT}
	 */
	EGLint MaxPBufferHeight(void) const
	{
		return GetAttrib(ConfigAttrib::MaxPBufferHeight);
	}

	/// Returns the maximum size (number of pixels) of PBuffers
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{MAX_PBUFFER_PIXELS}
	 */
	EGLint MaxPBufferPixels(void) const
	{
		return GetAttrib(ConfigAttrib::MaxPBufferPixels);
	}

	/// Returns the caveat for this config
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{CONFIG_CAVEAT}
	 */
	eglplus::ConfigCaveat ConfigCaveat(void) const
	{
		return eglplus::ConfigCaveat(
			GetAttrib(ConfigAttrib::ConfigCaveat)
		);
	}

	/// Returns the color buffer type
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{COLOR_BUFFER_TYPE}
	 */
	eglplus::ColorBufferType ColorBufferType(void) const
	{
		return eglplus::ColorBufferType(
			GetAttrib(ConfigAttrib::ColorBufferType)
		);
	}

	/// Returns the transparency type
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{TRANSPARENT_TYPE}
	 */
	eglplus::TransparentType TransparentType(void) const
	{
		return eglplus::TransparentType(
			GetAttrib(ConfigAttrib::TransparentType)
		);
	}

	/// Returns the renderable type bits
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{RENDERABLE_TYPE}
	 */
	Bitfield<eglplus::RenderableTypeBit> RenderableTypes(void) const
	{
		return Bitfield<eglplus::RenderableTypeBit>(
			GetAttrib(ConfigAttrib::RenderableType)
		);
	}

	/// Returns true if a specified renderable type is supported
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{RENDERABLE_TYPE}
	 */
	bool HasRenderableType(eglplus::RenderableTypeBit type) const
	{
		EGLint a = GetAttrib(ConfigAttrib::RenderableType);
		EGLint b = EGLint(type);
		return (a & b) == b;
	}

	/// Returns the surface type bits
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{SURFACE_TYPE}
	 */
	Bitfield<eglplus::SurfaceTypeBit> SurfaceTypes(void) const
	{
		return Bitfield<eglplus::SurfaceTypeBit>(
			GetAttrib(ConfigAttrib::SurfaceType)
		);
	}

	/// Returns true if a specified surface type is supported
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{SURFACE_TYPE}
	 */
	bool HasSurfaceType(eglplus::SurfaceTypeBit type) const
	{
		EGLint a = GetAttrib(ConfigAttrib::SurfaceType);
		EGLint b = EGLint(type);
		return (a & b) == b;
	}

	/// Returns the conformant bits for this config
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{CONFORMANT}
	 */
	Bitfield<eglplus::RenderableTypeBit> Conformant(void) const
	{
		return Bitfield<eglplus::RenderableTypeBit>(
			GetAttrib(ConfigAttrib::Conformant)
		);
	}

	/// Returns true if the config is conformant to a renderable type
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetConfigAttrib}
	 *  @egldefref{CONFORMANT}
	 */
	bool IsConformantTo(eglplus::RenderableTypeBit type) const
	{
		EGLint a = GetAttrib(ConfigAttrib::Conformant);
		EGLint b = EGLint(type);
		return (a & b) == b;
	}
};

/// A provides access to all configurations of a Display
class Configs
 : public FriendOf<Display>
{
private:
	Display _display;
	std::vector<EGLConfig> _configs;

	struct _config_range_conv
	{
		Display _display;

		_config_range_conv(const Display& display)
		 : _display(display)
		{ }

		Config operator()(EGLConfig handle) const
		{
			return Config(_display, handle);
		}
	};
public:
	/// Gets the configurations for the specified display
	Configs(const Display& display)
	 : _display(display)
	{
		EGLint num = 0;
		EGLPLUS_EGLFUNC(GetConfigs)(
			FriendOf<Display>::GetHandle(_display),
			nullptr,
			0,
			&num
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(GetConfigs));
		_configs.resize(num);
		EGLPLUS_EGLFUNC(GetConfigs)(
			FriendOf<Display>::GetHandle(_display),
			_configs.data(),
			num,
			&num
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(GetConfigs));
	}

	typedef aux::ConvIterRange<
		std::vector<EGLConfig>::const_iterator,
		Config,
		_config_range_conv
	> ConfigRange;

	/// Returns a range of all supported configurations
	ConfigRange All(void) const
	{
		return ConfigRange(
			_config_range_conv(_display),
			_configs.begin(),
			_configs.end()
		);
	}
};

} // namespace oglplus

#endif // include guard
