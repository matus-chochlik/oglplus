/*
 *  .file oglplus/enums/sl_data_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/sl_data_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// FLOAT
Float,
/// FLOAT_VEC2
FloatVec2,
/// FLOAT_VEC3
FloatVec3,
/// FLOAT_VEC4
FloatVec4,
/// DOUBLE
Double,
/// DOUBLE_VEC2
DoubleVec2,
/// DOUBLE_VEC3
DoubleVec3,
/// DOUBLE_VEC4
DoubleVec4,
/// INT
Int,
/// INT_VEC2
IntVec2,
/// INT_VEC3
IntVec3,
/// INT_VEC4
IntVec4,
/// UNSIGNED_INT
UnsignedInt,
/// UNSIGNED_INT_VEC2
UnsignedIntVec2,
/// UNSIGNED_INT_VEC3
UnsignedIntVec3,
/// UNSIGNED_INT_VEC4
UnsignedIntVec4,
/// BOOL
Bool,
/// BOOL_VEC2
BoolVec2,
/// BOOL_VEC3
BoolVec3,
/// BOOL_VEC4
BoolVec4,
/// FLOAT_MAT2
FloatMat2,
/// FLOAT_MAT3
FloatMat3,
/// FLOAT_MAT4
FloatMat4,
/// FLOAT_MAT2x3
FloatMat2x3,
/// FLOAT_MAT2x4
FloatMat2x4,
/// FLOAT_MAT3x2
FloatMat3x2,
/// FLOAT_MAT3x4
FloatMat3x4,
/// FLOAT_MAT4x2
FloatMat4x2,
/// FLOAT_MAT4x3
FloatMat4x3,
/// DOUBLE_MAT2
DoubleMat2,
/// DOUBLE_MAT3
DoubleMat3,
/// DOUBLE_MAT4
DoubleMat4,
/// DOUBLE_MAT2x3
DoubleMat2x3,
/// DOUBLE_MAT2x4
DoubleMat2x4,
/// DOUBLE_MAT3x2
DoubleMat3x2,
/// DOUBLE_MAT3x4
DoubleMat3x4,
/// DOUBLE_MAT4x2
DoubleMat4x2,
/// DOUBLE_MAT4x3
DoubleMat4x3,
/// SAMPLER_1D
Sampler1D,
/// SAMPLER_2D
Sampler2D,
/// SAMPLER_3D
Sampler3D,
/// SAMPLER_CUBE
SamplerCube,
/// SAMPLER_1D_SHADOW
Sampler1DShadow,
/// SAMPLER_2D_SHADOW
Sampler2DShadow,
/// SAMPLER_1D_ARRAY
Sampler1DArray,
/// SAMPLER_2D_ARRAY
Sampler2DArray,
/// SAMPLER_CUBE_MAP_ARRAY
SamplerCubeMapArray,
/// SAMPLER_1D_ARRAY_SHADOW
Sampler1DArrayShadow,
/// SAMPLER_2D_ARRAY_SHADOW
Sampler2DArrayShadow,
/// SAMPLER_2D_MULTISAMPLE
Sampler2DMultisample,
/// SAMPLER_2D_MULTISAMPLE_ARRAY
Sampler2DMultisampleArray,
/// SAMPLER_CUBE_SHADOW
SamplerCubeShadow,
/// SAMPLER_CUBE_MAP_ARRAY_SHADOW
SamplerCubeMapArrayShadow,
/// SAMPLER_BUFFER
SamplerBuffer,
/// SAMPLER_2D_RECT
Sampler2DRect,
/// SAMPLER_2D_RECT_SHADOW
Sampler2DRectShadow,
/// INT_SAMPLER_1D
IntSampler1D,
/// INT_SAMPLER_2D
IntSampler2D,
/// INT_SAMPLER_3D
IntSampler3D,
/// INT_SAMPLER_CUBE
IntSamplerCube,
/// INT_SAMPLER_1D_ARRAY
IntSampler1DArray,
/// INT_SAMPLER_2D_ARRAY
IntSampler2DArray,
/// INT_SAMPLER_CUBE_MAP_ARRAY
IntSamplerCubeMapArray,
/// INT_SAMPLER_2D_MULTISAMPLE
IntSampler2DMultisample,
/// INT_SAMPLER_2D_MULTISAMPLE_ARRAY
IntSampler2DMultisampleArray,
/// INT_SAMPLER_BUFFER
IntSamplerBuffer,
/// INT_SAMPLER_2D_RECT
IntSampler2DRect,
/// UNSIGNED_INT_SAMPLER_1D
UnsignedIntSampler1D,
/// UNSIGNED_INT_SAMPLER_2D
UnsignedIntSampler2D,
/// UNSIGNED_INT_SAMPLER_3D
UnsignedIntSampler3D,
/// UNSIGNED_INT_SAMPLER_CUBE
UnsignedIntSamplerCube,
/// UNSIGNED_INT_SAMPLER_1D_ARRAY
UnsignedIntSampler1DArray,
/// UNSIGNED_INT_SAMPLER_2D_ARRAY
UnsignedIntSampler2DArray,
/// UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY
UnsignedIntSamplerCubeMapArray,
/// UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE
UnsignedIntSampler2DMultisample,
/// UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
UnsignedIntSampler2DMultisampleArray,
/// UNSIGNED_INT_SAMPLER_BUFFER
UnsignedIntSamplerBuffer,
/// UNSIGNED_INT_SAMPLER_2D_RECT
UnsignedIntSampler2DRect,
/// NONE
None

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_FLOAT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Float)
#  pragma push_macro("Float")
#  undef Float
   OGLPLUS_ENUM_CLASS_VALUE(Float, GL_FLOAT)
#  pragma pop_macro("Float")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Float, GL_FLOAT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_VEC2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatVec2)
#  pragma push_macro("FloatVec2")
#  undef FloatVec2
   OGLPLUS_ENUM_CLASS_VALUE(FloatVec2, GL_FLOAT_VEC2)
#  pragma pop_macro("FloatVec2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatVec2, GL_FLOAT_VEC2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_VEC3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatVec3)
#  pragma push_macro("FloatVec3")
#  undef FloatVec3
   OGLPLUS_ENUM_CLASS_VALUE(FloatVec3, GL_FLOAT_VEC3)
#  pragma pop_macro("FloatVec3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatVec3, GL_FLOAT_VEC3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_VEC4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatVec4)
#  pragma push_macro("FloatVec4")
#  undef FloatVec4
   OGLPLUS_ENUM_CLASS_VALUE(FloatVec4, GL_FLOAT_VEC4)
#  pragma pop_macro("FloatVec4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatVec4, GL_FLOAT_VEC4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Double)
#  pragma push_macro("Double")
#  undef Double
   OGLPLUS_ENUM_CLASS_VALUE(Double, GL_DOUBLE)
#  pragma pop_macro("Double")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Double, GL_DOUBLE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_VEC2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleVec2)
#  pragma push_macro("DoubleVec2")
#  undef DoubleVec2
   OGLPLUS_ENUM_CLASS_VALUE(DoubleVec2, GL_DOUBLE_VEC2)
#  pragma pop_macro("DoubleVec2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleVec2, GL_DOUBLE_VEC2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_VEC3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleVec3)
#  pragma push_macro("DoubleVec3")
#  undef DoubleVec3
   OGLPLUS_ENUM_CLASS_VALUE(DoubleVec3, GL_DOUBLE_VEC3)
#  pragma pop_macro("DoubleVec3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleVec3, GL_DOUBLE_VEC3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_VEC4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleVec4)
#  pragma push_macro("DoubleVec4")
#  undef DoubleVec4
   OGLPLUS_ENUM_CLASS_VALUE(DoubleVec4, GL_DOUBLE_VEC4)
#  pragma pop_macro("DoubleVec4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleVec4, GL_DOUBLE_VEC4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Int)
#  pragma push_macro("Int")
#  undef Int
   OGLPLUS_ENUM_CLASS_VALUE(Int, GL_INT)
#  pragma pop_macro("Int")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Int, GL_INT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_VEC2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntVec2)
#  pragma push_macro("IntVec2")
#  undef IntVec2
   OGLPLUS_ENUM_CLASS_VALUE(IntVec2, GL_INT_VEC2)
#  pragma pop_macro("IntVec2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntVec2, GL_INT_VEC2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_VEC3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntVec3)
#  pragma push_macro("IntVec3")
#  undef IntVec3
   OGLPLUS_ENUM_CLASS_VALUE(IntVec3, GL_INT_VEC3)
#  pragma pop_macro("IntVec3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntVec3, GL_INT_VEC3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_VEC4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntVec4)
#  pragma push_macro("IntVec4")
#  undef IntVec4
   OGLPLUS_ENUM_CLASS_VALUE(IntVec4, GL_INT_VEC4)
#  pragma pop_macro("IntVec4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntVec4, GL_INT_VEC4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedInt)
#  pragma push_macro("UnsignedInt")
#  undef UnsignedInt
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedInt, GL_UNSIGNED_INT)
#  pragma pop_macro("UnsignedInt")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedInt, GL_UNSIGNED_INT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_VEC2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntVec2)
#  pragma push_macro("UnsignedIntVec2")
#  undef UnsignedIntVec2
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntVec2, GL_UNSIGNED_INT_VEC2)
#  pragma pop_macro("UnsignedIntVec2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntVec2, GL_UNSIGNED_INT_VEC2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_VEC3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntVec3)
#  pragma push_macro("UnsignedIntVec3")
#  undef UnsignedIntVec3
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntVec3, GL_UNSIGNED_INT_VEC3)
#  pragma pop_macro("UnsignedIntVec3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntVec3, GL_UNSIGNED_INT_VEC3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_VEC4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntVec4)
#  pragma push_macro("UnsignedIntVec4")
#  undef UnsignedIntVec4
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntVec4, GL_UNSIGNED_INT_VEC4)
#  pragma pop_macro("UnsignedIntVec4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntVec4, GL_UNSIGNED_INT_VEC4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BOOL
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Bool)
#  pragma push_macro("Bool")
#  undef Bool
   OGLPLUS_ENUM_CLASS_VALUE(Bool, GL_BOOL)
#  pragma pop_macro("Bool")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Bool, GL_BOOL)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BOOL_VEC2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(BoolVec2)
#  pragma push_macro("BoolVec2")
#  undef BoolVec2
   OGLPLUS_ENUM_CLASS_VALUE(BoolVec2, GL_BOOL_VEC2)
#  pragma pop_macro("BoolVec2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(BoolVec2, GL_BOOL_VEC2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BOOL_VEC3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(BoolVec3)
#  pragma push_macro("BoolVec3")
#  undef BoolVec3
   OGLPLUS_ENUM_CLASS_VALUE(BoolVec3, GL_BOOL_VEC3)
#  pragma pop_macro("BoolVec3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(BoolVec3, GL_BOOL_VEC3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BOOL_VEC4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(BoolVec4)
#  pragma push_macro("BoolVec4")
#  undef BoolVec4
   OGLPLUS_ENUM_CLASS_VALUE(BoolVec4, GL_BOOL_VEC4)
#  pragma pop_macro("BoolVec4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(BoolVec4, GL_BOOL_VEC4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_MAT2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatMat2)
#  pragma push_macro("FloatMat2")
#  undef FloatMat2
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat2, GL_FLOAT_MAT2)
#  pragma pop_macro("FloatMat2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat2, GL_FLOAT_MAT2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_MAT3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatMat3)
#  pragma push_macro("FloatMat3")
#  undef FloatMat3
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat3, GL_FLOAT_MAT3)
#  pragma pop_macro("FloatMat3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat3, GL_FLOAT_MAT3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_MAT4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatMat4)
#  pragma push_macro("FloatMat4")
#  undef FloatMat4
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat4, GL_FLOAT_MAT4)
#  pragma pop_macro("FloatMat4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat4, GL_FLOAT_MAT4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_MAT2x3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatMat2x3)
#  pragma push_macro("FloatMat2x3")
#  undef FloatMat2x3
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat2x3, GL_FLOAT_MAT2x3)
#  pragma pop_macro("FloatMat2x3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat2x3, GL_FLOAT_MAT2x3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_MAT2x4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatMat2x4)
#  pragma push_macro("FloatMat2x4")
#  undef FloatMat2x4
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat2x4, GL_FLOAT_MAT2x4)
#  pragma pop_macro("FloatMat2x4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat2x4, GL_FLOAT_MAT2x4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_MAT3x2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatMat3x2)
#  pragma push_macro("FloatMat3x2")
#  undef FloatMat3x2
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat3x2, GL_FLOAT_MAT3x2)
#  pragma pop_macro("FloatMat3x2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat3x2, GL_FLOAT_MAT3x2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_MAT3x4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatMat3x4)
#  pragma push_macro("FloatMat3x4")
#  undef FloatMat3x4
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat3x4, GL_FLOAT_MAT3x4)
#  pragma pop_macro("FloatMat3x4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat3x4, GL_FLOAT_MAT3x4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_MAT4x2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatMat4x2)
#  pragma push_macro("FloatMat4x2")
#  undef FloatMat4x2
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat4x2, GL_FLOAT_MAT4x2)
#  pragma pop_macro("FloatMat4x2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat4x2, GL_FLOAT_MAT4x2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FLOAT_MAT4x3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(FloatMat4x3)
#  pragma push_macro("FloatMat4x3")
#  undef FloatMat4x3
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat4x3, GL_FLOAT_MAT4x3)
#  pragma pop_macro("FloatMat4x3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(FloatMat4x3, GL_FLOAT_MAT4x3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_MAT2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleMat2)
#  pragma push_macro("DoubleMat2")
#  undef DoubleMat2
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat2, GL_DOUBLE_MAT2)
#  pragma pop_macro("DoubleMat2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat2, GL_DOUBLE_MAT2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_MAT3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleMat3)
#  pragma push_macro("DoubleMat3")
#  undef DoubleMat3
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat3, GL_DOUBLE_MAT3)
#  pragma pop_macro("DoubleMat3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat3, GL_DOUBLE_MAT3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_MAT4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleMat4)
#  pragma push_macro("DoubleMat4")
#  undef DoubleMat4
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat4, GL_DOUBLE_MAT4)
#  pragma pop_macro("DoubleMat4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat4, GL_DOUBLE_MAT4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_MAT2x3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleMat2x3)
#  pragma push_macro("DoubleMat2x3")
#  undef DoubleMat2x3
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat2x3, GL_DOUBLE_MAT2x3)
#  pragma pop_macro("DoubleMat2x3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat2x3, GL_DOUBLE_MAT2x3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_MAT2x4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleMat2x4)
#  pragma push_macro("DoubleMat2x4")
#  undef DoubleMat2x4
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat2x4, GL_DOUBLE_MAT2x4)
#  pragma pop_macro("DoubleMat2x4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat2x4, GL_DOUBLE_MAT2x4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_MAT3x2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleMat3x2)
#  pragma push_macro("DoubleMat3x2")
#  undef DoubleMat3x2
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat3x2, GL_DOUBLE_MAT3x2)
#  pragma pop_macro("DoubleMat3x2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat3x2, GL_DOUBLE_MAT3x2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_MAT3x4
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleMat3x4)
#  pragma push_macro("DoubleMat3x4")
#  undef DoubleMat3x4
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat3x4, GL_DOUBLE_MAT3x4)
#  pragma pop_macro("DoubleMat3x4")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat3x4, GL_DOUBLE_MAT3x4)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_MAT4x2
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleMat4x2)
#  pragma push_macro("DoubleMat4x2")
#  undef DoubleMat4x2
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat4x2, GL_DOUBLE_MAT4x2)
#  pragma pop_macro("DoubleMat4x2")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat4x2, GL_DOUBLE_MAT4x2)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DOUBLE_MAT4x3
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(DoubleMat4x3)
#  pragma push_macro("DoubleMat4x3")
#  undef DoubleMat4x3
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat4x3, GL_DOUBLE_MAT4x3)
#  pragma pop_macro("DoubleMat4x3")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DoubleMat4x3, GL_DOUBLE_MAT4x3)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_1D
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler1D)
#  pragma push_macro("Sampler1D")
#  undef Sampler1D
   OGLPLUS_ENUM_CLASS_VALUE(Sampler1D, GL_SAMPLER_1D)
#  pragma pop_macro("Sampler1D")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler1D, GL_SAMPLER_1D)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_2D
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler2D)
#  pragma push_macro("Sampler2D")
#  undef Sampler2D
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2D, GL_SAMPLER_2D)
#  pragma pop_macro("Sampler2D")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2D, GL_SAMPLER_2D)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_3D
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler3D)
#  pragma push_macro("Sampler3D")
#  undef Sampler3D
   OGLPLUS_ENUM_CLASS_VALUE(Sampler3D, GL_SAMPLER_3D)
#  pragma pop_macro("Sampler3D")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler3D, GL_SAMPLER_3D)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_CUBE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SamplerCube)
#  pragma push_macro("SamplerCube")
#  undef SamplerCube
   OGLPLUS_ENUM_CLASS_VALUE(SamplerCube, GL_SAMPLER_CUBE)
#  pragma pop_macro("SamplerCube")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SamplerCube, GL_SAMPLER_CUBE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_1D_SHADOW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler1DShadow)
#  pragma push_macro("Sampler1DShadow")
#  undef Sampler1DShadow
   OGLPLUS_ENUM_CLASS_VALUE(Sampler1DShadow, GL_SAMPLER_1D_SHADOW)
#  pragma pop_macro("Sampler1DShadow")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler1DShadow, GL_SAMPLER_1D_SHADOW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_2D_SHADOW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler2DShadow)
#  pragma push_macro("Sampler2DShadow")
#  undef Sampler2DShadow
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DShadow, GL_SAMPLER_2D_SHADOW)
#  pragma pop_macro("Sampler2DShadow")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DShadow, GL_SAMPLER_2D_SHADOW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_1D_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler1DArray)
#  pragma push_macro("Sampler1DArray")
#  undef Sampler1DArray
   OGLPLUS_ENUM_CLASS_VALUE(Sampler1DArray, GL_SAMPLER_1D_ARRAY)
#  pragma pop_macro("Sampler1DArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler1DArray, GL_SAMPLER_1D_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_2D_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler2DArray)
#  pragma push_macro("Sampler2DArray")
#  undef Sampler2DArray
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DArray, GL_SAMPLER_2D_ARRAY)
#  pragma pop_macro("Sampler2DArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DArray, GL_SAMPLER_2D_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_CUBE_MAP_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SamplerCubeMapArray)
#  pragma push_macro("SamplerCubeMapArray")
#  undef SamplerCubeMapArray
   OGLPLUS_ENUM_CLASS_VALUE(SamplerCubeMapArray, GL_SAMPLER_CUBE_MAP_ARRAY)
#  pragma pop_macro("SamplerCubeMapArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SamplerCubeMapArray, GL_SAMPLER_CUBE_MAP_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_1D_ARRAY_SHADOW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler1DArrayShadow)
#  pragma push_macro("Sampler1DArrayShadow")
#  undef Sampler1DArrayShadow
   OGLPLUS_ENUM_CLASS_VALUE(Sampler1DArrayShadow, GL_SAMPLER_1D_ARRAY_SHADOW)
#  pragma pop_macro("Sampler1DArrayShadow")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler1DArrayShadow, GL_SAMPLER_1D_ARRAY_SHADOW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_2D_ARRAY_SHADOW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler2DArrayShadow)
#  pragma push_macro("Sampler2DArrayShadow")
#  undef Sampler2DArrayShadow
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DArrayShadow, GL_SAMPLER_2D_ARRAY_SHADOW)
#  pragma pop_macro("Sampler2DArrayShadow")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DArrayShadow, GL_SAMPLER_2D_ARRAY_SHADOW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_2D_MULTISAMPLE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler2DMultisample)
#  pragma push_macro("Sampler2DMultisample")
#  undef Sampler2DMultisample
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DMultisample, GL_SAMPLER_2D_MULTISAMPLE)
#  pragma pop_macro("Sampler2DMultisample")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DMultisample, GL_SAMPLER_2D_MULTISAMPLE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_2D_MULTISAMPLE_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler2DMultisampleArray)
#  pragma push_macro("Sampler2DMultisampleArray")
#  undef Sampler2DMultisampleArray
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DMultisampleArray, GL_SAMPLER_2D_MULTISAMPLE_ARRAY)
#  pragma pop_macro("Sampler2DMultisampleArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DMultisampleArray, GL_SAMPLER_2D_MULTISAMPLE_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_CUBE_SHADOW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SamplerCubeShadow)
#  pragma push_macro("SamplerCubeShadow")
#  undef SamplerCubeShadow
   OGLPLUS_ENUM_CLASS_VALUE(SamplerCubeShadow, GL_SAMPLER_CUBE_SHADOW)
#  pragma pop_macro("SamplerCubeShadow")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SamplerCubeShadow, GL_SAMPLER_CUBE_SHADOW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SamplerCubeMapArrayShadow)
#  pragma push_macro("SamplerCubeMapArrayShadow")
#  undef SamplerCubeMapArrayShadow
   OGLPLUS_ENUM_CLASS_VALUE(SamplerCubeMapArrayShadow, GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW)
#  pragma pop_macro("SamplerCubeMapArrayShadow")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SamplerCubeMapArrayShadow, GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(SamplerBuffer)
#  pragma push_macro("SamplerBuffer")
#  undef SamplerBuffer
   OGLPLUS_ENUM_CLASS_VALUE(SamplerBuffer, GL_SAMPLER_BUFFER)
#  pragma pop_macro("SamplerBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(SamplerBuffer, GL_SAMPLER_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_2D_RECT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler2DRect)
#  pragma push_macro("Sampler2DRect")
#  undef Sampler2DRect
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DRect, GL_SAMPLER_2D_RECT)
#  pragma pop_macro("Sampler2DRect")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DRect, GL_SAMPLER_2D_RECT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_SAMPLER_2D_RECT_SHADOW
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Sampler2DRectShadow)
#  pragma push_macro("Sampler2DRectShadow")
#  undef Sampler2DRectShadow
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DRectShadow, GL_SAMPLER_2D_RECT_SHADOW)
#  pragma pop_macro("Sampler2DRectShadow")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Sampler2DRectShadow, GL_SAMPLER_2D_RECT_SHADOW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_1D
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSampler1D)
#  pragma push_macro("IntSampler1D")
#  undef IntSampler1D
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler1D, GL_INT_SAMPLER_1D)
#  pragma pop_macro("IntSampler1D")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler1D, GL_INT_SAMPLER_1D)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_2D
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSampler2D)
#  pragma push_macro("IntSampler2D")
#  undef IntSampler2D
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2D, GL_INT_SAMPLER_2D)
#  pragma pop_macro("IntSampler2D")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2D, GL_INT_SAMPLER_2D)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_3D
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSampler3D)
#  pragma push_macro("IntSampler3D")
#  undef IntSampler3D
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler3D, GL_INT_SAMPLER_3D)
#  pragma pop_macro("IntSampler3D")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler3D, GL_INT_SAMPLER_3D)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_CUBE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSamplerCube)
#  pragma push_macro("IntSamplerCube")
#  undef IntSamplerCube
   OGLPLUS_ENUM_CLASS_VALUE(IntSamplerCube, GL_INT_SAMPLER_CUBE)
#  pragma pop_macro("IntSamplerCube")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSamplerCube, GL_INT_SAMPLER_CUBE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_1D_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSampler1DArray)
#  pragma push_macro("IntSampler1DArray")
#  undef IntSampler1DArray
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler1DArray, GL_INT_SAMPLER_1D_ARRAY)
#  pragma pop_macro("IntSampler1DArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler1DArray, GL_INT_SAMPLER_1D_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_2D_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSampler2DArray)
#  pragma push_macro("IntSampler2DArray")
#  undef IntSampler2DArray
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2DArray, GL_INT_SAMPLER_2D_ARRAY)
#  pragma pop_macro("IntSampler2DArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2DArray, GL_INT_SAMPLER_2D_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_CUBE_MAP_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSamplerCubeMapArray)
#  pragma push_macro("IntSamplerCubeMapArray")
#  undef IntSamplerCubeMapArray
   OGLPLUS_ENUM_CLASS_VALUE(IntSamplerCubeMapArray, GL_INT_SAMPLER_CUBE_MAP_ARRAY)
#  pragma pop_macro("IntSamplerCubeMapArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSamplerCubeMapArray, GL_INT_SAMPLER_CUBE_MAP_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_2D_MULTISAMPLE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSampler2DMultisample)
#  pragma push_macro("IntSampler2DMultisample")
#  undef IntSampler2DMultisample
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2DMultisample, GL_INT_SAMPLER_2D_MULTISAMPLE)
#  pragma pop_macro("IntSampler2DMultisample")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2DMultisample, GL_INT_SAMPLER_2D_MULTISAMPLE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSampler2DMultisampleArray)
#  pragma push_macro("IntSampler2DMultisampleArray")
#  undef IntSampler2DMultisampleArray
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2DMultisampleArray, GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY)
#  pragma pop_macro("IntSampler2DMultisampleArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2DMultisampleArray, GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSamplerBuffer)
#  pragma push_macro("IntSamplerBuffer")
#  undef IntSamplerBuffer
   OGLPLUS_ENUM_CLASS_VALUE(IntSamplerBuffer, GL_INT_SAMPLER_BUFFER)
#  pragma pop_macro("IntSamplerBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSamplerBuffer, GL_INT_SAMPLER_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INT_SAMPLER_2D_RECT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(IntSampler2DRect)
#  pragma push_macro("IntSampler2DRect")
#  undef IntSampler2DRect
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2DRect, GL_INT_SAMPLER_2D_RECT)
#  pragma pop_macro("IntSampler2DRect")
# else
   OGLPLUS_ENUM_CLASS_VALUE(IntSampler2DRect, GL_INT_SAMPLER_2D_RECT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_1D
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSampler1D)
#  pragma push_macro("UnsignedIntSampler1D")
#  undef UnsignedIntSampler1D
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler1D, GL_UNSIGNED_INT_SAMPLER_1D)
#  pragma pop_macro("UnsignedIntSampler1D")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler1D, GL_UNSIGNED_INT_SAMPLER_1D)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSampler2D)
#  pragma push_macro("UnsignedIntSampler2D")
#  undef UnsignedIntSampler2D
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2D, GL_UNSIGNED_INT_SAMPLER_2D)
#  pragma pop_macro("UnsignedIntSampler2D")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2D, GL_UNSIGNED_INT_SAMPLER_2D)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_3D
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSampler3D)
#  pragma push_macro("UnsignedIntSampler3D")
#  undef UnsignedIntSampler3D
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler3D, GL_UNSIGNED_INT_SAMPLER_3D)
#  pragma pop_macro("UnsignedIntSampler3D")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler3D, GL_UNSIGNED_INT_SAMPLER_3D)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_CUBE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSamplerCube)
#  pragma push_macro("UnsignedIntSamplerCube")
#  undef UnsignedIntSamplerCube
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSamplerCube, GL_UNSIGNED_INT_SAMPLER_CUBE)
#  pragma pop_macro("UnsignedIntSamplerCube")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSamplerCube, GL_UNSIGNED_INT_SAMPLER_CUBE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_1D_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSampler1DArray)
#  pragma push_macro("UnsignedIntSampler1DArray")
#  undef UnsignedIntSampler1DArray
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler1DArray, GL_UNSIGNED_INT_SAMPLER_1D_ARRAY)
#  pragma pop_macro("UnsignedIntSampler1DArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler1DArray, GL_UNSIGNED_INT_SAMPLER_1D_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSampler2DArray)
#  pragma push_macro("UnsignedIntSampler2DArray")
#  undef UnsignedIntSampler2DArray
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2DArray, GL_UNSIGNED_INT_SAMPLER_2D_ARRAY)
#  pragma pop_macro("UnsignedIntSampler2DArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2DArray, GL_UNSIGNED_INT_SAMPLER_2D_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSamplerCubeMapArray)
#  pragma push_macro("UnsignedIntSamplerCubeMapArray")
#  undef UnsignedIntSamplerCubeMapArray
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSamplerCubeMapArray, GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY)
#  pragma pop_macro("UnsignedIntSamplerCubeMapArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSamplerCubeMapArray, GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSampler2DMultisample)
#  pragma push_macro("UnsignedIntSampler2DMultisample")
#  undef UnsignedIntSampler2DMultisample
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2DMultisample, GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE)
#  pragma pop_macro("UnsignedIntSampler2DMultisample")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2DMultisample, GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSampler2DMultisampleArray)
#  pragma push_macro("UnsignedIntSampler2DMultisampleArray")
#  undef UnsignedIntSampler2DMultisampleArray
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2DMultisampleArray, GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY)
#  pragma pop_macro("UnsignedIntSampler2DMultisampleArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2DMultisampleArray, GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_BUFFER
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSamplerBuffer)
#  pragma push_macro("UnsignedIntSamplerBuffer")
#  undef UnsignedIntSamplerBuffer
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSamplerBuffer, GL_UNSIGNED_INT_SAMPLER_BUFFER)
#  pragma pop_macro("UnsignedIntSamplerBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSamplerBuffer, GL_UNSIGNED_INT_SAMPLER_BUFFER)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_UNSIGNED_INT_SAMPLER_2D_RECT
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(UnsignedIntSampler2DRect)
#  pragma push_macro("UnsignedIntSampler2DRect")
#  undef UnsignedIntSampler2DRect
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2DRect, GL_UNSIGNED_INT_SAMPLER_2D_RECT)
#  pragma pop_macro("UnsignedIntSampler2DRect")
# else
   OGLPLUS_ENUM_CLASS_VALUE(UnsignedIntSampler2DRect, GL_UNSIGNED_INT_SAMPLER_2D_RECT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_NONE
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(None)
#  pragma push_macro("None")
#  undef None
   OGLPLUS_ENUM_CLASS_VALUE(None, GL_NONE)
#  pragma pop_macro("None")
# else
   OGLPLUS_ENUM_CLASS_VALUE(None, GL_NONE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

