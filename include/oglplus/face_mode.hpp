/**
 *  @file oglplus/face_mode.hpp
 *  @brief OpenGL face type-related enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_FACE_MODE_1107121519_HPP
#define OGLPLUS_FACE_MODE_1107121519_HPP

namespace oglplus {

/// Polygon facing enumeration
/**
 *  @ingroup enumerations
 */
enum class Face : GLenum
{
	/// FRONT
	Front = GL_FRONT,
	/// BACK
	Back = GL_BACK,
	/// FRONT_AND_BACK
	FrontAndBack = GL_FRONT_AND_BACK
};

/// Face orientation enumeration
/**
 *  @ingroup enumerations
 */
enum class FaceOrientation : GLenum
{
	/// Clockwise (CW)
	CW = GL_CW,
	/// Counter clockwise (CCW)
	CCW = GL_CCW
};

} // namespace oglplus

#endif // include guard
