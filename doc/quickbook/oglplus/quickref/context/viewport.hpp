/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_Viewport_helpers
namespace oglplus {
namespace context {

struct ViewportPosition /*<
Helper structure storing position in a 2D viewport.
>*/
{
	GLfloat X(void) const
	noexcept;

	GLfloat Y(void) const
	noexcept;
};

struct ViewportSize /*<
Helper structure storing the dimensions of a 2D viewport.
>*/
{
	GLfloat Width(void) const
	noexcept;

	GLfloat Height(void) const
	noexcept;
};

struct ViewportExtents /*<
Helper structure storing the extents of a 2D viewport.
>*/
{
	GLfloat X(void) const
	noexcept;

	GLfloat Y(void) const
	noexcept;

	GLfloat Width(void) const
	noexcept;

	GLfloat Height(void) const
	noexcept;
};

struct BoundsRange /*<
Helper structure storing the min/max bounds range.
>*/
{
	GLfloat Min(void) const
	noexcept;

	GLfloat Max(void) const
	noexcept;
};

struct ViewportDepthRange /*<
Helper structure storing the near/far depth range.
>*/
{
	GLfloat Near(void) const
	noexcept;

	GLfloat Far(void) const
	noexcept;
};
//]
//[oglplus_context_ViewportState
class ViewportState
{
public:
	static void Viewport(GLint x, GLint y, GLsizei w, GLsizei h); /*<
	Sets the extents of the current viewport.
	See [glfunc Viewport].
	>*/
	static void Viewport(GLsizei w, GLsizei h); /*<
	Sets the size of the current viewport starting at (0,0).
	See [glfunc Viewport].
	>*/
	static void Viewport(const __context_ViewportExtents& vp);

	static __context_ViewportExtents Viewport(void); /*<
	Returns the extents of the current viewport.
	See [glfunc Get], [glconst VIEWPORT].
	>*/

	static void DepthRange(GLclampf near, GLclampf far); /*<
	Sets the [^near] / [^far] depth range values of the default viewport.
	See [glfunc DepthRangeIndexed].
	>*/
	static void DepthRange(const __context_ViewportDepthRange&);

	static __context_ViewportDepthRange DepthRange(void); /*<
	Returns the depth range values of the current viewport.
	See [glfunc Get], [glconst DEPTH_RANGE].
	>*/

#if GL_VERSION_4_1 || GL_ARB_viewport_array
	static void Viewport(GLuint viewport, const GLfloat* extents); /*<
	Sets the [^extents] of the specified [^viewport].
	See [glfunc ViewportIndexedfv].
	>*/
	static void Viewport(
		GLuint viewport,
		GLfloat x,
		GLfloat y,
		GLfloat width,
		GLfloat height
	); /*<
	Sets the extents of the specified [^viewport].
	See [glfunc ViewportIndexedf].
	>*/
	static void Viewport(GLuint viewport, const __context_ViewportExtents&);

	static void ViewportArray(
		GLuint first,
		GLsizei count,
		const GLfloat* extents
	); /*<
	Sets [^extents] of the viewports specified by [^first] and [^count].
	See [glfunc ViewportIndexedfv].
	>*/

	static __context_ViewportExtents Viewport(GLuint viewport); /*<
	Returns the extents of the specified [^viewport].
	See [glfunc Get], [glconst VIEWPORT].
	>*/

	static void DepthRange(GLuint viewport, GLclampd near, GLclampd far); /*<
	Sets the [^near] / [^far] depth range values of the default viewport.
	See [glfunc DepthRangeIndexed].
	>*/
	static void DepthRange(GLuint viewport, const __context_ViewportDepthRange&);

	static void DepthRangeArray(GLuint first, GLsizei count, const GLclampd *v); /*<
	Sets depth ranges of viewports specified by [^first] and [^count].
	See [glfunc DepthRangeArray].
	>*/

	static __context_ViewportDepthRange DepthRange(GLuint viewport); /*<
	Returns the depth range of the specified [^viewport].
	See [glfunc Get], [glconst DEPTH_RANGE].
	>*/
#endif
};
//]
//[oglplus_context_ViewportOps
class ViewportOps
{
public:
	static ViewportSize MaxViewportDims(void); /*<
	Returns the implementation-dependent maximum viewport dimensions.
	See [glfunc Get], [glconst MAX_VIEWPORT_DIMS].
	>*/


#if GL_VERSION_4_1 || GL_ARB_viewport_array
	static GLuint MaxViewports(void); /*<
	Returns the number of available viewports.
	See [glfunc Get], [glconst MAX_VIEWPORTS].
	>*/

	static BoundsRange ViewportBoundsRange(void); /*<
	Returns the implementation-dependent viewport bounds range.
	See [glfunc Get], [glconst VIEWPORT_BOUNDS_RANGE].
	>*/
#endif

};

} // namespace context
} // namespace oglplus
//]

