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
#include <oglplus/enums/face.ipp>
};

/// Face orientation enumeration
/**
 *  @ingroup enumerations
 */
enum class FaceOrientation : GLenum
{
#include <oglplus/enums/face_orientation.ipp>
};

} // namespace oglplus

#endif // include guard
