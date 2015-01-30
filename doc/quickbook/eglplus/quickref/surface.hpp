/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[eglplus_surface_attribs
namespace eglplus {

typedef __AttributeList<__SurfaceAttrib, ...> SurfaceAttribs; /*<
Attribute list type for surface attributes.
>*/

typedef __FinishedAttributeList<__SurfaceAttrib, ...> FinishedSurfaceAttribs; /*<
Finished attribute list type for surface attributes.
>*/

//]
//[eglplus_surface_1

class Surface
{
public:
	Surface(Surface&& tmp)
	noexcept;

	~Surface(void); /*<
	Destroys the wrapped surface.
	See [eglfunref DestroySurface].
	>*/

	static Surface Pbuffer(
		const __Display& display,
		const __Config& config,
		const __FinishedSurfaceAttribs& attribs
	); /*<
	Creates a Pbuffer surface.
	See [eglfunc CreatePbufferSurface].
	>*/

	static Surface Pixmap(
		const __Display& display,
		const __Config& config,
		EGLNativePixmapType pixmap,
		const __FinishedSurfaceAttribs& attribs
	); /*<
	Creates a Pixmap surface.
	See [eglfunc CreatePixmapSurface].
	>*/

	static Surface Window(
		const __Display& display,
		const __Config& config,
		EGLNativeWindowType window,
		const __FinishedSurfaceAttribs& attribs
	); /*<
	Creates a Window surface.
	See [eglfunc CreateWindowSurface].
	>*/

// TODO
//]
//[eglplus_surface_2
};

::EGLSurface GetEGLHandle(const __Surface& surface)
noexcept; /*<
Returns the EGL surface handle wrapped by a __Surface.
>*/

} // namespace eglplus
//]

