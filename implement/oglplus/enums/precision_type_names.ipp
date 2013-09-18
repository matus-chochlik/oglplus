/*
 *  .file oglplus/enums/precision_type_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/precision_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PrecisionType*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PRECISIONTYPE)
#define OGLPLUS_IMPL_EVN_PRECISIONTYPE
{
switch(value)
{
#if defined GL_LOW_FLOAT
	case GL_LOW_FLOAT: return StrLit("LOW_FLOAT");
#endif
#if defined GL_MEDIUM_FLOAT
	case GL_MEDIUM_FLOAT: return StrLit("MEDIUM_FLOAT");
#endif
#if defined GL_HIGH_FLOAT
	case GL_HIGH_FLOAT: return StrLit("HIGH_FLOAT");
#endif
#if defined GL_LOW_INT
	case GL_LOW_INT: return StrLit("LOW_INT");
#endif
#if defined GL_MEDIUM_INT
	case GL_MEDIUM_INT: return StrLit("MEDIUM_INT");
#endif
#if defined GL_HIGH_INT
	case GL_HIGH_INT: return StrLit("HIGH_INT");
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

