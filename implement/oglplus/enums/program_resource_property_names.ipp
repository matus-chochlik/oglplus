/*
 *  .file oglplus/enums/program_resource_property_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/program_resource_property.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	ProgramResourceProperty*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PROGRAMRESOURCEPROPERTY)
#define OGLPLUS_IMPL_EVN_PROGRAMRESOURCEPROPERTY
{
switch(value)
{
#if defined GL_ARRAY_SIZE
	case GL_ARRAY_SIZE: return StrLit("ARRAY_SIZE");
#endif
#if defined GL_OFFSET
	case GL_OFFSET: return StrLit("OFFSET");
#endif
#if defined GL_BLOCK_INDEX
	case GL_BLOCK_INDEX: return StrLit("BLOCK_INDEX");
#endif
#if defined GL_ARRAY_STRIDE
	case GL_ARRAY_STRIDE: return StrLit("ARRAY_STRIDE");
#endif
#if defined GL_MATRIX_STRIDE
	case GL_MATRIX_STRIDE: return StrLit("MATRIX_STRIDE");
#endif
#if defined GL_IS_ROW_MAJOR
	case GL_IS_ROW_MAJOR: return StrLit("IS_ROW_MAJOR");
#endif
#if defined GL_ATOMIC_COUNTER_BUFFER_INDEX
	case GL_ATOMIC_COUNTER_BUFFER_INDEX: return StrLit("ATOMIC_COUNTER_BUFFER_INDEX");
#endif
#if defined GL_BUFFER_BINDING
	case GL_BUFFER_BINDING: return StrLit("BUFFER_BINDING");
#endif
#if defined GL_BUFFER_DATA_SIZE
	case GL_BUFFER_DATA_SIZE: return StrLit("BUFFER_DATA_SIZE");
#endif
#if defined GL_NUM_ACTIVE_VARIABLES
	case GL_NUM_ACTIVE_VARIABLES: return StrLit("NUM_ACTIVE_VARIABLES");
#endif
#if defined GL_ACTIVE_VARIABLES
	case GL_ACTIVE_VARIABLES: return StrLit("ACTIVE_VARIABLES");
#endif
#if defined GL_REFERENCED_BY_VERTEX_SHADER
	case GL_REFERENCED_BY_VERTEX_SHADER: return StrLit("REFERENCED_BY_VERTEX_SHADER");
#endif
#if defined GL_REFERENCED_BY_TESS_CONTROL_SHADER
	case GL_REFERENCED_BY_TESS_CONTROL_SHADER: return StrLit("REFERENCED_BY_TESS_CONTROL_SHADER");
#endif
#if defined GL_REFERENCED_BY_TESS_EVALUATION_SHADER
	case GL_REFERENCED_BY_TESS_EVALUATION_SHADER: return StrLit("REFERENCED_BY_TESS_EVALUATION_SHADER");
#endif
#if defined GL_REFERENCED_BY_GEOMETRY_SHADER
	case GL_REFERENCED_BY_GEOMETRY_SHADER: return StrLit("REFERENCED_BY_GEOMETRY_SHADER");
#endif
#if defined GL_REFERENCED_BY_FRAGMENT_SHADER
	case GL_REFERENCED_BY_FRAGMENT_SHADER: return StrLit("REFERENCED_BY_FRAGMENT_SHADER");
#endif
#if defined GL_REFERENCED_BY_COMPUTE_SHADER
	case GL_REFERENCED_BY_COMPUTE_SHADER: return StrLit("REFERENCED_BY_COMPUTE_SHADER");
#endif
#if defined GL_NUM_COMPATIBLE_SUBROUTINES
	case GL_NUM_COMPATIBLE_SUBROUTINES: return StrLit("NUM_COMPATIBLE_SUBROUTINES");
#endif
#if defined GL_COMPATIBLE_SUBROUTINES
	case GL_COMPATIBLE_SUBROUTINES: return StrLit("COMPATIBLE_SUBROUTINES");
#endif
#if defined GL_TOP_LEVEL_ARRAY_SIZE
	case GL_TOP_LEVEL_ARRAY_SIZE: return StrLit("TOP_LEVEL_ARRAY_SIZE");
#endif
#if defined GL_TOP_LEVEL_ARRAY_STRIDE
	case GL_TOP_LEVEL_ARRAY_STRIDE: return StrLit("TOP_LEVEL_ARRAY_STRIDE");
#endif
#if defined GL_LOCATION
	case GL_LOCATION: return StrLit("LOCATION");
#endif
#if defined GL_LOCATION_INDEX
	case GL_LOCATION_INDEX: return StrLit("LOCATION_INDEX");
#endif
#if defined GL_LOCATION_COMPONENT
	case GL_LOCATION_COMPONENT: return StrLit("LOCATION_COMPONENT");
#endif
#if defined GL_IS_PER_PATCH
	case GL_IS_PER_PATCH: return StrLit("IS_PER_PATCH");
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER_INDEX
	case GL_TRANSFORM_FEEDBACK_BUFFER_INDEX: return StrLit("TRANSFORM_FEEDBACK_BUFFER_INDEX");
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE
	case GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE: return StrLit("TRANSFORM_FEEDBACK_BUFFER_STRIDE");
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

