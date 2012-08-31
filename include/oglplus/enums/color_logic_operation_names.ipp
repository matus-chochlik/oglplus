/*
 *  .file oglplus/enums/color_logic_operation_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/color_logic_operation.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	ColorLogicOperation*,
	GLenum value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
switch(value)
{
#if defined GL_CLEAR
	case GL_CLEAR: return StrLit("CLEAR");
#endif
#if defined GL_AND
	case GL_AND: return StrLit("AND");
#endif
#if defined GL_AND_REVERSE
	case GL_AND_REVERSE: return StrLit("AND_REVERSE");
#endif
#if defined GL_COPY
	case GL_COPY: return StrLit("COPY");
#endif
#if defined GL_AND_INVERTED
	case GL_AND_INVERTED: return StrLit("AND_INVERTED");
#endif
#if defined GL_NOOP
	case GL_NOOP: return StrLit("NOOP");
#endif
#if defined GL_XOR
	case GL_XOR: return StrLit("XOR");
#endif
#if defined GL_OR
	case GL_OR: return StrLit("OR");
#endif
#if defined GL_NOR
	case GL_NOR: return StrLit("NOR");
#endif
#if defined GL_EQUIV
	case GL_EQUIV: return StrLit("EQUIV");
#endif
#if defined GL_INVERT
	case GL_INVERT: return StrLit("INVERT");
#endif
#if defined GL_OR_REVERSE
	case GL_OR_REVERSE: return StrLit("OR_REVERSE");
#endif
#if defined GL_COPY_INVERTED
	case GL_COPY_INVERTED: return StrLit("COPY_INVERTED");
#endif
#if defined GL_OR_INVERTED
	case GL_OR_INVERTED: return StrLit("OR_INVERTED");
#endif
#if defined GL_NAND
	case GL_NAND: return StrLit("NAND");
#endif
#if defined GL_SET
	case GL_SET: return StrLit("SET");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#endif

