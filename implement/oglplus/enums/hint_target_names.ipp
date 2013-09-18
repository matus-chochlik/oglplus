/*
 *  .file oglplus/enums/hint_target_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/hint_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	HintTarget*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_HINTTARGET)
#define OGLPLUS_IMPL_EVN_HINTTARGET
{
switch(value)
{
#if defined GL_LINE_SMOOTH_HINT
	case GL_LINE_SMOOTH_HINT: return StrLit("LINE_SMOOTH_HINT");
#endif
#if defined GL_POLYGON_SMOOTH_HINT
	case GL_POLYGON_SMOOTH_HINT: return StrLit("POLYGON_SMOOTH_HINT");
#endif
#if defined GL_TEXTURE_COMPRESSION_HINT
	case GL_TEXTURE_COMPRESSION_HINT: return StrLit("TEXTURE_COMPRESSION_HINT");
#endif
#if defined GL_FRAGMENT_SHADER_DERIVATIVE_HINT
	case GL_FRAGMENT_SHADER_DERIVATIVE_HINT: return StrLit("FRAGMENT_SHADER_DERIVATIVE_HINT");
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

