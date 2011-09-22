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
/**
 *  @ingroup enumerations
 */
enum class DataType : GLenum
{
	/// BYTE
	Byte = GL_BYTE,
	/// SHORT
	Short = GL_SHORT,
	/// INT
	Int = GL_INT,
	/// FIXED
	Fixed = GL_FIXED,
	/// FLOAT
	Float = GL_FLOAT,
	/// HALF_FLOAT
	HalfFloat = GL_HALF_FLOAT,
	/// DOUBLE
	Double = GL_DOUBLE,
	/// UNSIGNED_BYTE
	UnsignedByte = GL_UNSIGNED_BYTE,
	/// UNSIGNED_SHORT
	UnsignedShort = GL_UNSIGNED_SHORT,
	/// UNSIGNED_INT
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

/// Returns the DataType for the specified type @p T
template <typename T>
DataType GetDataType(void)
{
	return GetDataType((T*)nullptr);
}


/// OpenGL Shading Language data type enumeration
/**
 *  @ingroup enumerations
 */
enum class SLDataType : GLenum
{
	/// FLOAT,
	Float = GL_FLOAT,
	/// FLOAT_VEC2
	FloatVec2 = GL_FLOAT_VEC2,
	/// FLOAT_VEC3
	FloatVec3 = GL_FLOAT_VEC3,
	/// FLOAT_VEC4
	FloatVec4 = GL_FLOAT_VEC4,
	/// DOUBLE
	Double = GL_DOUBLE,
	/// DOUBLE_VEC2
	DoubleVec2 = GL_DOUBLE_VEC2,
	/// DOUBLE_VEC3
	DoubleVec3 = GL_DOUBLE_VEC3,
	/// DOUBLE_VEC4
	DoubleVec4 = GL_DOUBLE_VEC4,
	/// INT
	Int = GL_INT,
	/// INT_VEC2
	IntVec2 = GL_INT_VEC2,
	/// INT_VEC3
	IntVec3 = GL_INT_VEC3,
	/// INT_VEC4
	IntVec4 = GL_INT_VEC4,
	/// UNSIGNED_INT
	UnsignedInt = GL_UNSIGNED_INT,
	/// UNSIGNED_INT_VEC2
	UnsignedIntVec2 = GL_UNSIGNED_INT_VEC2,
	/// UNSIGNED_INT_VEC3
	UnsignedIntVec3 = GL_UNSIGNED_INT_VEC3,
	/// UNSIGNED_INT_VEC4
	UnsignedIntVec4 = GL_UNSIGNED_INT_VEC4,
	/// BOOL
	Bool = GL_BOOL,
	/// BOOL_VEC2
	BoolVec2 = GL_BOOL_VEC2,
	/// BOOL_VEC3
	BoolVec3 = GL_BOOL_VEC3,
	/// BOOL_VEC4
	BoolVec4 = GL_BOOL_VEC4,
	/// FLOAT_MAT2
	FloatMat2 = GL_FLOAT_MAT2,
	/// FLOAT_MAT3
	FloatMat3 = GL_FLOAT_MAT3,
	/// FLOAT_MAT4
	FloatMat4 = GL_FLOAT_MAT4,
	/// FLOAT_MAT2x3
	FloatMat2x3 = GL_FLOAT_MAT2x3,
	/// FLOAT_MAT2x4
	FloatMat2x4 = GL_FLOAT_MAT2x4,
	/// FLOAT_MAT3x2
	FloatMat3x2 = GL_FLOAT_MAT3x2,
	/// FLOAT_MAT3x4
	FloatMat3x4 = GL_FLOAT_MAT3x4,
	/// FLOAT_MAT4x2
	FloatMat4x2 = GL_FLOAT_MAT4x2,
	/// FLOAT_MAT4x3
	FloatMat4x3 = GL_FLOAT_MAT4x3,
	/// DOUBLE_MAT2
	DoubleMat2 = GL_DOUBLE_MAT2,
	/// DOUBLE_MAT3
	DoubleMat3 = GL_DOUBLE_MAT3,
	/// DOUBLE_MAT4
	DoubleMat4 = GL_DOUBLE_MAT4,
	/// DOUBLE_MAT2x3
	DoubleMat2x3 = GL_DOUBLE_MAT2x3,
	/// DOUBLE_MAT2x4
	DoubleMat2x4 = GL_DOUBLE_MAT2x4,
	/// DOUBLE_MAT3x2
	DoubleMat3x2 = GL_DOUBLE_MAT3x2,
	/// DOUBLE_MAT3x4
	DoubleMat3x4 = GL_DOUBLE_MAT3x4,
	/// DOUBLE_MAT4x2
	DoubleMat4x2 = GL_DOUBLE_MAT4x2,
	/// DOUBLE_MAT4x3
	DoubleMat4x3 = GL_DOUBLE_MAT4x3,
	/// SAMPLER_1D
	Sampler1d = GL_SAMPLER_1D,
	/// SAMPLER_2D
	Sampler2d = GL_SAMPLER_2D,
	/// SAMPLER_3D
	Sampler3d = GL_SAMPLER_3D,
	/// SAMPLER_CUBE
	SamplerCube = GL_SAMPLER_CUBE,
	/// SAMPLER_1D_SHADOW
	Sampler1dShadow = GL_SAMPLER_1D_SHADOW,
	/// SAMPLER_2D_SHADOW
	Sampler2dShadow = GL_SAMPLER_2D_SHADOW,
	/// SAMPLER_1D_ARRAY
	Sampler1dArray = GL_SAMPLER_1D_ARRAY,
	/// SAMPLER_2D_ARRAY
	Sampler2dArray = GL_SAMPLER_2D_ARRAY,
	/// SAMPLER_CUBE_MAP_ARRAY
	SamplerCubeMapArray = GL_SAMPLER_CUBE_MAP_ARRAY,
	/// SAMPLER_1D_ARRAY_SHADOW
	Sampler1dArrayShadow = GL_SAMPLER_1D_ARRAY_SHADOW,
	/// SAMPLER_2D_ARRAY_SHADOW
	Sampler2dArrayShadow = GL_SAMPLER_2D_ARRAY_SHADOW,
	/// SAMPLER_2D_MULTISAMPLE
	Sampler2dMultisample = GL_SAMPLER_2D_MULTISAMPLE,
	/// SAMPLER_2D_MULTISAMPLE_ARRAY
	Sampler2dMultisampleArray = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
	/// SAMPLER_CUBE_SHADOW
	SamplerCubeShadow = GL_SAMPLER_CUBE_SHADOW,
	/// SAMPLER_CUBE_MAP_ARRAY_SHADOW
	SamplerCubeMapArrayShadow = GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW,
	/// SAMPLER_BUFFER
	SamplerBuffer = GL_SAMPLER_BUFFER,
	/// SAMPLER_2D_RECT
	Sampler2dRect = GL_SAMPLER_2D_RECT,
	/// SAMPLER_2D_RECT_SHADOW
	Sampler2dRectShadow = GL_SAMPLER_2D_RECT_SHADOW,
	/// INT_SAMPLER_1D
	IntSampler1d = GL_INT_SAMPLER_1D,
	/// INT_SAMPLER_2D
	IntSampler2d = GL_INT_SAMPLER_2D,
	/// INT_SAMPLER_3D
	IntSampler3d = GL_INT_SAMPLER_3D,
	/// INT_SAMPLER_CUBE
	IntSamplerCube = GL_INT_SAMPLER_CUBE,
	/// INT_SAMPLER_1D_ARRAY
	IntSampler1dArray = GL_INT_SAMPLER_1D_ARRAY,
	/// INT_SAMPLER_2D_ARRAY
	IntSampler2dArray = GL_INT_SAMPLER_2D_ARRAY,
	/// INT_SAMPLER_CUBE_MAP_ARRAY
	IntSamplerCubeMapArray = GL_INT_SAMPLER_CUBE_MAP_ARRAY,
	/// INT_SAMPLER_2D_MULTISAMPLE
	IntSampler2dMultisample = GL_INT_SAMPLER_2D_MULTISAMPLE,
	/// INT_SAMPLER_2D_MULTISAMPLE_ARRAY
	IntSampler2dMultisampleArray = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
	/// INT_SAMPLER_BUFFER
	IntSamplerBuffer = GL_INT_SAMPLER_BUFFER,
	/// INT_SAMPLER_2D_RECT
	IntSampler2dRect = GL_INT_SAMPLER_2D_RECT,
	/// UNSIGNED_INT_SAMPLER_1D
	UnsignedIntSampler1d = GL_UNSIGNED_INT_SAMPLER_1D,
	/// UNSIGNED_INT_SAMPLER_2D
	UnsignedIntSampler2d = GL_UNSIGNED_INT_SAMPLER_2D,
	/// UNSIGNED_INT_SAMPLER_3D
	UnsignedIntSampler3d = GL_UNSIGNED_INT_SAMPLER_3D,
	/// UNSIGNED_INT_SAMPLER_CUBE
	UnsignedIntSamplerCube = GL_UNSIGNED_INT_SAMPLER_CUBE,
	/// UNSIGNED_INT_SAMPLER_1D_ARRAY
	UnsignedIntSampler1dArray = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
	/// UNSIGNED_INT_SAMPLER_2D_ARRAY
	UnsignedIntSampler2dArray = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
	/// UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY
	UnsignedIntSamplerCubeMapArray = GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY,
	/// UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE
	UnsignedIntSampler2dMultisample = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
	/// UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
	UnsignedIntSampler2dMultisampleArray = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
	/// UNSIGNED_INT_SAMPLER_BUFFER
	UnsignedIntSamplerBuffer = GL_UNSIGNED_INT_SAMPLER_BUFFER,
	/// UNSIGNED_INT_SAMPLER_2D_RECT
	UnsignedIntSampler2dRect = GL_UNSIGNED_INT_SAMPLER_2D_RECT,
	/// NONE
	None = GL_NONE
};

} // namespace oglplus

#endif // include guard
