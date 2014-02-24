/**
 *  @file advanced/cloud_trace/textures.cpp
 *  @brief Implementation of texture classes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "textures.hpp"

#include <oglplus/images/cloud.hpp>

namespace oglplus {
namespace cloud_trace {

CloudTexture::CloudTexture(RenderData& data)
{
	*this	<< TextureTarget::_3D
		<< TextureWrap::ClampToBorder
		<< TextureFilter::Linear
		<< images::Cloud(
			data.cloud_res,
			data.cloud_res,
			data.cloud_res,
			Vec3f(),
			0.5f
		);
}

} // namespace cloud_trace
} // namespace oglplus
