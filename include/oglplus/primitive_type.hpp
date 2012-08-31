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
 *
 *  @glsymbols
 *  @glfunref{DrawArrays}
 *  @glfunref{DrawArraysInstanced}
 *  @glfunref{DrawElements}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PrimitiveType, GLenum)
#include <oglplus/enums/primitive_type.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	PrimitiveType*,
	EnumBaseType<PrimitiveType>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/primitive_type.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif

/// Tesselation generation stage primitive type
/**
 * @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TessGenPrimitiveType, GLenum)
#include <oglplus/enums/tess_gen_primitive_type.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	TessGenPrimitiveType*,
	EnumBaseType<TessGenPrimitiveType>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/tess_gen_primitive_type.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif

/// Tesselation primitive spacing
/**
 * @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TessGenPrimitiveSpacing, GLenum)
#include <oglplus/enums/tess_gen_primitive_spacing.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	TessGenPrimitiveSpacing*,
	EnumBaseType<TessGenPrimitiveSpacing>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/tess_gen_primitive_spacing.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif

} // namespace oglplus

#endif // include guard
