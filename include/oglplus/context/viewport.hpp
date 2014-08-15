/**
 *  @file oglplus/context/viewport.hpp
 *  @brief Wrappers for viewport-related operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_VIEWPORT_1201040722_HPP
#define OGLPLUS_CONTEXT_VIEWPORT_1201040722_HPP

#include <oglplus/glfunc.hpp>

namespace oglplus {
namespace context {

/// Helper structure storing position in a 2D viewport
struct ViewportPosition
{
	// private implementation detail, do not use
	GLfloat _v[2];

	/// The x-coordinate
	GLfloat X(void) const
	{
		return _v[0];
	}

	/// The y-coordinate
	GLfloat Y(void) const
	{
		return _v[1];
	}
};

/// Helper structure storing the dimensions of a 2D viewport
struct ViewportSize
{
	// private implementation detail, do not use
	GLfloat _v[2];

	/// The width of the viewport
	GLfloat Width(void) const
	{
		return _v[0];
	}

	/// The height of the viewport
	GLfloat Height(void) const
	{
		return _v[1];
	}
};

/// Helper structure storing the extents of a 2D viewport
struct ViewportExtents
{
	// private implementation detail, do not use
	GLfloat _v[4];

	/// The x-coordinate
	GLfloat X(void) const
	{
		return _v[0];
	}

	/// The y-coordinate
	GLfloat Y(void) const
	{
		return _v[1];
	}

	/// The width of the viewport
	GLfloat Width(void) const
	{
		return _v[2];
	}

	/// The height of the viewport
	GLfloat Height(void) const
	{
		return _v[3];
	}
};

/// Helper structure storing the min/max bounds range
struct BoundsRange
{
	// private implementation detail, do not use
	GLfloat _v[2];

	/// The min limit
	GLfloat Min(void) const
	{
		return _v[0];
	}

	/// The max limit
	GLfloat Max(void) const
	{
		return _v[1];
	}
};

/// Helper structure storing the near/far depth range
struct DepthRange
{
	// private implementation detail, do not use
	GLfloat _v[2];

	/// The near limit
	GLfloat Near(void) const
	{
		return _v[0];
	}

	/// The far limit
	GLfloat Far(void) const
	{
		return _v[1];
	}
};

/// Wrapper for the viewport-related operations
/**
 *  @ingroup ogl_context
 */
class ViewportOps
{
public:
	/// Sets the extents of the current viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Viewport}
	 */
	static void Viewport(GLint x, GLint y, GLsizei w, GLsizei h)
	{
		OGLPLUS_GLFUNC(Viewport)(x, y, w, h);
		OGLPLUS_CHECK_SIMPLE(Viewport);
	}

