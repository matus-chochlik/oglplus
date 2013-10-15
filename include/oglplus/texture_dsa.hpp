/**
 *  @file oglplus/texture_dsa.hpp
 *  @brief Texture object wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_DSA_1310102147_HPP
#define OGLPLUS_TEXTURE_DSA_1310102147_HPP

#if GL_EXT_direct_state_access
#include <oglplus/ext/EXT_direct_state_access/texture.hpp>
#else
#error Direct State Access Textures not available
#endif

namespace oglplus {

#if GL_EXT_direct_state_access
typedef DSATextureEXTOps DSATextureOps;
typedef DSATextureEXT DSATexture;
#endif

} // namespace oglplus

#endif // include guard
