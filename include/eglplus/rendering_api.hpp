/**
 *  @file eglplus/rendering_api.hpp
 *  @brief EGL rendering API enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_RENDERING_API_1303292057_HPP
#define EGLPLUS_RENDERING_API_1303292057_HPP

#include <eglplus/enumerations.hpp>
#include <eglplus/eglfunc.hpp>
#include <eglplus/error/basic.hpp>

namespace eglplus {

/// Rendering API enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(RenderingAPI, EGLenum)
#include <eglplus/enums/rendering_api.ipp>
EGLPLUS_ENUM_CLASS_END(RenderingAPI)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/rendering_api_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/rendering_api_range.ipp>
#endif

/// Bind the specified rendering API
/**
 *  @eglsymbols
 *  @eglfunref{BindAPI}
 */
inline bool BindAPI(RenderingAPI api)
{
	bool result = EGLPLUS_EGLFUNC(BindAPI)(EGLenum(api));
	EGLPLUS_VERIFY_SIMPLE(BindAPI);
	return result;
}

/// Query the currently bound rendering API
/**
 *  @eglsymbols
 *  @eglfunref{QueryAPI}
 */
inline RenderingAPI QueryAPI(void)
{
	EGLenum result = EGLPLUS_EGLFUNC(QueryAPI)();
	EGLPLUS_VERIFY_SIMPLE(QueryAPI);
	return RenderingAPI(result);
}

} // namespace eglplus

#endif // include guard
