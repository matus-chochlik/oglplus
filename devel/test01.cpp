/**
 *  .file devel/test01.cpp
 *  This source file is here for development/testing purposes
 *  and its contents may change without any prior notice.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef NOT_DEFINED // TODO: remove this

#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include <string>
#include <stdexcept>
#include <iostream>
#include <cassert>

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

namespace x11 {

template <typename Object>
class FriendOf
{
protected:
	static auto GetHandle(const Object& object) ->
	decltype(object._handle)
	{
		return object._handle;
	}
};

} // namespace x11

namespace glx {

using x11::FriendOf;

} // namespace glx

namespace x11 {

class Display
{
private:
	::Display* _handle;

	friend class FriendOf<Display>;
public:
	Display(const char* name = 0)
	 : _handle(::XOpenDisplay(name))
	{
		if(!_handle)
			throw std::runtime_error("Failed to open X display");
	}

	Display(const Display&) = delete;
	Display(Display&& temp)
	 : _handle(temp._handle)
	{
		temp._handle = 0;
	}

	~Display(void)
	{
		if(_handle) ::XCloseDisplay(_handle);
	}
};

} // namespace x11

namespace glx {

class FBConfigs;

class FBConfig
{
private:
	::GLXFBConfig _handle;

	FBConfig(::GLXFBConfig handle)
	 : _handle(handle)
	{ }

	friend class FBConfigs;
	friend class FriendOf<FBConfig>;
public:
};

} // namespace glx

namespace x11 {

class VisualInfo
 : public FriendOf<x11::Display>
 , public FriendOf<glx::FBConfig>
{
private:
	::XVisualInfo* _handle;

	friend class FriendOf<VisualInfo>;
public:
	VisualInfo(const Display& display, const glx::FBConfig& fbc)
	 : _handle(
		::glXGetVisualFromFBConfig(
			FriendOf<Display>::GetHandle(display),
			FriendOf<glx::FBConfig>::GetHandle(fbc)
		)
	)
	{
		if(!_handle)
		{
			throw std::runtime_error(
				"Error Getting X VisualInfo from GLX FB config"
			);
		}
	}

	VisualInfo(const VisualInfo&) = delete;
	VisualInfo(VisualInfo&& temp)
	 : _handle(temp._handle)
	{
		temp._handle = 0;
	}

	~VisualInfo(void)
	{
		if(_handle) ::XFree(_handle);
	}
};

class ColorMap
 : public FriendOf<Display>
 , public FriendOf<VisualInfo>
{
private:
	const Display& _display;
	::Colormap _handle;

	friend class FriendOf<ColorMap>;
public:
	ColorMap(const Display& display, const VisualInfo& vi)
	 : _display(display)
	 , _handle(
		::XCreateColormap(
			FriendOf<Display>::GetHandle(_display),
			RootWindow(
				FriendOf<Display>::GetHandle(_display),
				FriendOf<VisualInfo>::GetHandle(vi)->screen
			),
			FriendOf<VisualInfo>::GetHandle(vi)->visual,
			AllocNone
		)
	)
	{
		if(!_handle)
		{
			throw std::runtime_error(
				"Error creating X colormap"
			);
		}
	}

	ColorMap(const ColorMap&) = delete;

	ColorMap(ColorMap&& temp)
	 : _display(temp._display)
	 , _handle(temp._handle)
	{
		temp._handle = 0;
	}

	~ColorMap(void)
	{
		if(_handle)
		{
			::XFreeColormap(
				FriendOf<Display>::GetHandle(_display),
				_handle
			);
		}
	}

};

class Window
 : public FriendOf<Display>
 , public FriendOf<VisualInfo>
 , public FriendOf<ColorMap>
{
private:
	const Display& _display;
	ColorMap _cmap;
	::Window _handle;

	static ::Window make_window(
		const Display& display,
		const VisualInfo& vi,
		const ColorMap& cmap
	)
	{
		::XSetWindowAttributes swa;
		swa.colormap = FriendOf<ColorMap>::GetHandle(cmap);
		swa.background_pixmap = None;
		swa.border_pixel = 0;
		swa.event_mask = StructureNotifyMask;
		//
		return ::XCreateWindow(
			FriendOf<Display>::GetHandle(display),
			RootWindow(
				FriendOf<Display>::GetHandle(display),
				FriendOf<VisualInfo>::GetHandle(vi)->screen
			),
			0, 0, 800, 600,
			0,
			FriendOf<VisualInfo>::GetHandle(vi)->depth,
			InputOutput,
			FriendOf<VisualInfo>::GetHandle(vi)->visual,
			CWBorderPixel | CWColormap | CWEventMask,
			&swa
		);
	}

	friend class FriendOf<Window>;
public:
	Window(
		const Display& display,
		const VisualInfo& vi,
		ColorMap&& cmap,
		const char* title
	): _display(display)
	 , _cmap(std::move(cmap))
	 , _handle(make_window(_display, vi, _cmap))
	{
		if(!_handle)
		{
			throw std::runtime_error(
				"Error creating X window"
			);
		}
		::XStoreName(
			FriendOf<Display>::GetHandle(_display),
			_handle,
			title
		);
		::XMapWindow(
			FriendOf<Display>::GetHandle(_display),
			_handle
		);
	}

	Window(const Window&) = delete;

	Window(Window&& temp)
	 : _display(temp._display)
	 , _cmap(std::move(temp._cmap))
	 , _handle(temp._handle)
	{
		temp._handle = 0;
	}

	~Window(void)
	{
		if(_handle)
		{
			::XDestroyWindow(
				FriendOf<Display>::GetHandle(_display),
				_handle
			);
		}
	}
};

} // namespace x11

namespace glx {

class Version
 : public FriendOf<x11::Display>
{
private:
	int _major;
	int _minor;
public:
	Version(const x11::Display& display)
	 : _major(0)
	 , _minor(0)
	{
		if(!::glXQueryVersion(
			GetHandle(display),
			&_major,
			&_minor
		)) throw std::runtime_error("Error querying GLX version");
	}

	void AssertAtLeast(int major, int minor) const
	{
		if((_major < major) || ((_major == major) && (_minor < minor)))
			throw std::runtime_error("Invalid GLX version");
	}

	int Major(void) const
	{
		return _major;
	}

	int Minor(void) const
	{
		return _minor;
	}
};

class FBConfigs
 : public FriendOf<x11::Display>
 , public FriendOf<x11::VisualInfo>
{
private:
	int _count;
	GLXFBConfig* _handle;
public:
	FBConfigs(const x11::Display& display, const int* visual_attribs)
	 : _count(0)
	 , _handle(
		::glXChooseFBConfig(
			FriendOf<x11::Display>::GetHandle(display),
			DefaultScreen(FriendOf<x11::Display>::GetHandle(display)),
			visual_attribs,
			&_count
		)
	)
	{
		if(!_handle || (_count <= 0))
		{
			throw std::runtime_error(
				"Failed to get matching framebuffer configs"
			);
		}
	}

	FBConfigs(const FBConfigs&) = delete;

	FBConfigs(FBConfigs&& temp)
	 : _count(temp._count)
	 , _handle(temp._handle)
	{
		temp._count = 0;
		temp._handle = 0;
	}

	~FBConfigs(void)
	{
		if(_handle) ::XFree(_handle);
	}

	FBConfig FindBest(const x11::Display& display) const
	{
		int best = -1, best_num = -1;
		assert(_count > 0);
		for(int i=0;i!=_count;++i)
		{
			int sample_buf, samples;

			::glXGetFBConfigAttrib(
				FriendOf<x11::Display>::GetHandle(display),
				_handle[i],
				GLX_SAMPLE_BUFFERS,
				&sample_buf
			);
			::glXGetFBConfigAttrib(
				FriendOf<x11::Display>::GetHandle(display),
				_handle[i],
				GLX_SAMPLES,
				&samples
			);
			if((best < 0) || (sample_buf && (samples > best_num)))
			{
				best = i;
				best_num = samples;
			}
		}
		assert(best >= 0);
		assert(best < _count);
		return FBConfig(_handle[best]);
	}
};

class Context
 : public FriendOf<x11::Display>
 , public FriendOf<x11::Window>
 , public FriendOf<FBConfig>
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
		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) \
		glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

		int context_attribs[] =
		{
			GLX_CONTEXT_MAJOR_VERSION_ARB, version_major,
			GLX_CONTEXT_MINOR_VERSION_ARB, version_minor,
			None
		};
		::GLXContext res = glXCreateContextAttribsARB(
			FriendOf<x11::Display>::GetHandle(display),
			FriendOf<FBConfig>::GetHandle(fbc),
			0, True, context_attribs
		);
		::XSync(
			FriendOf<x11::Display>::GetHandle(display),
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
				FriendOf<x11::Display>::GetHandle(_display),
				_handle
			);
		}
	}

	void MakeCurrent(const x11::Window& window) const
	{
		::glXMakeCurrent(
			FriendOf<x11::Display>::GetHandle(_display),
			FriendOf<x11::Window>::GetHandle(window),
			_handle
		);
	}

	static void Release(const x11::Display& display)
	{
		::glXMakeCurrent(
			FriendOf<x11::Display>::GetHandle(display),
			0, 0
		);
	}

	void SwapBuffers(const x11::Window& window) const
	{
		::glXSwapBuffers(
			FriendOf<x11::Display>::GetHandle(_display),
			FriendOf<x11::Window>::GetHandle(window)
		);
	}
};

} // namespace glx

void run(const x11::Display& display)
{
	static int visual_attribs[] =
	{
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		//GLX_SAMPLE_BUFFERS  , 1,
		//GLX_SAMPLES         , 4,
		None
	};
	glx::Version version(display);
	version.AssertAtLeast(1, 3);

	glx::FBConfig fbc = glx::FBConfigs(
		display,
		visual_attribs
	).FindBest(display);

	x11::VisualInfo vi(display, fbc);
	x11::Window win(
		display,
		vi,
		x11::ColorMap(display, vi),
		"OpenGL 3.0 window"
	);
	glx::Context ctx(display, fbc, 3, 0);
	ctx.MakeCurrent(win);

	glClearColor ( 0, 0.5, 1, 1 );
	glClear( GL_COLOR_BUFFER_BIT );
	ctx.SwapBuffers(win);

	::sleep(1);
	ctx.Release(display);
}

int main (int argc, char ** argv)
{
	try
	{
		run(x11::Display());
		std::cout << "Done" << std::endl;
	}
	catch(std::runtime_error& rte)
	{
		std::cerr << "Error: " << rte.what() << std::endl;
		return 1;
	}
	return 0;
}
#else
int main(void){return 0;}
#endif
