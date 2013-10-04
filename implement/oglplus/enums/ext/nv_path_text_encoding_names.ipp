/*
 *  .file oglplus/enums/ext/nv_path_text_encoding_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_text_encoding.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PathNVTextEncoding*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVTEXTENCODING)
#define OGLPLUS_IMPL_EVN_PATHNVTEXTENCODING
{
switch(value)
{
#if defined GL_UTF8_NV
	case GL_UTF8_NV: return StrLit("UTF8_NV");
#endif
#if defined GL_UTF16_NV
	case GL_UTF16_NV: return StrLit("UTF16_NV");
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

