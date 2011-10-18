/**
 *  @file oglplus/primitive_type.hpp
 *  @brief OpenGL primitive type-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PRIMITIVE_TYPE_1107121519_HPP
#define OGLPLUS_PRIMITIVE_TYPE_1107121519_HPP

namespace oglplus {

/// Primitive type enumeration
/**
 *  @ingroup enumerations
 */
enum class PrimitiveType : GLenum
{
#include <oglplus/enums/primitive_type.ipp>
};

/// Tesselation generation stage primitive type
/**
 * @ingroup enumerations
 */
enum class TessGenPrimitiveType : GLenum
{
#include <oglplus/enums/tess_gen_primitive_type.ipp>
};

/// Tesselation primitive spacing
/**
 * @ingroup enumerations
 */
enum class TessGenPrimitiveSpacing : GLenum
{
#include <oglplus/enums/tess_gen_primitive_spacing.ipp>
};

} // namespace oglplus

#endif // include guard
