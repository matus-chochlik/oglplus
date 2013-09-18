/*
 *  .file oglplus/enums/pixel_data_type_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/pixel_data_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PixelDataType*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PIXELDATATYPE)
#define OGLPLUS_IMPL_EVN_PIXELDATATYPE
{
switch(value)
{
#if defined GL_UNSIGNED_BYTE
	case GL_UNSIGNED_BYTE: return StrLit("UNSIGNED_BYTE");
#endif
#if defined GL_BYTE
	case GL_BYTE: return StrLit("BYTE");
#endif
#if defined GL_UNSIGNED_SHORT
	case GL_UNSIGNED_SHORT: return StrLit("UNSIGNED_SHORT");
#endif
#if defined GL_SHORT
	case GL_SHORT: return StrLit("SHORT");
#endif
#if defined GL_UNSIGNED_INT
	case GL_UNSIGNED_INT: return StrLit("UNSIGNED_INT");
#endif
#if defined GL_INT
	case GL_INT: return StrLit("INT");
#endif
#if defined GL_HALF_FLOAT
	case GL_HALF_FLOAT: return StrLit("HALF_FLOAT");
#endif
#if defined GL_FLOAT
	case GL_FLOAT: return StrLit("FLOAT");
#endif
#if defined GL_UNSIGNED_BYTE_3_3_2
	case GL_UNSIGNED_BYTE_3_3_2: return StrLit("UNSIGNED_BYTE_3_3_2");
#endif
#if defined GL_UNSIGNED_BYTE_2_3_3_REV
	case GL_UNSIGNED_BYTE_2_3_3_REV: return StrLit("UNSIGNED_BYTE_2_3_3_REV");
#endif
#if defined GL_UNSIGNED_SHORT_5_6_5
	case GL_UNSIGNED_SHORT_5_6_5: return StrLit("UNSIGNED_SHORT_5_6_5");
#endif
#if defined GL_UNSIGNED_SHORT_5_6_5_REV
	case GL_UNSIGNED_SHORT_5_6_5_REV: return StrLit("UNSIGNED_SHORT_5_6_5_REV");
#endif
#if defined GL_UNSIGNED_SHORT_4_4_4_4
	case GL_UNSIGNED_SHORT_4_4_4_4: return StrLit("UNSIGNED_SHORT_4_4_4_4");
#endif
#if defined GL_UNSIGNED_SHORT_4_4_4_4_REV
	case GL_UNSIGNED_SHORT_4_4_4_4_REV: return StrLit("UNSIGNED_SHORT_4_4_4_4_REV");
#endif
#if defined GL_UNSIGNED_SHORT_5_5_5_1
	case GL_UNSIGNED_SHORT_5_5_5_1: return StrLit("UNSIGNED_SHORT_5_5_5_1");
#endif
#if defined GL_UNSIGNED_SHORT_1_5_5_5_REV
	case GL_UNSIGNED_SHORT_1_5_5_5_REV: return StrLit("UNSIGNED_SHORT_1_5_5_5_REV");
#endif
#if defined GL_UNSIGNED_INT_8_8_8_8
	case GL_UNSIGNED_INT_8_8_8_8: return StrLit("UNSIGNED_INT_8_8_8_8");
#endif
#if defined GL_UNSIGNED_INT_8_8_8_8_REV
	case GL_UNSIGNED_INT_8_8_8_8_REV: return StrLit("UNSIGNED_INT_8_8_8_8_REV");
#endif
#if defined GL_UNSIGNED_INT_10_10_10_2
	case GL_UNSIGNED_INT_10_10_10_2: return StrLit("UNSIGNED_INT_10_10_10_2");
#endif
#if defined GL_UNSIGNED_INT_2_10_10_10_REV
	case GL_UNSIGNED_INT_2_10_10_10_REV: return StrLit("UNSIGNED_INT_2_10_10_10_REV");
#endif
#if defined GL_UNSIGNED_INT_24_8
	case GL_UNSIGNED_INT_24_8: return StrLit("UNSIGNED_INT_24_8");
#endif
#if defined GL_UNSIGNED_INT_10F_11F_11F_REV
	case GL_UNSIGNED_INT_10F_11F_11F_REV: return StrLit("UNSIGNED_INT_10F_11F_11F_REV");
#endif
#if defined GL_UNSIGNED_INT_5_9_9_9_REV
	case GL_UNSIGNED_INT_5_9_9_9_REV: return StrLit("UNSIGNED_INT_5_9_9_9_REV");
#endif
#if defined GL_FLOAT_32_UNSIGNED_INT_24_8_REV
	case GL_FLOAT_32_UNSIGNED_INT_24_8_REV: return StrLit("FLOAT_32_UNSIGNED_INT_24_8_REV");
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

