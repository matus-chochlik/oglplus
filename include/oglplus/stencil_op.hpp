/**
 *  @file oglplus/stencil_op.hpp
 *  @brief OpenGL stencil operation enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_STENCIL_FUNC_1107121519_HPP
#define OGLPLUS_STENCIL_FUNC_1107121519_HPP

namespace oglplus {

/// Stencil operation type enumeration
/**
 *  @ingroup enumerations
 */
enum class StencilOperation : GLenum
{
#include <oglplus/enums/stencil_operation.ipp>
};

/// Alternate name for the StencilOperation enumeration
typedef StencilOperation StencilOp;

} // namespace oglplus

#endif // include guard
