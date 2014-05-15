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
struct Nothing
{
	typedef Nothing Type;
	typedef int _value_type;
};

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

struct VertexAttrib;
struct Uniform;
struct UniformBlock;
struct Subroutine;
struct SubroutineUniform;

struct NativeTypes;
struct MatrixTypes;

struct DirectInit;
struct EagerInit;
struct LazyInit;

struct Typecheck;
struct NoTypecheck;

struct ExplicitSel;
struct ImplicitSel;
struct DirectState;
struct CurrentBound;
} // namespace tag

template <typename T>
struct AllowedSpecialization;

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
typedef ObjectName<tag::PerfMonitorAMD> PerfMonitorAMDName;
typedef ObjectName<tag::PathNV> PathNVName;

template <typename ObjTag>
GLuint GetGLName(ObjectName<ObjTag>);

template <typename ObjName>
class Sequence;

template <typename ObjName>
const GLuint* GetGLNames(const Sequence<ObjName>&);

template <typename ObjTag>
class ObjGenDelOps;

template <typename ObjTag>
class ObjBindingOps;

template <typename ObjTag>
class ObjCommonOps;

template <typename ObjTag>
class BoundObjOps;

template <typename OpsTag, typename ObjTag>
class ObjZeroOps;

template <typename OpsTag, typename ObjTag>
class ObjectOps;

template <typename CommonOps>
class ObjectZero;

template <typename ObjectOps>
class Object;

template <typename Object>
struct ObjectTag;

template <typename ObjTag>
struct ObjectTag<ObjectName<ObjTag>>
{
	typedef ObjTag Type;
};

template <typename OpsTag, typename ObjTag>
struct ObjectTag<ObjectOps<OpsTag, ObjTag>>
 : ObjectTag<ObjectName<ObjTag>>
{ };

template <template <typename> class Wrapper, typename ObjectOps>
struct ObjectTag<Wrapper<ObjectOps>>
 : ObjectTag<ObjectOps>
{ };

template <typename Target>
struct ObjectTargetTag;

template <typename ObjectT>
class Reference;

template <typename Object>
class Managed;

template <typename X>
class Optional;

template <typename Object>
class Array;

template <typename Object>
class Group;

class Shader;

template <typename VarTag>
class ProgVarLoc;

typedef ProgVarLoc<tag::VertexAttrib> VertexAttribLoc;
typedef ProgVarLoc<tag::Uniform> UniformLoc;
typedef ProgVarLoc<tag::UniformBlock> UniformBlockLoc;
typedef ProgVarLoc<tag::Subroutine> SubroutineLoc;
typedef ProgVarLoc<tag::SubroutineUniform> SubroutineUniformLoc;

template <typename VarTag>
GLint GetGLLocation(ProgVarLoc<VarTag>);

template <typename VarTag>
class ProgVarLocOps;

template <typename VarTag>
class ProgVarTypeOps;

template <typename ChkTag, typename VarTag>
class ProgVarTypecheck;

template <typename OpsTag, typename VarTag, typename TypTag>
class ProgVarSetters;

template <typename OpsTag, typename T>
class ProgVarCallers;

template <typename VarTag>
class ProgVarCommonOps;

template <typename OpsTag, typename VarTag, typename T>
class ProgVarGetSetOps;

template <typename ProgVar>
class Typechecked;

} // namespace oglplus

#endif // include guard
