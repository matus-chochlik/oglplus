//  File implement/oglplus/enums/color_logic_operation_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/color_logic_operation.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	ColorLogicOperation*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_COLORLOGICOPERATION)
#define OGLPLUS_IMPL_EVN_COLORLOGICOPERATION
{
switch(value)
{
#if defined GL_CLEAR
	case GL_CLEAR: return CStrRef("CLEAR");
#endif
#if defined GL_AND
	case GL_AND: return CStrRef("AND");
#endif
#if defined GL_AND_REVERSE
	case GL_AND_REVERSE: return CStrRef("AND_REVERSE");
#endif
#if defined GL_COPY
	case GL_COPY: return CStrRef("COPY");
#endif
#if defined GL_AND_INVERTED
	case GL_AND_INVERTED: return CStrRef("AND_INVERTED");
#endif
#if defined GL_NOOP
	case GL_NOOP: return CStrRef("NOOP");
#endif
#if defined GL_XOR
	case GL_XOR: return CStrRef("XOR");
#endif
#if defined GL_OR
	case GL_OR: return CStrRef("OR");
#endif
#if defined GL_NOR
	case GL_NOR: return CStrRef("NOR");
#endif
#if defined GL_EQUIV
	case GL_EQUIV: return CStrRef("EQUIV");
#endif
#if defined GL_INVERT
	case GL_INVERT: return CStrRef("INVERT");
#endif
#if defined GL_OR_REVERSE
	case GL_OR_REVERSE: return CStrRef("OR_REVERSE");
#endif
#if defined GL_COPY_INVERTED
	case GL_COPY_INVERTED: return CStrRef("COPY_INVERTED");
#endif
#if defined GL_OR_INVERTED
	case GL_OR_INVERTED: return CStrRef("OR_INVERTED");
#endif
#if defined GL_NAND
	case GL_NAND: return CStrRef("NAND");
#endif
#if defined GL_SET
	case GL_SET: return CStrRef("SET");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

