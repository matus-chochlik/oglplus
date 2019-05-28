/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[eglplus_surface_attribs

using SurfaceAttribs = __AttributeList<__SurfaceAttrib, ...>; /*<
Attribute list type for surface attributes.
>*/

using FinishedSurfaceAttribs =
  __FinishedAttributeList<__SurfaceAttrib, ...>; /*<
Finished attribute list type for surface attributes.
>*/

//]
//[eglplus_surface_1

class Surface {
public:
    Surface(Surface&& tmp) noexcept;

    ~Surface(); /*<
    Destroys the wrapped surface.
    See [eglfunref DestroySurface].
    >*/

    static Surface Pbuffer(
      const __Display& display,
      const __Config& config,
      const __FinishedSurfaceAttribs& attribs); /*<
                                             Creates a Pbuffer surface.
                                             See [eglfunc CreatePbufferSurface].
                                             >*/

    static Surface Pixmap(
      const __Display& display,
      const __Config& config,
      EGLNativePixmapType pixmap,
      const __FinishedSurfaceAttribs& attribs); /*<
                                             Creates a Pixmap surface.
                                             See [eglfunc CreatePixmapSurface].
                                             >*/

    static Surface Window(
      const __Display& display,
      const __Config& config,
      EGLNativeWindowType window,
      const __FinishedSurfaceAttribs& attribs); /*<
                                             Creates a Window surface.
                                             See [eglfunc CreateWindowSurface].
                                             >*/

    __Boolean SwapBuffers(); /*<
    Swap the front and back buffers.
    See [eglfunc SwapBuffers].
    >*/

    __Boolean CopyBuffers(EGLNativePixmapType target); /*<
    Copy buffer to native pixmap.
    See [eglfunc CopyBuffers].
    >*/

    __Boolean Attrib(__SurfaceAttrib attrib, EGLint value); /*<
    Sets the value of the specified attribute.
    See [eglfunc SurfaceAttrib].
    >*/

    __Boolean QueryAttrib(__SurfaceAttrib attrib, EGLint& value) const; /*<
    Queries the specified surface attribute value.
    See [eglfunc QuerySurface].
    >*/

    EGLint GetAttrib(__SurfaceAttrib attrib) const; /*<
    Gets the specified surface attribute value.
    See [eglfunc QuerySurface].
    >*/

    EGLint Width() const; /*<
    Returns the width of the surface.
    See [eglfunc QuerySurface], [eglconst WIDTH].
    >*/

    EGLint Height() const; /*<
    Returns the height of the surface.
    See [eglfunc QuerySurface], [eglconst HEIGHT].
    >*/
    //]
    //[eglplus_surface_2

    __RenderBuffer RenderBuffer() const; /*<
    Returns the render buffer setting of the surface.
    See [eglfunc QuerySurface], [eglconst RENDER_BUFFER].
    >*/

    void RenderBuffer(__RenderBuffer render_buffer); /*<
    Changes the render buffer setting of the surface.
    See [eglfunc SurfaceAttrib], [eglconst RENDER_BUFFER].
    >*/

    __MultisampleResolve MultisampleResolve() const; /*<
    Returns the multisample resolve setting of the surface.
    See [eglfunc QuerySurface], [eglconst MULTISAMPLE_RESOLVE].
    >*/

    void MultisampleResolve(__MultisampleResolve value); /*<
    Changes the multisample resolve setting of the surface.
    See [eglfunc SurfaceAttrib], [eglconst MULTISAMPLE_RESOLVE].
    >*/

    __SwapBehavior SwapBehavior() const; /*<
    Returns the buffer swap behavior setting of the surface.
    See [eglfunc QuerySurface], [eglconst SWAP_BEHAVIOR].
    >*/

    void SwapBehavior(__SwapBehavior value); /*<
    Changes the buffer swap behavior setting of the surface.
    See [eglfunc SurfaceAttrib], [eglconst SWAP_BEHAVIOR].
    >*/

    __TextureTarget TextureTarget() const; /*<
    Returns the texture target setting of the surface.
    See [eglfunc QuerySurface], [eglconst TEXTURE_TARGET].
    >*/

    __TextureFormat TextureFormat() const; /*<
    Returns the texture format setting of the surface.
    See [eglfunc QuerySurface], [eglconst TEXTURE_FORMAT].
    >*/

    __GLColorspace GLColorspace() const; /*<
    Returns the OpenGL colorspace setting of the surface.
    See [eglfunc QuerySurface], [eglconst GL_COLORSPACE].
    >*/

    __VGColorspace VGColorspace() const; /*<
    Returns the OpenVG colorspace setting of the surface.
    See [eglfunc QuerySurface], [eglconst VG_COLORSPACE].
    >*/

    __VGAlphaFormat VGAlphaFormat() const; /*<
    Returns the OpenVG alpha format of the surface.
    See [eglfunc QuerySurface], [eglconst VG_ALPHA_FORMAT].
    >*/
};

::EGLSurface GetEGLHandle(
  const __Surface&
    surface) noexcept; /*<
             Returns the EGL surface handle wrapped by a __Surface.
             >*/

//]
