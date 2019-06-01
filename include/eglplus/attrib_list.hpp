/**
 *  @file eglplus/attrib_list.hpp
 *  @brief Template for EGL surface and configuration attribute list
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_ATTRIB_LIST_1303292057_HPP
#define EGLPLUS_ATTRIB_LIST_1303292057_HPP

#include <oglplus/detail/attrib_list.hpp>

#include <cassert>
#include <vector>

namespace eglplus {

/// Reused FinishedAttributeList from OGLplus
using oglplus::FinishedAttributeList;

/// Reused FinishedAttributeList from OGLplus
using oglplus::AttributeList;

struct AttributeListTraits {
    using Int = EGLint;

    template <typename Enum>
    struct EnumBaseType {
        using Type = typename eglplus::enums::EnumBaseType<Enum>::Type;
    };

    static EGLint ListEnd() {
        return EGL_NONE;
    }
    static EGLint TrueValue() {
        return EGL_TRUE;
    }
    static EGLint FalseValue() {
        return EGL_FALSE;
    }
    static EGLint DontCare() {
        return EGL_DONT_CARE;
    }
};

} // namespace eglplus

#endif // include guard
