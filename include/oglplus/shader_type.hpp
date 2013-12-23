/**
 *  @file oglplus/shader_type.hpp
 *  @brief Shader type enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHADER_TYPE_1107121519_HPP
#define OGLPLUS_SHADER_TYPE_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// The type of a Shader
/**
 *  @ingroup enumerations
 *
 *  @see Shader::Type()
 */
OGLPLUS_ENUM_CLASS_BEGIN(ShaderType, GLenum)
#include <oglplus/enums/shader_type.ipp>
OGLPLUS_ENUM_CLASS_END(ShaderType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/shader_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/shader_type_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
