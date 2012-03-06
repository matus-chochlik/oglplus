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
namespace ext {

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
};
#endif

} // namespace ext
} // namespace oglplus

#endif // include guard
