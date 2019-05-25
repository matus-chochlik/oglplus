/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_Viewport_helpers
namespace context {

struct ViewportPosition /*<
Helper structure storing position in a 2D viewport.
>*/
{
    GLfloat X() const noexcept;

    GLfloat Y() const noexcept;
};

struct ViewportSize /*<
Helper structure storing the dimensions of a 2D viewport.
>*/
{
    GLfloat Width() const noexcept;

    GLfloat Height() const noexcept;
};

struct ViewportExtents /*<
Helper structure storing the extents of a 2D viewport.
>*/
{
    GLfloat X() const noexcept;

    GLfloat Y() const noexcept;

    GLfloat Width() const noexcept;

    GLfloat Height() const noexcept;
};

struct BoundsRange /*<
Helper structure storing the min/max bounds range.
>*/
{
    GLfloat Min() const noexcept;

    GLfloat Max() const noexcept;
};

struct ViewportDepthRange /*<
Helper structure storing the near/far depth range.
>*/
{
    GLfloat Near() const noexcept;

    GLfloat Far() const noexcept;
};
//]
//[oglplus_context_ViewportState
class ViewportState {
public:
    static void Viewport(GLint x, GLint y, __SizeType w, __SizeType h); /*<
    Sets the extents of the current viewport.
    See [glfunc Viewport].
    >*/
    static void Viewport(__SizeType w, __SizeType h); /*<
    Sets the size of the current viewport starting at (0,0).
    See [glfunc Viewport].
    >*/
    static void Viewport(const __context_ViewportExtents& vp);

    static __context_ViewportExtents Viewport(); /*<
    Returns the extents of the current viewport.
    See [glfunc Get], [glconst VIEWPORT].
    >*/

    static void DepthRange(GLclampf near, GLclampf far); /*<
    Sets the [^near] / [^far] depth range values of the default viewport.
    See [glfunc DepthRangeIndexed].
    >*/
    static void DepthRange(const __context_ViewportDepthRange&);

    static __context_ViewportDepthRange DepthRange(); /*<
    Returns the depth range values of the current viewport.
    See [glfunc Get], [glconst DEPTH_RANGE].
    >*/

#if GL_VERSION_4_1 || GL_ARB_viewport_array
    static void Viewport(
      __ViewportIndex viewport,
      const GLfloat* extents); /*<
                            Sets the [^extents] of the specified [^viewport].
                            See [glfunc ViewportIndexedfv].
                            >*/
    static void Viewport(
      __ViewportIndex viewport,
      GLfloat x,
      GLfloat y,
      GLfloat width,
      GLfloat height); /*<
                    Sets the extents of the specified [^viewport].
                    See [glfunc ViewportIndexedf].
                    >*/
    static void Viewport(
      __ViewportIndex viewport, const __context_ViewportExtents&);

    static void ViewportArray(
      GLuint first,
      __SizeType count,
      const GLfloat*
        extents); /*<
               Sets [^extents] of the viewports specified by [^first] and
               [^count]. See [glfunc ViewportIndexedfv].
               >*/

    static __context_ViewportExtents Viewport(__ViewportIndex viewport); /*<
    Returns the extents of the specified [^viewport].
    See [glfunc Get], [glconst VIEWPORT].
    >*/

    static void DepthRange(
      __ViewportIndex viewport,
      GLclampd near,
      GLclampd far); /*<
                  Sets the [^near] / [^far] depth range values of the default
                  viewport. See [glfunc DepthRangeIndexed].
                  >*/
    static void DepthRange(
      __ViewportIndex viewport, const __context_ViewportDepthRange&);

    static void DepthRangeArray(
      GLuint first, __SizeType count, const GLclampd* v); /*<
Sets depth ranges of viewports specified by [^first] and [^count].
See [glfunc DepthRangeArray].
>*/

    static __context_ViewportDepthRange DepthRange(
      __ViewportIndex viewport); /*<
Returns the depth range of the specified [^viewport].
See [glfunc Get], [glconst DEPTH_RANGE].
>*/
#endif
};
//]
//[oglplus_context_ViewportOps
class ViewportOps {
public:
    static ViewportSize MaxViewportDims(); /*<
    Returns the implementation-dependent maximum viewport dimensions.
    See [glfunc Get], [glconst MAX_VIEWPORT_DIMS].
    >*/

#if GL_VERSION_4_1 || GL_ARB_viewport_array
    static GLuint MaxViewports(); /*<
    Returns the number of available viewports.
    See [glfunc Get], [glconst MAX_VIEWPORTS].
    >*/

    static BoundsRange ViewportBoundsRange(); /*<
    Returns the implementation-dependent viewport bounds range.
    See [glfunc Get], [glconst VIEWPORT_BOUNDS_RANGE].
    >*/
#endif
};

} // namespace context
//]
