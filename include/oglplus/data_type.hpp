/**
 *  @file oglplus/data_type.hpp
 *  @brief Data type-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_DATA_TYPE_1107121519_HPP
#define OGLPLUS_DATA_TYPE_1107121519_HPP

#include <oglplus/config.hpp>

namespace oglplus {

/// OpenGL data type enumeration
enum class DataType : GLenum
{
	Byte = GL_BYTE,
	Short = GL_SHORT,
	Int = GL_INT,
	Fixed = GL_FIXED,
	Float = GL_FLOAT,
	HalfFloat = GL_HALF_FLOAT,
	Double = GL_DOUBLE,
	UnsignedByte = GL_UNSIGNED_BYTE,
	UnsignedShort = GL_UNSIGNED_SHORT,
	UnsignedInt = GL_UNSIGNED_INT
};

DataType GetDataType(GLbyte*)
{
	return DataType::Byte;
}

DataType GetDataType(GLshort*)
{
	return DataType::Short;
}

DataType GetDataType(GLint*)
{
	return DataType::Int;
}

DataType GetDataType(GLubyte*)
{
	return DataType::UnsignedByte;
}

DataType GetDataType(GLushort*)
{
	return DataType::UnsignedShort;
}

DataType GetDataType(GLuint*)
{
	return DataType::UnsignedInt;
}

DataType GetDataType(GLfloat*)
{
	return DataType::Float;
}

DataType GetDataType(GLdouble*)
{
	return DataType::Double;
}

template <typename T>
DataType GetDataType(void)
{
	return GetDataType((T*)nullptr);
}


/// OpenGL Shading Language data type enumeration
enum class SLDataType : GLenum
{
	Float = GL_FLOAT,
	FloatVec2 = GL_FLOAT_VEC2,
	FloatVec3 = GL_FLOAT_VEC3,
	FloatVec4 = GL_FLOAT_VEC4,
	Double = GL_DOUBLE,
	DoubleVec2 = GL_DOUBLE_VEC2,
	DoubleVec3 = GL_DOUBLE_VEC3,
	DoubleVec4 = GL_DOUBLE_VEC4,
	Int = GL_INT,
	IntVec2 = GL_INT_VEC2,
	IntVec3 = GL_INT_VEC3,
	IntVec4 = GL_INT_VEC4,
	UnsignedInt = GL_UNSIGNED_INT,
	UnsignedIntVec2 = GL_UNSIGNED_INT_VEC2,
	UnsignedIntVec3 = GL_UNSIGNED_INT_VEC3,
	UnsignedIntVec4 = GL_UNSIGNED_INT_VEC4,
	Bool = GL_BOOL,
	BoolVec2 = GL_BOOL_VEC2,
	BoolVec3 = GL_BOOL_VEC3,
	BoolVec4 = GL_BOOL_VEC4,
	FloatMat2 = GL_FLOAT_MAT2,
	FloatMat3 = GL_FLOAT_MAT3,
	FloatMat4 = GL_FLOAT_MAT4,
	FloatMat2x3 = GL_FLOAT_MAT2x3,
	FloatMat2x4 = GL_FLOAT_MAT2x4,
	FloatMat3x2 = GL_FLOAT_MAT3x2,
	FloatMat3x4 = GL_FLOAT_MAT3x4,
	FloatMat4x2 = GL_FLOAT_MAT4x2,
	FloatMat4x3 = GL_FLOAT_MAT4x3,
	DoubleMat2 = GL_DOUBLE_MAT2,
	DoubleMat3 = GL_DOUBLE_MAT3,
	DoubleMat4 = GL_DOUBLE_MAT4,
	DoubleMat2x3 = GL_DOUBLE_MAT2x3,
	DoubleMat2x4 = GL_DOUBLE_MAT2x4,
	DoubleMat3x2 = GL_DOUBLE_MAT3x2,
	DoubleMat3x4 = GL_DOUBLE_MAT3x4,
	DoubleMat4x2 = GL_DOUBLE_MAT4x2,
	DoubleMat4x3 = GL_DOUBLE_MAT4x3,
	Sampler1d = GL_SAMPLER_1D,
	Sampler2d = GL_SAMPLER_2D,
	Sampler3d = GL_SAMPLER_3D,
	SamplerCube = GL_SAMPLER_CUBE,
	Sampler1dShadow = GL_SAMPLER_1D_SHADOW,
	Sampler2dShadow = GL_SAMPLER_2D_SHADOW,
	Sampler1dArray = GL_SAMPLER_1D_ARRAY,
	Sampler2dArray = GL_SAMPLER_2D_ARRAY,
	//SamplerCubeMapArray = GL_SAMPLER_CUBE_MAP_ARRAY,
	Sampler1dArrayShadow = GL_SAMPLER_1D_ARRAY_SHADOW,
	Sampler2dArrayShadow = GL_SAMPLER_2D_ARRAY_SHADOW,
	Sampler2dMultisample = GL_SAMPLER_2D_MULTISAMPLE,
	Sampler2dMultisampleArray = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
	SamplerCubeShadow = GL_SAMPLER_CUBE_SHADOW,
	//SamplerCubeMapArrayShadow = GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW,
	SamplerBuffer = GL_SAMPLER_BUFFER,
	Sampler2dRect = GL_SAMPLER_2D_RECT,
	Sampler2dRectShadow = GL_SAMPLER_2D_RECT_SHADOW,
	IntSampler1d = GL_INT_SAMPLER_1D,
	IntSampler2d = GL_INT_SAMPLER_2D,
	IntSampler3d = GL_INT_SAMPLER_3D,
	IntSamplerCube = GL_INT_SAMPLER_CUBE,
	IntSampler1dArray = GL_INT_SAMPLER_1D_ARRAY,
	IntSampler2dArray = GL_INT_SAMPLER_2D_ARRAY,
	//IntSamplerCubeMapArray = GL_INT_SAMPLER_CUBE_MAP_ARRAY,
	IntSampler2dMultisample = GL_INT_SAMPLER_2D_MULTISAMPLE,
	IntSampler2dMultisampleArray = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
	IntSamplerBuffer = GL_INT_SAMPLER_BUFFER,
	IntSampler2dRect = GL_INT_SAMPLER_2D_RECT,
	UnsignedIntSampler1d = GL_UNSIGNED_INT_SAMPLER_1D,
	UnsignedIntSampler2d = GL_UNSIGNED_INT_SAMPLER_2D,
	UnsignedIntSampler3d = GL_UNSIGNED_INT_SAMPLER_3D,
	UnsignedIntSamplerCube = GL_UNSIGNED_INT_SAMPLER_CUBE,
	UnsignedIntSampler1dArray = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
	UnsignedIntSampler2dArray = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
	//UnsignedIntSamplerCubeMapArray = GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY,
	UnsignedIntSampler2dMultisample = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
	UnsignedIntSampler2dMultisampleArray = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
	UnsignedIntSamplerBuffer = GL_UNSIGNED_INT_SAMPLER_BUFFER,
	UnsignedIntSampler2dRect = GL_UNSIGNED_INT_SAMPLER_2D_RECT
};

} // namespace oglplus

#endif // include guard
