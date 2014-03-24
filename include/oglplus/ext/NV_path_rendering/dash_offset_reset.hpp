/**
 *  @file oglplus/ext/NV_path_rendering/dash_offset_reset.hpp
 *  @brief Wrapper for the NV_path_rendering dash offset reset enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_NV_PATH_RENDERING_DASH_OFFSET_RESET_1203031902_HPP
#define OGLPLUS_EXT_NV_PATH_RENDERING_DASH_OFFSET_RESET_1203031902_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Path dash offset reset mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVDashOffsetReset, GLenum)
#include <oglplus/enums/ext/nv_path_dash_offset_reset.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVDashOffsetReset)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_dash_offset_reset_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_dash_offset_reset_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
