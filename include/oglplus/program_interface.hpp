/**
 *  @file oglplus/primitive_interface.hpp
 *  @brief OpenGL program interface enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PROGRAM_INTERFACE_1208301144_HPP
#define OGLPLUS_PROGRAM_INTERFACE_1208301144_HPP

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
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	ProgramInterface*,
	EnumBaseType<ProgramInterface>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/program_interface.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif

} // namespace oglplus

#endif // include guard
