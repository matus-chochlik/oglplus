/**
 *  @file oglplus/ext/ARB/compatibility.hpp
 *  @brief Wrapper for the ARB_compatibility extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXT_ARB_COMPATIBILITY_1203031902_HPP
#define OGLPLUS_EXT_ARB_COMPATIBILITY_1203031902_HPP

#include <oglplus/extension.hpp>

namespace oglplus {

/// Compatibility primitive type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Begin}
 *  @glextref{ARB,compatibility}
 */
enum class CompatibilityPrimitiveType : GLenum
{
#include <oglplus/enums/ext/compat_prim_type.ipp>
};

/// Shorter name for CompatibilityPrimitiveType
typedef CompatibilityPrimitiveType CompatPrimType;

inline const GLchar* EnumValueName(CompatibilityPrimitiveType value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/ext/compat_prim_type.ipp>
#endif
	return "";
}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_compatibility
/// Wrapper for the ARB_compatibility extension
/**
 *  @glsymbols
 *  @glextref{ARB,compatibility}
 *
 *  @ingroup extensions
 */
class ARB_compatibility
{
public:
	OGLPLUS_EXTENSION_CLASS(ARB, compatibility)

	/// Begins geometric object specification
	/**
	 *  @glsymbols
	 *  @glfunref{Begin}
	 */
	static void Begin(CompatibilityPrimitiveType mode)
	{
		OGLPLUS_GLFUNC(Begin)(GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(Begin));
	}

	/// Ends geometric object specification
	/**
	 *  @glsymbols
	 *  @glfunref{End}
	 */
	static void End(void)
	{
		OGLPLUS_GLFUNC(End)();
		AssertNoError(OGLPLUS_ERROR_INFO(End));
	}
};
#endif

} // namespace oglplus

#endif // include guard
