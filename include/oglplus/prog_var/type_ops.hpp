/**
 *  @file oglplus/prog_var/type_ops.hpp
 *  @brief Program variable type operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROG_VAR_TYPE_OPS_1405052234_HPP
#define OGLPLUS_PROG_VAR_TYPE_OPS_1405052234_HPP

#include <oglplus/detail/glsl_to_cpp.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/object/name.hpp>
#include <oglplus/string/ref.hpp>

namespace oglplus {

// Tag template that can be used to declare an Uniform from SLDataType
template <oglplus::SLDataType>
struct SLtoCpp;

template <typename T>
struct AdjustProgVar {
    using BaseType = T;
    using ValueType = T;

    inline static BaseType Adjust(const ValueType& value) {
        return value;
    }
};

template <>
struct AdjustProgVar<void> {
    using BaseType = void;
};

template <>
struct AdjustProgVar<bool> {
    using BaseType = GLboolean;
    using ValueType = bool;

    inline static BaseType Adjust(ValueType value) {
        return value ? GL_TRUE : GL_FALSE;
    }
};

template <std::size_t N>
struct AdjustProgVar<oglplus::Vector<bool, N>> {
    using BaseType = oglplus::Vector<GLboolean, N>;
    using ValueType = const oglplus::Vector<bool, N>&;

    inline static BaseType Adjust(ValueType value) {
        return BaseType(value);
    }
};

template <oglplus::SLDataType SLType>
struct AdjustProgVar<SLtoCpp<SLType>> {
    using BaseType = typename aux::GLSL2Cpp<SLType>::Type;
    using ValueType = BaseType;

    inline static BaseType Adjust(ValueType value) {
        return value;
    }
};

template <>
class ProgVarTypeOps<tag::Uniform> {
protected:
    static GLenum GetType(ProgramName, GLint location, StrCRef identifier);
};

} // namespace oglplus

#endif // include guard
