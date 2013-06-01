/**
 *  @file eglplus/context.hpp
 *  @brief Declares and implements wrapper for EGLContext
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_CONTEXT_1305291005_HPP
#define EGLPLUS_CONTEXT_1305291005_HPP

#include <eglplus/eglfunc.hpp>
#include <eglplus/error.hpp>
#include <eglplus/display.hpp>
#include <eglplus/friend_of.hpp>
#include <eglplus/attrib_list.hpp>
#include <eglplus/context_attrib.hpp>

namespace eglplus {

/// Attribute list for context attributes
typedef AttributeList<ContextAttrib> ContextAttribs;

/// Wrapper around EGLContext
class Context
 : public FriendOf<Display>
 , public FriendOf<Config>
 , public FriendOf<Surface>
{
private:
	Display _display;
	::EGLContext _handle;

	friend class FriendOf<Context>;

	Context(const Context&);

	Context(
		Display display,
		::EGLContext handle
	): _display(display)
	 , _handle(handle)
	{ }

	static ::EGLContext _init(
		const Display& display,
		const Config& config,
		::EGLContext share_context,
		const EGLint* attribs
	)
	{
		::EGLContext result = EGLPLUS_EGLFUNC(CreateContext)(
			FriendOf<Display>::GetHandle(display),
			FriendOf<Config>::GetHandle(config),
			share_context,
			attribs
		);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(DestroyContext));
		return result;
	}
public:
	/// Contexts are move constructible
	Context(Context&& tmp)
	 : _display(tmp._display)
	 , _handle(tmp._handle)
	{
		tmp._handle = EGL_NO_CONTEXT;
	}

	/// Construct a non-sharing context without any attributes
	/**
	 *  @eglsymbols
	 *  @eglfunref{CreateContext}
	 */
	Context(
		const Display& display,
		const Config& config
	): _display(display)
	 , _handle(_init(display, config, EGL_NO_CONTEXT, nullptr))
	{ }

	/// Construct a sharing context without any attributes
	/**
	 *  @eglsymbols
	 *  @eglfunref{CreateContext}
	 */
	Context(
		const Display& display,
		const Config& config,
		const Context& shared_context
	): _display(display)
	 , _handle(_init(display, config, shared_context._handle, nullptr))
	{ }

	/// Destroys the wrapped context
	/**
	 *  @eglsymbols
	 *  @eglfunref{DestroyContext}
	 */
	~Context(void)
	{
		if(_handle != EGL_NO_CONTEXT)
		{
			EGLPLUS_EGLFUNC(DestroyContext)(
				FriendOf<Display>::GetHandle(_display),
				_handle
			);
			EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(DestroyContext));
		}
	}

	/// Makes the context current
	/**
	 *  @eglsymbols
	 *  @eglfunref{MakeCurrent}
	 */
	bool MakeCurrent(
		const Surface& draw_surface,
		const Surface& read_surface
	)
	{
		EGLBoolean result = EGLPLUS_EGLFUNC(MakeCurrent)(
			FriendOf<Display>::GetHandle(_display),
			FriendOf<Surface>::GetHandle(draw_surface),
			FriendOf<Surface>::GetHandle(read_surface),
			_handle
		);
		EGLPLUS_CHECK(EGLPLUS_ERROR_INFO(MakeCurrent));
		return result == EGL_TRUE;
	}

	/// Makes the context current
	/**
	 *  @eglsymbols
	 *  @eglfunref{MakeCurrent}
	 */
	bool MakeCurrent(const Surface& surface)
	{
		EGLBoolean result = EGLPLUS_EGLFUNC(MakeCurrent)(
			FriendOf<Display>::GetHandle(_display),
			FriendOf<Surface>::GetHandle(surface),
			FriendOf<Surface>::GetHandle(surface),
			_handle
		);
		EGLPLUS_CHECK(EGLPLUS_ERROR_INFO(MakeCurrent));
		return result == EGL_TRUE;
	}

	/// Queries a context attribute
	/**
	 *  @eglsymbols
	 *  @eglfunref{QueryContext}
	 */
	bool Query(ContextAttrib attrib, EGLint& value) const
	{
		EGLBoolean result = EGLPLUS_EGLFUNC(QueryContext)(
			FriendOf<Display>::GetHandle(_display),
			_handle,
			EGLint(EGLenum(attrib)),
			&value
		);
		EGLPLUS_CHECK(EGLPLUS_ERROR_INFO(QueryContext));
		return result == EGL_TRUE;
	}

	/// Wait for client API commands to complete
	/**
	 *  @eglsymbols
	 *  @eglfunref{WaitClient}
	 */
	bool WaitClient(void) const
	{
		EGLBoolean result = EGLPLUS_EGLFUNC(WaitClient)();
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(WaitClient));
		return result == EGL_TRUE;
	}

	/// Wait for GL API commands to complete
	/**
	 *  @eglsymbols
	 *  @eglfunref{WaitGL}
	 */
	bool WaitGL(void) const
	{
		EGLBoolean result = EGLPLUS_EGLFUNC(WaitGL)();
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(WaitGL));
		return result == EGL_TRUE;
	}

	/// Wait for native API commands to complete
	/**
	 *  @eglsymbols
	 *  @eglfunref{WaitNative}
	 */
	bool WaitNative(EGLint engine) const
	{
		EGLBoolean result = EGLPLUS_EGLFUNC(WaitNative)(engine);
		EGLPLUS_VERIFY(EGLPLUS_ERROR_INFO(WaitNative));
		return result == EGL_TRUE;
	}
};

} // namespace eglplus

#endif // include guard
