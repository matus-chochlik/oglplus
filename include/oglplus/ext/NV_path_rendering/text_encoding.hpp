/**
 *  @file oglplus/ext/NV_path_rendering/text_encoding.hpp
 *  @brief Wrapper for the NV_path_rendering text encoding enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_NV_PATH_RENDERING_TEXT_ENCODING_1203031902_HPP
#define OGLPLUS_EXT_NV_PATH_RENDERING_TEXT_ENCODING_1203031902_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Text encoding type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PathNVTextEncoding, GLenum)
#include <oglplus/enums/ext/nv_path_text_encoding.ipp>
OGLPLUS_ENUM_CLASS_END(PathNVTextEncoding)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/nv_path_text_encoding_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/nv_path_text_encoding_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
