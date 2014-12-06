//  File implement/oglplus/enums/sl_data_type_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/sl_data_type.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	SLDataType*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_SLDATATYPE)
#define OGLPLUS_IMPL_EVN_SLDATATYPE
{
switch(value)
{
#if defined GL_FLOAT
	case GL_FLOAT: return CStrRef("FLOAT");
#endif
#if defined GL_FLOAT_VEC2
	case GL_FLOAT_VEC2: return CStrRef("FLOAT_VEC2");
#endif
#if defined GL_FLOAT_VEC3
	case GL_FLOAT_VEC3: return CStrRef("FLOAT_VEC3");
#endif
#if defined GL_FLOAT_VEC4
	case GL_FLOAT_VEC4: return CStrRef("FLOAT_VEC4");
#endif
#if defined GL_DOUBLE
	case GL_DOUBLE: return CStrRef("DOUBLE");
#endif
#if defined GL_DOUBLE_VEC2
	case GL_DOUBLE_VEC2: return CStrRef("DOUBLE_VEC2");
#endif
#if defined GL_DOUBLE_VEC3
	case GL_DOUBLE_VEC3: return CStrRef("DOUBLE_VEC3");
#endif
#if defined GL_DOUBLE_VEC4
	case GL_DOUBLE_VEC4: return CStrRef("DOUBLE_VEC4");
#endif
#if defined GL_INT
	case GL_INT: return CStrRef("INT");
#endif
#if defined GL_INT_VEC2
	case GL_INT_VEC2: return CStrRef("INT_VEC2");
#endif
#if defined GL_INT_VEC3
	case GL_INT_VEC3: return CStrRef("INT_VEC3");
#endif
#if defined GL_INT_VEC4
	case GL_INT_VEC4: return CStrRef("INT_VEC4");
#endif
#if defined GL_UNSIGNED_INT
	case GL_UNSIGNED_INT: return CStrRef("UNSIGNED_INT");
#endif
#if defined GL_UNSIGNED_INT_VEC2
	case GL_UNSIGNED_INT_VEC2: return CStrRef("UNSIGNED_INT_VEC2");
#endif
#if defined GL_UNSIGNED_INT_VEC3
	case GL_UNSIGNED_INT_VEC3: return CStrRef("UNSIGNED_INT_VEC3");
#endif
#if defined GL_UNSIGNED_INT_VEC4
	case GL_UNSIGNED_INT_VEC4: return CStrRef("UNSIGNED_INT_VEC4");
#endif
#if defined GL_BOOL
	case GL_BOOL: return CStrRef("BOOL");
#endif
#if defined GL_BOOL_VEC2
	case GL_BOOL_VEC2: return CStrRef("BOOL_VEC2");
#endif
#if defined GL_BOOL_VEC3
	case GL_BOOL_VEC3: return CStrRef("BOOL_VEC3");
#endif
#if defined GL_BOOL_VEC4
	case GL_BOOL_VEC4: return CStrRef("BOOL_VEC4");
#endif
#if defined GL_FLOAT_MAT2
	case GL_FLOAT_MAT2: return CStrRef("FLOAT_MAT2");
#endif
#if defined GL_FLOAT_MAT3
	case GL_FLOAT_MAT3: return CStrRef("FLOAT_MAT3");
#endif
#if defined GL_FLOAT_MAT4
	case GL_FLOAT_MAT4: return CStrRef("FLOAT_MAT4");
#endif
#if defined GL_FLOAT_MAT2x3
	case GL_FLOAT_MAT2x3: return CStrRef("FLOAT_MAT2x3");
#endif
#if defined GL_FLOAT_MAT2x4
	case GL_FLOAT_MAT2x4: return CStrRef("FLOAT_MAT2x4");
#endif
#if defined GL_FLOAT_MAT3x2
	case GL_FLOAT_MAT3x2: return CStrRef("FLOAT_MAT3x2");
#endif
#if defined GL_FLOAT_MAT3x4
	case GL_FLOAT_MAT3x4: return CStrRef("FLOAT_MAT3x4");
#endif
#if defined GL_FLOAT_MAT4x2
	case GL_FLOAT_MAT4x2: return CStrRef("FLOAT_MAT4x2");
#endif
#if defined GL_FLOAT_MAT4x3
	case GL_FLOAT_MAT4x3: return CStrRef("FLOAT_MAT4x3");
#endif
#if defined GL_DOUBLE_MAT2
	case GL_DOUBLE_MAT2: return CStrRef("DOUBLE_MAT2");
#endif
#if defined GL_DOUBLE_MAT3
	case GL_DOUBLE_MAT3: return CStrRef("DOUBLE_MAT3");
#endif
#if defined GL_DOUBLE_MAT4
	case GL_DOUBLE_MAT4: return CStrRef("DOUBLE_MAT4");
#endif
#if defined GL_DOUBLE_MAT2x3
	case GL_DOUBLE_MAT2x3: return CStrRef("DOUBLE_MAT2x3");
#endif
#if defined GL_DOUBLE_MAT2x4
	case GL_DOUBLE_MAT2x4: return CStrRef("DOUBLE_MAT2x4");
#endif
#if defined GL_DOUBLE_MAT3x2
	case GL_DOUBLE_MAT3x2: return CStrRef("DOUBLE_MAT3x2");
#endif
#if defined GL_DOUBLE_MAT3x4
	case GL_DOUBLE_MAT3x4: return CStrRef("DOUBLE_MAT3x4");
#endif
#if defined GL_DOUBLE_MAT4x2
	case GL_DOUBLE_MAT4x2: return CStrRef("DOUBLE_MAT4x2");
#endif
#if defined GL_DOUBLE_MAT4x3
	case GL_DOUBLE_MAT4x3: return CStrRef("DOUBLE_MAT4x3");
#endif
#if defined GL_SAMPLER_1D
	case GL_SAMPLER_1D: return CStrRef("SAMPLER_1D");
#endif
#if defined GL_SAMPLER_2D
	case GL_SAMPLER_2D: return CStrRef("SAMPLER_2D");
#endif
#if defined GL_SAMPLER_3D
	case GL_SAMPLER_3D: return CStrRef("SAMPLER_3D");
#endif
#if defined GL_SAMPLER_CUBE
	case GL_SAMPLER_CUBE: return CStrRef("SAMPLER_CUBE");
#endif
#if defined GL_SAMPLER_1D_SHADOW
	case GL_SAMPLER_1D_SHADOW: return CStrRef("SAMPLER_1D_SHADOW");
#endif
#if defined GL_SAMPLER_2D_SHADOW
	case GL_SAMPLER_2D_SHADOW: return CStrRef("SAMPLER_2D_SHADOW");
#endif
#if defined GL_SAMPLER_1D_ARRAY
	case GL_SAMPLER_1D_ARRAY: return CStrRef("SAMPLER_1D_ARRAY");
#endif
#if defined GL_SAMPLER_2D_ARRAY
	case GL_SAMPLER_2D_ARRAY: return CStrRef("SAMPLER_2D_ARRAY");
#endif
#if defined GL_SAMPLER_CUBE_MAP_ARRAY
	case GL_SAMPLER_CUBE_MAP_ARRAY: return CStrRef("SAMPLER_CUBE_MAP_ARRAY");
#endif
#if defined GL_SAMPLER_1D_ARRAY_SHADOW
	case GL_SAMPLER_1D_ARRAY_SHADOW: return CStrRef("SAMPLER_1D_ARRAY_SHADOW");
#endif
#if defined GL_SAMPLER_2D_ARRAY_SHADOW
	case GL_SAMPLER_2D_ARRAY_SHADOW: return CStrRef("SAMPLER_2D_ARRAY_SHADOW");
#endif
#if defined GL_SAMPLER_2D_MULTISAMPLE
	case GL_SAMPLER_2D_MULTISAMPLE: return CStrRef("SAMPLER_2D_MULTISAMPLE");
#endif
#if defined GL_SAMPLER_2D_MULTISAMPLE_ARRAY
	case GL_SAMPLER_2D_MULTISAMPLE_ARRAY: return CStrRef("SAMPLER_2D_MULTISAMPLE_ARRAY");
#endif
#if defined GL_SAMPLER_CUBE_SHADOW
	case GL_SAMPLER_CUBE_SHADOW: return CStrRef("SAMPLER_CUBE_SHADOW");
#endif
#if defined GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW
	case GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW: return CStrRef("SAMPLER_CUBE_MAP_ARRAY_SHADOW");
#endif
#if defined GL_SAMPLER_BUFFER
	case GL_SAMPLER_BUFFER: return CStrRef("SAMPLER_BUFFER");
#endif
#if defined GL_SAMPLER_2D_RECT
	case GL_SAMPLER_2D_RECT: return CStrRef("SAMPLER_2D_RECT");
#endif
#if defined GL_SAMPLER_2D_RECT_SHADOW
	case GL_SAMPLER_2D_RECT_SHADOW: return CStrRef("SAMPLER_2D_RECT_SHADOW");
#endif
#if defined GL_INT_SAMPLER_1D
	case GL_INT_SAMPLER_1D: return CStrRef("INT_SAMPLER_1D");
#endif
#if defined GL_INT_SAMPLER_2D
	case GL_INT_SAMPLER_2D: return CStrRef("INT_SAMPLER_2D");
#endif
#if defined GL_INT_SAMPLER_3D
	case GL_INT_SAMPLER_3D: return CStrRef("INT_SAMPLER_3D");
#endif
#if defined GL_INT_SAMPLER_CUBE
	case GL_INT_SAMPLER_CUBE: return CStrRef("INT_SAMPLER_CUBE");
#endif
#if defined GL_INT_SAMPLER_1D_ARRAY
	case GL_INT_SAMPLER_1D_ARRAY: return CStrRef("INT_SAMPLER_1D_ARRAY");
#endif
#if defined GL_INT_SAMPLER_2D_ARRAY
	case GL_INT_SAMPLER_2D_ARRAY: return CStrRef("INT_SAMPLER_2D_ARRAY");
#endif
#if defined GL_INT_SAMPLER_CUBE_MAP_ARRAY
	case GL_INT_SAMPLER_CUBE_MAP_ARRAY: return CStrRef("INT_SAMPLER_CUBE_MAP_ARRAY");
#endif
#if defined GL_INT_SAMPLER_2D_MULTISAMPLE
	case GL_INT_SAMPLER_2D_MULTISAMPLE: return CStrRef("INT_SAMPLER_2D_MULTISAMPLE");
#endif
#if defined GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
	case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY: return CStrRef("INT_SAMPLER_2D_MULTISAMPLE_ARRAY");
#endif
#if defined GL_INT_SAMPLER_BUFFER
	case GL_INT_SAMPLER_BUFFER: return CStrRef("INT_SAMPLER_BUFFER");
#endif
#if defined GL_INT_SAMPLER_2D_RECT
	case GL_INT_SAMPLER_2D_RECT: return CStrRef("INT_SAMPLER_2D_RECT");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_1D
	case GL_UNSIGNED_INT_SAMPLER_1D: return CStrRef("UNSIGNED_INT_SAMPLER_1D");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D
	case GL_UNSIGNED_INT_SAMPLER_2D: return CStrRef("UNSIGNED_INT_SAMPLER_2D");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_3D
	case GL_UNSIGNED_INT_SAMPLER_3D: return CStrRef("UNSIGNED_INT_SAMPLER_3D");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_CUBE
	case GL_UNSIGNED_INT_SAMPLER_CUBE: return CStrRef("UNSIGNED_INT_SAMPLER_CUBE");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_1D_ARRAY
	case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY: return CStrRef("UNSIGNED_INT_SAMPLER_1D_ARRAY");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_ARRAY
	case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY: return CStrRef("UNSIGNED_INT_SAMPLER_2D_ARRAY");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY
	case GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY: return CStrRef("UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE
	case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE: return CStrRef("UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
	case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY: return CStrRef("UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_BUFFER
	case GL_UNSIGNED_INT_SAMPLER_BUFFER: return CStrRef("UNSIGNED_INT_SAMPLER_BUFFER");
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_RECT
	case GL_UNSIGNED_INT_SAMPLER_2D_RECT: return CStrRef("UNSIGNED_INT_SAMPLER_2D_RECT");
#endif
#if defined GL_IMAGE_1D
	case GL_IMAGE_1D: return CStrRef("IMAGE_1D");
#endif
#if defined GL_IMAGE_2D
	case GL_IMAGE_2D: return CStrRef("IMAGE_2D");
#endif
#if defined GL_IMAGE_3D
	case GL_IMAGE_3D: return CStrRef("IMAGE_3D");
#endif
#if defined GL_IMAGE_2D_RECT
	case GL_IMAGE_2D_RECT: return CStrRef("IMAGE_2D_RECT");
#endif
#if defined GL_IMAGE_CUBE
	case GL_IMAGE_CUBE: return CStrRef("IMAGE_CUBE");
#endif
#if defined GL_IMAGE_BUFFER
	case GL_IMAGE_BUFFER: return CStrRef("IMAGE_BUFFER");
#endif
#if defined GL_IMAGE_1D_ARRAY
	case GL_IMAGE_1D_ARRAY: return CStrRef("IMAGE_1D_ARRAY");
#endif
#if defined GL_IMAGE_2D_ARRAY
	case GL_IMAGE_2D_ARRAY: return CStrRef("IMAGE_2D_ARRAY");
#endif
#if defined GL_IMAGE_2D_MULTISAMPLE
	case GL_IMAGE_2D_MULTISAMPLE: return CStrRef("IMAGE_2D_MULTISAMPLE");
#endif
#if defined GL_IMAGE_2D_MULTISAMPLE_ARRAY
	case GL_IMAGE_2D_MULTISAMPLE_ARRAY: return CStrRef("IMAGE_2D_MULTISAMPLE_ARRAY");
#endif
#if defined GL_INT_IMAGE_1D
	case GL_INT_IMAGE_1D: return CStrRef("INT_IMAGE_1D");
#endif
#if defined GL_INT_IMAGE_2D
	case GL_INT_IMAGE_2D: return CStrRef("INT_IMAGE_2D");
#endif
#if defined GL_INT_IMAGE_3D
	case GL_INT_IMAGE_3D: return CStrRef("INT_IMAGE_3D");
#endif
#if defined GL_INT_IMAGE_2D_RECT
	case GL_INT_IMAGE_2D_RECT: return CStrRef("INT_IMAGE_2D_RECT");
#endif
#if defined GL_INT_IMAGE_CUBE
	case GL_INT_IMAGE_CUBE: return CStrRef("INT_IMAGE_CUBE");
#endif
#if defined GL_INT_IMAGE_BUFFER
	case GL_INT_IMAGE_BUFFER: return CStrRef("INT_IMAGE_BUFFER");
#endif
#if defined GL_INT_IMAGE_1D_ARRAY
	case GL_INT_IMAGE_1D_ARRAY: return CStrRef("INT_IMAGE_1D_ARRAY");
#endif
#if defined GL_INT_IMAGE_2D_ARRAY
	case GL_INT_IMAGE_2D_ARRAY: return CStrRef("INT_IMAGE_2D_ARRAY");
#endif
#if defined GL_INT_IMAGE_2D_MULTISAMPLE
	case GL_INT_IMAGE_2D_MULTISAMPLE: return CStrRef("INT_IMAGE_2D_MULTISAMPLE");
#endif
#if defined GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY
	case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY: return CStrRef("INT_IMAGE_2D_MULTISAMPLE_ARRAY");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_1D
	case GL_UNSIGNED_INT_IMAGE_1D: return CStrRef("UNSIGNED_INT_IMAGE_1D");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D
	case GL_UNSIGNED_INT_IMAGE_2D: return CStrRef("UNSIGNED_INT_IMAGE_2D");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_3D
	case GL_UNSIGNED_INT_IMAGE_3D: return CStrRef("UNSIGNED_INT_IMAGE_3D");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D_RECT
	case GL_UNSIGNED_INT_IMAGE_2D_RECT: return CStrRef("UNSIGNED_INT_IMAGE_2D_RECT");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_CUBE
	case GL_UNSIGNED_INT_IMAGE_CUBE: return CStrRef("UNSIGNED_INT_IMAGE_CUBE");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_BUFFER
	case GL_UNSIGNED_INT_IMAGE_BUFFER: return CStrRef("UNSIGNED_INT_IMAGE_BUFFER");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_1D_ARRAY
	case GL_UNSIGNED_INT_IMAGE_1D_ARRAY: return CStrRef("UNSIGNED_INT_IMAGE_1D_ARRAY");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D_ARRAY
	case GL_UNSIGNED_INT_IMAGE_2D_ARRAY: return CStrRef("UNSIGNED_INT_IMAGE_2D_ARRAY");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE
	case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE: return CStrRef("UNSIGNED_INT_IMAGE_2D_MULTISAMPLE");
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY
	case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY: return CStrRef("UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY");
#endif
#if defined GL_UNSIGNED_INT_ATOMIC_COUNTER
	case GL_UNSIGNED_INT_ATOMIC_COUNTER: return CStrRef("UNSIGNED_INT_ATOMIC_COUNTER");
#endif
#if defined GL_NONE
	case GL_NONE: return CStrRef("NONE");
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

