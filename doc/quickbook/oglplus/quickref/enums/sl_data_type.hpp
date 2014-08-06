//  File doc/quickbook/oglplus/quickref/enums/sl_data_type.hpp
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
//[oglplus_enums_sl_data_type
namespace oglplus {

enum class SLDataType : GLenum
{
	Float                                = GL_FLOAT,
	FloatVec2                            = GL_FLOAT_VEC2,
	FloatVec3                            = GL_FLOAT_VEC3,
	FloatVec4                            = GL_FLOAT_VEC4,
	Double                               = GL_DOUBLE,
	DoubleVec2                           = GL_DOUBLE_VEC2,
	DoubleVec3                           = GL_DOUBLE_VEC3,
	DoubleVec4                           = GL_DOUBLE_VEC4,
	Int                                  = GL_INT,
	IntVec2                              = GL_INT_VEC2,
	IntVec3                              = GL_INT_VEC3,
	IntVec4                              = GL_INT_VEC4,
	UnsignedInt                          = GL_UNSIGNED_INT,
	UnsignedIntVec2                      = GL_UNSIGNED_INT_VEC2,
	UnsignedIntVec3                      = GL_UNSIGNED_INT_VEC3,
	UnsignedIntVec4                      = GL_UNSIGNED_INT_VEC4,
	Bool                                 = GL_BOOL,
	BoolVec2                             = GL_BOOL_VEC2,
	BoolVec3                             = GL_BOOL_VEC3,
	BoolVec4                             = GL_BOOL_VEC4,
	FloatMat2                            = GL_FLOAT_MAT2,
	FloatMat3                            = GL_FLOAT_MAT3,
	FloatMat4                            = GL_FLOAT_MAT4,
	FloatMat2x3                          = GL_FLOAT_MAT2x3,
	FloatMat2x4                          = GL_FLOAT_MAT2x4,
	FloatMat3x2                          = GL_FLOAT_MAT3x2,
	FloatMat3x4                          = GL_FLOAT_MAT3x4,
	FloatMat4x2                          = GL_FLOAT_MAT4x2,
	FloatMat4x3                          = GL_FLOAT_MAT4x3,
	DoubleMat2                           = GL_DOUBLE_MAT2,
	DoubleMat3                           = GL_DOUBLE_MAT3,
	DoubleMat4                           = GL_DOUBLE_MAT4,
	DoubleMat2x3                         = GL_DOUBLE_MAT2x3,
	DoubleMat2x4                         = GL_DOUBLE_MAT2x4,
	DoubleMat3x2                         = GL_DOUBLE_MAT3x2,
	DoubleMat3x4                         = GL_DOUBLE_MAT3x4,
	DoubleMat4x2                         = GL_DOUBLE_MAT4x2,
	DoubleMat4x3                         = GL_DOUBLE_MAT4x3,
	Sampler1d                            = GL_SAMPLER_1D,
	Sampler2d                            = GL_SAMPLER_2D,
	Sampler3d                            = GL_SAMPLER_3D,
	SamplerCube                          = GL_SAMPLER_CUBE,
	Sampler1dShadow                      = GL_SAMPLER_1D_SHADOW,
	Sampler2dShadow                      = GL_SAMPLER_2D_SHADOW,
	Sampler1dArray                       = GL_SAMPLER_1D_ARRAY,
	Sampler2dArray                       = GL_SAMPLER_2D_ARRAY,
	SamplerCubeMapArray                  = GL_SAMPLER_CUBE_MAP_ARRAY,
	Sampler1dArrayShadow                 = GL_SAMPLER_1D_ARRAY_SHADOW,
	Sampler2dArrayShadow                 = GL_SAMPLER_2D_ARRAY_SHADOW,
	Sampler2dMultisample                 = GL_SAMPLER_2D_MULTISAMPLE,
	Sampler2dMultisampleArray            = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
	SamplerCubeShadow                    = GL_SAMPLER_CUBE_SHADOW,
	SamplerCubeMapArrayShadow            = GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW,
	SamplerBuffer                        = GL_SAMPLER_BUFFER,
	Sampler2dRect                        = GL_SAMPLER_2D_RECT,
	Sampler2dRectShadow                  = GL_SAMPLER_2D_RECT_SHADOW,
	IntSampler1d                         = GL_INT_SAMPLER_1D,
	IntSampler2d                         = GL_INT_SAMPLER_2D,
	IntSampler3d                         = GL_INT_SAMPLER_3D,
	IntSamplerCube                       = GL_INT_SAMPLER_CUBE,
	IntSampler1dArray                    = GL_INT_SAMPLER_1D_ARRAY,
	IntSampler2dArray                    = GL_INT_SAMPLER_2D_ARRAY,
	IntSamplerCubeMapArray               = GL_INT_SAMPLER_CUBE_MAP_ARRAY,
	IntSampler2dMultisample              = GL_INT_SAMPLER_2D_MULTISAMPLE,
	IntSampler2dMultisampleArray         = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
	IntSamplerBuffer                     = GL_INT_SAMPLER_BUFFER,
	IntSampler2dRect                     = GL_INT_SAMPLER_2D_RECT,
	UnsignedIntSampler1d                 = GL_UNSIGNED_INT_SAMPLER_1D,
	UnsignedIntSampler2d                 = GL_UNSIGNED_INT_SAMPLER_2D,
	UnsignedIntSampler3d                 = GL_UNSIGNED_INT_SAMPLER_3D,
	UnsignedIntSamplerCube               = GL_UNSIGNED_INT_SAMPLER_CUBE,
	UnsignedIntSampler1dArray            = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
	UnsignedIntSampler2dArray            = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
	UnsignedIntSamplerCubeMapArray       = GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY,
	UnsignedIntSampler2dMultisample      = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
	UnsignedIntSampler2dMultisampleArray = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
	UnsignedIntSamplerBuffer             = GL_UNSIGNED_INT_SAMPLER_BUFFER,
	UnsignedIntSampler2dRect             = GL_UNSIGNED_INT_SAMPLER_2D_RECT,
	Image1d                              = GL_IMAGE_1D,
	Image2d                              = GL_IMAGE_2D,
	Image3d                              = GL_IMAGE_3D,
	Image2dRect                          = GL_IMAGE_2D_RECT,
	ImageCube                            = GL_IMAGE_CUBE,
	ImageBuffer                          = GL_IMAGE_BUFFER,
	Image1dArray                         = GL_IMAGE_1D_ARRAY,
	Image2dArray                         = GL_IMAGE_2D_ARRAY,
	Image2dMultisample                   = GL_IMAGE_2D_MULTISAMPLE,
	Image2dMultisampleArray              = GL_IMAGE_2D_MULTISAMPLE_ARRAY,
	IntImage1d                           = GL_INT_IMAGE_1D,
	IntImage2d                           = GL_INT_IMAGE_2D,
	IntImage3d                           = GL_INT_IMAGE_3D,
	IntImage2dRect                       = GL_INT_IMAGE_2D_RECT,
	IntImageCube                         = GL_INT_IMAGE_CUBE,
	IntImageBuffer                       = GL_INT_IMAGE_BUFFER,
	IntImage1dArray                      = GL_INT_IMAGE_1D_ARRAY,
	IntImage2dArray                      = GL_INT_IMAGE_2D_ARRAY,
	IntImage2dMultisample                = GL_INT_IMAGE_2D_MULTISAMPLE,
	IntImage2dMultisampleArray           = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
	UnsignedIntImage1d                   = GL_UNSIGNED_INT_IMAGE_1D,
	UnsignedIntImage2d                   = GL_UNSIGNED_INT_IMAGE_2D,
	UnsignedIntImage3d                   = GL_UNSIGNED_INT_IMAGE_3D,
	UnsignedIntImage2dRect               = GL_UNSIGNED_INT_IMAGE_2D_RECT,
	UnsignedIntImageCube                 = GL_UNSIGNED_INT_IMAGE_CUBE,
	UnsignedIntImageBuffer               = GL_UNSIGNED_INT_IMAGE_BUFFER,
	UnsignedIntImage1dArray              = GL_UNSIGNED_INT_IMAGE_1D_ARRAY,
	UnsignedIntImage2dArray              = GL_UNSIGNED_INT_IMAGE_2D_ARRAY,
	UnsignedIntImage2dMultisample        = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,
	UnsignedIntImage2dMultisampleArray   = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
	UnsignedIntAtomicCounter             = GL_UNSIGNED_INT_ATOMIC_COUNTER,
	None                                 = GL_NONE
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<SLDataType> __EnumValueRange<SLDataType>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(SLDataType);
#endif

} // namespace oglplus
//]
