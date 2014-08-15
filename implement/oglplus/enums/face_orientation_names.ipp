/*
 *  .file oglplus/enums/face_orientation_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/face_orientation.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	FaceOrientation*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_FACEORIENTATION)
#define OGLPLUS_IMPL_EVN_FACEORIENTATION
{
switch(value)
{
#if defined GL_CW
	case GL_CW: return StrCRef("CW");
#endif
#if defined GL_CCW
	case GL_CCW: return StrCRef("CCW");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrCRef();
}
#else
;
#endif
} // namespace enums

