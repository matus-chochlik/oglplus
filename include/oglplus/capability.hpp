/**
 *  @file oglplus/capability.hpp
 *  @brief Enumeration of OpenGL capabilities that can be Enabled/Disabled
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CAPABILITY_1107121519_HPP
#define OGLPLUS_CAPABILITY_1107121519_HPP

namespace oglplus {

/// Capability enumeration
enum class Capability: GLenum
{
	/// DEPTH_TEST
	DepthTest = GL_DEPTH_TEST,
	/// STENCIL_TEST
	StencilTest = GL_STENCIL_TEST,

	/// CULL_FACE
	CullFace = GL_CULL_FACE,

	/// POLYGON_OFFSET_POINT
	PolygonOffsetPoint = GL_POLYGON_OFFSET_POINT,
	/// POLYGON_OFFSET_LINE
	PolygonOffsetLine = GL_POLYGON_OFFSET_LINE,
	/// POLYGON_OFFSET_FILL
	PolygonOffsetFill = GL_POLYGON_OFFSET_FILL,

	/// BLEND
	Blend = GL_BLEND
};

} // namespace oglplus

#endif // include guard