	/// Sets the size of the current viewport starting at (0,0)
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Viewport}
	 */
	static void Viewport(GLsizei w, GLsizei h)
	{
		OGLPLUS_GLFUNC(Viewport)(0, 0, w, h);
		OGLPLUS_CHECK_SIMPLE(Viewport);
	}

	/// Returns the extents of the current viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{VIEWPORT}
	 */
	static ViewportExtents Viewport(void)
	{
		ViewportExtents result;
		OGLPLUS_GLFUNC(GetFloatv)(GL_VIEWPORT, result._v);
		OGLPLUS_CHECK_SIMPLE(GetFloatv);
		return result;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_viewport_array
	/// Returns the implementation-dependent viewport bounds range
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{VIEWPORT_BOUNDS_RANGE}
	 */
	static BoundsRange ViewportBoundsRange(void)
	{
		BoundsRange result;
		OGLPLUS_GLFUNC(GetFloatv)(
			GL_VIEWPORT_BOUNDS_RANGE,
			result._v
		);
		OGLPLUS_VERIFY_SIMPLE(GetFloatv);
		return result;
	}
#endif

	/// Returns the implementation-dependent maximum viewport dimensions
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{MAX_VIEWPORT_DIMS}
	 */
	static ViewportSize MaxViewportDims(void)
	{
		ViewportSize result;
		OGLPLUS_GLFUNC(GetFloatv)(
			GL_MAX_VIEWPORT_DIMS,
			result._v
		);
		OGLPLUS_VERIFY_SIMPLE(GetFloatv);
		return result;
	}


#if OGLPLUS_DOCUMENTATION_ONLY || \
	GL_ES_VERSION_3_0 || \
	GL_VERSION_4_1 || \
	GL_ARB_ES2_compatibility
	/// Sets the @p near_val / @p far_val depth range of the default viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DepthRangef}
	 */
	static void DepthRange(GLclampf near_val, GLclampf far_val)
	{
		OGLPLUS_GLFUNC(DepthRangef)(near_val, far_val);
		OGLPLUS_CHECK_SIMPLE(DepthRangef);
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	/// Sets the @p near_val / @p far_val depth range of the default viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DepthRangef}
	 */
	static void DepthRange(GLclampd near_val, GLclampd far_val)
	{
		OGLPLUS_GLFUNC(DepthRange)(near_val, far_val);
		OGLPLUS_CHECK_SIMPLE(DepthRange);
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_viewport_array
	/// Returns the number of available viewports
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{MAX_VIEWPORTS}
	 */
	static GLuint MaxViewports(void)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_MAX_VIEWPORTS, &result);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return GLuint(result);
	}

	/// Sets the extents of the specified @p viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ViewportIndexedf}
	 */
	static void Viewport(
		GLuint viewport,
		GLfloat x,
		GLfloat y,
		GLfloat width,
		GLfloat height
	)
	{
		OGLPLUS_GLFUNC(ViewportIndexedf)(viewport, x, y, width, height);
		OGLPLUS_CHECK(
			ViewportIndexedf,
			Error,
			Index(viewport)
		);
	}

	/// Sets the @p extents of the specified @p viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ViewportIndexedfv}
	 */
	static void Viewport(GLuint viewport, const GLfloat* extents)
	{
		OGLPLUS_GLFUNC(ViewportIndexedfv)(viewport, extents);
		OGLPLUS_CHECK(
			ViewportIndexedfv,
			Error,
			Index(viewport)
		);
	}

	/// Sets @p extents of the viewports specified by @p first and @p count
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ViewportIndexedfv}
	 */
	static void ViewportArray(
		GLuint first,
		GLsizei count,
		const GLfloat* extents
	)
	{
		OGLPLUS_GLFUNC(ViewportArrayv)(first, count, extents);
		OGLPLUS_CHECK_SIMPLE(ViewportArrayv);
	}

	/// Returns the extents of the specified @p viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{VIEWPORT}
	 */
	static ViewportExtents Viewport(GLuint viewport)
	{
		ViewportExtents result;
		OGLPLUS_GLFUNC(GetFloati_v)(GL_VIEWPORT, viewport, result._v);
		OGLPLUS_CHECK_SIMPLE(GetFloati_v);
		return result;
	}


	/// Sets the @p near_val / @p far_val depth range of a @p viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DepthRangeIndexed}
	 */
	static void DepthRange(GLuint viewport, GLclampd near_val, GLclampd far_val)
	{
		OGLPLUS_GLFUNC(DepthRangeIndexed)(viewport, near_val, far_val);
		OGLPLUS_CHECK(
			DepthRangeIndexed,
			Error,
			Index(viewport)
		);
	}

	/// Sets depth ranges of viewports specified by @p first and @p count
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DepthRangeArrayv}
	 */
	static void DepthRangeArray(
		GLuint first,
		GLsizei count,
		const GLclampd *v
	)
	{
		OGLPLUS_GLFUNC(DepthRangeArrayv)(first, count, v);
		OGLPLUS_CHECK_SIMPLE(DepthRangeArrayv);
	}

	/// Returns the depth range of the specified @p viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{DEPTH_RANGE}
	 */
	static oglplus::context::DepthRange ViewportDepthRange(GLuint viewport)
	{
		oglplus::context::DepthRange result;
		OGLPLUS_GLFUNC(GetFloati_v)(GL_DEPTH_RANGE, viewport,result._v);
		OGLPLUS_CHECK(
			GetFloati_v,
			Error,
			Index(viewport)
		);
		return result;
	}
#endif
};

} // namespace context
} // namespace oglplus

#endif // include guard
