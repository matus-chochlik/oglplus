/*
 *  .file oglplus/enums/capability_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/capability.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	Capability*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_CAPABILITY)
#define OGLPLUS_IMPL_EVN_CAPABILITY
{
switch(value)
{
#if defined GL_PRIMITIVE_RESTART
	case GL_PRIMITIVE_RESTART: return StrLit("PRIMITIVE_RESTART");
#endif
#if defined GL_DEPTH_TEST
	case GL_DEPTH_TEST: return StrLit("DEPTH_TEST");
#endif
#if defined GL_STENCIL_TEST
	case GL_STENCIL_TEST: return StrLit("STENCIL_TEST");
#endif
#if defined GL_SCISSOR_TEST
	case GL_SCISSOR_TEST: return StrLit("SCISSOR_TEST");
#endif
#if defined GL_CULL_FACE
	case GL_CULL_FACE: return StrLit("CULL_FACE");
#endif
#if defined GL_RASTERIZER_DISCARD
	case GL_RASTERIZER_DISCARD: return StrLit("RASTERIZER_DISCARD");
#endif
#if defined GL_POLYGON_OFFSET_POINT
	case GL_POLYGON_OFFSET_POINT: return StrLit("POLYGON_OFFSET_POINT");
#endif
#if defined GL_POLYGON_OFFSET_LINE
	case GL_POLYGON_OFFSET_LINE: return StrLit("POLYGON_OFFSET_LINE");
#endif
#if defined GL_POLYGON_OFFSET_FILL
	case GL_POLYGON_OFFSET_FILL: return StrLit("POLYGON_OFFSET_FILL");
#endif
#if defined GL_BLEND
	case GL_BLEND: return StrLit("BLEND");
#endif
#if defined GL_COLOR_LOGIC_OP
	case GL_COLOR_LOGIC_OP: return StrLit("COLOR_LOGIC_OP");
#endif
#if defined GL_DITHER
	case GL_DITHER: return StrLit("DITHER");
#endif
#if defined GL_MULTISAMPLE
	case GL_MULTISAMPLE: return StrLit("MULTISAMPLE");
#endif
#if defined GL_SAMPLE_SHADING
	case GL_SAMPLE_SHADING: return StrLit("SAMPLE_SHADING");
#endif
#if defined GL_LINE_SMOOTH
	case GL_LINE_SMOOTH: return StrLit("LINE_SMOOTH");
#endif
#if defined GL_POLYGON_SMOOTH
	case GL_POLYGON_SMOOTH: return StrLit("POLYGON_SMOOTH");
#endif
#if defined GL_PROGRAM_POINT_SIZE
	case GL_PROGRAM_POINT_SIZE: return StrLit("PROGRAM_POINT_SIZE");
#endif
#if defined GL_TEXTURE_CUBE_MAP_SEAMLESS
	case GL_TEXTURE_CUBE_MAP_SEAMLESS: return StrLit("TEXTURE_CUBE_MAP_SEAMLESS");
#endif
#if defined GL_SAMPLE_ALPHA_TO_COVERAGE
	case GL_SAMPLE_ALPHA_TO_COVERAGE: return StrLit("SAMPLE_ALPHA_TO_COVERAGE");
#endif
#if defined GL_SAMPLE_ALPHA_TO_ONE
	case GL_SAMPLE_ALPHA_TO_ONE: return StrLit("SAMPLE_ALPHA_TO_ONE");
#endif
#if defined GL_SAMPLE_COVERAGE
	case GL_SAMPLE_COVERAGE: return StrLit("SAMPLE_COVERAGE");
#endif
#if defined GL_FRAMEBUFFER_SRGB
	case GL_FRAMEBUFFER_SRGB: return StrLit("FRAMEBUFFER_SRGB");
#endif
#if defined GL_STREAM_RASTERIZATION_AMD
	case GL_STREAM_RASTERIZATION_AMD: return StrLit("STREAM_RASTERIZATION_AMD");
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

