/**
 *  @file advanced/cloud_trace/textures.hpp
 *  @brief Declaration of texture classes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_ADVANCED_CLOUD_TRACE_TEXTURES_1119071146_HPP
#define OGLPLUS_ADVANCED_CLOUD_TRACE_TEXTURES_1119071146_HPP

#include "render_data.hpp"

#include <oglplus/gl.hpp>
#include <oglplus/fix_gl_version.hpp>
#include <oglplus/texture.hpp>

namespace oglplus {
namespace cloud_trace {

class CloudTexture : public Texture
{
public:
	CloudTexture(RenderData& data);
};

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
