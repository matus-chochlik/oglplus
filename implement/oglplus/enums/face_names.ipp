/*
 *  .file oglplus/enums/face_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/face.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	Face*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_FACE)
#define OGLPLUS_IMPL_EVN_FACE
{
switch(value)
{
#if defined GL_FRONT
	case GL_FRONT: return StrLit("FRONT");
#endif
#if defined GL_BACK
	case GL_BACK: return StrLit("BACK");
#endif
#if defined GL_FRONT_AND_BACK
	case GL_FRONT_AND_BACK: return StrLit("FRONT_AND_BACK");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

