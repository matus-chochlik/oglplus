/**
 *  @file oglplus/glx/context.hpp
 *  @brief Wrapper for GLX contexts
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef UTILS_OGLPLUS_GLX_CONTEXT_1107121519_HPP
#define UTILS_OGLPLUS_GLX_CONTEXT_1107121519_HPP

#include <oglplus/friendly_to.hpp>
#include <oglplus/x11/display.hpp>
#include <oglplus/x11/window.hpp>
#include <oglplus/glx/fb_config.hpp>

#include <X11/Xlib.h>
#include <stdexcept>


namespace oglplus {
namespace glx {

class Context
 : public FriendlyTo<x11::Display>
 , public FriendlyTo<x11::Window>
 , public FriendlyTo<FBConfig>
{
private:
	const x11::Display& _display;
	::GLXContext _handle;

	static ::GLXContext make_context(
		const x11::Display& display,
		const FBConfig& fbc,
		int version_major,
		int version_minor
	)
	{
		typedef GLXContext (*glXCreateContextAttribsARBProc)(
			::Display*,
			::GLXFBConfig,
			::GLXContext,
			Bool,
			 const int*
		);

		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) \
		glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

		const int CONTEXT_MAJOR_VERSION_ARB = 0x2091;
		const int CONTEXT_MINOR_VERSION_ARB = 0x2092;
		int context_attribs[] =
		{
			CONTEXT_MAJOR_VERSION_ARB, version_major,
			CONTEXT_MINOR_VERSION_ARB, version_minor,
			None
		};
		::GLXContext res = glXCreateContextAttribsARB(
			FriendlyTo<x11::Display>::GetHandle(display),
			FriendlyTo<FBConfig>::GetHandle(fbc),
			0, True, context_attribs
		);
		::XSync(
			FriendlyTo<x11::Display>::GetHandle(display),
			False
		);
		return res;
	}
public:
	Context(
		const x11::Display& display,
		const FBConfig& fbc,
		int version_major,
		int version_minor
	): _display(display)
	 , _handle(make_context(_display, fbc, version_major, version_minor))
	{
		if(!_handle)
		{
			throw std::runtime_error(
				"Error creating GLX context"
			);
		}
	}

	Context(const Context&) = delete;

	Context(Context&& temp)
	 : _display(temp._display)
	 , _handle(temp._handle)
	{
		temp._handle = 0;
	}

	~Context(void)
	{
		if(_handle)
		{
			::glXDestroyContext(
				FriendlyTo<x11::Display>::GetHandle(_display),
				_handle
			);
		}
	}

	void MakeCurrent(const x11::Window& window) const
	{
		::glXMakeCurrent(
			FriendlyTo<x11::Display>::GetHandle(_display),
			FriendlyTo<x11::Window>::GetHandle(window),
			_handle
		);
	}

	static void Release(const x11::Display& display)
	{
		::glXMakeCurrent(
			FriendlyTo<x11::Display>::GetHandle(display),
			0, 0
		);
	}

	void SwapBuffers(const x11::Window& window) const
	{
		::glXSwapBuffers(
			FriendlyTo<x11::Display>::GetHandle(_display),
			FriendlyTo<x11::Window>::GetHandle(window)
		);
	}
};


} // namespace glx
} // namespace oglplus

#endif // include guard
