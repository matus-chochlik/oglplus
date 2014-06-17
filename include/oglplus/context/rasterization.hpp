/**
 *  @file oglplus/context/rasterization.hpp
 *  @brief Wrappers for basic point, line and polygon resterization operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_RASTERIZATION_1201040722_HPP
#define OGLPLUS_CONTEXT_RASTERIZATION_1201040722_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/face_mode.hpp>
#include <oglplus/polygon_mode.hpp>
#include <oglplus/provoke_mode.hpp>
#include <oglplus/math/vector.hpp>

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
		OGLPLUS_VERIFY(
			FrontFace,
			Error,
			EnumParam(orientation)
		);
	}

	/// Sets the face culling mode
	/**
	 *  @glsymbols
	 *  @glfunref{CullFace}
	 */
	static void CullFace(Face mode)
	{
		OGLPLUS_GLFUNC(CullFace)(GLenum(mode));
		OGLPLUS_VERIFY(
			CullFace,
			Error,
			EnumParam(mode)
		);
	}

	/// Returns the face culling mode
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{CULL_FACE_MODE}
	 */
	static Face CullFaceMode(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_CULL_FACE_MODE, &result);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return Face(result);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	/// Sets the polygon rasterization mode
	/**
	 *  @glsymbols
	 *  @glfunref{PolygonMode}
	 */
	static void PolygonMode(Face face, oglplus::PolygonMode mode)
	{
		OGLPLUS_GLFUNC(PolygonMode)(GLenum(face), GLenum(mode));
		OGLPLUS_VERIFY(
			PolygonMode,
			Error,
			EnumParam(mode)
		);
	}

	/// Sets the polygon rasterization mode
	/**
	 *  @glsymbols
	 *  @glfunref{PolygonMode}
	 */
	static void PolygonMode(oglplus::PolygonMode mode)
	{
		OGLPLUS_GLFUNC(PolygonMode)(GL_FRONT_AND_BACK, GLenum(mode));
		OGLPLUS_VERIFY(
			PolygonMode,
			Error,
			EnumParam(mode)
		);
	}

	/// Returns the face culling mode
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{POLYGON_MODE}
	 */
	static oglplus::PolygonMode PolygonMode(void)
	{
		GLint result[2];
		OGLPLUS_GLFUNC(GetIntegerv)(GL_POLYGON_MODE, result);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return oglplus::PolygonMode(result[1]);
	}
#endif // GL_VERSION_3_0

	/// Sets the polygon depth offset
	/**
	 *  @glsymbols
	 *  @glfunref{PolygonOffset}
	 */
	static void PolygonOffset(GLfloat factor, GLfloat units)
	{
		OGLPLUS_GLFUNC(PolygonOffset)(factor, units);
		OGLPLUS_VERIFY_SIMPLE(PolygonOffset);
	}

	/// Returns the polygon offset factor
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{POLYGON_OFFSET_FACTOR}
	 */
	static GLfloat PolygonOffsetFactor(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetFloatv)(GL_POLYGON_OFFSET_FACTOR, &result);
		OGLPLUS_VERIFY_SIMPLE(GetFloatv);
		return result;
	}

	/// Returns the polygon offset units
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{POLYGON_OFFSET_UNITS}
	 */
	static GLfloat PolygonOffsetUnits(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetFloatv)(GL_POLYGON_OFFSET_UNITS, &result);
		OGLPLUS_VERIFY_SIMPLE(GetFloatv);
		return result;
	}

	/// Sets the line width
	/**
	 *  @glsymbols
	 *  @glfunref{LineWidth}
	 */
	static void LineWidth(GLfloat width)
	{
		OGLPLUS_GLFUNC(LineWidth)(width);
		OGLPLUS_VERIFY_SIMPLE(LineWidth);
	}

	/// Returns the line width
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{LINE_WIDTH}
	 */
	static GLfloat LineWidth(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetFloatv)(GL_LINE_WIDTH, &result);
		OGLPLUS_VERIFY_SIMPLE(GetFloatv);
		return result;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	/// Sets the point size
	/**
	 *  @glsymbols
	 *  @glfunref{PointSize}
	 */
	static void PointSize(GLfloat size)
	{
		OGLPLUS_GLFUNC(PointSize)(size);
		OGLPLUS_VERIFY_SIMPLE(PointSize);
	}

	/// Returns the point size
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{POINT_SIZE}
	 */
	static GLfloat PointSize(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetFloatv)(GL_POINT_SIZE, &result);
		OGLPLUS_VERIFY_SIMPLE(GetFloatv);
		return result;
	}

	/// Sets the point fade threshold size
	/**
	 *  @glsymbols
	 *  @glfunref{PointParameter}
	 *  @gldefref{POINT_FADE_THRESHOLD_SIZE}
	 */
	static void PointFadeThresholdSize(GLfloat size)
	{
		OGLPLUS_GLFUNC(PointParameterf)(
			GL_POINT_FADE_THRESHOLD_SIZE,
			size
		);
		OGLPLUS_VERIFY_SIMPLE(PointParameterf);
	}

	/// Returns the point fade threshold size
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{POINT_FADE_THRESHOLD_SIZE}
	 */
	static GLfloat PointFadeThresholdSize(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetFloatv)(GL_POINT_FADE_THRESHOLD_SIZE,&result);
		OGLPLUS_VERIFY_SIMPLE(GetFloatv);
		return result;
	}
