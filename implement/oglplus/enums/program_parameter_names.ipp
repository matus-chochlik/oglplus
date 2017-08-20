//  File implement/oglplus/enums/program_parameter_names.ipp
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
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	ProgramParameter*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PROGRAMPARAMETER)
#define OGLPLUS_IMPL_EVN_PROGRAMPARAMETER
{
switch(value)
{
#if defined GL_DELETE_STATUS
	case GL_DELETE_STATUS: return StrCRef("DELETE_STATUS");
#endif
#if defined GL_LINK_STATUS
	case GL_LINK_STATUS: return StrCRef("LINK_STATUS");
#endif
#if defined GL_VALIDATE_STATUS
	case GL_VALIDATE_STATUS: return StrCRef("VALIDATE_STATUS");
#endif
#if defined GL_INFO_LOG_LENGTH
	case GL_INFO_LOG_LENGTH: return StrCRef("INFO_LOG_LENGTH");
#endif
#if defined GL_ATTACHED_SHADERS
	case GL_ATTACHED_SHADERS: return StrCRef("ATTACHED_SHADERS");
#endif
#if defined GL_ACTIVE_ATOMIC_COUNTER_BUFFERS
	case GL_ACTIVE_ATOMIC_COUNTER_BUFFERS: return StrCRef("ACTIVE_ATOMIC_COUNTER_BUFFERS");
#endif
#if defined GL_ACTIVE_ATTRIBUTES
	case GL_ACTIVE_ATTRIBUTES: return StrCRef("ACTIVE_ATTRIBUTES");
#endif
#if defined GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
	case GL_ACTIVE_ATTRIBUTE_MAX_LENGTH: return StrCRef("ACTIVE_ATTRIBUTE_MAX_LENGTH");
#endif
#if defined GL_ACTIVE_UNIFORMS
	case GL_ACTIVE_UNIFORMS: return StrCRef("ACTIVE_UNIFORMS");
#endif
#if defined GL_ACTIVE_UNIFORM_MAX_LENGTH
	case GL_ACTIVE_UNIFORM_MAX_LENGTH: return StrCRef("ACTIVE_UNIFORM_MAX_LENGTH");
#endif
#if defined GL_PROGRAM_BINARY_LENGTH
	case GL_PROGRAM_BINARY_LENGTH: return StrCRef("PROGRAM_BINARY_LENGTH");
#endif
#if defined GL_COMPUTE_WORK_GROUP_SIZE
	case GL_COMPUTE_WORK_GROUP_SIZE: return StrCRef("COMPUTE_WORK_GROUP_SIZE");
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER_MODE
	case GL_TRANSFORM_FEEDBACK_BUFFER_MODE: return StrCRef("TRANSFORM_FEEDBACK_BUFFER_MODE");
#endif
#if defined GL_TRANSFORM_FEEDBACK_VARYINGS
	case GL_TRANSFORM_FEEDBACK_VARYINGS: return StrCRef("TRANSFORM_FEEDBACK_VARYINGS");
#endif
#if defined GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH
	case GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH: return StrCRef("TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH");
#endif
#if defined GL_GEOMETRY_VERTICES_OUT
	case GL_GEOMETRY_VERTICES_OUT: return StrCRef("GEOMETRY_VERTICES_OUT");
#endif
#if defined GL_GEOMETRY_INPUT_TYPE
	case GL_GEOMETRY_INPUT_TYPE: return StrCRef("GEOMETRY_INPUT_TYPE");
#endif
#if defined GL_GEOMETRY_OUTPUT_TYPE
	case GL_GEOMETRY_OUTPUT_TYPE: return StrCRef("GEOMETRY_OUTPUT_TYPE");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrCRef();
}
#else
;
#endif
} // namespace enums

