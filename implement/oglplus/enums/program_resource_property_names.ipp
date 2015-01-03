//  File implement/oglplus/enums/program_resource_property_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/program_resource_property.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	ProgramResourceProperty*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PROGRAMRESOURCEPROPERTY)
#define OGLPLUS_IMPL_EVN_PROGRAMRESOURCEPROPERTY
{
switch(value)
{
#if defined GL_ARRAY_SIZE
	case GL_ARRAY_SIZE: return CStrRef("ARRAY_SIZE");
#endif
#if defined GL_OFFSET
	case GL_OFFSET: return CStrRef("OFFSET");
#endif
#if defined GL_BLOCK_INDEX
	case GL_BLOCK_INDEX: return CStrRef("BLOCK_INDEX");
#endif
#if defined GL_ARRAY_STRIDE
	case GL_ARRAY_STRIDE: return CStrRef("ARRAY_STRIDE");
#endif
#if defined GL_MATRIX_STRIDE
	case GL_MATRIX_STRIDE: return CStrRef("MATRIX_STRIDE");
#endif
#if defined GL_IS_ROW_MAJOR
	case GL_IS_ROW_MAJOR: return CStrRef("IS_ROW_MAJOR");
#endif
#if defined GL_ATOMIC_COUNTER_BUFFER_INDEX
	case GL_ATOMIC_COUNTER_BUFFER_INDEX: return CStrRef("ATOMIC_COUNTER_BUFFER_INDEX");
#endif
#if defined GL_BUFFER_BINDING
	case GL_BUFFER_BINDING: return CStrRef("BUFFER_BINDING");
#endif
#if defined GL_BUFFER_DATA_SIZE
	case GL_BUFFER_DATA_SIZE: return CStrRef("BUFFER_DATA_SIZE");
#endif
#if defined GL_NUM_ACTIVE_VARIABLES
	case GL_NUM_ACTIVE_VARIABLES: return CStrRef("NUM_ACTIVE_VARIABLES");
#endif
#if defined GL_ACTIVE_VARIABLES
	case GL_ACTIVE_VARIABLES: return CStrRef("ACTIVE_VARIABLES");
#endif
#if defined GL_REFERENCED_BY_VERTEX_SHADER
	case GL_REFERENCED_BY_VERTEX_SHADER: return CStrRef("REFERENCED_BY_VERTEX_SHADER");
#endif
#if defined GL_REFERENCED_BY_TESS_CONTROL_SHADER
	case GL_REFERENCED_BY_TESS_CONTROL_SHADER: return CStrRef("REFERENCED_BY_TESS_CONTROL_SHADER");
#endif
#if defined GL_REFERENCED_BY_TESS_EVALUATION_SHADER
	case GL_REFERENCED_BY_TESS_EVALUATION_SHADER: return CStrRef("REFERENCED_BY_TESS_EVALUATION_SHADER");
#endif
#if defined GL_REFERENCED_BY_GEOMETRY_SHADER
	case GL_REFERENCED_BY_GEOMETRY_SHADER: return CStrRef("REFERENCED_BY_GEOMETRY_SHADER");
#endif
#if defined GL_REFERENCED_BY_FRAGMENT_SHADER
	case GL_REFERENCED_BY_FRAGMENT_SHADER: return CStrRef("REFERENCED_BY_FRAGMENT_SHADER");
#endif
#if defined GL_REFERENCED_BY_COMPUTE_SHADER
	case GL_REFERENCED_BY_COMPUTE_SHADER: return CStrRef("REFERENCED_BY_COMPUTE_SHADER");
#endif
#if defined GL_NUM_COMPATIBLE_SUBROUTINES
	case GL_NUM_COMPATIBLE_SUBROUTINES: return CStrRef("NUM_COMPATIBLE_SUBROUTINES");
#endif
#if defined GL_COMPATIBLE_SUBROUTINES
	case GL_COMPATIBLE_SUBROUTINES: return CStrRef("COMPATIBLE_SUBROUTINES");
#endif
#if defined GL_TOP_LEVEL_ARRAY_SIZE
	case GL_TOP_LEVEL_ARRAY_SIZE: return CStrRef("TOP_LEVEL_ARRAY_SIZE");
#endif
#if defined GL_TOP_LEVEL_ARRAY_STRIDE
	case GL_TOP_LEVEL_ARRAY_STRIDE: return CStrRef("TOP_LEVEL_ARRAY_STRIDE");
#endif
#if defined GL_LOCATION
	case GL_LOCATION: return CStrRef("LOCATION");
#endif
#if defined GL_LOCATION_INDEX
	case GL_LOCATION_INDEX: return CStrRef("LOCATION_INDEX");
#endif
#if defined GL_LOCATION_COMPONENT
	case GL_LOCATION_COMPONENT: return CStrRef("LOCATION_COMPONENT");
#endif
#if defined GL_IS_PER_PATCH
	case GL_IS_PER_PATCH: return CStrRef("IS_PER_PATCH");
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER_INDEX
	case GL_TRANSFORM_FEEDBACK_BUFFER_INDEX: return CStrRef("TRANSFORM_FEEDBACK_BUFFER_INDEX");
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE
	case GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE: return CStrRef("TRANSFORM_FEEDBACK_BUFFER_STRIDE");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

