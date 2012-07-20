/*
 *  .file oglplus/enums/capability.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/capability.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// PRIMITIVE_RESTART
PrimitiveRestart,
/// DEPTH_TEST
DepthTest,
/// STENCIL_TEST
StencilTest,
/// SCISSOR_TEST
ScissorTest,
/// CULL_FACE
CullFace,
/// RASTERIZER_DISCARD
RasterizerDiscard,
/// POLYGON_OFFSET_POINT
PolygonOffsetPoint,
/// POLYGON_OFFSET_LINE
PolygonOffsetLine,
/// POLYGON_OFFSET_FILL
PolygonOffsetFill,
/// BLEND
Blend,
/// COLOR_LOGIC_OP
ColorLogicOp,
/// DITHER
Dither,
/// MULTISAMPLE
Multisample,
/// SAMPLE_SHADING
SampleShading,
/// LINE_SMOOTH
LineSmooth,
/// POLYGON_SMOOTH
PolygonSmooth,
/// PROGRAM_POINT_SIZE
ProgramPointSize,
/// TEXTURE_CUBE_MAP_SEAMLESS
TextureCubeMapSeamless,
/// SAMPLE_ALPHA_TO_COVERAGE
SampleAlphaToCoverage,
/// SAMPLE_ALPHA_TO_ONE
SampleAlphaToOne,
/// SAMPLE_COVERAGE
SampleCoverage,
/// FRAMEBUFFER_SRGB
FramebufferSrgb

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_PRIMITIVE_RESTART
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(PrimitiveRestart)
#  pragma push_macro("PrimitiveRestart")
#  undef PrimitiveRestart
   OGLPLUS_ENUM_CLASS_VALUE(PrimitiveRestart, GL_PRIMITIVE_RESTART)
#  pragma pop_macro("PrimitiveRestart")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PrimitiveRestart, GL_PRIMITIVE_RESTART)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEPTH_TEST
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DepthTest)
#  pragma push_macro("DepthTest")
#  undef DepthTest
   OGLPLUS_ENUM_CLASS_VALUE(DepthTest, GL_DEPTH_TEST)
#  pragma pop_macro("DepthTest")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DepthTest, GL_DEPTH_TEST)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STENCIL_TEST
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(StencilTest)
#  pragma push_macro("StencilTest")
#  undef StencilTest
   OGLPLUS_ENUM_CLASS_VALUE(StencilTest, GL_STENCIL_TEST)
#  pragma pop_macro("StencilTest")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StencilTest, GL_STENCIL_TEST)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SCISSOR_TEST
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ScissorTest)
#  pragma push_macro("ScissorTest")
#  undef ScissorTest
   OGLPLUS_ENUM_CLASS_VALUE(ScissorTest, GL_SCISSOR_TEST)
#  pragma pop_macro("ScissorTest")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ScissorTest, GL_SCISSOR_TEST)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_CULL_FACE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(CullFace)
#  pragma push_macro("CullFace")
#  undef CullFace
   OGLPLUS_ENUM_CLASS_VALUE(CullFace, GL_CULL_FACE)
#  pragma pop_macro("CullFace")
# else
   OGLPLUS_ENUM_CLASS_VALUE(CullFace, GL_CULL_FACE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_RASTERIZER_DISCARD
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(RasterizerDiscard)
#  pragma push_macro("RasterizerDiscard")
#  undef RasterizerDiscard
   OGLPLUS_ENUM_CLASS_VALUE(RasterizerDiscard, GL_RASTERIZER_DISCARD)
#  pragma pop_macro("RasterizerDiscard")
# else
   OGLPLUS_ENUM_CLASS_VALUE(RasterizerDiscard, GL_RASTERIZER_DISCARD)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_POLYGON_OFFSET_POINT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(PolygonOffsetPoint)
#  pragma push_macro("PolygonOffsetPoint")
#  undef PolygonOffsetPoint
   OGLPLUS_ENUM_CLASS_VALUE(PolygonOffsetPoint, GL_POLYGON_OFFSET_POINT)
#  pragma pop_macro("PolygonOffsetPoint")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PolygonOffsetPoint, GL_POLYGON_OFFSET_POINT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_POLYGON_OFFSET_LINE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(PolygonOffsetLine)
#  pragma push_macro("PolygonOffsetLine")
#  undef PolygonOffsetLine
   OGLPLUS_ENUM_CLASS_VALUE(PolygonOffsetLine, GL_POLYGON_OFFSET_LINE)
#  pragma pop_macro("PolygonOffsetLine")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PolygonOffsetLine, GL_POLYGON_OFFSET_LINE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_POLYGON_OFFSET_FILL
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(PolygonOffsetFill)
#  pragma push_macro("PolygonOffsetFill")
#  undef PolygonOffsetFill
   OGLPLUS_ENUM_CLASS_VALUE(PolygonOffsetFill, GL_POLYGON_OFFSET_FILL)
#  pragma pop_macro("PolygonOffsetFill")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PolygonOffsetFill, GL_POLYGON_OFFSET_FILL)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BLEND
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Blend)
#  pragma push_macro("Blend")
#  undef Blend
   OGLPLUS_ENUM_CLASS_VALUE(Blend, GL_BLEND)
#  pragma pop_macro("Blend")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Blend, GL_BLEND)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COLOR_LOGIC_OP
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ColorLogicOp)
#  pragma push_macro("ColorLogicOp")
#  undef ColorLogicOp
   OGLPLUS_ENUM_CLASS_VALUE(ColorLogicOp, GL_COLOR_LOGIC_OP)
#  pragma pop_macro("ColorLogicOp")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ColorLogicOp, GL_COLOR_LOGIC_OP)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DITHER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Dither)
#  pragma push_macro("Dither")
#  undef Dither
   OGLPLUS_ENUM_CLASS_VALUE(Dither, GL_DITHER)
#  pragma pop_macro("Dither")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Dither, GL_DITHER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MULTISAMPLE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Multisample)
#  pragma push_macro("Multisample")
#  undef Multisample
   OGLPLUS_ENUM_CLASS_VALUE(Multisample, GL_MULTISAMPLE)
#  pragma pop_macro("Multisample")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Multisample, GL_MULTISAMPLE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLE_SHADING
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SampleShading)
#  pragma push_macro("SampleShading")
#  undef SampleShading
   OGLPLUS_ENUM_CLASS_VALUE(SampleShading, GL_SAMPLE_SHADING)
#  pragma pop_macro("SampleShading")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SampleShading, GL_SAMPLE_SHADING)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINE_SMOOTH
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(LineSmooth)
#  pragma push_macro("LineSmooth")
#  undef LineSmooth
   OGLPLUS_ENUM_CLASS_VALUE(LineSmooth, GL_LINE_SMOOTH)
#  pragma pop_macro("LineSmooth")
# else
   OGLPLUS_ENUM_CLASS_VALUE(LineSmooth, GL_LINE_SMOOTH)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_POLYGON_SMOOTH
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(PolygonSmooth)
#  pragma push_macro("PolygonSmooth")
#  undef PolygonSmooth
   OGLPLUS_ENUM_CLASS_VALUE(PolygonSmooth, GL_POLYGON_SMOOTH)
#  pragma pop_macro("PolygonSmooth")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PolygonSmooth, GL_POLYGON_SMOOTH)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PROGRAM_POINT_SIZE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ProgramPointSize)
#  pragma push_macro("ProgramPointSize")
#  undef ProgramPointSize
   OGLPLUS_ENUM_CLASS_VALUE(ProgramPointSize, GL_PROGRAM_POINT_SIZE)
#  pragma pop_macro("ProgramPointSize")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ProgramPointSize, GL_PROGRAM_POINT_SIZE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP_SEAMLESS
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(TextureCubeMapSeamless)
#  pragma push_macro("TextureCubeMapSeamless")
#  undef TextureCubeMapSeamless
   OGLPLUS_ENUM_CLASS_VALUE(TextureCubeMapSeamless, GL_TEXTURE_CUBE_MAP_SEAMLESS)
#  pragma pop_macro("TextureCubeMapSeamless")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TextureCubeMapSeamless, GL_TEXTURE_CUBE_MAP_SEAMLESS)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLE_ALPHA_TO_COVERAGE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SampleAlphaToCoverage)
#  pragma push_macro("SampleAlphaToCoverage")
#  undef SampleAlphaToCoverage
   OGLPLUS_ENUM_CLASS_VALUE(SampleAlphaToCoverage, GL_SAMPLE_ALPHA_TO_COVERAGE)
#  pragma pop_macro("SampleAlphaToCoverage")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SampleAlphaToCoverage, GL_SAMPLE_ALPHA_TO_COVERAGE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLE_ALPHA_TO_ONE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SampleAlphaToOne)
#  pragma push_macro("SampleAlphaToOne")
#  undef SampleAlphaToOne
   OGLPLUS_ENUM_CLASS_VALUE(SampleAlphaToOne, GL_SAMPLE_ALPHA_TO_ONE)
#  pragma pop_macro("SampleAlphaToOne")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SampleAlphaToOne, GL_SAMPLE_ALPHA_TO_ONE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLE_COVERAGE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SampleCoverage)
#  pragma push_macro("SampleCoverage")
#  undef SampleCoverage
   OGLPLUS_ENUM_CLASS_VALUE(SampleCoverage, GL_SAMPLE_COVERAGE)
#  pragma pop_macro("SampleCoverage")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SampleCoverage, GL_SAMPLE_COVERAGE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRAMEBUFFER_SRGB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FramebufferSrgb)
#  pragma push_macro("FramebufferSrgb")
#  undef FramebufferSrgb
   OGLPLUS_ENUM_CLASS_VALUE(FramebufferSrgb, GL_FRAMEBUFFER_SRGB)
#  pragma pop_macro("FramebufferSrgb")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FramebufferSrgb, GL_FRAMEBUFFER_SRGB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

