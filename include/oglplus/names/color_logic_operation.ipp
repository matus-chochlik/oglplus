/*
 *  .file oglplus/names/color_logic_operation.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/color_logic_operation.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_CLEAR
	case GL_CLEAR: return "CLEAR";
#endif
#if defined GL_AND
	case GL_AND: return "AND";
#endif
#if defined GL_AND_REVERSE
	case GL_AND_REVERSE: return "AND_REVERSE";
#endif
#if defined GL_COPY
	case GL_COPY: return "COPY";
#endif
#if defined GL_AND_INVERTED
	case GL_AND_INVERTED: return "AND_INVERTED";
#endif
#if defined GL_NOOP
	case GL_NOOP: return "NOOP";
#endif
#if defined GL_XOR
	case GL_XOR: return "XOR";
#endif
#if defined GL_OR
	case GL_OR: return "OR";
#endif
#if defined GL_NOR
	case GL_NOR: return "NOR";
#endif
#if defined GL_EQUIV
	case GL_EQUIV: return "EQUIV";
#endif
#if defined GL_INVERT
	case GL_INVERT: return "INVERT";
#endif
#if defined GL_OR_REVERSE
	case GL_OR_REVERSE: return "OR_REVERSE";
#endif
#if defined GL_COPY_INVERTED
	case GL_COPY_INVERTED: return "COPY_INVERTED";
#endif
#if defined GL_OR_INVERTED
	case GL_OR_INVERTED: return "OR_INVERTED";
#endif
#if defined GL_NAND
	case GL_NAND: return "NAND";
#endif
#if defined GL_SET
	case GL_SET: return "SET";
#endif
	default:;
}

