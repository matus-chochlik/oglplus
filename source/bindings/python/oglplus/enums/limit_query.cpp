/*
 *  .file oglplus/enums/limit_query.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/limit_query.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/limit_query.hpp>

#include <boost/python.hpp>

void oglplus_py_limit_query(void)
{
	boost::python::enum_<oglplus::LimitQuery>("LimitQuery")
#if defined GL_MAX_3D_TEXTURE_SIZE
# if defined Max3DTextureSize
#  pragma push_macro("Max3DTextureSize")
#  undef Max3DTextureSize
	.value("Max3DTextureSize", oglplus::LimitQuery::Max3DTextureSize)
#  pragma pop_macro("Max3DTextureSize")
# else
	.value("Max3DTextureSize", oglplus::LimitQuery::Max3DTextureSize)
# endif
#endif
#if defined GL_MAX_ARRAY_TEXTURE_LAYERS
# if defined MaxArrayTextureLayers
#  pragma push_macro("MaxArrayTextureLayers")
#  undef MaxArrayTextureLayers
	.value("MaxArrayTextureLayers", oglplus::LimitQuery::MaxArrayTextureLayers)
#  pragma pop_macro("MaxArrayTextureLayers")
# else
	.value("MaxArrayTextureLayers", oglplus::LimitQuery::MaxArrayTextureLayers)
# endif
#endif
#if defined GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS
# if defined MaxAtomicCounterBufferBindings
#  pragma push_macro("MaxAtomicCounterBufferBindings")
#  undef MaxAtomicCounterBufferBindings
	.value("MaxAtomicCounterBufferBindings", oglplus::LimitQuery::MaxAtomicCounterBufferBindings)
#  pragma pop_macro("MaxAtomicCounterBufferBindings")
# else
	.value("MaxAtomicCounterBufferBindings", oglplus::LimitQuery::MaxAtomicCounterBufferBindings)
# endif
#endif
#if defined GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE
# if defined MaxAtomicCounterBufferSize
#  pragma push_macro("MaxAtomicCounterBufferSize")
#  undef MaxAtomicCounterBufferSize
	.value("MaxAtomicCounterBufferSize", oglplus::LimitQuery::MaxAtomicCounterBufferSize)
#  pragma pop_macro("MaxAtomicCounterBufferSize")
# else
	.value("MaxAtomicCounterBufferSize", oglplus::LimitQuery::MaxAtomicCounterBufferSize)
# endif
#endif
#if defined GL_MAX_CLIP_DISTANCES
# if defined MaxClipDistances
#  pragma push_macro("MaxClipDistances")
#  undef MaxClipDistances
	.value("MaxClipDistances", oglplus::LimitQuery::MaxClipDistances)
#  pragma pop_macro("MaxClipDistances")
# else
	.value("MaxClipDistances", oglplus::LimitQuery::MaxClipDistances)
# endif
#endif
#if defined GL_MAX_COLOR_ATTACHMENTS
# if defined MaxColorAttachments
#  pragma push_macro("MaxColorAttachments")
#  undef MaxColorAttachments
	.value("MaxColorAttachments", oglplus::LimitQuery::MaxColorAttachments)
#  pragma pop_macro("MaxColorAttachments")
# else
	.value("MaxColorAttachments", oglplus::LimitQuery::MaxColorAttachments)
# endif
#endif
#if defined GL_MAX_COLOR_TEXTURE_SAMPLES
# if defined MaxColorTextureSamples
#  pragma push_macro("MaxColorTextureSamples")
#  undef MaxColorTextureSamples
	.value("MaxColorTextureSamples", oglplus::LimitQuery::MaxColorTextureSamples)
#  pragma pop_macro("MaxColorTextureSamples")
# else
	.value("MaxColorTextureSamples", oglplus::LimitQuery::MaxColorTextureSamples)
# endif
#endif
#if defined GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS
# if defined MaxCombinedAtomicCounterBuffers
#  pragma push_macro("MaxCombinedAtomicCounterBuffers")
#  undef MaxCombinedAtomicCounterBuffers
	.value("MaxCombinedAtomicCounterBuffers", oglplus::LimitQuery::MaxCombinedAtomicCounterBuffers)
#  pragma pop_macro("MaxCombinedAtomicCounterBuffers")
# else
	.value("MaxCombinedAtomicCounterBuffers", oglplus::LimitQuery::MaxCombinedAtomicCounterBuffers)
# endif
#endif
#if defined GL_MAX_COMBINED_ATOMIC_COUNTERS
# if defined MaxCombinedAtomicCounters
#  pragma push_macro("MaxCombinedAtomicCounters")
#  undef MaxCombinedAtomicCounters
	.value("MaxCombinedAtomicCounters", oglplus::LimitQuery::MaxCombinedAtomicCounters)
#  pragma pop_macro("MaxCombinedAtomicCounters")
# else
	.value("MaxCombinedAtomicCounters", oglplus::LimitQuery::MaxCombinedAtomicCounters)
# endif
#endif
#if defined GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS
# if defined MaxCombinedFragmentUniformComponents
#  pragma push_macro("MaxCombinedFragmentUniformComponents")
#  undef MaxCombinedFragmentUniformComponents
	.value("MaxCombinedFragmentUniformComponents", oglplus::LimitQuery::MaxCombinedFragmentUniformComponents)
#  pragma pop_macro("MaxCombinedFragmentUniformComponents")
# else
	.value("MaxCombinedFragmentUniformComponents", oglplus::LimitQuery::MaxCombinedFragmentUniformComponents)
# endif
#endif
#if defined GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS
# if defined MaxCombinedGeometryUniformComponents
#  pragma push_macro("MaxCombinedGeometryUniformComponents")
#  undef MaxCombinedGeometryUniformComponents
	.value("MaxCombinedGeometryUniformComponents", oglplus::LimitQuery::MaxCombinedGeometryUniformComponents)
#  pragma pop_macro("MaxCombinedGeometryUniformComponents")
# else
	.value("MaxCombinedGeometryUniformComponents", oglplus::LimitQuery::MaxCombinedGeometryUniformComponents)
# endif
#endif
#if defined GL_MAX_COMBINED_IMAGE_UNIFORMS
# if defined MaxCombinedImageUniforms
#  pragma push_macro("MaxCombinedImageUniforms")
#  undef MaxCombinedImageUniforms
	.value("MaxCombinedImageUniforms", oglplus::LimitQuery::MaxCombinedImageUniforms)
#  pragma pop_macro("MaxCombinedImageUniforms")
# else
	.value("MaxCombinedImageUniforms", oglplus::LimitQuery::MaxCombinedImageUniforms)
# endif
#endif
#if defined GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS
# if defined MaxCombinedImageUnitsAndFragmentOutputs
#  pragma push_macro("MaxCombinedImageUnitsAndFragmentOutputs")
#  undef MaxCombinedImageUnitsAndFragmentOutputs
	.value("MaxCombinedImageUnitsAndFragmentOutputs", oglplus::LimitQuery::MaxCombinedImageUnitsAndFragmentOutputs)
#  pragma pop_macro("MaxCombinedImageUnitsAndFragmentOutputs")
# else
	.value("MaxCombinedImageUnitsAndFragmentOutputs", oglplus::LimitQuery::MaxCombinedImageUnitsAndFragmentOutputs)
# endif
#endif
#if defined GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS
# if defined MaxCombinedTessControlUniformComponents
#  pragma push_macro("MaxCombinedTessControlUniformComponents")
#  undef MaxCombinedTessControlUniformComponents
	.value("MaxCombinedTessControlUniformComponents", oglplus::LimitQuery::MaxCombinedTessControlUniformComponents)
#  pragma pop_macro("MaxCombinedTessControlUniformComponents")
# else
	.value("MaxCombinedTessControlUniformComponents", oglplus::LimitQuery::MaxCombinedTessControlUniformComponents)
# endif
#endif
#if defined GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS
# if defined MaxCombinedTessEvaluationUniformComponents
#  pragma push_macro("MaxCombinedTessEvaluationUniformComponents")
#  undef MaxCombinedTessEvaluationUniformComponents
	.value("MaxCombinedTessEvaluationUniformComponents", oglplus::LimitQuery::MaxCombinedTessEvaluationUniformComponents)
#  pragma pop_macro("MaxCombinedTessEvaluationUniformComponents")
# else
	.value("MaxCombinedTessEvaluationUniformComponents", oglplus::LimitQuery::MaxCombinedTessEvaluationUniformComponents)
# endif
#endif
#if defined GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
# if defined MaxCombinedTextureImageUnits
#  pragma push_macro("MaxCombinedTextureImageUnits")
#  undef MaxCombinedTextureImageUnits
	.value("MaxCombinedTextureImageUnits", oglplus::LimitQuery::MaxCombinedTextureImageUnits)
#  pragma pop_macro("MaxCombinedTextureImageUnits")
# else
	.value("MaxCombinedTextureImageUnits", oglplus::LimitQuery::MaxCombinedTextureImageUnits)
# endif
#endif
#if defined GL_MAX_COMBINED_UNIFORM_BLOCKS
# if defined MaxCombinedUniformBlocks
#  pragma push_macro("MaxCombinedUniformBlocks")
#  undef MaxCombinedUniformBlocks
	.value("MaxCombinedUniformBlocks", oglplus::LimitQuery::MaxCombinedUniformBlocks)
#  pragma pop_macro("MaxCombinedUniformBlocks")
# else
	.value("MaxCombinedUniformBlocks", oglplus::LimitQuery::MaxCombinedUniformBlocks)
# endif
#endif
#if defined GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS
# if defined MaxCombinedVertexUniformComponents
#  pragma push_macro("MaxCombinedVertexUniformComponents")
#  undef MaxCombinedVertexUniformComponents
	.value("MaxCombinedVertexUniformComponents", oglplus::LimitQuery::MaxCombinedVertexUniformComponents)
#  pragma pop_macro("MaxCombinedVertexUniformComponents")
# else
	.value("MaxCombinedVertexUniformComponents", oglplus::LimitQuery::MaxCombinedVertexUniformComponents)
# endif
#endif
#if defined GL_MAX_CUBE_MAP_TEXTURE_SIZE
# if defined MaxCubeMapTextureSize
#  pragma push_macro("MaxCubeMapTextureSize")
#  undef MaxCubeMapTextureSize
	.value("MaxCubeMapTextureSize", oglplus::LimitQuery::MaxCubeMapTextureSize)
#  pragma pop_macro("MaxCubeMapTextureSize")
# else
	.value("MaxCubeMapTextureSize", oglplus::LimitQuery::MaxCubeMapTextureSize)
# endif
#endif
#if defined GL_MAX_DEPTH_TEXTURE_SAMPLES
# if defined MaxDepthTextureSamples
#  pragma push_macro("MaxDepthTextureSamples")
#  undef MaxDepthTextureSamples
	.value("MaxDepthTextureSamples", oglplus::LimitQuery::MaxDepthTextureSamples)
#  pragma pop_macro("MaxDepthTextureSamples")
# else
	.value("MaxDepthTextureSamples", oglplus::LimitQuery::MaxDepthTextureSamples)
# endif
#endif
#if defined GL_MAX_DRAW_BUFFERS
# if defined MaxDrawBuffers
#  pragma push_macro("MaxDrawBuffers")
#  undef MaxDrawBuffers
	.value("MaxDrawBuffers", oglplus::LimitQuery::MaxDrawBuffers)
#  pragma pop_macro("MaxDrawBuffers")
# else
	.value("MaxDrawBuffers", oglplus::LimitQuery::MaxDrawBuffers)
# endif
#endif
#if defined GL_MAX_DUAL_SOURCE_DRAW_BUFFERS
# if defined MaxDualSourceDrawBuffers
#  pragma push_macro("MaxDualSourceDrawBuffers")
#  undef MaxDualSourceDrawBuffers
	.value("MaxDualSourceDrawBuffers", oglplus::LimitQuery::MaxDualSourceDrawBuffers)
#  pragma pop_macro("MaxDualSourceDrawBuffers")
# else
	.value("MaxDualSourceDrawBuffers", oglplus::LimitQuery::MaxDualSourceDrawBuffers)
# endif
#endif
#if defined GL_MAX_ELEMENTS_INDICES
# if defined MaxElementsIndices
#  pragma push_macro("MaxElementsIndices")
#  undef MaxElementsIndices
	.value("MaxElementsIndices", oglplus::LimitQuery::MaxElementsIndices)
#  pragma pop_macro("MaxElementsIndices")
# else
	.value("MaxElementsIndices", oglplus::LimitQuery::MaxElementsIndices)
# endif
#endif
#if defined GL_MAX_ELEMENTS_VERTICES
# if defined MaxElementsVertices
#  pragma push_macro("MaxElementsVertices")
#  undef MaxElementsVertices
	.value("MaxElementsVertices", oglplus::LimitQuery::MaxElementsVertices)
#  pragma pop_macro("MaxElementsVertices")
# else
	.value("MaxElementsVertices", oglplus::LimitQuery::MaxElementsVertices)
# endif
#endif
#if defined GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS
# if defined MaxFragmentAtomicCounterBuffers
#  pragma push_macro("MaxFragmentAtomicCounterBuffers")
#  undef MaxFragmentAtomicCounterBuffers
	.value("MaxFragmentAtomicCounterBuffers", oglplus::LimitQuery::MaxFragmentAtomicCounterBuffers)
#  pragma pop_macro("MaxFragmentAtomicCounterBuffers")
# else
	.value("MaxFragmentAtomicCounterBuffers", oglplus::LimitQuery::MaxFragmentAtomicCounterBuffers)
# endif
#endif
#if defined GL_MAX_FRAGMENT_ATOMIC_COUNTERS
# if defined MaxFragmentAtomicCounters
#  pragma push_macro("MaxFragmentAtomicCounters")
#  undef MaxFragmentAtomicCounters
	.value("MaxFragmentAtomicCounters", oglplus::LimitQuery::MaxFragmentAtomicCounters)
#  pragma pop_macro("MaxFragmentAtomicCounters")
# else
	.value("MaxFragmentAtomicCounters", oglplus::LimitQuery::MaxFragmentAtomicCounters)
# endif
#endif
#if defined GL_MAX_FRAGMENT_IMAGE_UNIFORMS
# if defined MaxFragmentImageUniforms
#  pragma push_macro("MaxFragmentImageUniforms")
#  undef MaxFragmentImageUniforms
	.value("MaxFragmentImageUniforms", oglplus::LimitQuery::MaxFragmentImageUniforms)
#  pragma pop_macro("MaxFragmentImageUniforms")
# else
	.value("MaxFragmentImageUniforms", oglplus::LimitQuery::MaxFragmentImageUniforms)
# endif
#endif
#if defined GL_MAX_FRAGMENT_INPUT_COMPONENTS
# if defined MaxFragmentInputComponents
#  pragma push_macro("MaxFragmentInputComponents")
#  undef MaxFragmentInputComponents
	.value("MaxFragmentInputComponents", oglplus::LimitQuery::MaxFragmentInputComponents)
#  pragma pop_macro("MaxFragmentInputComponents")
# else
	.value("MaxFragmentInputComponents", oglplus::LimitQuery::MaxFragmentInputComponents)
# endif
#endif
#if defined GL_MAX_FRAGMENT_INTERPOLATION_OFFSET
# if defined MaxFragmentInterpolationOffset
#  pragma push_macro("MaxFragmentInterpolationOffset")
#  undef MaxFragmentInterpolationOffset
	.value("MaxFragmentInterpolationOffset", oglplus::LimitQuery::MaxFragmentInterpolationOffset)
#  pragma pop_macro("MaxFragmentInterpolationOffset")
# else
	.value("MaxFragmentInterpolationOffset", oglplus::LimitQuery::MaxFragmentInterpolationOffset)
# endif
#endif
#if defined GL_MAX_FRAGMENT_UNIFORM_BLOCKS
# if defined MaxFragmentUniformBlocks
#  pragma push_macro("MaxFragmentUniformBlocks")
#  undef MaxFragmentUniformBlocks
	.value("MaxFragmentUniformBlocks", oglplus::LimitQuery::MaxFragmentUniformBlocks)
#  pragma pop_macro("MaxFragmentUniformBlocks")
# else
	.value("MaxFragmentUniformBlocks", oglplus::LimitQuery::MaxFragmentUniformBlocks)
# endif
#endif
#if defined GL_MAX_FRAGMENT_UNIFORM_COMPONENTS
# if defined MaxFragmentUniformComponents
#  pragma push_macro("MaxFragmentUniformComponents")
#  undef MaxFragmentUniformComponents
	.value("MaxFragmentUniformComponents", oglplus::LimitQuery::MaxFragmentUniformComponents)
#  pragma pop_macro("MaxFragmentUniformComponents")
# else
	.value("MaxFragmentUniformComponents", oglplus::LimitQuery::MaxFragmentUniformComponents)
# endif
#endif
#if defined GL_MAX_FRAGMENT_UNIFORM_VECTORS
# if defined MaxFragmentUniformVectors
#  pragma push_macro("MaxFragmentUniformVectors")
#  undef MaxFragmentUniformVectors
	.value("MaxFragmentUniformVectors", oglplus::LimitQuery::MaxFragmentUniformVectors)
#  pragma pop_macro("MaxFragmentUniformVectors")
# else
	.value("MaxFragmentUniformVectors", oglplus::LimitQuery::MaxFragmentUniformVectors)
# endif
#endif
#if defined GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS
# if defined MaxGeometryAtomicCounterBuffers
#  pragma push_macro("MaxGeometryAtomicCounterBuffers")
#  undef MaxGeometryAtomicCounterBuffers
	.value("MaxGeometryAtomicCounterBuffers", oglplus::LimitQuery::MaxGeometryAtomicCounterBuffers)
#  pragma pop_macro("MaxGeometryAtomicCounterBuffers")
# else
	.value("MaxGeometryAtomicCounterBuffers", oglplus::LimitQuery::MaxGeometryAtomicCounterBuffers)
# endif
#endif
#if defined GL_MAX_GEOMETRY_ATOMIC_COUNTERS
# if defined MaxGeometryAtomicCounters
#  pragma push_macro("MaxGeometryAtomicCounters")
#  undef MaxGeometryAtomicCounters
	.value("MaxGeometryAtomicCounters", oglplus::LimitQuery::MaxGeometryAtomicCounters)
#  pragma pop_macro("MaxGeometryAtomicCounters")
# else
	.value("MaxGeometryAtomicCounters", oglplus::LimitQuery::MaxGeometryAtomicCounters)
# endif
#endif
#if defined GL_MAX_GEOMETRY_IMAGE_UNIFORMS
# if defined MaxGeometryImageUniforms
#  pragma push_macro("MaxGeometryImageUniforms")
#  undef MaxGeometryImageUniforms
	.value("MaxGeometryImageUniforms", oglplus::LimitQuery::MaxGeometryImageUniforms)
#  pragma pop_macro("MaxGeometryImageUniforms")
# else
	.value("MaxGeometryImageUniforms", oglplus::LimitQuery::MaxGeometryImageUniforms)
# endif
#endif
#if defined GL_MAX_GEOMETRY_INPUT_COMPONENTS
# if defined MaxGeometryInputComponents
#  pragma push_macro("MaxGeometryInputComponents")
#  undef MaxGeometryInputComponents
	.value("MaxGeometryInputComponents", oglplus::LimitQuery::MaxGeometryInputComponents)
#  pragma pop_macro("MaxGeometryInputComponents")
# else
	.value("MaxGeometryInputComponents", oglplus::LimitQuery::MaxGeometryInputComponents)
# endif
#endif
#if defined GL_MAX_GEOMETRY_OUTPUT_COMPONENTS
# if defined MaxGeometryOutputComponents
#  pragma push_macro("MaxGeometryOutputComponents")
#  undef MaxGeometryOutputComponents
	.value("MaxGeometryOutputComponents", oglplus::LimitQuery::MaxGeometryOutputComponents)
#  pragma pop_macro("MaxGeometryOutputComponents")
# else
	.value("MaxGeometryOutputComponents", oglplus::LimitQuery::MaxGeometryOutputComponents)
# endif
#endif
#if defined GL_MAX_GEOMETRY_OUTPUT_VERTICES
# if defined MaxGeometryOutputVertices
#  pragma push_macro("MaxGeometryOutputVertices")
#  undef MaxGeometryOutputVertices
	.value("MaxGeometryOutputVertices", oglplus::LimitQuery::MaxGeometryOutputVertices)
#  pragma pop_macro("MaxGeometryOutputVertices")
# else
	.value("MaxGeometryOutputVertices", oglplus::LimitQuery::MaxGeometryOutputVertices)
# endif
#endif
#if defined GL_MAX_GEOMETRY_SHADER_INVOCATIONS
# if defined MaxGeometryShaderInvocations
#  pragma push_macro("MaxGeometryShaderInvocations")
#  undef MaxGeometryShaderInvocations
	.value("MaxGeometryShaderInvocations", oglplus::LimitQuery::MaxGeometryShaderInvocations)
#  pragma pop_macro("MaxGeometryShaderInvocations")
# else
	.value("MaxGeometryShaderInvocations", oglplus::LimitQuery::MaxGeometryShaderInvocations)
# endif
#endif
#if defined GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS
# if defined MaxGeometryTextureImageUnits
#  pragma push_macro("MaxGeometryTextureImageUnits")
#  undef MaxGeometryTextureImageUnits
	.value("MaxGeometryTextureImageUnits", oglplus::LimitQuery::MaxGeometryTextureImageUnits)
#  pragma pop_macro("MaxGeometryTextureImageUnits")
# else
	.value("MaxGeometryTextureImageUnits", oglplus::LimitQuery::MaxGeometryTextureImageUnits)
# endif
#endif
#if defined GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS
# if defined MaxGeometryTotalOutputComponents
#  pragma push_macro("MaxGeometryTotalOutputComponents")
#  undef MaxGeometryTotalOutputComponents
	.value("MaxGeometryTotalOutputComponents", oglplus::LimitQuery::MaxGeometryTotalOutputComponents)
#  pragma pop_macro("MaxGeometryTotalOutputComponents")
# else
	.value("MaxGeometryTotalOutputComponents", oglplus::LimitQuery::MaxGeometryTotalOutputComponents)
# endif
#endif
#if defined GL_MAX_GEOMETRY_UNIFORM_BLOCKS
# if defined MaxGeometryUniformBlocks
#  pragma push_macro("MaxGeometryUniformBlocks")
#  undef MaxGeometryUniformBlocks
	.value("MaxGeometryUniformBlocks", oglplus::LimitQuery::MaxGeometryUniformBlocks)
#  pragma pop_macro("MaxGeometryUniformBlocks")
# else
	.value("MaxGeometryUniformBlocks", oglplus::LimitQuery::MaxGeometryUniformBlocks)
# endif
#endif
#if defined GL_MAX_GEOMETRY_UNIFORM_COMPONENTS
# if defined MaxGeometryUniformComponents
#  pragma push_macro("MaxGeometryUniformComponents")
#  undef MaxGeometryUniformComponents
	.value("MaxGeometryUniformComponents", oglplus::LimitQuery::MaxGeometryUniformComponents)
#  pragma pop_macro("MaxGeometryUniformComponents")
# else
	.value("MaxGeometryUniformComponents", oglplus::LimitQuery::MaxGeometryUniformComponents)
# endif
#endif
#if defined GL_MAX_IMAGE_SAMPLES
# if defined MaxImageSamples
#  pragma push_macro("MaxImageSamples")
#  undef MaxImageSamples
	.value("MaxImageSamples", oglplus::LimitQuery::MaxImageSamples)
#  pragma pop_macro("MaxImageSamples")
# else
	.value("MaxImageSamples", oglplus::LimitQuery::MaxImageSamples)
# endif
#endif
#if defined GL_MAX_IMAGE_UNITS
# if defined MaxImageUnits
#  pragma push_macro("MaxImageUnits")
#  undef MaxImageUnits
	.value("MaxImageUnits", oglplus::LimitQuery::MaxImageUnits)
#  pragma pop_macro("MaxImageUnits")
# else
	.value("MaxImageUnits", oglplus::LimitQuery::MaxImageUnits)
# endif
#endif
#if defined GL_MAX_INTEGER_SAMPLES
# if defined MaxIntegerSamples
#  pragma push_macro("MaxIntegerSamples")
#  undef MaxIntegerSamples
	.value("MaxIntegerSamples", oglplus::LimitQuery::MaxIntegerSamples)
#  pragma pop_macro("MaxIntegerSamples")
# else
	.value("MaxIntegerSamples", oglplus::LimitQuery::MaxIntegerSamples)
# endif
#endif
#if defined GL_MAX_PATCH_VERTICES
# if defined MaxPatchVertices
#  pragma push_macro("MaxPatchVertices")
#  undef MaxPatchVertices
	.value("MaxPatchVertices", oglplus::LimitQuery::MaxPatchVertices)
#  pragma pop_macro("MaxPatchVertices")
# else
	.value("MaxPatchVertices", oglplus::LimitQuery::MaxPatchVertices)
# endif
#endif
#if defined GL_MAX_PROGRAM_TEXEL_OFFSET
# if defined MaxProgramTexelOffset
#  pragma push_macro("MaxProgramTexelOffset")
#  undef MaxProgramTexelOffset
	.value("MaxProgramTexelOffset", oglplus::LimitQuery::MaxProgramTexelOffset)
#  pragma pop_macro("MaxProgramTexelOffset")
# else
	.value("MaxProgramTexelOffset", oglplus::LimitQuery::MaxProgramTexelOffset)
# endif
#endif
#if defined GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET
# if defined MaxProgramTextureGatherOffset
#  pragma push_macro("MaxProgramTextureGatherOffset")
#  undef MaxProgramTextureGatherOffset
	.value("MaxProgramTextureGatherOffset", oglplus::LimitQuery::MaxProgramTextureGatherOffset)
#  pragma pop_macro("MaxProgramTextureGatherOffset")
# else
	.value("MaxProgramTextureGatherOffset", oglplus::LimitQuery::MaxProgramTextureGatherOffset)
# endif
#endif
#if defined GL_MAX_RECTANGLE_TEXTURE_SIZE
# if defined MaxRectangleTextureSize
#  pragma push_macro("MaxRectangleTextureSize")
#  undef MaxRectangleTextureSize
	.value("MaxRectangleTextureSize", oglplus::LimitQuery::MaxRectangleTextureSize)
#  pragma pop_macro("MaxRectangleTextureSize")
# else
	.value("MaxRectangleTextureSize", oglplus::LimitQuery::MaxRectangleTextureSize)
# endif
#endif
#if defined GL_MAX_RENDERBUFFER_SIZE
# if defined MaxRenderbufferSize
#  pragma push_macro("MaxRenderbufferSize")
#  undef MaxRenderbufferSize
	.value("MaxRenderbufferSize", oglplus::LimitQuery::MaxRenderbufferSize)
#  pragma pop_macro("MaxRenderbufferSize")
# else
	.value("MaxRenderbufferSize", oglplus::LimitQuery::MaxRenderbufferSize)
# endif
#endif
#if defined GL_MAX_SAMPLE_MASK_WORDS
# if defined MaxSampleMaskWords
#  pragma push_macro("MaxSampleMaskWords")
#  undef MaxSampleMaskWords
	.value("MaxSampleMaskWords", oglplus::LimitQuery::MaxSampleMaskWords)
#  pragma pop_macro("MaxSampleMaskWords")
# else
	.value("MaxSampleMaskWords", oglplus::LimitQuery::MaxSampleMaskWords)
# endif
#endif
#if defined GL_MAX_SAMPLES
# if defined MaxSamples
#  pragma push_macro("MaxSamples")
#  undef MaxSamples
	.value("MaxSamples", oglplus::LimitQuery::MaxSamples)
#  pragma pop_macro("MaxSamples")
# else
	.value("MaxSamples", oglplus::LimitQuery::MaxSamples)
# endif
#endif
#if defined GL_MAX_SERVER_WAIT_TIMEOUT
# if defined MaxServerWaitTimeout
#  pragma push_macro("MaxServerWaitTimeout")
#  undef MaxServerWaitTimeout
	.value("MaxServerWaitTimeout", oglplus::LimitQuery::MaxServerWaitTimeout)
#  pragma pop_macro("MaxServerWaitTimeout")
# else
	.value("MaxServerWaitTimeout", oglplus::LimitQuery::MaxServerWaitTimeout)
# endif
#endif
#if defined GL_MAX_SUBROUTINES
# if defined MaxSubroutines
#  pragma push_macro("MaxSubroutines")
#  undef MaxSubroutines
	.value("MaxSubroutines", oglplus::LimitQuery::MaxSubroutines)
#  pragma pop_macro("MaxSubroutines")
# else
	.value("MaxSubroutines", oglplus::LimitQuery::MaxSubroutines)
# endif
#endif
#if defined GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS
# if defined MaxSubroutineUniformLocations
#  pragma push_macro("MaxSubroutineUniformLocations")
#  undef MaxSubroutineUniformLocations
	.value("MaxSubroutineUniformLocations", oglplus::LimitQuery::MaxSubroutineUniformLocations)
#  pragma pop_macro("MaxSubroutineUniformLocations")
# else
	.value("MaxSubroutineUniformLocations", oglplus::LimitQuery::MaxSubroutineUniformLocations)
# endif
#endif
#if defined GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS
# if defined MaxTessControlAtomicCounterBuffers
#  pragma push_macro("MaxTessControlAtomicCounterBuffers")
#  undef MaxTessControlAtomicCounterBuffers
	.value("MaxTessControlAtomicCounterBuffers", oglplus::LimitQuery::MaxTessControlAtomicCounterBuffers)
#  pragma pop_macro("MaxTessControlAtomicCounterBuffers")
# else
	.value("MaxTessControlAtomicCounterBuffers", oglplus::LimitQuery::MaxTessControlAtomicCounterBuffers)
# endif
#endif
#if defined GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS
# if defined MaxTessControlAtomicCounters
#  pragma push_macro("MaxTessControlAtomicCounters")
#  undef MaxTessControlAtomicCounters
	.value("MaxTessControlAtomicCounters", oglplus::LimitQuery::MaxTessControlAtomicCounters)
#  pragma pop_macro("MaxTessControlAtomicCounters")
# else
	.value("MaxTessControlAtomicCounters", oglplus::LimitQuery::MaxTessControlAtomicCounters)
# endif
#endif
#if defined GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS
# if defined MaxTessControlImageUniforms
#  pragma push_macro("MaxTessControlImageUniforms")
#  undef MaxTessControlImageUniforms
	.value("MaxTessControlImageUniforms", oglplus::LimitQuery::MaxTessControlImageUniforms)
#  pragma pop_macro("MaxTessControlImageUniforms")
# else
	.value("MaxTessControlImageUniforms", oglplus::LimitQuery::MaxTessControlImageUniforms)
# endif
#endif
#if defined GL_MAX_TESS_CONTROL_INPUT_COMPONENTS
# if defined MaxTessControlInputComponents
#  pragma push_macro("MaxTessControlInputComponents")
#  undef MaxTessControlInputComponents
	.value("MaxTessControlInputComponents", oglplus::LimitQuery::MaxTessControlInputComponents)
#  pragma pop_macro("MaxTessControlInputComponents")
# else
	.value("MaxTessControlInputComponents", oglplus::LimitQuery::MaxTessControlInputComponents)
# endif
#endif
#if defined GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS
# if defined MaxTessControlOutputComponents
#  pragma push_macro("MaxTessControlOutputComponents")
#  undef MaxTessControlOutputComponents
	.value("MaxTessControlOutputComponents", oglplus::LimitQuery::MaxTessControlOutputComponents)
#  pragma pop_macro("MaxTessControlOutputComponents")
# else
	.value("MaxTessControlOutputComponents", oglplus::LimitQuery::MaxTessControlOutputComponents)
# endif
#endif
#if defined GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS
# if defined MaxTessControlTextureImageUnits
#  pragma push_macro("MaxTessControlTextureImageUnits")
#  undef MaxTessControlTextureImageUnits
	.value("MaxTessControlTextureImageUnits", oglplus::LimitQuery::MaxTessControlTextureImageUnits)
#  pragma pop_macro("MaxTessControlTextureImageUnits")
# else
	.value("MaxTessControlTextureImageUnits", oglplus::LimitQuery::MaxTessControlTextureImageUnits)
# endif
#endif
#if defined GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS
# if defined MaxTessControlTotalOutputComponents
#  pragma push_macro("MaxTessControlTotalOutputComponents")
#  undef MaxTessControlTotalOutputComponents
	.value("MaxTessControlTotalOutputComponents", oglplus::LimitQuery::MaxTessControlTotalOutputComponents)
#  pragma pop_macro("MaxTessControlTotalOutputComponents")
# else
	.value("MaxTessControlTotalOutputComponents", oglplus::LimitQuery::MaxTessControlTotalOutputComponents)
# endif
#endif
#if defined GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS
# if defined MaxTessControlUniformBlocks
#  pragma push_macro("MaxTessControlUniformBlocks")
#  undef MaxTessControlUniformBlocks
	.value("MaxTessControlUniformBlocks", oglplus::LimitQuery::MaxTessControlUniformBlocks)
#  pragma pop_macro("MaxTessControlUniformBlocks")
# else
	.value("MaxTessControlUniformBlocks", oglplus::LimitQuery::MaxTessControlUniformBlocks)
# endif
#endif
#if defined GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS
# if defined MaxTessControlUniformComponents
#  pragma push_macro("MaxTessControlUniformComponents")
#  undef MaxTessControlUniformComponents
	.value("MaxTessControlUniformComponents", oglplus::LimitQuery::MaxTessControlUniformComponents)
#  pragma pop_macro("MaxTessControlUniformComponents")
# else
	.value("MaxTessControlUniformComponents", oglplus::LimitQuery::MaxTessControlUniformComponents)
# endif
#endif
#if defined GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS
# if defined MaxTessEvaluationAtomicCounterBuffers
#  pragma push_macro("MaxTessEvaluationAtomicCounterBuffers")
#  undef MaxTessEvaluationAtomicCounterBuffers
	.value("MaxTessEvaluationAtomicCounterBuffers", oglplus::LimitQuery::MaxTessEvaluationAtomicCounterBuffers)
#  pragma pop_macro("MaxTessEvaluationAtomicCounterBuffers")
# else
	.value("MaxTessEvaluationAtomicCounterBuffers", oglplus::LimitQuery::MaxTessEvaluationAtomicCounterBuffers)
# endif
#endif
#if defined GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS
# if defined MaxTessEvaluationAtomicCounters
#  pragma push_macro("MaxTessEvaluationAtomicCounters")
#  undef MaxTessEvaluationAtomicCounters
	.value("MaxTessEvaluationAtomicCounters", oglplus::LimitQuery::MaxTessEvaluationAtomicCounters)
#  pragma pop_macro("MaxTessEvaluationAtomicCounters")
# else
	.value("MaxTessEvaluationAtomicCounters", oglplus::LimitQuery::MaxTessEvaluationAtomicCounters)
# endif
#endif
#if defined GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS
# if defined MaxTessEvaluationImageUniforms
#  pragma push_macro("MaxTessEvaluationImageUniforms")
#  undef MaxTessEvaluationImageUniforms
	.value("MaxTessEvaluationImageUniforms", oglplus::LimitQuery::MaxTessEvaluationImageUniforms)
#  pragma pop_macro("MaxTessEvaluationImageUniforms")
# else
	.value("MaxTessEvaluationImageUniforms", oglplus::LimitQuery::MaxTessEvaluationImageUniforms)
# endif
#endif
#if defined GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS
# if defined MaxTessEvaluationInputComponents
#  pragma push_macro("MaxTessEvaluationInputComponents")
#  undef MaxTessEvaluationInputComponents
	.value("MaxTessEvaluationInputComponents", oglplus::LimitQuery::MaxTessEvaluationInputComponents)
#  pragma pop_macro("MaxTessEvaluationInputComponents")
# else
	.value("MaxTessEvaluationInputComponents", oglplus::LimitQuery::MaxTessEvaluationInputComponents)
# endif
#endif
#if defined GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS
# if defined MaxTessEvaluationOutputComponents
#  pragma push_macro("MaxTessEvaluationOutputComponents")
#  undef MaxTessEvaluationOutputComponents
	.value("MaxTessEvaluationOutputComponents", oglplus::LimitQuery::MaxTessEvaluationOutputComponents)
#  pragma pop_macro("MaxTessEvaluationOutputComponents")
# else
	.value("MaxTessEvaluationOutputComponents", oglplus::LimitQuery::MaxTessEvaluationOutputComponents)
# endif
#endif
#if defined GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS
# if defined MaxTessEvaluationTextureImageUnits
#  pragma push_macro("MaxTessEvaluationTextureImageUnits")
#  undef MaxTessEvaluationTextureImageUnits
	.value("MaxTessEvaluationTextureImageUnits", oglplus::LimitQuery::MaxTessEvaluationTextureImageUnits)
#  pragma pop_macro("MaxTessEvaluationTextureImageUnits")
# else
	.value("MaxTessEvaluationTextureImageUnits", oglplus::LimitQuery::MaxTessEvaluationTextureImageUnits)
# endif
#endif
#if defined GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS
# if defined MaxTessEvaluationUniformBlocks
#  pragma push_macro("MaxTessEvaluationUniformBlocks")
#  undef MaxTessEvaluationUniformBlocks
	.value("MaxTessEvaluationUniformBlocks", oglplus::LimitQuery::MaxTessEvaluationUniformBlocks)
#  pragma pop_macro("MaxTessEvaluationUniformBlocks")
# else
	.value("MaxTessEvaluationUniformBlocks", oglplus::LimitQuery::MaxTessEvaluationUniformBlocks)
# endif
#endif
#if defined GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS
# if defined MaxTessEvaluationUniformComponents
#  pragma push_macro("MaxTessEvaluationUniformComponents")
#  undef MaxTessEvaluationUniformComponents
	.value("MaxTessEvaluationUniformComponents", oglplus::LimitQuery::MaxTessEvaluationUniformComponents)
#  pragma pop_macro("MaxTessEvaluationUniformComponents")
# else
	.value("MaxTessEvaluationUniformComponents", oglplus::LimitQuery::MaxTessEvaluationUniformComponents)
# endif
#endif
#if defined GL_MAX_TESS_GEN_LEVEL
# if defined MaxTessGenLevel
#  pragma push_macro("MaxTessGenLevel")
#  undef MaxTessGenLevel
	.value("MaxTessGenLevel", oglplus::LimitQuery::MaxTessGenLevel)
#  pragma pop_macro("MaxTessGenLevel")
# else
	.value("MaxTessGenLevel", oglplus::LimitQuery::MaxTessGenLevel)
# endif
#endif
#if defined GL_MAX_TESS_PATCH_COMPONENTS
# if defined MaxTessPatchComponents
#  pragma push_macro("MaxTessPatchComponents")
#  undef MaxTessPatchComponents
	.value("MaxTessPatchComponents", oglplus::LimitQuery::MaxTessPatchComponents)
#  pragma pop_macro("MaxTessPatchComponents")
# else
	.value("MaxTessPatchComponents", oglplus::LimitQuery::MaxTessPatchComponents)
# endif
#endif
#if defined GL_MAX_TEXTURE_BUFFER_SIZE
# if defined MaxTextureBufferSize
#  pragma push_macro("MaxTextureBufferSize")
#  undef MaxTextureBufferSize
	.value("MaxTextureBufferSize", oglplus::LimitQuery::MaxTextureBufferSize)
#  pragma pop_macro("MaxTextureBufferSize")
# else
	.value("MaxTextureBufferSize", oglplus::LimitQuery::MaxTextureBufferSize)
# endif
#endif
#if defined GL_MAX_TEXTURE_IMAGE_UNITS
# if defined MaxTextureImageUnits
#  pragma push_macro("MaxTextureImageUnits")
#  undef MaxTextureImageUnits
	.value("MaxTextureImageUnits", oglplus::LimitQuery::MaxTextureImageUnits)
#  pragma pop_macro("MaxTextureImageUnits")
# else
	.value("MaxTextureImageUnits", oglplus::LimitQuery::MaxTextureImageUnits)
# endif
#endif
#if defined GL_MAX_TEXTURE_LOD_BIAS
# if defined MaxTextureLodBias
#  pragma push_macro("MaxTextureLodBias")
#  undef MaxTextureLodBias
	.value("MaxTextureLodBias", oglplus::LimitQuery::MaxTextureLodBias)
#  pragma pop_macro("MaxTextureLodBias")
# else
	.value("MaxTextureLodBias", oglplus::LimitQuery::MaxTextureLodBias)
# endif
#endif
#if defined GL_MAX_TEXTURE_SIZE
# if defined MaxTextureSize
#  pragma push_macro("MaxTextureSize")
#  undef MaxTextureSize
	.value("MaxTextureSize", oglplus::LimitQuery::MaxTextureSize)
#  pragma pop_macro("MaxTextureSize")
# else
	.value("MaxTextureSize", oglplus::LimitQuery::MaxTextureSize)
# endif
#endif
#if defined GL_MAX_TRANSFORM_FEEDBACK_BUFFERS
# if defined MaxTransformFeedbackBuffers
#  pragma push_macro("MaxTransformFeedbackBuffers")
#  undef MaxTransformFeedbackBuffers
	.value("MaxTransformFeedbackBuffers", oglplus::LimitQuery::MaxTransformFeedbackBuffers)
#  pragma pop_macro("MaxTransformFeedbackBuffers")
# else
	.value("MaxTransformFeedbackBuffers", oglplus::LimitQuery::MaxTransformFeedbackBuffers)
# endif
#endif
#if defined GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS
# if defined MaxTransformFeedbackInterleavedComponents
#  pragma push_macro("MaxTransformFeedbackInterleavedComponents")
#  undef MaxTransformFeedbackInterleavedComponents
	.value("MaxTransformFeedbackInterleavedComponents", oglplus::LimitQuery::MaxTransformFeedbackInterleavedComponents)
#  pragma pop_macro("MaxTransformFeedbackInterleavedComponents")
# else
	.value("MaxTransformFeedbackInterleavedComponents", oglplus::LimitQuery::MaxTransformFeedbackInterleavedComponents)
# endif
#endif
#if defined GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS
# if defined MaxTransformFeedbackSeparateAttribs
#  pragma push_macro("MaxTransformFeedbackSeparateAttribs")
#  undef MaxTransformFeedbackSeparateAttribs
	.value("MaxTransformFeedbackSeparateAttribs", oglplus::LimitQuery::MaxTransformFeedbackSeparateAttribs)
#  pragma pop_macro("MaxTransformFeedbackSeparateAttribs")
# else
	.value("MaxTransformFeedbackSeparateAttribs", oglplus::LimitQuery::MaxTransformFeedbackSeparateAttribs)
# endif
#endif
#if defined GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS
# if defined MaxTransformFeedbackSeparateComponents
#  pragma push_macro("MaxTransformFeedbackSeparateComponents")
#  undef MaxTransformFeedbackSeparateComponents
	.value("MaxTransformFeedbackSeparateComponents", oglplus::LimitQuery::MaxTransformFeedbackSeparateComponents)
#  pragma pop_macro("MaxTransformFeedbackSeparateComponents")
# else
	.value("MaxTransformFeedbackSeparateComponents", oglplus::LimitQuery::MaxTransformFeedbackSeparateComponents)
# endif
#endif
#if defined GL_MAX_UNIFORM_BLOCK_SIZE
# if defined MaxUniformBlockSize
#  pragma push_macro("MaxUniformBlockSize")
#  undef MaxUniformBlockSize
	.value("MaxUniformBlockSize", oglplus::LimitQuery::MaxUniformBlockSize)
#  pragma pop_macro("MaxUniformBlockSize")
# else
	.value("MaxUniformBlockSize", oglplus::LimitQuery::MaxUniformBlockSize)
# endif
#endif
#if defined GL_MAX_UNIFORM_BUFFER_BINDINGS
# if defined MaxUniformBufferBindings
#  pragma push_macro("MaxUniformBufferBindings")
#  undef MaxUniformBufferBindings
	.value("MaxUniformBufferBindings", oglplus::LimitQuery::MaxUniformBufferBindings)
#  pragma pop_macro("MaxUniformBufferBindings")
# else
	.value("MaxUniformBufferBindings", oglplus::LimitQuery::MaxUniformBufferBindings)
# endif
#endif
#if defined GL_MAX_VARYING_COMPONENTS
# if defined MaxVaryingComponents
#  pragma push_macro("MaxVaryingComponents")
#  undef MaxVaryingComponents
	.value("MaxVaryingComponents", oglplus::LimitQuery::MaxVaryingComponents)
#  pragma pop_macro("MaxVaryingComponents")
# else
	.value("MaxVaryingComponents", oglplus::LimitQuery::MaxVaryingComponents)
# endif
#endif
#if defined GL_MAX_VARYING_VECTORS
# if defined MaxVaryingVectors
#  pragma push_macro("MaxVaryingVectors")
#  undef MaxVaryingVectors
	.value("MaxVaryingVectors", oglplus::LimitQuery::MaxVaryingVectors)
#  pragma pop_macro("MaxVaryingVectors")
# else
	.value("MaxVaryingVectors", oglplus::LimitQuery::MaxVaryingVectors)
# endif
#endif
#if defined GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS
# if defined MaxVertexAtomicCounterBuffers
#  pragma push_macro("MaxVertexAtomicCounterBuffers")
#  undef MaxVertexAtomicCounterBuffers
	.value("MaxVertexAtomicCounterBuffers", oglplus::LimitQuery::MaxVertexAtomicCounterBuffers)
#  pragma pop_macro("MaxVertexAtomicCounterBuffers")
# else
	.value("MaxVertexAtomicCounterBuffers", oglplus::LimitQuery::MaxVertexAtomicCounterBuffers)
# endif
#endif
#if defined GL_MAX_VERTEX_ATOMIC_COUNTERS
# if defined MaxVertexAtomicCounters
#  pragma push_macro("MaxVertexAtomicCounters")
#  undef MaxVertexAtomicCounters
	.value("MaxVertexAtomicCounters", oglplus::LimitQuery::MaxVertexAtomicCounters)
#  pragma pop_macro("MaxVertexAtomicCounters")
# else
	.value("MaxVertexAtomicCounters", oglplus::LimitQuery::MaxVertexAtomicCounters)
# endif
#endif
#if defined GL_MAX_VERTEX_ATTRIBS
# if defined MaxVertexAttribs
#  pragma push_macro("MaxVertexAttribs")
#  undef MaxVertexAttribs
	.value("MaxVertexAttribs", oglplus::LimitQuery::MaxVertexAttribs)
#  pragma pop_macro("MaxVertexAttribs")
# else
	.value("MaxVertexAttribs", oglplus::LimitQuery::MaxVertexAttribs)
# endif
#endif
#if defined GL_MAX_VERTEX_IMAGE_UNIFORMS
# if defined MaxVertexImageUniforms
#  pragma push_macro("MaxVertexImageUniforms")
#  undef MaxVertexImageUniforms
	.value("MaxVertexImageUniforms", oglplus::LimitQuery::MaxVertexImageUniforms)
#  pragma pop_macro("MaxVertexImageUniforms")
# else
	.value("MaxVertexImageUniforms", oglplus::LimitQuery::MaxVertexImageUniforms)
# endif
#endif
#if defined GL_MAX_VERTEX_OUTPUT_COMPONENTS
# if defined MaxVertexOutputComponents
#  pragma push_macro("MaxVertexOutputComponents")
#  undef MaxVertexOutputComponents
	.value("MaxVertexOutputComponents", oglplus::LimitQuery::MaxVertexOutputComponents)
#  pragma pop_macro("MaxVertexOutputComponents")
# else
	.value("MaxVertexOutputComponents", oglplus::LimitQuery::MaxVertexOutputComponents)
# endif
#endif
#if defined GL_MAX_VERTEX_STREAMS
# if defined MaxVertexStreams
#  pragma push_macro("MaxVertexStreams")
#  undef MaxVertexStreams
	.value("MaxVertexStreams", oglplus::LimitQuery::MaxVertexStreams)
#  pragma pop_macro("MaxVertexStreams")
# else
	.value("MaxVertexStreams", oglplus::LimitQuery::MaxVertexStreams)
# endif
#endif
#if defined GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
# if defined MaxVertexTextureImageUnits
#  pragma push_macro("MaxVertexTextureImageUnits")
#  undef MaxVertexTextureImageUnits
	.value("MaxVertexTextureImageUnits", oglplus::LimitQuery::MaxVertexTextureImageUnits)
#  pragma pop_macro("MaxVertexTextureImageUnits")
# else
	.value("MaxVertexTextureImageUnits", oglplus::LimitQuery::MaxVertexTextureImageUnits)
# endif
#endif
#if defined GL_MAX_VERTEX_UNIFORM_BLOCKS
# if defined MaxVertexUniformBlocks
#  pragma push_macro("MaxVertexUniformBlocks")
#  undef MaxVertexUniformBlocks
	.value("MaxVertexUniformBlocks", oglplus::LimitQuery::MaxVertexUniformBlocks)
#  pragma pop_macro("MaxVertexUniformBlocks")
# else
	.value("MaxVertexUniformBlocks", oglplus::LimitQuery::MaxVertexUniformBlocks)
# endif
#endif
#if defined GL_MAX_VERTEX_UNIFORM_COMPONENTS
# if defined MaxVertexUniformComponents
#  pragma push_macro("MaxVertexUniformComponents")
#  undef MaxVertexUniformComponents
	.value("MaxVertexUniformComponents", oglplus::LimitQuery::MaxVertexUniformComponents)
#  pragma pop_macro("MaxVertexUniformComponents")
# else
	.value("MaxVertexUniformComponents", oglplus::LimitQuery::MaxVertexUniformComponents)
# endif
#endif
#if defined GL_MAX_VERTEX_UNIFORM_VECTORS
# if defined MaxVertexUniformVectors
#  pragma push_macro("MaxVertexUniformVectors")
#  undef MaxVertexUniformVectors
	.value("MaxVertexUniformVectors", oglplus::LimitQuery::MaxVertexUniformVectors)
#  pragma pop_macro("MaxVertexUniformVectors")
# else
	.value("MaxVertexUniformVectors", oglplus::LimitQuery::MaxVertexUniformVectors)
# endif
#endif
#if defined GL_MAX_VIEWPORT_DIMS
# if defined MaxViewportDims
#  pragma push_macro("MaxViewportDims")
#  undef MaxViewportDims
	.value("MaxViewportDims", oglplus::LimitQuery::MaxViewportDims)
#  pragma pop_macro("MaxViewportDims")
# else
	.value("MaxViewportDims", oglplus::LimitQuery::MaxViewportDims)
# endif
#endif
#if defined GL_MAX_VIEWPORTS
# if defined MaxViewports
#  pragma push_macro("MaxViewports")
#  undef MaxViewports
	.value("MaxViewports", oglplus::LimitQuery::MaxViewports)
#  pragma pop_macro("MaxViewports")
# else
	.value("MaxViewports", oglplus::LimitQuery::MaxViewports)
# endif
#endif
#if defined GL_MAX_COMPUTE_WORK_GROUP_COUNT
# if defined MaxComputeWorkGroupCount
#  pragma push_macro("MaxComputeWorkGroupCount")
#  undef MaxComputeWorkGroupCount
	.value("MaxComputeWorkGroupCount", oglplus::LimitQuery::MaxComputeWorkGroupCount)
#  pragma pop_macro("MaxComputeWorkGroupCount")
# else
	.value("MaxComputeWorkGroupCount", oglplus::LimitQuery::MaxComputeWorkGroupCount)
# endif
#endif
#if defined GL_MAX_COMPUTE_WORK_GROUP_SIZE
# if defined MaxComputeWorkGroupSize
#  pragma push_macro("MaxComputeWorkGroupSize")
#  undef MaxComputeWorkGroupSize
	.value("MaxComputeWorkGroupSize", oglplus::LimitQuery::MaxComputeWorkGroupSize)
#  pragma pop_macro("MaxComputeWorkGroupSize")
# else
	.value("MaxComputeWorkGroupSize", oglplus::LimitQuery::MaxComputeWorkGroupSize)
# endif
#endif
#if defined GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS
# if defined MaxComputeWorkGroupInvocations
#  pragma push_macro("MaxComputeWorkGroupInvocations")
#  undef MaxComputeWorkGroupInvocations
	.value("MaxComputeWorkGroupInvocations", oglplus::LimitQuery::MaxComputeWorkGroupInvocations)
#  pragma pop_macro("MaxComputeWorkGroupInvocations")
# else
	.value("MaxComputeWorkGroupInvocations", oglplus::LimitQuery::MaxComputeWorkGroupInvocations)
# endif
#endif
#if defined GL_MAX_COMPUTE_SHARED_MEMORY_SIZE
# if defined MaxComputeSharedMemorySize
#  pragma push_macro("MaxComputeSharedMemorySize")
#  undef MaxComputeSharedMemorySize
	.value("MaxComputeSharedMemorySize", oglplus::LimitQuery::MaxComputeSharedMemorySize)
#  pragma pop_macro("MaxComputeSharedMemorySize")
# else
	.value("MaxComputeSharedMemorySize", oglplus::LimitQuery::MaxComputeSharedMemorySize)
# endif
#endif
#if defined GL_MIN_FRAGMENT_INTERPOLATION_OFFSET
# if defined MinFragmentInterpolationOffset
#  pragma push_macro("MinFragmentInterpolationOffset")
#  undef MinFragmentInterpolationOffset
	.value("MinFragmentInterpolationOffset", oglplus::LimitQuery::MinFragmentInterpolationOffset)
#  pragma pop_macro("MinFragmentInterpolationOffset")
# else
	.value("MinFragmentInterpolationOffset", oglplus::LimitQuery::MinFragmentInterpolationOffset)
# endif
#endif
#if defined GL_MIN_MAP_BUFFER_ALIGNMENT
# if defined MinMapBufferAlignment
#  pragma push_macro("MinMapBufferAlignment")
#  undef MinMapBufferAlignment
	.value("MinMapBufferAlignment", oglplus::LimitQuery::MinMapBufferAlignment)
#  pragma pop_macro("MinMapBufferAlignment")
# else
	.value("MinMapBufferAlignment", oglplus::LimitQuery::MinMapBufferAlignment)
# endif
#endif
#if defined GL_MIN_PROGRAM_TEXEL_OFFSET
# if defined MinProgramTexelOffset
#  pragma push_macro("MinProgramTexelOffset")
#  undef MinProgramTexelOffset
	.value("MinProgramTexelOffset", oglplus::LimitQuery::MinProgramTexelOffset)
#  pragma pop_macro("MinProgramTexelOffset")
# else
	.value("MinProgramTexelOffset", oglplus::LimitQuery::MinProgramTexelOffset)
# endif
#endif
#if defined GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET
# if defined MinProgramTextureGatherOffset
#  pragma push_macro("MinProgramTextureGatherOffset")
#  undef MinProgramTextureGatherOffset
	.value("MinProgramTextureGatherOffset", oglplus::LimitQuery::MinProgramTextureGatherOffset)
#  pragma pop_macro("MinProgramTextureGatherOffset")
# else
	.value("MinProgramTextureGatherOffset", oglplus::LimitQuery::MinProgramTextureGatherOffset)
# endif
#endif
#if defined GL_MIN_SAMPLE_SHADING_VALUE
# if defined MinSampleShadingValue
#  pragma push_macro("MinSampleShadingValue")
#  undef MinSampleShadingValue
	.value("MinSampleShadingValue", oglplus::LimitQuery::MinSampleShadingValue)
#  pragma pop_macro("MinSampleShadingValue")
# else
	.value("MinSampleShadingValue", oglplus::LimitQuery::MinSampleShadingValue)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::LimitQuery) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
