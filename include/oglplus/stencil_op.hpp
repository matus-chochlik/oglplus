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
enum class StencilOperation : GLenum
{
	Keep = GL_KEEP,
	Zero = GL_ZERO,
	Replace = GL_REPLACE,
	Incr = GL_INCR,
	Decr = GL_DECR,
	Invert = GL_INVERT,
	IncrWrap = GL_INCR_WRAP,
	DercWrap = GL_DECR_WRAP
};

typedef StencilOperation StencilOp;

} // namespace oglplus

#endif // include guard
