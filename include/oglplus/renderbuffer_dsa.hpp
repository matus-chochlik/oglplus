/**
 *  @file oglplus/renderbuffer_dsa.hpp
 *  @brief Renderbuffer object wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_RENDERBUFFER_DSA_1310102147_HPP
#define OGLPLUS_RENDERBUFFER_DSA_1310102147_HPP

#if GL_EXT_direct_state_access
#include <oglplus/ext/EXT_direct_state_access/renderbuffer.hpp>
#else
#error Direct State Access Renderbuffers not available
#endif

namespace oglplus {

#if GL_EXT_direct_state_access
typedef DSARenderbufferEXTOps DSARenderbufferOps;
typedef DSARenderbufferEXT DSARenderbuffer;
#endif

} // namespace oglplus

#endif // include guard
