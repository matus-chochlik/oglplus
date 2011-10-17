/**
 *  @file oglplus/capability.hpp
 *  @brief Enumeration of OpenGL capabilities that can be Enabled/Disabled
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CAPABILITY_1107121519_HPP
#define OGLPLUS_CAPABILITY_1107121519_HPP

namespace oglplus {

/// Capability enumeration
/**
 *  @ingroup enumerations
 */
enum class Capability: GLenum
{
#include <oglplus/enums/capability.ipp>
};

} // namespace oglplus

#endif // include guard
