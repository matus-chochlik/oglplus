/*
 *  .file oglplus/enums/data_type_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/data_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	DataType*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_DATATYPE)
#define OGLPLUS_IMPL_EVN_DATATYPE
{
switch(value)
{
#if defined GL_BYTE
	case GL_BYTE: return StrLit("BYTE");
#endif
#if defined GL_SHORT
	case GL_SHORT: return StrLit("SHORT");
#endif
#if defined GL_INT
	case GL_INT: return StrLit("INT");
#endif
#if defined GL_FIXED
	case GL_FIXED: return StrLit("FIXED");
#endif
#if defined GL_FLOAT
	case GL_FLOAT: return StrLit("FLOAT");
#endif
#if defined GL_HALF_FLOAT
	case GL_HALF_FLOAT: return StrLit("HALF_FLOAT");
#endif
#if defined GL_DOUBLE
	case GL_DOUBLE: return StrLit("DOUBLE");
#endif
#if defined GL_UNSIGNED_BYTE
	case GL_UNSIGNED_BYTE: return StrLit("UNSIGNED_BYTE");
#endif
#if defined GL_UNSIGNED_SHORT
	case GL_UNSIGNED_SHORT: return StrLit("UNSIGNED_SHORT");
#endif
#if defined GL_UNSIGNED_INT
	case GL_UNSIGNED_INT: return StrLit("UNSIGNED_INT");
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

