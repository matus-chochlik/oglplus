/*
 *  .file oglplus/auxiliary/glsl_to_cpp.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/sl_data_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef GL_FLOAT
template <>
struct GLSL2Cpp<SLDataType::Float>
{
	typedef GLfloat Type;
};
#endif // FLOAT

#ifdef GL_FLOAT_VEC2
template <>
struct GLSL2Cpp<SLDataType::FloatVec2>
{
	typedef oglplus::Vector<GLfloat, 2> Type;
};
#endif // FLOAT_VEC2

#ifdef GL_FLOAT_VEC3
template <>
struct GLSL2Cpp<SLDataType::FloatVec3>
{
	typedef oglplus::Vector<GLfloat, 3> Type;
};
#endif // FLOAT_VEC3

#ifdef GL_FLOAT_VEC4
template <>
struct GLSL2Cpp<SLDataType::FloatVec4>
{
	typedef oglplus::Vector<GLfloat, 4> Type;
};
#endif // FLOAT_VEC4

#ifdef GL_DOUBLE
template <>
struct GLSL2Cpp<SLDataType::Double>
{
	typedef GLdouble Type;
};
#endif // DOUBLE

#ifdef GL_DOUBLE_VEC2
template <>
struct GLSL2Cpp<SLDataType::DoubleVec2>
{
	typedef oglplus::Vector<GLdouble, 2> Type;
};
#endif // DOUBLE_VEC2

#ifdef GL_DOUBLE_VEC3
template <>
struct GLSL2Cpp<SLDataType::DoubleVec3>
{
	typedef oglplus::Vector<GLdouble, 3> Type;
};
#endif // DOUBLE_VEC3

#ifdef GL_DOUBLE_VEC4
template <>
struct GLSL2Cpp<SLDataType::DoubleVec4>
{
	typedef oglplus::Vector<GLdouble, 4> Type;
};
#endif // DOUBLE_VEC4

#ifdef GL_INT
template <>
struct GLSL2Cpp<SLDataType::Int>
{
	typedef GLint Type;
};
#endif // INT

#ifdef GL_INT_VEC2
template <>
struct GLSL2Cpp<SLDataType::IntVec2>
{
	typedef oglplus::Vector<GLint, 2> Type;
};
#endif // INT_VEC2

#ifdef GL_INT_VEC3
template <>
struct GLSL2Cpp<SLDataType::IntVec3>
{
	typedef oglplus::Vector<GLint, 3> Type;
};
#endif // INT_VEC3

#ifdef GL_INT_VEC4
template <>
struct GLSL2Cpp<SLDataType::IntVec4>
{
	typedef oglplus::Vector<GLint, 4> Type;
};
#endif // INT_VEC4

#ifdef GL_UNSIGNED_INT
template <>
struct GLSL2Cpp<SLDataType::UnsignedInt>
{
	typedef GLuint Type;
};
#endif // UNSIGNED_INT

#ifdef GL_UNSIGNED_INT_VEC2
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntVec2>
{
	typedef oglplus::Vector<GLuint, 2> Type;
};
#endif // UNSIGNED_INT_VEC2

#ifdef GL_UNSIGNED_INT_VEC3
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntVec3>
{
	typedef oglplus::Vector<GLuint, 3> Type;
};
#endif // UNSIGNED_INT_VEC3

#ifdef GL_UNSIGNED_INT_VEC4
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntVec4>
{
	typedef oglplus::Vector<GLuint, 4> Type;
};
#endif // UNSIGNED_INT_VEC4

#ifdef GL_BOOL
template <>
struct GLSL2Cpp<SLDataType::Bool>
{
	typedef GLboolean Type;
};
#endif // BOOL

#ifdef GL_BOOL_VEC2
template <>
struct GLSL2Cpp<SLDataType::BoolVec2>
{
	typedef oglplus::Vector<GLboolean, 2> Type;
};
#endif // BOOL_VEC2

#ifdef GL_BOOL_VEC3
template <>
struct GLSL2Cpp<SLDataType::BoolVec3>
{
	typedef oglplus::Vector<GLboolean, 3> Type;
};
#endif // BOOL_VEC3

#ifdef GL_BOOL_VEC4
template <>
struct GLSL2Cpp<SLDataType::BoolVec4>
{
	typedef oglplus::Vector<GLboolean, 4> Type;
};
#endif // BOOL_VEC4

#ifdef GL_FLOAT_MAT2
template <>
struct GLSL2Cpp<SLDataType::FloatMat2>
{
	typedef oglplus::Matrix<GLfloat, 2, 2> Type;
};
#endif // FLOAT_MAT2

#ifdef GL_FLOAT_MAT3
template <>
struct GLSL2Cpp<SLDataType::FloatMat3>
{
	typedef oglplus::Matrix<GLfloat, 3, 3> Type;
};
#endif // FLOAT_MAT3

#ifdef GL_FLOAT_MAT4
template <>
struct GLSL2Cpp<SLDataType::FloatMat4>
{
	typedef oglplus::Matrix<GLfloat, 4, 4> Type;
};
#endif // FLOAT_MAT4

#ifdef GL_FLOAT_MAT2x3
template <>
struct GLSL2Cpp<SLDataType::FloatMat2x3>
{
	typedef oglplus::Matrix<GLfloat, 3, 2> Type;
};
#endif // FLOAT_MAT2x3

#ifdef GL_FLOAT_MAT2x4
template <>
struct GLSL2Cpp<SLDataType::FloatMat2x4>
{
	typedef oglplus::Matrix<GLfloat, 4, 2> Type;
};
#endif // FLOAT_MAT2x4

#ifdef GL_FLOAT_MAT3x2
template <>
struct GLSL2Cpp<SLDataType::FloatMat3x2>
{
	typedef oglplus::Matrix<GLfloat, 2, 3> Type;
};
#endif // FLOAT_MAT3x2

#ifdef GL_FLOAT_MAT3x4
template <>
struct GLSL2Cpp<SLDataType::FloatMat3x4>
{
	typedef oglplus::Matrix<GLfloat, 4, 3> Type;
};
#endif // FLOAT_MAT3x4

#ifdef GL_FLOAT_MAT4x2
template <>
struct GLSL2Cpp<SLDataType::FloatMat4x2>
{
	typedef oglplus::Matrix<GLfloat, 2, 4> Type;
};
#endif // FLOAT_MAT4x2

#ifdef GL_FLOAT_MAT4x3
template <>
struct GLSL2Cpp<SLDataType::FloatMat4x3>
{
	typedef oglplus::Matrix<GLfloat, 3, 4> Type;
};
#endif // FLOAT_MAT4x3

#ifdef GL_DOUBLE_MAT2
template <>
struct GLSL2Cpp<SLDataType::DoubleMat2>
{
	typedef oglplus::Matrix<GLdouble, 2, 2> Type;
};
#endif // DOUBLE_MAT2

#ifdef GL_DOUBLE_MAT3
template <>
struct GLSL2Cpp<SLDataType::DoubleMat3>
{
	typedef oglplus::Matrix<GLdouble, 3, 3> Type;
};
#endif // DOUBLE_MAT3

#ifdef GL_DOUBLE_MAT4
template <>
struct GLSL2Cpp<SLDataType::DoubleMat4>
{
	typedef oglplus::Matrix<GLdouble, 4, 4> Type;
};
#endif // DOUBLE_MAT4

#ifdef GL_DOUBLE_MAT2x3
template <>
struct GLSL2Cpp<SLDataType::DoubleMat2x3>
{
	typedef oglplus::Matrix<GLdouble, 3, 2> Type;
};
#endif // DOUBLE_MAT2x3

#ifdef GL_DOUBLE_MAT2x4
template <>
struct GLSL2Cpp<SLDataType::DoubleMat2x4>
{
	typedef oglplus::Matrix<GLdouble, 4, 2> Type;
};
#endif // DOUBLE_MAT2x4

#ifdef GL_DOUBLE_MAT3x2
template <>
struct GLSL2Cpp<SLDataType::DoubleMat3x2>
{
	typedef oglplus::Matrix<GLdouble, 2, 3> Type;
};
#endif // DOUBLE_MAT3x2

#ifdef GL_DOUBLE_MAT3x4
template <>
struct GLSL2Cpp<SLDataType::DoubleMat3x4>
{
	typedef oglplus::Matrix<GLdouble, 4, 3> Type;
};
#endif // DOUBLE_MAT3x4

#ifdef GL_DOUBLE_MAT4x2
template <>
struct GLSL2Cpp<SLDataType::DoubleMat4x2>
{
	typedef oglplus::Matrix<GLdouble, 2, 4> Type;
};
#endif // DOUBLE_MAT4x2

#ifdef GL_DOUBLE_MAT4x3
template <>
struct GLSL2Cpp<SLDataType::DoubleMat4x3>
{
	typedef oglplus::Matrix<GLdouble, 3, 4> Type;
};
#endif // DOUBLE_MAT4x3

#ifdef GL_SAMPLER_1D
template <>
struct GLSL2Cpp<SLDataType::Sampler1D>
{
	typedef GLint Type;
};
#endif // SAMPLER_1D

#ifdef GL_SAMPLER_2D
template <>
struct GLSL2Cpp<SLDataType::Sampler2D>
{
	typedef GLint Type;
};
#endif // SAMPLER_2D

#ifdef GL_SAMPLER_3D
template <>
struct GLSL2Cpp<SLDataType::Sampler3D>
{
	typedef GLint Type;
};
#endif // SAMPLER_3D

#ifdef GL_SAMPLER_CUBE
template <>
struct GLSL2Cpp<SLDataType::SamplerCube>
{
	typedef GLint Type;
};
#endif // SAMPLER_CUBE

#ifdef GL_SAMPLER_1D_SHADOW
template <>
struct GLSL2Cpp<SLDataType::Sampler1DShadow>
{
	typedef GLint Type;
};
#endif // SAMPLER_1D_SHADOW

#ifdef GL_SAMPLER_2D_SHADOW
template <>
struct GLSL2Cpp<SLDataType::Sampler2DShadow>
{
	typedef GLint Type;
};
#endif // SAMPLER_2D_SHADOW

#ifdef GL_SAMPLER_1D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::Sampler1DArray>
{
	typedef GLint Type;
};
#endif // SAMPLER_1D_ARRAY

#ifdef GL_SAMPLER_2D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::Sampler2DArray>
{
	typedef GLint Type;
};
#endif // SAMPLER_2D_ARRAY

#ifdef GL_SAMPLER_CUBE_MAP_ARRAY
template <>
struct GLSL2Cpp<SLDataType::SamplerCubeMapArray>
{
	typedef GLint Type;
};
#endif // SAMPLER_CUBE_MAP_ARRAY

#ifdef GL_SAMPLER_1D_ARRAY_SHADOW
template <>
struct GLSL2Cpp<SLDataType::Sampler1DArrayShadow>
{
	typedef GLint Type;
};
#endif // SAMPLER_1D_ARRAY_SHADOW

#ifdef GL_SAMPLER_2D_ARRAY_SHADOW
template <>
struct GLSL2Cpp<SLDataType::Sampler2DArrayShadow>
{
	typedef GLint Type;
};
#endif // SAMPLER_2D_ARRAY_SHADOW

#ifdef GL_SAMPLER_2D_MULTISAMPLE
template <>
struct GLSL2Cpp<SLDataType::Sampler2DMultisample>
{
	typedef GLint Type;
};
#endif // SAMPLER_2D_MULTISAMPLE

#ifdef GL_SAMPLER_2D_MULTISAMPLE_ARRAY
template <>
struct GLSL2Cpp<SLDataType::Sampler2DMultisampleArray>
{
	typedef GLint Type;
};
#endif // SAMPLER_2D_MULTISAMPLE_ARRAY

#ifdef GL_SAMPLER_CUBE_SHADOW
template <>
struct GLSL2Cpp<SLDataType::SamplerCubeShadow>
{
	typedef GLint Type;
};
#endif // SAMPLER_CUBE_SHADOW

#ifdef GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW
template <>
struct GLSL2Cpp<SLDataType::SamplerCubeMapArrayShadow>
{
	typedef GLint Type;
};
#endif // SAMPLER_CUBE_MAP_ARRAY_SHADOW

#ifdef GL_SAMPLER_BUFFER
template <>
struct GLSL2Cpp<SLDataType::SamplerBuffer>
{
	typedef GLint Type;
};
#endif // SAMPLER_BUFFER

#ifdef GL_SAMPLER_2D_RECT
template <>
struct GLSL2Cpp<SLDataType::Sampler2DRect>
{
	typedef GLint Type;
};
#endif // SAMPLER_2D_RECT

#ifdef GL_SAMPLER_2D_RECT_SHADOW
template <>
struct GLSL2Cpp<SLDataType::Sampler2DRectShadow>
{
	typedef GLint Type;
};
#endif // SAMPLER_2D_RECT_SHADOW

#ifdef GL_INT_SAMPLER_1D
template <>
struct GLSL2Cpp<SLDataType::IntSampler1D>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_1D

#ifdef GL_INT_SAMPLER_2D
template <>
struct GLSL2Cpp<SLDataType::IntSampler2D>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_2D

#ifdef GL_INT_SAMPLER_3D
template <>
struct GLSL2Cpp<SLDataType::IntSampler3D>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_3D

#ifdef GL_INT_SAMPLER_CUBE
template <>
struct GLSL2Cpp<SLDataType::IntSamplerCube>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_CUBE

#ifdef GL_INT_SAMPLER_1D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::IntSampler1DArray>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_1D_ARRAY

#ifdef GL_INT_SAMPLER_2D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::IntSampler2DArray>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_2D_ARRAY

#ifdef GL_INT_SAMPLER_CUBE_MAP_ARRAY
template <>
struct GLSL2Cpp<SLDataType::IntSamplerCubeMapArray>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_CUBE_MAP_ARRAY

#ifdef GL_INT_SAMPLER_2D_MULTISAMPLE
template <>
struct GLSL2Cpp<SLDataType::IntSampler2DMultisample>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_2D_MULTISAMPLE

#ifdef GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
template <>
struct GLSL2Cpp<SLDataType::IntSampler2DMultisampleArray>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_2D_MULTISAMPLE_ARRAY

#ifdef GL_INT_SAMPLER_BUFFER
template <>
struct GLSL2Cpp<SLDataType::IntSamplerBuffer>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_BUFFER

#ifdef GL_INT_SAMPLER_2D_RECT
template <>
struct GLSL2Cpp<SLDataType::IntSampler2DRect>
{
	typedef GLint Type;
};
#endif // INT_SAMPLER_2D_RECT

#ifdef GL_UNSIGNED_INT_SAMPLER_1D
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSampler1D>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_1D

#ifdef GL_UNSIGNED_INT_SAMPLER_2D
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSampler2D>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_2D

#ifdef GL_UNSIGNED_INT_SAMPLER_3D
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSampler3D>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_3D

#ifdef GL_UNSIGNED_INT_SAMPLER_CUBE
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSamplerCube>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_CUBE

#ifdef GL_UNSIGNED_INT_SAMPLER_1D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSampler1DArray>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_1D_ARRAY

#ifdef GL_UNSIGNED_INT_SAMPLER_2D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSampler2DArray>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_2D_ARRAY

#ifdef GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSamplerCubeMapArray>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY

#ifdef GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSampler2DMultisample>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE

#ifdef GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSampler2DMultisampleArray>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY

#ifdef GL_UNSIGNED_INT_SAMPLER_BUFFER
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSamplerBuffer>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_BUFFER

#ifdef GL_UNSIGNED_INT_SAMPLER_2D_RECT
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntSampler2DRect>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_SAMPLER_2D_RECT

#ifdef GL_IMAGE_1D
template <>
struct GLSL2Cpp<SLDataType::Image1D>
{
	typedef GLint Type;
};
#endif // IMAGE_1D

#ifdef GL_IMAGE_2D
template <>
struct GLSL2Cpp<SLDataType::Image2D>
{
	typedef GLint Type;
};
#endif // IMAGE_2D

#ifdef GL_IMAGE_3D
template <>
struct GLSL2Cpp<SLDataType::Image3D>
{
	typedef GLint Type;
};
#endif // IMAGE_3D

#ifdef GL_IMAGE_2D_RECT
template <>
struct GLSL2Cpp<SLDataType::Image2DRect>
{
	typedef GLint Type;
};
#endif // IMAGE_2D_RECT

#ifdef GL_IMAGE_CUBE
template <>
struct GLSL2Cpp<SLDataType::ImageCube>
{
	typedef GLint Type;
};
#endif // IMAGE_CUBE

#ifdef GL_IMAGE_BUFFER
template <>
struct GLSL2Cpp<SLDataType::ImageBuffer>
{
	typedef GLint Type;
};
#endif // IMAGE_BUFFER

#ifdef GL_IMAGE_1D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::Image1DArray>
{
	typedef GLint Type;
};
#endif // IMAGE_1D_ARRAY

#ifdef GL_IMAGE_2D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::Image2DArray>
{
	typedef GLint Type;
};
#endif // IMAGE_2D_ARRAY

#ifdef GL_IMAGE_2D_MULTISAMPLE
template <>
struct GLSL2Cpp<SLDataType::Image2DMultisample>
{
	typedef GLint Type;
};
#endif // IMAGE_2D_MULTISAMPLE

#ifdef GL_IMAGE_2D_MULTISAMPLE_ARRAY
template <>
struct GLSL2Cpp<SLDataType::Image2DMultisampleArray>
{
	typedef GLint Type;
};
#endif // IMAGE_2D_MULTISAMPLE_ARRAY

#ifdef GL_INT_IMAGE_1D
template <>
struct GLSL2Cpp<SLDataType::IntImage1D>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_1D

#ifdef GL_INT_IMAGE_2D
template <>
struct GLSL2Cpp<SLDataType::IntImage2D>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_2D

#ifdef GL_INT_IMAGE_3D
template <>
struct GLSL2Cpp<SLDataType::IntImage3D>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_3D

#ifdef GL_INT_IMAGE_2D_RECT
template <>
struct GLSL2Cpp<SLDataType::IntImage2DRect>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_2D_RECT

#ifdef GL_INT_IMAGE_CUBE
template <>
struct GLSL2Cpp<SLDataType::IntImageCube>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_CUBE

#ifdef GL_INT_IMAGE_BUFFER
template <>
struct GLSL2Cpp<SLDataType::IntImageBuffer>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_BUFFER

#ifdef GL_INT_IMAGE_1D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::IntImage1DArray>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_1D_ARRAY

#ifdef GL_INT_IMAGE_2D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::IntImage2DArray>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_2D_ARRAY

#ifdef GL_INT_IMAGE_2D_MULTISAMPLE
template <>
struct GLSL2Cpp<SLDataType::IntImage2DMultisample>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_2D_MULTISAMPLE

#ifdef GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY
template <>
struct GLSL2Cpp<SLDataType::IntImage2DMultisampleArray>
{
	typedef GLint Type;
};
#endif // INT_IMAGE_2D_MULTISAMPLE_ARRAY

#ifdef GL_UNSIGNED_INT_IMAGE_1D
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImage1D>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_1D

#ifdef GL_UNSIGNED_INT_IMAGE_2D
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImage2D>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_2D

#ifdef GL_UNSIGNED_INT_IMAGE_3D
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImage3D>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_3D

#ifdef GL_UNSIGNED_INT_IMAGE_2D_RECT
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImage2DRect>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_2D_RECT

#ifdef GL_UNSIGNED_INT_IMAGE_CUBE
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImageCube>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_CUBE

#ifdef GL_UNSIGNED_INT_IMAGE_BUFFER
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImageBuffer>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_BUFFER

#ifdef GL_UNSIGNED_INT_IMAGE_1D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImage1DArray>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_1D_ARRAY

#ifdef GL_UNSIGNED_INT_IMAGE_2D_ARRAY
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImage2DArray>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_2D_ARRAY

#ifdef GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImage2DMultisample>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_2D_MULTISAMPLE

#ifdef GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntImage2DMultisampleArray>
{
	typedef GLint Type;
};
#endif // UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY

#ifdef GL_UNSIGNED_INT_ATOMIC_COUNTER
template <>
struct GLSL2Cpp<SLDataType::UnsignedIntAtomicCounter>
{
	typedef GLuint Type;
};
#endif // UNSIGNED_INT_ATOMIC_COUNTER

#ifdef GL_NONE
template <>
struct GLSL2Cpp<SLDataType::None>
{
	typedef void Type;
};
#endif // NONE


