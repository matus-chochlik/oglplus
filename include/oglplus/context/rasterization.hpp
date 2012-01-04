/**
 *  @file oglplus/context/rasterization.hpp
 *  @brief Wrappers for basic point, line and polygon resterization operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_POLY_RASTERIZE_1201040722_HPP
#define OGLPLUS_CONTEXT_POLY_RASTERIZE_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/face_mode.hpp>
#include <oglplus/polygon_mode.hpp>
#include <oglplus/provoke_mode.hpp>

namespace oglplus {
namespace context {

/// Wrapper for the basic point, line and polygon rasterization operations
/**
 *  @ingroup ogl_context
 */
class Rasterization
{
public:
	/// Sets the polygon facing mode
	/**
	 *  @glsymbols
	 *  @glfunref{FrontFace}
	 */
	static void FrontFace(FaceOrientation orientation)
	{
		OGLPLUS_GLFUNC(FrontFace)(GLenum(orientation));
		AssertNoError(OGLPLUS_ERROR_INFO(FrontFace));
	}

	/// Sets the face culling mode
	/**
	 *  @glsymbols
	 *  @glfunref{CullFace}
	 */
	static void CullFace(Face mode)
	{
		OGLPLUS_GLFUNC(CullFace)(GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(CullFace));
	}

	/// Sets the polygon rasterization mode
	/**
	 *  @glsymbols
	 *  @glfunref{PolygonMode}
	 */
	static void PolygonMode(Face face, oglplus::PolygonMode mode)
	{
		OGLPLUS_GLFUNC(PolygonMode)(GLenum(face), GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(PolygonMode));
	}

	/// Sets the polygon depth offset
	/**
	 *  @glsymbols
	 *  @glfunref{PolygonOffset}
	 */
	static void PolygonOffset(GLfloat factor, GLfloat units)
	{
		OGLPLUS_GLFUNC(PolygonOffset)(factor, units);
		AssertNoError(OGLPLUS_ERROR_INFO(PolygonOffset));
	}

	/// Sets the line width
	/**
	 *  @glsymbols
	 *  @glfunref{LineWidth}
	 */
	static void LineWidth(GLfloat width)
	{
		OGLPLUS_GLFUNC(LineWidth)(width);
		AssertNoError(OGLPLUS_ERROR_INFO(LineWidth));
	}

	/// Sets the point size
	/**
	 *  @glsymbols
	 *  @glfunref{PointSize}
	 */
	static void PointSize(GLfloat size)
	{
		OGLPLUS_GLFUNC(PointSize)(size);
		AssertNoError(OGLPLUS_ERROR_INFO(PointSize));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2 || GL_ARB_provoking_vertex
	/// Sets the provoking vertex selection mode for flatshading
	/**
	 *  @glsymbols
	 *  @glfunref{ProvokingVertex}
	 */
	static void ProvokingVertex(ProvokeMode mode)
	{
		OGLPLUS_GLFUNC(ProvokingVertex)(GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(ProvokingVertex));
	}
#endif
};

} // namespace context
} // namespace oglplus

#endif // include guard
