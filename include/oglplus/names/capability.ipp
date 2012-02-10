/*
 *  .file oglplus/names/capability.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/capability.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_PRIMITIVE_RESTART
	case GL_PRIMITIVE_RESTART: return "PRIMITIVE_RESTART";
#endif
#if defined GL_DEPTH_TEST
	case GL_DEPTH_TEST: return "DEPTH_TEST";
#endif
#if defined GL_STENCIL_TEST
	case GL_STENCIL_TEST: return "STENCIL_TEST";
#endif
#if defined GL_SCISSOR_TEST
	case GL_SCISSOR_TEST: return "SCISSOR_TEST";
#endif
#if defined GL_CULL_FACE
	case GL_CULL_FACE: return "CULL_FACE";
#endif
#if defined GL_RASTERIZER_DISCARD
	case GL_RASTERIZER_DISCARD: return "RASTERIZER_DISCARD";
#endif
#if defined GL_POLYGON_OFFSET_POINT
	case GL_POLYGON_OFFSET_POINT: return "POLYGON_OFFSET_POINT";
#endif
#if defined GL_POLYGON_OFFSET_LINE
	case GL_POLYGON_OFFSET_LINE: return "POLYGON_OFFSET_LINE";
#endif
#if defined GL_POLYGON_OFFSET_FILL
	case GL_POLYGON_OFFSET_FILL: return "POLYGON_OFFSET_FILL";
#endif
#if defined GL_BLEND
	case GL_BLEND: return "BLEND";
#endif
#if defined GL_COLOR_LOGIC_OP
	case GL_COLOR_LOGIC_OP: return "COLOR_LOGIC_OP";
#endif
#if defined GL_DITHER
	case GL_DITHER: return "DITHER";
#endif
#if defined GL_MULTISAMPLE
	case GL_MULTISAMPLE: return "MULTISAMPLE";
#endif
#if defined GL_SAMPLE_SHADING
	case GL_SAMPLE_SHADING: return "SAMPLE_SHADING";
#endif
#if defined GL_LINE_SMOOTH
	case GL_LINE_SMOOTH: return "LINE_SMOOTH";
#endif
#if defined GL_POLYGON_SMOOTH
	case GL_POLYGON_SMOOTH: return "POLYGON_SMOOTH";
#endif
#if defined GL_PROGRAM_POINT_SIZE
	case GL_PROGRAM_POINT_SIZE: return "PROGRAM_POINT_SIZE";
#endif
#if defined GL_TEXTURE_CUBE_MAP_SEAMLESS
	case GL_TEXTURE_CUBE_MAP_SEAMLESS: return "TEXTURE_CUBE_MAP_SEAMLESS";
#endif
#if defined GL_SAMPLE_ALPHA_TO_COVERAGE
	case GL_SAMPLE_ALPHA_TO_COVERAGE: return "SAMPLE_ALPHA_TO_COVERAGE";
#endif
#if defined GL_SAMPLE_ALPHA_TO_ONE
	case GL_SAMPLE_ALPHA_TO_ONE: return "SAMPLE_ALPHA_TO_ONE";
#endif
#if defined GL_SAMPLE_COVERAGE
	case GL_SAMPLE_COVERAGE: return "SAMPLE_COVERAGE";
#endif
#if defined GL_FRAMEBUFFER_SRGB
	case GL_FRAMEBUFFER_SRGB: return "FRAMEBUFFER_SRGB";
#endif
	default:;
}

