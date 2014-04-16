/**
 *  @file oglplus/ext/NV_path_rendering/format.hpp
 *  @brief Wrapper for the NV_path_rendering format enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_NV_PATH_RENDERING_FORMAT_1203031902_HPP
#define OGLPLUS_EXT_NV_PATH_RENDERING_FORMAT_1203031902_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Path specification string format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVFormat, GLenum)
#include <oglplus/enums/ext/nv_path_format.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVFormat)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_format_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_format_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
