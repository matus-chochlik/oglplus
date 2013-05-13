/**
 *  @file oglplus/face_mode.hpp
 *  @brief OpenGL face type-related enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FACE_MODE_1107121519_HPP
#define OGLPLUS_FACE_MODE_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Polygon facing enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{CullFace}
 *  @glfunref{PolygonMode}
 *  @glfunref{StencilFuncSeparate}
 *  @glfunref{StencilMaskSeparate}
 */
OGLPLUS_ENUM_CLASS_BEGIN(Face, GLenum)
#include <oglplus/enums/face.ipp>
OGLPLUS_ENUM_CLASS_END(Face)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/face_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/face_range.ipp>
#endif

/// Face orientation enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{FrontFace}
 */
OGLPLUS_ENUM_CLASS_BEGIN(FaceOrientation, GLenum)
#include <oglplus/enums/face_orientation.ipp>
OGLPLUS_ENUM_CLASS_END(FaceOrientation)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/face_orientation_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/face_orientation_range.ipp>
#endif

/// Inverts the face orientation (CW to CCW and CCW to CW)
/**
 *  @see FaceOrientation
 *
 *  @glsymbols
 *  @glfunref{FrontFace}
 */
inline FaceOrientation Inverted(FaceOrientation winding)
{
	if(winding == FaceOrientation::CW)
		return FaceOrientation::CCW;
	else return FaceOrientation::CW;
}

} // namespace oglplus

#endif // include guard
