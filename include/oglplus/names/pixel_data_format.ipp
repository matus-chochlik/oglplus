/*
 *  .file oglplus/names/pixel_data_format.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/pixel_data_format.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_STENCIL_INDEX
	case GL_STENCIL_INDEX: return "STENCIL_INDEX";
#endif
#if defined GL_DEPTH_COMPONENT
	case GL_DEPTH_COMPONENT: return "DEPTH_COMPONENT";
#endif
#if defined GL_DEPTH_STENCIL
	case GL_DEPTH_STENCIL: return "DEPTH_STENCIL";
#endif
#if defined GL_RED
	case GL_RED: return "RED";
#endif
#if defined GL_GREEN
	case GL_GREEN: return "GREEN";
#endif
#if defined GL_BLUE
	case GL_BLUE: return "BLUE";
#endif
#if defined GL_RG
	case GL_RG: return "RG";
#endif
#if defined GL_RGB
	case GL_RGB: return "RGB";
#endif
#if defined GL_RGBA
	case GL_RGBA: return "RGBA";
#endif
#if defined GL_BGR
	case GL_BGR: return "BGR";
#endif
#if defined GL_BGRA
	case GL_BGRA: return "BGRA";
#endif
#if defined GL_RED_INTEGER
	case GL_RED_INTEGER: return "RED_INTEGER";
#endif
#if defined GL_GREEN_INTEGER
	case GL_GREEN_INTEGER: return "GREEN_INTEGER";
#endif
#if defined GL_BLUE_INTEGER
	case GL_BLUE_INTEGER: return "BLUE_INTEGER";
#endif
#if defined GL_RG_INTEGER
	case GL_RG_INTEGER: return "RG_INTEGER";
#endif
#if defined GL_RGB_INTEGER
	case GL_RGB_INTEGER: return "RGB_INTEGER";
#endif
#if defined GL_RGBA_INTEGER
	case GL_RGBA_INTEGER: return "RGBA_INTEGER";
#endif
#if defined GL_BGR_INTEGER
	case GL_BGR_INTEGER: return "BGR_INTEGER";
#endif
#if defined GL_BGRA_INTEGER
	case GL_BGRA_INTEGER: return "BGRA_INTEGER";
#endif
	default:;
}

