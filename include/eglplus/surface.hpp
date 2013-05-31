/**
 *  @file eglplus/surface.hpp
 *  @brief Declares and implements wrapper for EGLContext
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_SURFACE_1305291005_HPP
#define EGLPLUS_SURFACE_1305291005_HPP

#include <eglplus/eglfunc.hpp>
#include <eglplus/error.hpp>
#include <eglplus/display.hpp>
#include <eglplus/friend_of.hpp>
#include <eglplus/attrib_list.hpp>
#include <eglplus/surface_attrib.hpp>

#include <eglplus/render_buffer.hpp>
#include <eglplus/multisample_resolve.hpp>
#include <eglplus/swap_behavior.hpp>
#include <eglplus/texture_format.hpp>
#include <eglplus/texture_target.hpp>
#include <eglplus/vg_colorspace.hpp>
#include <eglplus/vg_alpha_format.hpp>

namespace eglplus {

/// Attribute list for surface attributes
typedef AttributeList<SurfaceAttrib> SurfaceAttribs;

/// Wrapper for EGLSurfaces
class Surface
 : public FriendOf<Display>
 , public FriendOf<Config>
{
private:
	Display _display;
	::EGLSurface _handle;

	friend class FriendOf<Surface>;

	Surface(const Surface&);


	struct _PBuffer { };

	static ::EGLSurface _init(
		_PBuffer,
		const Display& display,
		const Config& config,
		const SurfaceAttribs& attribs
	)
	{
		::EGLSurface result = EGLPLUS_EGLFUNC(CreatePbufferSurface)(
			FriendOf<Display>::GetHandle(display),
			FriendOf<Config>::GetHandle(config),
			attribs.Get()
		);
		EGLPLUS_CHECK(EGLPLUS_ERROR_INFO(CreatePbufferSurface));
		return result;
	}

	Surface(
		_PBuffer sel,
		const Display& display,
		const Config& config,
		const SurfaceAttribs& attribs
	): _display(display)
	 , _handle(_init(sel, _display, config, attribs))
	{ }

	struct _Pixmap{ };

	static ::EGLSurface _init(
		_Pixmap,
		const Display& display,
		const Config& config,
		EGLNativePixmapType pixmap,
		const SurfaceAttribs& attribs
	)
	{
		::EGLSurface result = EGLPLUS_EGLFUNC(CreatePixmapSurface)(
			FriendOf<Display>::GetHandle(display),
			FriendOf<Config>::GetHandle(config),
			pixmap,
			attribs.Get()
		);
		EGLPLUS_CHECK(EGLPLUS_ERROR_INFO(CreatePixmapSurface));
		return result;
	}

	Surface(
		_Pixmap sel,
		const Display& display,
		const Config& config,
		EGLNativePixmapType pixmap,
		const SurfaceAttribs& attribs
	): _display(display)
	 , _handle(_init(sel, _display, config, pixmap, attribs))
	{ }

	struct _Window { };

	static ::EGLSurface _init(
		_Window,
		const Display& display,
		const Config& config,
		EGLNativeWindowType window,
		const SurfaceAttribs& attribs
	)
	{
		::EGLSurface result = EGLPLUS_EGLFUNC(CreateWindowSurface)(
			FriendOf<Display>::GetHandle(display),
			FriendOf<Config>::GetHandle(config),
			window,
			attribs.Get()
		);
		EGLPLUS_CHECK(EGLPLUS_ERROR_INFO(CreateWindowSurface));
		return result;
	}

	Surface(
		_Window sel,
		const Display& display,
		const Config& config,
		EGLNativeWindowType window,
		const SurfaceAttribs& attribs
	): _display(display)
	 , _handle(_init(sel, _display, config, window, attribs))
	{ }
public:
	/// Surfaces are move-constructible
	Surface(Surface&& tmp)
	 : _display(tmp._display)
	 , _handle(tmp._handle)
	{
		tmp._handle = EGL_NO_SURFACE;
	}

	/// Destroys the wrapped surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{DestroySurface}
	 */
	~Surface(void)
	{
		if(_handle != EGL_NO_SURFACE)
		{
			EGLPLUS_EGLFUNC(DestroySurface)(
				FriendOf<Display>::GetHandle(_display),
				_handle
			);
			EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(DestroySurface));
		}
	}

	/// Creates a PBuffer surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{CreatePbufferSurface}
	 */
	static Surface PBuffer(
		const Display& display,
		const Config& config,
		SurfaceAttribs& attribs
	)
	{
		return Surface(
			_PBuffer(),
			display,
			config,
			attribs.Finish()
		);
	}

	/// Creates a PBuffer surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{CreatePbufferSurface}
	 */
	static Surface PBuffer(
		const Display& display,
		const Config& config,
		SurfaceAttribs&& attribs
	)
	{
		return Surface(
			_PBuffer(),
			display,
			config,
			attribs.Finish()
		);
	}

	/// Creates a Pixmap surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{CreatePixmapSurface}
	 */
	static Surface Pixmap(
		const Display& display,
		const Config& config,
		EGLNativePixmapType pixmap,
		SurfaceAttribs& attribs
	)
	{
		return Surface(
			_Pixmap(),
			display,
			config,
			pixmap,
			attribs.Finish()
		);
	}

	/// Creates a PBuffer surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{CreatePixmapSurface}
	 */
	static Surface Pixmap(
		const Display& display,
		const Config& config,
		EGLNativePixmapType pixmap,
		SurfaceAttribs&& attribs
	)
	{
		return Surface(
			_Pixmap(),
			display,
			config,
			pixmap,
			attribs.Finish()
		);
	}

	/// Creates a Window surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{CreateWindowSurface}
	 */
	static Surface Window(
		const Display& display,
		const Config& config,
		EGLNativeWindowType window,
		SurfaceAttribs& attribs
	)
	{
		return Surface(
			_Window(),
			display,
			config,
			window,
			attribs.Finish()
		);
	}

	/// Creates a PBuffer surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{CreateWindowSurface}
	 */
	static Surface Window(
		const Display& display,
		const Config& config,
		EGLNativeWindowType window,
		SurfaceAttribs&& attribs
	)
	{
		return Surface(
			_Window(),
			display,
			config,
			window,
			attribs.Finish()
		);
	}

	/// Swap buffers
	/**
	 *  @eglsymbols
	 *  @eglfunref{SwapBuffers}
	 */
	bool SwapBuffers(void)
	{
		bool result = EGLPLUS_EGLFUNC(SwapBuffers)(
			FriendOf<Display>::GetHandle(_display),
			_handle
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(SwapBuffers));
		return result;
	}

	/// Copy buffer to native pixmap
	/**
	 *  @eglsymbols
	 *  @eglfunref{CopyBuffers}
	 */
	bool CopyBuffers(EGLNativePixmapType target)
	{
		bool result = EGLPLUS_EGLFUNC(CopyBuffers)(
			FriendOf<Display>::GetHandle(_display),
			_handle,
			target
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(CopyBuffers));
		return result;
	}

	/// Sets the value of the specified attribute
	/**
	 *  @eglsymbols
	 *  @eglfunref{SurfaceAttrib}
	 */
	bool Attrib(SurfaceAttrib attrib, EGLint value)
	{
		bool result = EGLPLUS_EGLFUNC(SurfaceAttrib)(
			FriendOf<Display>::GetHandle(_display),
			_handle,
			EGLint(attrib),
			value
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(SurfaceAttrib));
		return result;
	}

	/// Queries the specified surface attribute value
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 */
	bool QueryAttrib(SurfaceAttrib attrib, EGLint& value) const
	{
		bool result = EGLPLUS_EGLFUNC(QuerySurface)(
			FriendOf<Display>::GetHandle(_display),
			_handle,
			EGLint(attrib),
			&value
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(QuerySurface));
		return result;
	}

	/// Gets the specified surface attribute value
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 */
	EGLint GetAttrib(SurfaceAttrib attrib) const
	{
		EGLint result = EGL_UNKNOWN;
		QueryAttrib(attrib, result);
		return result;
	}

	/// Returns the Width of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 *  @egldefref{WIDTH}
	 */
	EGLint Width(void) const
	{
		return GetAttrib(SurfaceAttrib::Width);
	}

	/// Returns the height of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 *  @egldefref{HEIGHT}
	 */
	EGLint Height(void) const
	{
		return GetAttrib(SurfaceAttrib::Height);
	}

	/// Returns the render buffer setting of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 *  @egldefref{RENDER_BUFFER}
	 */
	eglplus::RenderBuffer RenderBuffer(void) const
	{
		return eglplus::RenderBuffer(
			GetAttrib(SurfaceAttrib::RenderBuffer)
		);
	}

	/// Sets the render buffer setting of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{SurfaceAttrib}
	 *  @egldefref{RENDER_BUFFER}
	 */
	void RenderBuffer(eglplus::RenderBuffer render_buffer)
	{
		Attrib(
			SurfaceAttrib::RenderBuffer,
			EGLint(render_buffer)
		);
	}

	/// Returns the multisample resolve setting of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 *  @egldefref{MULTISAMPLE_RESOLVE}
	 */
	eglplus::MultisampleResolve MultisampleResolve(void) const
	{
		return eglplus::MultisampleResolve(
			GetAttrib(SurfaceAttrib::MultisampleResolve)
		);
	}

	/// Sets the multisample resolve setting of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{SurfaceAttrib}
	 *  @egldefref{MULTISAMPLE_RESOLVE}
	 */
	void MultisampleResolve(eglplus::MultisampleResolve value)
	{
		Attrib(
			SurfaceAttrib::MultisampleResolve,
			EGLint(value)
		);
	}

	/// Returns the buffer swap behavior setting of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 *  @egldefref{SWAP_BEHAVIOR}
	 */
	eglplus::SwapBehavior SwapBehavior(void) const
	{
		return eglplus::SwapBehavior(
			GetAttrib(SurfaceAttrib::SwapBehavior)
		);
	}

	/// Sets the buffer swap behavior setting of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{SurfaceAttrib}
	 *  @egldefref{SWAP_BEHAVIOR}
	 */
	void SwapBehavior(eglplus::SwapBehavior value)
	{
		Attrib(
			SurfaceAttrib::SwapBehavior,
			EGLint(value)
		);
	}

	/// Returns the texture target setting of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 *  @egldefref{TEXTURE_TARGET}
	 */
	eglplus::TextureTarget TextureTarget(void) const
	{
		return eglplus::TextureTarget(
			GetAttrib(SurfaceAttrib::TextureTarget)
		);
	}

	/// Returns the texture format setting of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 *  @egldefref{TEXTURE_FORMAT}
	 */
	eglplus::TextureFormat TextureFormat(void) const
	{
		return eglplus::TextureFormat(
			GetAttrib(SurfaceAttrib::TextureFormat)
		);
	}

	/// Returns the OpenVG colorspace setting of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 *  @egldefref{VG_COLORSPACE}
	 */
	eglplus::VGColorspace VGColorspace(void) const
	{
		return eglplus::VGColorspace(
			GetAttrib(SurfaceAttrib::VGColorspace)
		);
	}

	/// Returns the OpenVG alpha format of the surface
	/**
	 *  @eglsymbols
	 *  @eglfunref{QuerySurface}
	 *  @egldefref{VG_ALPHA_FORMAT}
	 */
	eglplus::VGAlphaFormat VGAlphaFormat(void) const
	{
		return eglplus::VGAlphaFormat(
			GetAttrib(SurfaceAttrib::VGAlphaFormat)
		);
	}
};

} // namespace eglplus

#endif // include guard
