/**
 *  @file oglplus/polygon_mode.hpp
 *  @brief OpenGL polygon rasterization mode-related enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_POLYGON_MODE_1107121519_HPP
#define OGLPLUS_POLYGON_MODE_1107121519_HPP

namespace oglplus {

/// Polygon rasterization mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{PolygonMode}
 */
enum class PolygonMode : GLenum
{
#include <oglplus/enums/polygon_mode.ipp>
};

inline StrLit EnumValueName(PolygonMode value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/polygon_mode.ipp>
#endif
	return StrLit();
}

} // namespace oglplus

#endif // include guard
