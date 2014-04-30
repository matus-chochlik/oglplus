/**
 *  @file oglplus/fwd.hpp
 *  @brief Forward declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FWD_1107121519_HPP
#define OGLPLUS_FWD_1107121519_HPP

#include <oglplus/config_compiler.hpp>
#include <type_traits>
#include <cstddef>

namespace oglplus {

// Nothing
struct Nothing { typedef int _value_type; };

// Angle
template <typename T>
class Angle;

template <typename T>
T Radians(const Angle<T>&);

template <typename T>
T Degrees(const Angle<T>&);

template <typename T>
T Sin(const Angle<T>&);

template <typename T>
T Cos(const Angle<T>&);

template <typename T>
T Tan(const Angle<T>&);

// Vector
template <typename T, std::size_t N>
class Vector;

template <typename T, std::size_t N>
const T* Data(const Vector<T, N>& a);

template <typename T, std::size_t N>
std::size_t Size(const Vector<T, N>&);

template <typename T, std::size_t N>
T At(const Vector<T, N>& a, std::size_t i);

template <typename T, std::size_t N>
T At(const Vector<T, N>& a, std::size_t i, T fallback);

// Quaternion
template <typename T>
class Quaternion;

// Matrix
template <typename T, std::size_t Rows, std::size_t Cols>
class Matrix;

template <typename T, std::size_t R, std::size_t C>
const T* Data(const Matrix<T, R, C>& matrix);

template <typename T, std::size_t R, std::size_t C>
std::size_t Size(const Matrix<T, R, C>&);

template <typename T, std::size_t R, std::size_t C>
std::size_t Rows(const Matrix<T, R, C>&);

template <typename T, std::size_t R, std::size_t C>
std::size_t Cols(const Matrix<T, R, C>&);

template <typename T, std::size_t R, std::size_t C>
T At(const Matrix<T, R, C>& matrix, std::size_t i, std::size_t j);

// ObjectTypeId
template <typename ObjectOps>
struct ObjectTypeId;

template <typename Id>
struct ObjectTypeById;

#define OGLPLUS_OBJECT_TYPE_ID(OBJECT, ID) \
template <> struct ObjectTypeId<OBJECT##Ops> \
 : public std::integral_constant<int, ID> { }; \
template <> struct ObjectTypeById<std::integral_constant<int, ID> > \
{ typedef OBJECT##Ops Type; };

class RenderbufferOps;
OGLPLUS_OBJECT_TYPE_ID(Renderbuffer, 1)

class FramebufferOps;
OGLPLUS_OBJECT_TYPE_ID(Framebuffer, 2)

class TextureOps;
OGLPLUS_OBJECT_TYPE_ID(Texture, 3)

class BufferOps;
OGLPLUS_OBJECT_TYPE_ID(Buffer, 4)

class QueryOps;
OGLPLUS_OBJECT_TYPE_ID(Query, 5)

class ProgramPipelineOps;
OGLPLUS_OBJECT_TYPE_ID(ProgramPipeline, 6)

class ProgramOps;
OGLPLUS_OBJECT_TYPE_ID(Program, 7)

class TransformFeedbackOps;
OGLPLUS_OBJECT_TYPE_ID(TransformFeedback, 8)

class SamplerOps;
OGLPLUS_OBJECT_TYPE_ID(Sampler, 9)

class VertexArrayOps;
OGLPLUS_OBJECT_TYPE_ID(VertexArray, 10)

class ShaderOps;
OGLPLUS_OBJECT_TYPE_ID(Shader, 11)

class PerfMonitorAMDOps;
OGLPLUS_OBJECT_TYPE_ID(PerfMonitorAMD, 12)

class PathNVOps;
OGLPLUS_OBJECT_TYPE_ID(PathNV, 13)

class DSATextureEXTOps;
OGLPLUS_OBJECT_TYPE_ID(DSATextureEXT, 14)

class DSABufferEXTOps;
OGLPLUS_OBJECT_TYPE_ID(DSABufferEXT, 15)

class DSAFramebufferEXTOps;
OGLPLUS_OBJECT_TYPE_ID(DSAFramebufferEXT, 16)

class DSARenderbufferEXTOps;
OGLPLUS_OBJECT_TYPE_ID(DSARenderbufferEXT, 17)

class DSAVertexArrayEXTOps;
OGLPLUS_OBJECT_TYPE_ID(DSAVertexArrayEXT, 18)

template <typename ObjectOps>
struct ObjectBaseOps;

template <typename Target>
struct ObjectTargetOps;

template <typename ObjectOps>
class Object;

template <typename ObjectOps>
class Managed;

template <class Object>
class FriendOf;

template <template <class, class> class Base, class BaseParam, class Bindable>
class BoundTemplate;

template <typename ObjectOps>
struct NonDSAtoDSA;

template <typename ObjectOps>
struct DSAtoNonDSA;

} // namespace oglplus

#endif // include guard
