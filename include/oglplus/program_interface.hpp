/**
 *  @file oglplus/program_interface.hpp
 *  @brief OpenGL program interface enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROGRAM_INTERFACE_1208301144_HPP
#define OGLPLUS_PROGRAM_INTERFACE_1208301144_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Program interface enumeration
/**
 *  @ingroup enumerations
 *
 *  @see Program
 *  @see ProgramResource
 *
 *  @glsymbols
 *  @glfunref{GetProgramResourceName}
 *  @glfunref{GetProgramInterface}
 *  @glfunref{GetProgramResourceIndex}
 *  @glfunref{GetProgramResource}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ProgramInterface, GLenum)
#include <oglplus/enums/program_interface.ipp>
OGLPLUS_ENUM_CLASS_END(ProgramInterface)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/program_interface_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/program_interface_range.ipp>
#endif

/// Program resource property enumeration
/**
 *  @ingroup enumerations
 *
 *  @see Program
 *  @see ProgramResource
 *
 *  @glsymbols
 *  @glfunref{GetProgramInterface}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ProgramResourceProperty, GLenum)
#include <oglplus/enums/program_resource_property.ipp>
OGLPLUS_ENUM_CLASS_END(ProgramResourceProperty)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/program_resource_property_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/program_resource_property_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
