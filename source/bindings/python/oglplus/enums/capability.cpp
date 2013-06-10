/*
 *  .file oglplus/enums/capability.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/capability.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/capability.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_capability(void)
{
	boost::python::enum_<oglplus::Capability>("Capability")
#if defined GL_PRIMITIVE_RESTART
# if defined PrimitiveRestart
#  pragma push_macro("PrimitiveRestart")
#  undef PrimitiveRestart
	.value("PrimitiveRestart", oglplus::Capability::PrimitiveRestart)
#  pragma pop_macro("PrimitiveRestart")
# else
	.value("PrimitiveRestart", oglplus::Capability::PrimitiveRestart)
# endif
#endif
#if defined GL_DEPTH_TEST
# if defined DepthTest
#  pragma push_macro("DepthTest")
#  undef DepthTest
	.value("DepthTest", oglplus::Capability::DepthTest)
#  pragma pop_macro("DepthTest")
# else
	.value("DepthTest", oglplus::Capability::DepthTest)
# endif
#endif
#if defined GL_STENCIL_TEST
# if defined StencilTest
#  pragma push_macro("StencilTest")
#  undef StencilTest
	.value("StencilTest", oglplus::Capability::StencilTest)
#  pragma pop_macro("StencilTest")
# else
	.value("StencilTest", oglplus::Capability::StencilTest)
# endif
#endif
#if defined GL_SCISSOR_TEST
# if defined ScissorTest
#  pragma push_macro("ScissorTest")
#  undef ScissorTest
	.value("ScissorTest", oglplus::Capability::ScissorTest)
#  pragma pop_macro("ScissorTest")
# else
	.value("ScissorTest", oglplus::Capability::ScissorTest)
# endif
#endif
#if defined GL_CULL_FACE
# if defined CullFace
#  pragma push_macro("CullFace")
#  undef CullFace
	.value("CullFace", oglplus::Capability::CullFace)
#  pragma pop_macro("CullFace")
# else
	.value("CullFace", oglplus::Capability::CullFace)
# endif
#endif
#if defined GL_RASTERIZER_DISCARD
# if defined RasterizerDiscard
#  pragma push_macro("RasterizerDiscard")
#  undef RasterizerDiscard
	.value("RasterizerDiscard", oglplus::Capability::RasterizerDiscard)
#  pragma pop_macro("RasterizerDiscard")
# else
	.value("RasterizerDiscard", oglplus::Capability::RasterizerDiscard)
# endif
#endif
#if defined GL_POLYGON_OFFSET_POINT
# if defined PolygonOffsetPoint
#  pragma push_macro("PolygonOffsetPoint")
#  undef PolygonOffsetPoint
	.value("PolygonOffsetPoint", oglplus::Capability::PolygonOffsetPoint)
#  pragma pop_macro("PolygonOffsetPoint")
# else
	.value("PolygonOffsetPoint", oglplus::Capability::PolygonOffsetPoint)
# endif
#endif
#if defined GL_POLYGON_OFFSET_LINE
# if defined PolygonOffsetLine
#  pragma push_macro("PolygonOffsetLine")
#  undef PolygonOffsetLine
	.value("PolygonOffsetLine", oglplus::Capability::PolygonOffsetLine)
#  pragma pop_macro("PolygonOffsetLine")
# else
	.value("PolygonOffsetLine", oglplus::Capability::PolygonOffsetLine)
# endif
#endif
#if defined GL_POLYGON_OFFSET_FILL
# if defined PolygonOffsetFill
#  pragma push_macro("PolygonOffsetFill")
#  undef PolygonOffsetFill
	.value("PolygonOffsetFill", oglplus::Capability::PolygonOffsetFill)
#  pragma pop_macro("PolygonOffsetFill")
# else
	.value("PolygonOffsetFill", oglplus::Capability::PolygonOffsetFill)
# endif
#endif
#if defined GL_BLEND
# if defined Blend
#  pragma push_macro("Blend")
#  undef Blend
	.value("Blend", oglplus::Capability::Blend)
#  pragma pop_macro("Blend")
# else
	.value("Blend", oglplus::Capability::Blend)
# endif
#endif
#if defined GL_COLOR_LOGIC_OP
# if defined ColorLogicOp
#  pragma push_macro("ColorLogicOp")
#  undef ColorLogicOp
	.value("ColorLogicOp", oglplus::Capability::ColorLogicOp)
#  pragma pop_macro("ColorLogicOp")
# else
	.value("ColorLogicOp", oglplus::Capability::ColorLogicOp)
# endif
#endif
#if defined GL_DITHER
# if defined Dither
#  pragma push_macro("Dither")
#  undef Dither
	.value("Dither", oglplus::Capability::Dither)
#  pragma pop_macro("Dither")
# else
	.value("Dither", oglplus::Capability::Dither)
# endif
#endif
#if defined GL_MULTISAMPLE
# if defined Multisample
#  pragma push_macro("Multisample")
#  undef Multisample
	.value("Multisample", oglplus::Capability::Multisample)
#  pragma pop_macro("Multisample")
# else
	.value("Multisample", oglplus::Capability::Multisample)
# endif
#endif
#if defined GL_SAMPLE_SHADING
# if defined SampleShading
#  pragma push_macro("SampleShading")
#  undef SampleShading
	.value("SampleShading", oglplus::Capability::SampleShading)
#  pragma pop_macro("SampleShading")
# else
	.value("SampleShading", oglplus::Capability::SampleShading)
# endif
#endif
#if defined GL_LINE_SMOOTH
# if defined LineSmooth
#  pragma push_macro("LineSmooth")
#  undef LineSmooth
	.value("LineSmooth", oglplus::Capability::LineSmooth)
#  pragma pop_macro("LineSmooth")
# else
	.value("LineSmooth", oglplus::Capability::LineSmooth)
# endif
#endif
#if defined GL_POLYGON_SMOOTH
# if defined PolygonSmooth
#  pragma push_macro("PolygonSmooth")
#  undef PolygonSmooth
	.value("PolygonSmooth", oglplus::Capability::PolygonSmooth)
#  pragma pop_macro("PolygonSmooth")
# else
	.value("PolygonSmooth", oglplus::Capability::PolygonSmooth)
# endif
#endif
#if defined GL_PROGRAM_POINT_SIZE
# if defined ProgramPointSize
#  pragma push_macro("ProgramPointSize")
#  undef ProgramPointSize
	.value("ProgramPointSize", oglplus::Capability::ProgramPointSize)
#  pragma pop_macro("ProgramPointSize")
# else
	.value("ProgramPointSize", oglplus::Capability::ProgramPointSize)
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP_SEAMLESS
# if defined TextureCubeMapSeamless
#  pragma push_macro("TextureCubeMapSeamless")
#  undef TextureCubeMapSeamless
	.value("TextureCubeMapSeamless", oglplus::Capability::TextureCubeMapSeamless)
#  pragma pop_macro("TextureCubeMapSeamless")
# else
	.value("TextureCubeMapSeamless", oglplus::Capability::TextureCubeMapSeamless)
# endif
#endif
#if defined GL_SAMPLE_ALPHA_TO_COVERAGE
# if defined SampleAlphaToCoverage
#  pragma push_macro("SampleAlphaToCoverage")
#  undef SampleAlphaToCoverage
	.value("SampleAlphaToCoverage", oglplus::Capability::SampleAlphaToCoverage)
#  pragma pop_macro("SampleAlphaToCoverage")
# else
	.value("SampleAlphaToCoverage", oglplus::Capability::SampleAlphaToCoverage)
# endif
#endif
#if defined GL_SAMPLE_ALPHA_TO_ONE
# if defined SampleAlphaToOne
#  pragma push_macro("SampleAlphaToOne")
#  undef SampleAlphaToOne
	.value("SampleAlphaToOne", oglplus::Capability::SampleAlphaToOne)
#  pragma pop_macro("SampleAlphaToOne")
# else
	.value("SampleAlphaToOne", oglplus::Capability::SampleAlphaToOne)
# endif
#endif
#if defined GL_SAMPLE_COVERAGE
# if defined SampleCoverage
#  pragma push_macro("SampleCoverage")
#  undef SampleCoverage
	.value("SampleCoverage", oglplus::Capability::SampleCoverage)
#  pragma pop_macro("SampleCoverage")
# else
	.value("SampleCoverage", oglplus::Capability::SampleCoverage)
# endif
#endif
#if defined GL_FRAMEBUFFER_SRGB
# if defined FramebufferSrgb
#  pragma push_macro("FramebufferSrgb")
#  undef FramebufferSrgb
	.value("FramebufferSrgb", oglplus::Capability::FramebufferSrgb)
#  pragma pop_macro("FramebufferSrgb")
# else
	.value("FramebufferSrgb", oglplus::Capability::FramebufferSrgb)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::Capability) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::Capability
		>
	>("aux_CastIterRange_Capability");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::Capability
	> (*PEnumValueRange)(oglplus::Capability) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
