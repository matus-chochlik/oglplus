//  File doc/quickbook/oglplus/quickref/enums/program_parameter.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/program_parameter.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2019 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_program_parameter

enum class ProgramParameter : GLenum
{
	DeleteStatus                      = GL_DELETE_STATUS,
	LinkStatus                        = GL_LINK_STATUS,
	ValidateStatus                    = GL_VALIDATE_STATUS,
	InfoLogLength                     = GL_INFO_LOG_LENGTH,
	AttachedShaders                   = GL_ATTACHED_SHADERS,
	ActiveAtomicCounterBuffers        = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
	ActiveAttributes                  = GL_ACTIVE_ATTRIBUTES,
	ActiveAttributeMaxLength          = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
	ActiveUniforms                    = GL_ACTIVE_UNIFORMS,
	ActiveUniformMaxLength            = GL_ACTIVE_UNIFORM_MAX_LENGTH,
	ProgramBinaryLength               = GL_PROGRAM_BINARY_LENGTH,
	ComputeWorkGroupSize              = GL_COMPUTE_WORK_GROUP_SIZE,
	TransformFeedbackBufferMode       = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
	TransformFeedbackVaryings         = GL_TRANSFORM_FEEDBACK_VARYINGS,
	TransformFeedbackVaryingMaxLength = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
	GeometryVerticesOut               = GL_GEOMETRY_VERTICES_OUT,
	GeometryInputType                 = GL_GEOMETRY_INPUT_TYPE,
	GeometryOutputType                = GL_GEOMETRY_OUTPUT_TYPE
};

template <>
__Range<ProgramParameter> __EnumValueRange<ProgramParameter>();

__StrCRef __EnumValueName(ProgramParameter);

//]
