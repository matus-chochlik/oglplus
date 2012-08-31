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
OGLPLUS_ENUM_CLASS_BEGIN(Face, GLenum)
#include <oglplus/enums/face.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	Face*,
	EnumBaseType<Face>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/face.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
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
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	FaceOrientation*,
	EnumBaseType<FaceOrientation>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/face_orientation.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
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