#endif // GL_VERSION_3_0

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2 || GL_ARB_provoking_vertex
	/// Sets the provoking vertex selection mode for flatshading
	/**
	 *  @glvoereq{3,2,ARB,provoking_vertex}
	 *  @glsymbols
	 *  @glfunref{ProvokingVertex}
	 */
	static void ProvokingVertex(ProvokeMode mode)
	{
		OGLPLUS_GLFUNC(ProvokingVertex)(GLenum(mode));
		OGLPLUS_VERIFY_SIMPLE(ProvokingVertex);
	}

	/// Returns the provoking vertex selection mode for flatshading
	/**
	 *  @glvoereq{3,2,ARB,provoking_vertex}
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{PROVOKING_VERTEX}
	 */
	static ProvokeMode ProvokingVertex(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_PROVOKING_VERTEX, &result);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return ProvokeMode(result);
	}
#endif
	/// Returns the value of sample buffers
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{SAMPLE_BUFFERS}
	 */
	static GLint SampleBuffers(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_SAMPLE_BUFFERS, &result);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return result;
	}

	/// Returns the number of multisampling samples
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{SAMPLES}
	 */
	static GLint Samples(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_SAMPLES, &result);
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return result;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2
	/// Returns the position of the specified multisampling sample
	/**
	 *  @glverreq{3,2}
	 *  @glsymbols
	 *  @glfunref{GetMultisample}
	 *  @gldefref{SAMPLE_POSITION}
	 */
	static Vec2f SamplePosition(GLuint index)
	{
		Vec2f result;
		OGLPLUS_GLFUNC(GetMultisamplefv)(
			GL_SAMPLE_POSITION,
			index,
			result.Data()
		);
		OGLPLUS_VERIFY_SIMPLE(GetMultisamplefv);
		return result;
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
	/// Returns the minimal sample shading value
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{MIN_SAMPLE_SHADING_VALUE}
	 */
	static GLfloat MinSampleShading(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetFloatv)(GL_MIN_SAMPLE_SHADING_VALUE, &result);
		OGLPLUS_VERIFY_SIMPLE(GetFloatv);
		return result;
	}

	/// Sets the multisampling minimal sample shading value
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{MinSampleShading}
	 */
	static void MinSampleShading(GLfloat value)
	{
		OGLPLUS_GLFUNC(MinSampleShading)(value);
		OGLPLUS_VERIFY_SIMPLE(MinSampleShading);
	}
#endif
};

} // namespace context
} // namespace oglplus

#endif // include guard
