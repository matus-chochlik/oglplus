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
 *
 *  @glsymbols
 *  @glfunref{CullFace}
 *  @glfunref{PolygonMode}
 *  @glfunref{StencilFuncSeparate}
 *  @glfunref{StencilMaskSeparate}
 */
enum class Face : GLenum
{
#include <oglplus/enums/face.ipp>
};

inline const GLchar* EnumValueName(Face value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/face.ipp>
#endif
	return "";
}

/// Face orientation enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{FrontFace}
 */
enum class FaceOrientation : GLenum
{
#include <oglplus/enums/face_orientation.ipp>
};

inline const GLchar* EnumValueName(FaceOrientation value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/face_orientation.ipp>
#endif
	return "";
}

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
