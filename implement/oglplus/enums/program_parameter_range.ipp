//  File implement/oglplus/enums/program_parameter_range.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/program_parameter.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2017 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	ProgramParameter
> ValueRange_(ProgramParameter*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_PROGRAMPARAMETER)
#define OGLPLUS_IMPL_EVR_PROGRAMPARAMETER
{
static const GLenum _values[] = {
#if defined GL_DELETE_STATUS
GL_DELETE_STATUS,
#endif
#if defined GL_LINK_STATUS
GL_LINK_STATUS,
#endif
#if defined GL_VALIDATE_STATUS
GL_VALIDATE_STATUS,
#endif
#if defined GL_INFO_LOG_LENGTH
GL_INFO_LOG_LENGTH,
#endif
#if defined GL_ATTACHED_SHADERS
GL_ATTACHED_SHADERS,
#endif
#if defined GL_ACTIVE_ATOMIC_COUNTER_BUFFERS
GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
#endif
#if defined GL_ACTIVE_ATTRIBUTES
GL_ACTIVE_ATTRIBUTES,
#endif
#if defined GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
#endif
#if defined GL_ACTIVE_UNIFORMS
GL_ACTIVE_UNIFORMS,
#endif
#if defined GL_ACTIVE_UNIFORM_MAX_LENGTH
GL_ACTIVE_UNIFORM_MAX_LENGTH,
#endif
#if defined GL_PROGRAM_BINARY_LENGTH
GL_PROGRAM_BINARY_LENGTH,
#endif
#if defined GL_COMPUTE_WORK_GROUP_SIZE
GL_COMPUTE_WORK_GROUP_SIZE,
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER_MODE
GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
#endif
#if defined GL_TRANSFORM_FEEDBACK_VARYINGS
GL_TRANSFORM_FEEDBACK_VARYINGS,
#endif
#if defined GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH
GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
#endif
#if defined GL_GEOMETRY_VERTICES_OUT
GL_GEOMETRY_VERTICES_OUT,
#endif
#if defined GL_GEOMETRY_INPUT_TYPE
GL_GEOMETRY_INPUT_TYPE,
#endif
#if defined GL_GEOMETRY_OUTPUT_TYPE
GL_GEOMETRY_OUTPUT_TYPE,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	ProgramParameter
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

