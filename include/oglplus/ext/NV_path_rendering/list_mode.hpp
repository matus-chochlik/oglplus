/**
 *  @file oglplus/ext/NV_path_rendering/list_mode.hpp
 *  @brief Wrapper for the NV_path_rendering list mode enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_NV_PATH_RENDERING_LIST_MODE_1203031902_HPP
#define OGLPLUS_EXT_NV_PATH_RENDERING_LIST_MODE_1203031902_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Path list mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVListMode, GLenum)
#include <oglplus/enums/ext/nv_path_list_mode.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVListMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_list_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_list_mode_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
