/**
 *  @file oglplus/program_pipeline_stage.hpp
 *  @brief ProgramPipelineStage enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROGRAM_PIPELINE_STAGE_1107121519_HPP
#define OGLPLUS_PROGRAM_PIPELINE_STAGE_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/bitfield.hpp>
#include <oglplus/enumerations.hpp>

namespace oglplus {

// if program-pipeline is available
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects

/// Program pipeline stage enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(ProgramPipelineStage, GLbitfield)
#include <oglplus/enums/program_pipeline_stage.ipp>
OGLPLUS_ENUM_CLASS_END(ProgramPipelineStage)

OGLPLUS_MAKE_BITFIELD(ProgramPipelineStage)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/program_pipeline_stage_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/program_pipeline_stage_range.ipp>
#endif

#endif // GL_VERSION_4_1

} // namespace oglplus

#endif // include guard
