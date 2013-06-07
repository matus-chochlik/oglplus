/*
 *  .file oglplus/enums/sl_data_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/sl_data_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/data_type.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_sl_data_type(void)
{
	boost::python::enum_<oglplus::SLDataType>("SLDataType")
#if defined GL_FLOAT
# if defined Float
#  pragma push_macro("Float")
#  undef Float
	.value("Float", oglplus::SLDataType::Float)
#  pragma pop_macro("Float")
# else
	.value("Float", oglplus::SLDataType::Float)
# endif
#endif
#if defined GL_FLOAT_VEC2
# if defined FloatVec2
#  pragma push_macro("FloatVec2")
#  undef FloatVec2
	.value("FloatVec2", oglplus::SLDataType::FloatVec2)
#  pragma pop_macro("FloatVec2")
# else
	.value("FloatVec2", oglplus::SLDataType::FloatVec2)
# endif
#endif
#if defined GL_FLOAT_VEC3
# if defined FloatVec3
#  pragma push_macro("FloatVec3")
#  undef FloatVec3
	.value("FloatVec3", oglplus::SLDataType::FloatVec3)
#  pragma pop_macro("FloatVec3")
# else
	.value("FloatVec3", oglplus::SLDataType::FloatVec3)
# endif
#endif
#if defined GL_FLOAT_VEC4
# if defined FloatVec4
#  pragma push_macro("FloatVec4")
#  undef FloatVec4
	.value("FloatVec4", oglplus::SLDataType::FloatVec4)
#  pragma pop_macro("FloatVec4")
# else
	.value("FloatVec4", oglplus::SLDataType::FloatVec4)
# endif
#endif
#if defined GL_DOUBLE
# if defined Double
#  pragma push_macro("Double")
#  undef Double
	.value("Double", oglplus::SLDataType::Double)
#  pragma pop_macro("Double")
# else
	.value("Double", oglplus::SLDataType::Double)
# endif
#endif
#if defined GL_DOUBLE_VEC2
# if defined DoubleVec2
#  pragma push_macro("DoubleVec2")
#  undef DoubleVec2
	.value("DoubleVec2", oglplus::SLDataType::DoubleVec2)
#  pragma pop_macro("DoubleVec2")
# else
	.value("DoubleVec2", oglplus::SLDataType::DoubleVec2)
# endif
#endif
#if defined GL_DOUBLE_VEC3
# if defined DoubleVec3
#  pragma push_macro("DoubleVec3")
#  undef DoubleVec3
	.value("DoubleVec3", oglplus::SLDataType::DoubleVec3)
#  pragma pop_macro("DoubleVec3")
# else
	.value("DoubleVec3", oglplus::SLDataType::DoubleVec3)
# endif
#endif
#if defined GL_DOUBLE_VEC4
# if defined DoubleVec4
#  pragma push_macro("DoubleVec4")
#  undef DoubleVec4
	.value("DoubleVec4", oglplus::SLDataType::DoubleVec4)
#  pragma pop_macro("DoubleVec4")
# else
	.value("DoubleVec4", oglplus::SLDataType::DoubleVec4)
# endif
#endif
#if defined GL_INT
# if defined Int
#  pragma push_macro("Int")
#  undef Int
	.value("Int", oglplus::SLDataType::Int)
#  pragma pop_macro("Int")
# else
	.value("Int", oglplus::SLDataType::Int)
# endif
#endif
#if defined GL_INT_VEC2
# if defined IntVec2
#  pragma push_macro("IntVec2")
#  undef IntVec2
	.value("IntVec2", oglplus::SLDataType::IntVec2)
#  pragma pop_macro("IntVec2")
# else
	.value("IntVec2", oglplus::SLDataType::IntVec2)
# endif
#endif
#if defined GL_INT_VEC3
# if defined IntVec3
#  pragma push_macro("IntVec3")
#  undef IntVec3
	.value("IntVec3", oglplus::SLDataType::IntVec3)
#  pragma pop_macro("IntVec3")
# else
	.value("IntVec3", oglplus::SLDataType::IntVec3)
# endif
#endif
#if defined GL_INT_VEC4
# if defined IntVec4
#  pragma push_macro("IntVec4")
#  undef IntVec4
	.value("IntVec4", oglplus::SLDataType::IntVec4)
#  pragma pop_macro("IntVec4")
# else
	.value("IntVec4", oglplus::SLDataType::IntVec4)
# endif
#endif
#if defined GL_UNSIGNED_INT
# if defined UnsignedInt
#  pragma push_macro("UnsignedInt")
#  undef UnsignedInt
	.value("UnsignedInt", oglplus::SLDataType::UnsignedInt)
#  pragma pop_macro("UnsignedInt")
# else
	.value("UnsignedInt", oglplus::SLDataType::UnsignedInt)
# endif
#endif
#if defined GL_UNSIGNED_INT_VEC2
# if defined UnsignedIntVec2
#  pragma push_macro("UnsignedIntVec2")
#  undef UnsignedIntVec2
	.value("UnsignedIntVec2", oglplus::SLDataType::UnsignedIntVec2)
#  pragma pop_macro("UnsignedIntVec2")
# else
	.value("UnsignedIntVec2", oglplus::SLDataType::UnsignedIntVec2)
# endif
#endif
#if defined GL_UNSIGNED_INT_VEC3
# if defined UnsignedIntVec3
#  pragma push_macro("UnsignedIntVec3")
#  undef UnsignedIntVec3
	.value("UnsignedIntVec3", oglplus::SLDataType::UnsignedIntVec3)
#  pragma pop_macro("UnsignedIntVec3")
# else
	.value("UnsignedIntVec3", oglplus::SLDataType::UnsignedIntVec3)
# endif
#endif
#if defined GL_UNSIGNED_INT_VEC4
# if defined UnsignedIntVec4
#  pragma push_macro("UnsignedIntVec4")
#  undef UnsignedIntVec4
	.value("UnsignedIntVec4", oglplus::SLDataType::UnsignedIntVec4)
#  pragma pop_macro("UnsignedIntVec4")
# else
	.value("UnsignedIntVec4", oglplus::SLDataType::UnsignedIntVec4)
# endif
#endif
#if defined GL_BOOL
# if defined Bool
#  pragma push_macro("Bool")
#  undef Bool
	.value("Bool", oglplus::SLDataType::Bool)
#  pragma pop_macro("Bool")
# else
	.value("Bool", oglplus::SLDataType::Bool)
# endif
#endif
#if defined GL_BOOL_VEC2
# if defined BoolVec2
#  pragma push_macro("BoolVec2")
#  undef BoolVec2
	.value("BoolVec2", oglplus::SLDataType::BoolVec2)
#  pragma pop_macro("BoolVec2")
# else
	.value("BoolVec2", oglplus::SLDataType::BoolVec2)
# endif
#endif
#if defined GL_BOOL_VEC3
# if defined BoolVec3
#  pragma push_macro("BoolVec3")
#  undef BoolVec3
	.value("BoolVec3", oglplus::SLDataType::BoolVec3)
#  pragma pop_macro("BoolVec3")
# else
	.value("BoolVec3", oglplus::SLDataType::BoolVec3)
# endif
#endif
#if defined GL_BOOL_VEC4
# if defined BoolVec4
#  pragma push_macro("BoolVec4")
#  undef BoolVec4
	.value("BoolVec4", oglplus::SLDataType::BoolVec4)
#  pragma pop_macro("BoolVec4")
# else
	.value("BoolVec4", oglplus::SLDataType::BoolVec4)
# endif
#endif
#if defined GL_FLOAT_MAT2
# if defined FloatMat2
#  pragma push_macro("FloatMat2")
#  undef FloatMat2
	.value("FloatMat2", oglplus::SLDataType::FloatMat2)
#  pragma pop_macro("FloatMat2")
# else
	.value("FloatMat2", oglplus::SLDataType::FloatMat2)
# endif
#endif
#if defined GL_FLOAT_MAT3
# if defined FloatMat3
#  pragma push_macro("FloatMat3")
#  undef FloatMat3
	.value("FloatMat3", oglplus::SLDataType::FloatMat3)
#  pragma pop_macro("FloatMat3")
# else
	.value("FloatMat3", oglplus::SLDataType::FloatMat3)
# endif
#endif
#if defined GL_FLOAT_MAT4
# if defined FloatMat4
#  pragma push_macro("FloatMat4")
#  undef FloatMat4
	.value("FloatMat4", oglplus::SLDataType::FloatMat4)
#  pragma pop_macro("FloatMat4")
# else
	.value("FloatMat4", oglplus::SLDataType::FloatMat4)
# endif
#endif
#if defined GL_FLOAT_MAT2x3
# if defined FloatMat2x3
#  pragma push_macro("FloatMat2x3")
#  undef FloatMat2x3
	.value("FloatMat2x3", oglplus::SLDataType::FloatMat2x3)
#  pragma pop_macro("FloatMat2x3")
# else
	.value("FloatMat2x3", oglplus::SLDataType::FloatMat2x3)
# endif
#endif
#if defined GL_FLOAT_MAT2x4
# if defined FloatMat2x4
#  pragma push_macro("FloatMat2x4")
#  undef FloatMat2x4
	.value("FloatMat2x4", oglplus::SLDataType::FloatMat2x4)
#  pragma pop_macro("FloatMat2x4")
# else
	.value("FloatMat2x4", oglplus::SLDataType::FloatMat2x4)
# endif
#endif
#if defined GL_FLOAT_MAT3x2
# if defined FloatMat3x2
#  pragma push_macro("FloatMat3x2")
#  undef FloatMat3x2
	.value("FloatMat3x2", oglplus::SLDataType::FloatMat3x2)
#  pragma pop_macro("FloatMat3x2")
# else
	.value("FloatMat3x2", oglplus::SLDataType::FloatMat3x2)
# endif
#endif
#if defined GL_FLOAT_MAT3x4
# if defined FloatMat3x4
#  pragma push_macro("FloatMat3x4")
#  undef FloatMat3x4
	.value("FloatMat3x4", oglplus::SLDataType::FloatMat3x4)
#  pragma pop_macro("FloatMat3x4")
# else
	.value("FloatMat3x4", oglplus::SLDataType::FloatMat3x4)
# endif
#endif
#if defined GL_FLOAT_MAT4x2
# if defined FloatMat4x2
#  pragma push_macro("FloatMat4x2")
#  undef FloatMat4x2
	.value("FloatMat4x2", oglplus::SLDataType::FloatMat4x2)
#  pragma pop_macro("FloatMat4x2")
# else
	.value("FloatMat4x2", oglplus::SLDataType::FloatMat4x2)
# endif
#endif
#if defined GL_FLOAT_MAT4x3
# if defined FloatMat4x3
#  pragma push_macro("FloatMat4x3")
#  undef FloatMat4x3
	.value("FloatMat4x3", oglplus::SLDataType::FloatMat4x3)
#  pragma pop_macro("FloatMat4x3")
# else
	.value("FloatMat4x3", oglplus::SLDataType::FloatMat4x3)
# endif
#endif
#if defined GL_DOUBLE_MAT2
# if defined DoubleMat2
#  pragma push_macro("DoubleMat2")
#  undef DoubleMat2
	.value("DoubleMat2", oglplus::SLDataType::DoubleMat2)
#  pragma pop_macro("DoubleMat2")
# else
	.value("DoubleMat2", oglplus::SLDataType::DoubleMat2)
# endif
#endif
#if defined GL_DOUBLE_MAT3
# if defined DoubleMat3
#  pragma push_macro("DoubleMat3")
#  undef DoubleMat3
	.value("DoubleMat3", oglplus::SLDataType::DoubleMat3)
#  pragma pop_macro("DoubleMat3")
# else
	.value("DoubleMat3", oglplus::SLDataType::DoubleMat3)
# endif
#endif
#if defined GL_DOUBLE_MAT4
# if defined DoubleMat4
#  pragma push_macro("DoubleMat4")
#  undef DoubleMat4
	.value("DoubleMat4", oglplus::SLDataType::DoubleMat4)
#  pragma pop_macro("DoubleMat4")
# else
	.value("DoubleMat4", oglplus::SLDataType::DoubleMat4)
# endif
#endif
#if defined GL_DOUBLE_MAT2x3
# if defined DoubleMat2x3
#  pragma push_macro("DoubleMat2x3")
#  undef DoubleMat2x3
	.value("DoubleMat2x3", oglplus::SLDataType::DoubleMat2x3)
#  pragma pop_macro("DoubleMat2x3")
# else
	.value("DoubleMat2x3", oglplus::SLDataType::DoubleMat2x3)
# endif
#endif
#if defined GL_DOUBLE_MAT2x4
# if defined DoubleMat2x4
#  pragma push_macro("DoubleMat2x4")
#  undef DoubleMat2x4
	.value("DoubleMat2x4", oglplus::SLDataType::DoubleMat2x4)
#  pragma pop_macro("DoubleMat2x4")
# else
	.value("DoubleMat2x4", oglplus::SLDataType::DoubleMat2x4)
# endif
#endif
#if defined GL_DOUBLE_MAT3x2
# if defined DoubleMat3x2
#  pragma push_macro("DoubleMat3x2")
#  undef DoubleMat3x2
	.value("DoubleMat3x2", oglplus::SLDataType::DoubleMat3x2)
#  pragma pop_macro("DoubleMat3x2")
# else
	.value("DoubleMat3x2", oglplus::SLDataType::DoubleMat3x2)
# endif
#endif
#if defined GL_DOUBLE_MAT3x4
# if defined DoubleMat3x4
#  pragma push_macro("DoubleMat3x4")
#  undef DoubleMat3x4
	.value("DoubleMat3x4", oglplus::SLDataType::DoubleMat3x4)
#  pragma pop_macro("DoubleMat3x4")
# else
	.value("DoubleMat3x4", oglplus::SLDataType::DoubleMat3x4)
# endif
#endif
#if defined GL_DOUBLE_MAT4x2
# if defined DoubleMat4x2
#  pragma push_macro("DoubleMat4x2")
#  undef DoubleMat4x2
	.value("DoubleMat4x2", oglplus::SLDataType::DoubleMat4x2)
#  pragma pop_macro("DoubleMat4x2")
# else
	.value("DoubleMat4x2", oglplus::SLDataType::DoubleMat4x2)
# endif
#endif
#if defined GL_DOUBLE_MAT4x3
# if defined DoubleMat4x3
#  pragma push_macro("DoubleMat4x3")
#  undef DoubleMat4x3
	.value("DoubleMat4x3", oglplus::SLDataType::DoubleMat4x3)
#  pragma pop_macro("DoubleMat4x3")
# else
	.value("DoubleMat4x3", oglplus::SLDataType::DoubleMat4x3)
# endif
#endif
#if defined GL_SAMPLER_1D
# if defined Sampler1D
#  pragma push_macro("Sampler1D")
#  undef Sampler1D
	.value("Sampler1D", oglplus::SLDataType::Sampler1D)
#  pragma pop_macro("Sampler1D")
# else
	.value("Sampler1D", oglplus::SLDataType::Sampler1D)
# endif
#endif
#if defined GL_SAMPLER_2D
# if defined Sampler2D
#  pragma push_macro("Sampler2D")
#  undef Sampler2D
	.value("Sampler2D", oglplus::SLDataType::Sampler2D)
#  pragma pop_macro("Sampler2D")
# else
	.value("Sampler2D", oglplus::SLDataType::Sampler2D)
# endif
#endif
#if defined GL_SAMPLER_3D
# if defined Sampler3D
#  pragma push_macro("Sampler3D")
#  undef Sampler3D
	.value("Sampler3D", oglplus::SLDataType::Sampler3D)
#  pragma pop_macro("Sampler3D")
# else
	.value("Sampler3D", oglplus::SLDataType::Sampler3D)
# endif
#endif
#if defined GL_SAMPLER_CUBE
# if defined SamplerCube
#  pragma push_macro("SamplerCube")
#  undef SamplerCube
	.value("SamplerCube", oglplus::SLDataType::SamplerCube)
#  pragma pop_macro("SamplerCube")
# else
	.value("SamplerCube", oglplus::SLDataType::SamplerCube)
# endif
#endif
#if defined GL_SAMPLER_1D_SHADOW
# if defined Sampler1DShadow
#  pragma push_macro("Sampler1DShadow")
#  undef Sampler1DShadow
	.value("Sampler1DShadow", oglplus::SLDataType::Sampler1DShadow)
#  pragma pop_macro("Sampler1DShadow")
# else
	.value("Sampler1DShadow", oglplus::SLDataType::Sampler1DShadow)
# endif
#endif
#if defined GL_SAMPLER_2D_SHADOW
# if defined Sampler2DShadow
#  pragma push_macro("Sampler2DShadow")
#  undef Sampler2DShadow
	.value("Sampler2DShadow", oglplus::SLDataType::Sampler2DShadow)
#  pragma pop_macro("Sampler2DShadow")
# else
	.value("Sampler2DShadow", oglplus::SLDataType::Sampler2DShadow)
# endif
#endif
#if defined GL_SAMPLER_1D_ARRAY
# if defined Sampler1DArray
#  pragma push_macro("Sampler1DArray")
#  undef Sampler1DArray
	.value("Sampler1DArray", oglplus::SLDataType::Sampler1DArray)
#  pragma pop_macro("Sampler1DArray")
# else
	.value("Sampler1DArray", oglplus::SLDataType::Sampler1DArray)
# endif
#endif
#if defined GL_SAMPLER_2D_ARRAY
# if defined Sampler2DArray
#  pragma push_macro("Sampler2DArray")
#  undef Sampler2DArray
	.value("Sampler2DArray", oglplus::SLDataType::Sampler2DArray)
#  pragma pop_macro("Sampler2DArray")
# else
	.value("Sampler2DArray", oglplus::SLDataType::Sampler2DArray)
# endif
#endif
#if defined GL_SAMPLER_CUBE_MAP_ARRAY
# if defined SamplerCubeMapArray
#  pragma push_macro("SamplerCubeMapArray")
#  undef SamplerCubeMapArray
	.value("SamplerCubeMapArray", oglplus::SLDataType::SamplerCubeMapArray)
#  pragma pop_macro("SamplerCubeMapArray")
# else
	.value("SamplerCubeMapArray", oglplus::SLDataType::SamplerCubeMapArray)
# endif
#endif
#if defined GL_SAMPLER_1D_ARRAY_SHADOW
# if defined Sampler1DArrayShadow
#  pragma push_macro("Sampler1DArrayShadow")
#  undef Sampler1DArrayShadow
	.value("Sampler1DArrayShadow", oglplus::SLDataType::Sampler1DArrayShadow)
#  pragma pop_macro("Sampler1DArrayShadow")
# else
	.value("Sampler1DArrayShadow", oglplus::SLDataType::Sampler1DArrayShadow)
# endif
#endif
#if defined GL_SAMPLER_2D_ARRAY_SHADOW
# if defined Sampler2DArrayShadow
#  pragma push_macro("Sampler2DArrayShadow")
#  undef Sampler2DArrayShadow
	.value("Sampler2DArrayShadow", oglplus::SLDataType::Sampler2DArrayShadow)
#  pragma pop_macro("Sampler2DArrayShadow")
# else
	.value("Sampler2DArrayShadow", oglplus::SLDataType::Sampler2DArrayShadow)
# endif
#endif
#if defined GL_SAMPLER_2D_MULTISAMPLE
# if defined Sampler2DMultisample
#  pragma push_macro("Sampler2DMultisample")
#  undef Sampler2DMultisample
	.value("Sampler2DMultisample", oglplus::SLDataType::Sampler2DMultisample)
#  pragma pop_macro("Sampler2DMultisample")
# else
	.value("Sampler2DMultisample", oglplus::SLDataType::Sampler2DMultisample)
# endif
#endif
#if defined GL_SAMPLER_2D_MULTISAMPLE_ARRAY
# if defined Sampler2DMultisampleArray
#  pragma push_macro("Sampler2DMultisampleArray")
#  undef Sampler2DMultisampleArray
	.value("Sampler2DMultisampleArray", oglplus::SLDataType::Sampler2DMultisampleArray)
#  pragma pop_macro("Sampler2DMultisampleArray")
# else
	.value("Sampler2DMultisampleArray", oglplus::SLDataType::Sampler2DMultisampleArray)
# endif
#endif
#if defined GL_SAMPLER_CUBE_SHADOW
# if defined SamplerCubeShadow
#  pragma push_macro("SamplerCubeShadow")
#  undef SamplerCubeShadow
	.value("SamplerCubeShadow", oglplus::SLDataType::SamplerCubeShadow)
#  pragma pop_macro("SamplerCubeShadow")
# else
	.value("SamplerCubeShadow", oglplus::SLDataType::SamplerCubeShadow)
# endif
#endif
#if defined GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW
# if defined SamplerCubeMapArrayShadow
#  pragma push_macro("SamplerCubeMapArrayShadow")
#  undef SamplerCubeMapArrayShadow
	.value("SamplerCubeMapArrayShadow", oglplus::SLDataType::SamplerCubeMapArrayShadow)
#  pragma pop_macro("SamplerCubeMapArrayShadow")
# else
	.value("SamplerCubeMapArrayShadow", oglplus::SLDataType::SamplerCubeMapArrayShadow)
# endif
#endif
#if defined GL_SAMPLER_BUFFER
# if defined SamplerBuffer
#  pragma push_macro("SamplerBuffer")
#  undef SamplerBuffer
	.value("SamplerBuffer", oglplus::SLDataType::SamplerBuffer)
#  pragma pop_macro("SamplerBuffer")
# else
	.value("SamplerBuffer", oglplus::SLDataType::SamplerBuffer)
# endif
#endif
#if defined GL_SAMPLER_2D_RECT
# if defined Sampler2DRect
#  pragma push_macro("Sampler2DRect")
#  undef Sampler2DRect
	.value("Sampler2DRect", oglplus::SLDataType::Sampler2DRect)
#  pragma pop_macro("Sampler2DRect")
# else
	.value("Sampler2DRect", oglplus::SLDataType::Sampler2DRect)
# endif
#endif
#if defined GL_SAMPLER_2D_RECT_SHADOW
# if defined Sampler2DRectShadow
#  pragma push_macro("Sampler2DRectShadow")
#  undef Sampler2DRectShadow
	.value("Sampler2DRectShadow", oglplus::SLDataType::Sampler2DRectShadow)
#  pragma pop_macro("Sampler2DRectShadow")
# else
	.value("Sampler2DRectShadow", oglplus::SLDataType::Sampler2DRectShadow)
# endif
#endif
#if defined GL_INT_SAMPLER_1D
# if defined IntSampler1D
#  pragma push_macro("IntSampler1D")
#  undef IntSampler1D
	.value("IntSampler1D", oglplus::SLDataType::IntSampler1D)
#  pragma pop_macro("IntSampler1D")
# else
	.value("IntSampler1D", oglplus::SLDataType::IntSampler1D)
# endif
#endif
#if defined GL_INT_SAMPLER_2D
# if defined IntSampler2D
#  pragma push_macro("IntSampler2D")
#  undef IntSampler2D
	.value("IntSampler2D", oglplus::SLDataType::IntSampler2D)
#  pragma pop_macro("IntSampler2D")
# else
	.value("IntSampler2D", oglplus::SLDataType::IntSampler2D)
# endif
#endif
#if defined GL_INT_SAMPLER_3D
# if defined IntSampler3D
#  pragma push_macro("IntSampler3D")
#  undef IntSampler3D
	.value("IntSampler3D", oglplus::SLDataType::IntSampler3D)
#  pragma pop_macro("IntSampler3D")
# else
	.value("IntSampler3D", oglplus::SLDataType::IntSampler3D)
# endif
#endif
#if defined GL_INT_SAMPLER_CUBE
# if defined IntSamplerCube
#  pragma push_macro("IntSamplerCube")
#  undef IntSamplerCube
	.value("IntSamplerCube", oglplus::SLDataType::IntSamplerCube)
#  pragma pop_macro("IntSamplerCube")
# else
	.value("IntSamplerCube", oglplus::SLDataType::IntSamplerCube)
# endif
#endif
#if defined GL_INT_SAMPLER_1D_ARRAY
# if defined IntSampler1DArray
#  pragma push_macro("IntSampler1DArray")
#  undef IntSampler1DArray
	.value("IntSampler1DArray", oglplus::SLDataType::IntSampler1DArray)
#  pragma pop_macro("IntSampler1DArray")
# else
	.value("IntSampler1DArray", oglplus::SLDataType::IntSampler1DArray)
# endif
#endif
#if defined GL_INT_SAMPLER_2D_ARRAY
# if defined IntSampler2DArray
#  pragma push_macro("IntSampler2DArray")
#  undef IntSampler2DArray
	.value("IntSampler2DArray", oglplus::SLDataType::IntSampler2DArray)
#  pragma pop_macro("IntSampler2DArray")
# else
	.value("IntSampler2DArray", oglplus::SLDataType::IntSampler2DArray)
# endif
#endif
#if defined GL_INT_SAMPLER_CUBE_MAP_ARRAY
# if defined IntSamplerCubeMapArray
#  pragma push_macro("IntSamplerCubeMapArray")
#  undef IntSamplerCubeMapArray
	.value("IntSamplerCubeMapArray", oglplus::SLDataType::IntSamplerCubeMapArray)
#  pragma pop_macro("IntSamplerCubeMapArray")
# else
	.value("IntSamplerCubeMapArray", oglplus::SLDataType::IntSamplerCubeMapArray)
# endif
#endif
#if defined GL_INT_SAMPLER_2D_MULTISAMPLE
# if defined IntSampler2DMultisample
#  pragma push_macro("IntSampler2DMultisample")
#  undef IntSampler2DMultisample
	.value("IntSampler2DMultisample", oglplus::SLDataType::IntSampler2DMultisample)
#  pragma pop_macro("IntSampler2DMultisample")
# else
	.value("IntSampler2DMultisample", oglplus::SLDataType::IntSampler2DMultisample)
# endif
#endif
#if defined GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
# if defined IntSampler2DMultisampleArray
#  pragma push_macro("IntSampler2DMultisampleArray")
#  undef IntSampler2DMultisampleArray
	.value("IntSampler2DMultisampleArray", oglplus::SLDataType::IntSampler2DMultisampleArray)
#  pragma pop_macro("IntSampler2DMultisampleArray")
# else
	.value("IntSampler2DMultisampleArray", oglplus::SLDataType::IntSampler2DMultisampleArray)
# endif
#endif
#if defined GL_INT_SAMPLER_BUFFER
# if defined IntSamplerBuffer
#  pragma push_macro("IntSamplerBuffer")
#  undef IntSamplerBuffer
	.value("IntSamplerBuffer", oglplus::SLDataType::IntSamplerBuffer)
#  pragma pop_macro("IntSamplerBuffer")
# else
	.value("IntSamplerBuffer", oglplus::SLDataType::IntSamplerBuffer)
# endif
#endif
#if defined GL_INT_SAMPLER_2D_RECT
# if defined IntSampler2DRect
#  pragma push_macro("IntSampler2DRect")
#  undef IntSampler2DRect
	.value("IntSampler2DRect", oglplus::SLDataType::IntSampler2DRect)
#  pragma pop_macro("IntSampler2DRect")
# else
	.value("IntSampler2DRect", oglplus::SLDataType::IntSampler2DRect)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_1D
# if defined UnsignedIntSampler1D
#  pragma push_macro("UnsignedIntSampler1D")
#  undef UnsignedIntSampler1D
	.value("UnsignedIntSampler1D", oglplus::SLDataType::UnsignedIntSampler1D)
#  pragma pop_macro("UnsignedIntSampler1D")
# else
	.value("UnsignedIntSampler1D", oglplus::SLDataType::UnsignedIntSampler1D)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D
# if defined UnsignedIntSampler2D
#  pragma push_macro("UnsignedIntSampler2D")
#  undef UnsignedIntSampler2D
	.value("UnsignedIntSampler2D", oglplus::SLDataType::UnsignedIntSampler2D)
#  pragma pop_macro("UnsignedIntSampler2D")
# else
	.value("UnsignedIntSampler2D", oglplus::SLDataType::UnsignedIntSampler2D)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_3D
# if defined UnsignedIntSampler3D
#  pragma push_macro("UnsignedIntSampler3D")
#  undef UnsignedIntSampler3D
	.value("UnsignedIntSampler3D", oglplus::SLDataType::UnsignedIntSampler3D)
#  pragma pop_macro("UnsignedIntSampler3D")
# else
	.value("UnsignedIntSampler3D", oglplus::SLDataType::UnsignedIntSampler3D)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_CUBE
# if defined UnsignedIntSamplerCube
#  pragma push_macro("UnsignedIntSamplerCube")
#  undef UnsignedIntSamplerCube
	.value("UnsignedIntSamplerCube", oglplus::SLDataType::UnsignedIntSamplerCube)
#  pragma pop_macro("UnsignedIntSamplerCube")
# else
	.value("UnsignedIntSamplerCube", oglplus::SLDataType::UnsignedIntSamplerCube)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_1D_ARRAY
# if defined UnsignedIntSampler1DArray
#  pragma push_macro("UnsignedIntSampler1DArray")
#  undef UnsignedIntSampler1DArray
	.value("UnsignedIntSampler1DArray", oglplus::SLDataType::UnsignedIntSampler1DArray)
#  pragma pop_macro("UnsignedIntSampler1DArray")
# else
	.value("UnsignedIntSampler1DArray", oglplus::SLDataType::UnsignedIntSampler1DArray)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_ARRAY
# if defined UnsignedIntSampler2DArray
#  pragma push_macro("UnsignedIntSampler2DArray")
#  undef UnsignedIntSampler2DArray
	.value("UnsignedIntSampler2DArray", oglplus::SLDataType::UnsignedIntSampler2DArray)
#  pragma pop_macro("UnsignedIntSampler2DArray")
# else
	.value("UnsignedIntSampler2DArray", oglplus::SLDataType::UnsignedIntSampler2DArray)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY
# if defined UnsignedIntSamplerCubeMapArray
#  pragma push_macro("UnsignedIntSamplerCubeMapArray")
#  undef UnsignedIntSamplerCubeMapArray
	.value("UnsignedIntSamplerCubeMapArray", oglplus::SLDataType::UnsignedIntSamplerCubeMapArray)
#  pragma pop_macro("UnsignedIntSamplerCubeMapArray")
# else
	.value("UnsignedIntSamplerCubeMapArray", oglplus::SLDataType::UnsignedIntSamplerCubeMapArray)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE
# if defined UnsignedIntSampler2DMultisample
#  pragma push_macro("UnsignedIntSampler2DMultisample")
#  undef UnsignedIntSampler2DMultisample
	.value("UnsignedIntSampler2DMultisample", oglplus::SLDataType::UnsignedIntSampler2DMultisample)
#  pragma pop_macro("UnsignedIntSampler2DMultisample")
# else
	.value("UnsignedIntSampler2DMultisample", oglplus::SLDataType::UnsignedIntSampler2DMultisample)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
# if defined UnsignedIntSampler2DMultisampleArray
#  pragma push_macro("UnsignedIntSampler2DMultisampleArray")
#  undef UnsignedIntSampler2DMultisampleArray
	.value("UnsignedIntSampler2DMultisampleArray", oglplus::SLDataType::UnsignedIntSampler2DMultisampleArray)
#  pragma pop_macro("UnsignedIntSampler2DMultisampleArray")
# else
	.value("UnsignedIntSampler2DMultisampleArray", oglplus::SLDataType::UnsignedIntSampler2DMultisampleArray)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_BUFFER
# if defined UnsignedIntSamplerBuffer
#  pragma push_macro("UnsignedIntSamplerBuffer")
#  undef UnsignedIntSamplerBuffer
	.value("UnsignedIntSamplerBuffer", oglplus::SLDataType::UnsignedIntSamplerBuffer)
#  pragma pop_macro("UnsignedIntSamplerBuffer")
# else
	.value("UnsignedIntSamplerBuffer", oglplus::SLDataType::UnsignedIntSamplerBuffer)
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_RECT
# if defined UnsignedIntSampler2DRect
#  pragma push_macro("UnsignedIntSampler2DRect")
#  undef UnsignedIntSampler2DRect
	.value("UnsignedIntSampler2DRect", oglplus::SLDataType::UnsignedIntSampler2DRect)
#  pragma pop_macro("UnsignedIntSampler2DRect")
# else
	.value("UnsignedIntSampler2DRect", oglplus::SLDataType::UnsignedIntSampler2DRect)
# endif
#endif
#if defined GL_IMAGE_1D
# if defined Image1D
#  pragma push_macro("Image1D")
#  undef Image1D
	.value("Image1D", oglplus::SLDataType::Image1D)
#  pragma pop_macro("Image1D")
# else
	.value("Image1D", oglplus::SLDataType::Image1D)
# endif
#endif
#if defined GL_IMAGE_2D
# if defined Image2D
#  pragma push_macro("Image2D")
#  undef Image2D
	.value("Image2D", oglplus::SLDataType::Image2D)
#  pragma pop_macro("Image2D")
# else
	.value("Image2D", oglplus::SLDataType::Image2D)
# endif
#endif
#if defined GL_IMAGE_3D
# if defined Image3D
#  pragma push_macro("Image3D")
#  undef Image3D
	.value("Image3D", oglplus::SLDataType::Image3D)
#  pragma pop_macro("Image3D")
# else
	.value("Image3D", oglplus::SLDataType::Image3D)
# endif
#endif
#if defined GL_IMAGE_2D_RECT
# if defined Image2DRect
#  pragma push_macro("Image2DRect")
#  undef Image2DRect
	.value("Image2DRect", oglplus::SLDataType::Image2DRect)
#  pragma pop_macro("Image2DRect")
# else
	.value("Image2DRect", oglplus::SLDataType::Image2DRect)
# endif
#endif
#if defined GL_IMAGE_CUBE
# if defined ImageCube
#  pragma push_macro("ImageCube")
#  undef ImageCube
	.value("ImageCube", oglplus::SLDataType::ImageCube)
#  pragma pop_macro("ImageCube")
# else
	.value("ImageCube", oglplus::SLDataType::ImageCube)
# endif
#endif
#if defined GL_IMAGE_BUFFER
# if defined ImageBuffer
#  pragma push_macro("ImageBuffer")
#  undef ImageBuffer
	.value("ImageBuffer", oglplus::SLDataType::ImageBuffer)
#  pragma pop_macro("ImageBuffer")
# else
	.value("ImageBuffer", oglplus::SLDataType::ImageBuffer)
# endif
#endif
#if defined GL_IMAGE_1D_ARRAY
# if defined Image1DArray
#  pragma push_macro("Image1DArray")
#  undef Image1DArray
	.value("Image1DArray", oglplus::SLDataType::Image1DArray)
#  pragma pop_macro("Image1DArray")
# else
	.value("Image1DArray", oglplus::SLDataType::Image1DArray)
# endif
#endif
#if defined GL_IMAGE_2D_ARRAY
# if defined Image2DArray
#  pragma push_macro("Image2DArray")
#  undef Image2DArray
	.value("Image2DArray", oglplus::SLDataType::Image2DArray)
#  pragma pop_macro("Image2DArray")
# else
	.value("Image2DArray", oglplus::SLDataType::Image2DArray)
# endif
#endif
#if defined GL_IMAGE_2D_MULTISAMPLE
# if defined Image2DMultisample
#  pragma push_macro("Image2DMultisample")
#  undef Image2DMultisample
	.value("Image2DMultisample", oglplus::SLDataType::Image2DMultisample)
#  pragma pop_macro("Image2DMultisample")
# else
	.value("Image2DMultisample", oglplus::SLDataType::Image2DMultisample)
# endif
#endif
#if defined GL_IMAGE_2D_MULTISAMPLE_ARRAY
# if defined Image2DMultisampleArray
#  pragma push_macro("Image2DMultisampleArray")
#  undef Image2DMultisampleArray
	.value("Image2DMultisampleArray", oglplus::SLDataType::Image2DMultisampleArray)
#  pragma pop_macro("Image2DMultisampleArray")
# else
	.value("Image2DMultisampleArray", oglplus::SLDataType::Image2DMultisampleArray)
# endif
#endif
#if defined GL_INT_IMAGE_1D
# if defined IntImage1D
#  pragma push_macro("IntImage1D")
#  undef IntImage1D
	.value("IntImage1D", oglplus::SLDataType::IntImage1D)
#  pragma pop_macro("IntImage1D")
# else
	.value("IntImage1D", oglplus::SLDataType::IntImage1D)
# endif
#endif
#if defined GL_INT_IMAGE_2D
# if defined IntImage2D
#  pragma push_macro("IntImage2D")
#  undef IntImage2D
	.value("IntImage2D", oglplus::SLDataType::IntImage2D)
#  pragma pop_macro("IntImage2D")
# else
	.value("IntImage2D", oglplus::SLDataType::IntImage2D)
# endif
#endif
#if defined GL_INT_IMAGE_3D
# if defined IntImage3D
#  pragma push_macro("IntImage3D")
#  undef IntImage3D
	.value("IntImage3D", oglplus::SLDataType::IntImage3D)
#  pragma pop_macro("IntImage3D")
# else
	.value("IntImage3D", oglplus::SLDataType::IntImage3D)
# endif
#endif
#if defined GL_INT_IMAGE_2D_RECT
# if defined IntImage2DRect
#  pragma push_macro("IntImage2DRect")
#  undef IntImage2DRect
	.value("IntImage2DRect", oglplus::SLDataType::IntImage2DRect)
#  pragma pop_macro("IntImage2DRect")
# else
	.value("IntImage2DRect", oglplus::SLDataType::IntImage2DRect)
# endif
#endif
#if defined GL_INT_IMAGE_CUBE
# if defined IntImageCube
#  pragma push_macro("IntImageCube")
#  undef IntImageCube
	.value("IntImageCube", oglplus::SLDataType::IntImageCube)
#  pragma pop_macro("IntImageCube")
# else
	.value("IntImageCube", oglplus::SLDataType::IntImageCube)
# endif
#endif
#if defined GL_INT_IMAGE_BUFFER
# if defined IntImageBuffer
#  pragma push_macro("IntImageBuffer")
#  undef IntImageBuffer
	.value("IntImageBuffer", oglplus::SLDataType::IntImageBuffer)
#  pragma pop_macro("IntImageBuffer")
# else
	.value("IntImageBuffer", oglplus::SLDataType::IntImageBuffer)
# endif
#endif
#if defined GL_INT_IMAGE_1D_ARRAY
# if defined IntImage1DArray
#  pragma push_macro("IntImage1DArray")
#  undef IntImage1DArray
	.value("IntImage1DArray", oglplus::SLDataType::IntImage1DArray)
#  pragma pop_macro("IntImage1DArray")
# else
	.value("IntImage1DArray", oglplus::SLDataType::IntImage1DArray)
# endif
#endif
#if defined GL_INT_IMAGE_2D_ARRAY
# if defined IntImage2DArray
#  pragma push_macro("IntImage2DArray")
#  undef IntImage2DArray
	.value("IntImage2DArray", oglplus::SLDataType::IntImage2DArray)
#  pragma pop_macro("IntImage2DArray")
# else
	.value("IntImage2DArray", oglplus::SLDataType::IntImage2DArray)
# endif
#endif
#if defined GL_INT_IMAGE_2D_MULTISAMPLE
# if defined IntImage2DMultisample
#  pragma push_macro("IntImage2DMultisample")
#  undef IntImage2DMultisample
	.value("IntImage2DMultisample", oglplus::SLDataType::IntImage2DMultisample)
#  pragma pop_macro("IntImage2DMultisample")
# else
	.value("IntImage2DMultisample", oglplus::SLDataType::IntImage2DMultisample)
# endif
#endif
#if defined GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY
# if defined IntImage2DMultisampleArray
#  pragma push_macro("IntImage2DMultisampleArray")
#  undef IntImage2DMultisampleArray
	.value("IntImage2DMultisampleArray", oglplus::SLDataType::IntImage2DMultisampleArray)
#  pragma pop_macro("IntImage2DMultisampleArray")
# else
	.value("IntImage2DMultisampleArray", oglplus::SLDataType::IntImage2DMultisampleArray)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_1D
# if defined UnsignedIntImage1D
#  pragma push_macro("UnsignedIntImage1D")
#  undef UnsignedIntImage1D
	.value("UnsignedIntImage1D", oglplus::SLDataType::UnsignedIntImage1D)
#  pragma pop_macro("UnsignedIntImage1D")
# else
	.value("UnsignedIntImage1D", oglplus::SLDataType::UnsignedIntImage1D)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D
# if defined UnsignedIntImage2D
#  pragma push_macro("UnsignedIntImage2D")
#  undef UnsignedIntImage2D
	.value("UnsignedIntImage2D", oglplus::SLDataType::UnsignedIntImage2D)
#  pragma pop_macro("UnsignedIntImage2D")
# else
	.value("UnsignedIntImage2D", oglplus::SLDataType::UnsignedIntImage2D)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_3D
# if defined UnsignedIntImage3D
#  pragma push_macro("UnsignedIntImage3D")
#  undef UnsignedIntImage3D
	.value("UnsignedIntImage3D", oglplus::SLDataType::UnsignedIntImage3D)
#  pragma pop_macro("UnsignedIntImage3D")
# else
	.value("UnsignedIntImage3D", oglplus::SLDataType::UnsignedIntImage3D)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D_RECT
# if defined UnsignedIntImage2DRect
#  pragma push_macro("UnsignedIntImage2DRect")
#  undef UnsignedIntImage2DRect
	.value("UnsignedIntImage2DRect", oglplus::SLDataType::UnsignedIntImage2DRect)
#  pragma pop_macro("UnsignedIntImage2DRect")
# else
	.value("UnsignedIntImage2DRect", oglplus::SLDataType::UnsignedIntImage2DRect)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_CUBE
# if defined UnsignedIntImageCube
#  pragma push_macro("UnsignedIntImageCube")
#  undef UnsignedIntImageCube
	.value("UnsignedIntImageCube", oglplus::SLDataType::UnsignedIntImageCube)
#  pragma pop_macro("UnsignedIntImageCube")
# else
	.value("UnsignedIntImageCube", oglplus::SLDataType::UnsignedIntImageCube)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_BUFFER
# if defined UnsignedIntImageBuffer
#  pragma push_macro("UnsignedIntImageBuffer")
#  undef UnsignedIntImageBuffer
	.value("UnsignedIntImageBuffer", oglplus::SLDataType::UnsignedIntImageBuffer)
#  pragma pop_macro("UnsignedIntImageBuffer")
# else
	.value("UnsignedIntImageBuffer", oglplus::SLDataType::UnsignedIntImageBuffer)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_1D_ARRAY
# if defined UnsignedIntImage1DArray
#  pragma push_macro("UnsignedIntImage1DArray")
#  undef UnsignedIntImage1DArray
	.value("UnsignedIntImage1DArray", oglplus::SLDataType::UnsignedIntImage1DArray)
#  pragma pop_macro("UnsignedIntImage1DArray")
# else
	.value("UnsignedIntImage1DArray", oglplus::SLDataType::UnsignedIntImage1DArray)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D_ARRAY
# if defined UnsignedIntImage2DArray
#  pragma push_macro("UnsignedIntImage2DArray")
#  undef UnsignedIntImage2DArray
	.value("UnsignedIntImage2DArray", oglplus::SLDataType::UnsignedIntImage2DArray)
#  pragma pop_macro("UnsignedIntImage2DArray")
# else
	.value("UnsignedIntImage2DArray", oglplus::SLDataType::UnsignedIntImage2DArray)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE
# if defined UnsignedIntImage2DMultisample
#  pragma push_macro("UnsignedIntImage2DMultisample")
#  undef UnsignedIntImage2DMultisample
	.value("UnsignedIntImage2DMultisample", oglplus::SLDataType::UnsignedIntImage2DMultisample)
#  pragma pop_macro("UnsignedIntImage2DMultisample")
# else
	.value("UnsignedIntImage2DMultisample", oglplus::SLDataType::UnsignedIntImage2DMultisample)
# endif
#endif
#if defined GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY
# if defined UnsignedIntImage2DMultisampleArray
#  pragma push_macro("UnsignedIntImage2DMultisampleArray")
#  undef UnsignedIntImage2DMultisampleArray
	.value("UnsignedIntImage2DMultisampleArray", oglplus::SLDataType::UnsignedIntImage2DMultisampleArray)
#  pragma pop_macro("UnsignedIntImage2DMultisampleArray")
# else
	.value("UnsignedIntImage2DMultisampleArray", oglplus::SLDataType::UnsignedIntImage2DMultisampleArray)
# endif
#endif
#if defined GL_UNSIGNED_INT_ATOMIC_COUNTER
# if defined UnsignedIntAtomicCounter
#  pragma push_macro("UnsignedIntAtomicCounter")
#  undef UnsignedIntAtomicCounter
	.value("UnsignedIntAtomicCounter", oglplus::SLDataType::UnsignedIntAtomicCounter)
#  pragma pop_macro("UnsignedIntAtomicCounter")
# else
	.value("UnsignedIntAtomicCounter", oglplus::SLDataType::UnsignedIntAtomicCounter)
# endif
#endif
#if defined GL_NONE
# if defined None
#  pragma push_macro("None")
#  undef None
	.value("None", oglplus::SLDataType::None)
#  pragma pop_macro("None")
# else
	.value("None", oglplus::SLDataType::None)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::SLDataType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::SLDataType
		>
	>("aux_CastIterRange_SLDataType");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::SLDataType
	> (*PEnumValueRange)(oglplus::SLDataType) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
