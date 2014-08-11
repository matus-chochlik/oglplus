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
	GLfloat X(void) const;
	GLfloat Y(void) const;
};

struct ViewportSize /*<
Helper structure storing the dimensions of a 2D viewport.
>*/
{
	GLfloat Width(void) const;
	GLfloat Height(void) const;
};

struct ViewportExtents /*<
Helper structure storing the extents of a 2D viewport.
>*/
{
	GLfloat X(void) const;
	GLfloat Y(void) const;
	GLfloat Width(void) const;
	GLfloat Height(void) const;
};

struct BoundsRange /*<
Helper structure storing the min/max bounds range.
>*/
{
	GLfloat Min(void) const;
	GLfloat Max(void) const;
};

struct DepthRange /*<
Helper structure storing the near/far depth range.
>*/
{
	GLfloat Near(void) const;
	GLfloat Far(void) const;
};
//]

//[oglplus_context_Viewport
class ViewportOps
{
public:
	static ViewportSize MaxViewportDims(void); /*<
	Returns the implementation-dependent maximum viewport dimensions.
	See [glfunc Get], [glconst MAX_VIEWPORT_DIMS].
	>*/

	static void Viewport(GLint x, GLint y, GLsizei w, GLsizei h); /*<
	Sets the extents of the current viewport.
	See [glfunc Viewport].
	>*/
	static void Viewport(GLsizei w, GLsizei h); /*<
	Sets the size of the current viewport starting at (0,0).
	See [glfunc Viewport].
	>*/
	static ViewportExtents Viewport(void); /*<
	Returns the extents of the current viewport.
	See [glfunc Get], [glconst VIEWPORT].
	>*/


#if GL_VERSION_4_1 || GL_ARB_viewport_array
	static GLuint MaxViewports(void); /*<
	Returns the number of available viewports.
	See [glfunc Get], [glconst MAX_VIEWPORTS].
	>*/

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

	static void ViewportArray(
		GLuint first,
		GLsizei count,
		const GLfloat* extents
	); /*<
	Sets [^extents] of the viewports specified by [^first] and [^count].
	See [glfunc ViewportIndexedfv].
	>*/

	static ViewportExtents Viewport(GLuint viewport); /*<
	Returns the extents of the specified [^viewport].
	See [glfunc Get], [glconst VIEWPORT].
	>*/

	static BoundsRange ViewportBoundsRange(void); /*<
	Returns the implementation-dependent viewport bounds range.
	See [glfunc Get], [glconst VIEWPORT_BOUNDS_RANGE].
	>*/
	static DepthRange ViewportDepthRange(GLuint viewport); /*<
	Returns the depth range of the specified [^viewport].
	See [glfunc Get], [glconst DEPTH_RANGE].
	>*/

	static void DepthRange(GLuint viewport, GLclampd near, GLclampd far); /*<
	Sets the [^near] / [^far] depth range values of the default viewport.
	See [glfunc DepthRangeIndexed].
	>*/
	static void DepthRangeArray(GLuint first, GLsizei count, const GLclampd *v); /*<
	Sets depth ranges of viewports specified by [^first] and [^count].
	See [glfunc DepthRangeArray].
	>*/
#endif

#if GL_ES_VERSION_3_0 || GL_VERSION_4_1 || GL_ARB_ES2_compatibility
	static void DepthRange(GLclampf near, GLclampf far);
#endif
	static void DepthRange(GLclampd near, GLclampd far);
};

} // namespace context
} // namespace oglplus
//]

