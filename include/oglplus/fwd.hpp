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

// Tags
namespace tag {

struct Renderbuffer;
struct Framebuffer;
struct Texture;
struct Buffer;
struct Query;
struct ProgramPipeline;
struct Program;
struct TransformFeedback;
struct Sampler;
struct VertexArray;
struct Shader;
struct PerfMonitorAMD;
struct PathNV;

struct ExplicitSel;
struct ImplicitSel;
struct DirectState;
} // namespace tag

// Object

template <typename ObjTag>
struct IsMultiObject;

template <typename ObjTag>
class ObjectName;

typedef ObjectName<tag::Renderbuffer> RenderbufferName;
typedef ObjectName<tag::Framebuffer> FramebufferName;
typedef ObjectName<tag::Texture> TextureName;
typedef ObjectName<tag::Buffer> BufferName;
typedef ObjectName<tag::Query> QueryName;
typedef ObjectName<tag::ProgramPipeline> ProgramPipelineName;
typedef ObjectName<tag::Program> ProgramName;
typedef ObjectName<tag::TransformFeedback> TransformFeedbackName;
typedef ObjectName<tag::Sampler> SamplerName;
typedef ObjectName<tag::VertexArray> VertexArrayName;
typedef ObjectName<tag::Shader> ShaderName;

template <typename ObjTag>
GLuint GetGLName(ObjectName<ObjTag>);

template <typename ObjName>
class Sequence;

template <typename ObjName>
const GLuint* GetGLNames(const Sequence<ObjName>&);

template <typename ObjTag>
class GenDelOps;

template <typename ObjTag>
class BindingOps;

template <typename ObjTag>
class CommonOps;

template <typename OpsTag, typename ObjTag>
class ObjZeroOps;

template <typename OpsTag, typename ObjTag>
class ObjectOps;

template <typename CommonOps>
class ObjectZero;

template <typename ObjectOps>
class Object;

template <typename Target>
struct ObjectTargetTag;

template <typename Object>
class Managed;

template <typename Object>
class Array;

template <typename Object>
class Group;

} // namespace oglplus

#endif // include guard
