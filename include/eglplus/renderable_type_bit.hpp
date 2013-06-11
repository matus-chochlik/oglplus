/**
 *  @file eglplus/renderable_type_bit.hpp
 *  @brief EGL renderable type enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_RENDERABLE_TYPE_1303292057_HPP
#define EGLPLUS_RENDERABLE_TYPE_1303292057_HPP

#include <eglplus/enumerations.hpp>
#include <eglplus/bitfield.hpp>

namespace eglplus {

/// EGL renderable type bits enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(RenderableTypeBit, EGLenum)
#include <eglplus/enums/renderable_type_bit.ipp>
EGLPLUS_ENUM_CLASS_END(RenderableTypeBit)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/renderable_type_bit_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/renderable_type_bit_range.ipp>
#endif

EGLPLUS_MAKE_BITFIELD(RenderableTypeBit)

} // namespace eglplus

#endif // include guard
