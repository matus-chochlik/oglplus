/**
 *  @file advanced/cloud_trace/copier_default.cpp
 *  @brief Implements the default class that handles copying of raytrace output
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "copier_default.hpp"

#include <oglplus/binding.hpp>

namespace oglplus {
namespace cloud_trace {

RaytraceCopier::RaytraceCopier(AppData&, RaytraceTarget& target)
 : rt_target(target)
{
	AutoRebind<Framebuffer> rebind_fb(FramebufferTarget::Draw);

	fbo	<< FramebufferTarget::Draw
		<< FramebufferAttachment::Color << target.tex;
}

void RaytraceCopier::Copy(
	AppData& app_data,
	Raytracer& raytracer,
	unsigned tile
)
{
	const unsigned w = app_data.cols();
	const unsigned h = app_data.rows();
	unsigned i = tile % w;
	unsigned j = tile / w;
	assert(j*h+i < w*h);

	j = h-j-1;

	raytracer.fbo << FramebufferTarget::Read;
	fbo << FramebufferTarget::Draw;

	gl.Flush();
	gl.BlitFramebuffer(
		app_data.tile*(i+0),
		app_data.tile*(j+0),
		app_data.tile*(i+1),
		app_data.tile*(j+1),
		app_data.tile*(i+0),
		app_data.tile*(j+0),
		app_data.tile*(i+1),
		app_data.tile*(j+1),
		BufferSelectBit::ColorBuffer,
		BlitFilter::Nearest
	);

	raytracer.fbo << FramebufferTarget::Draw;
}

} // namespace cloud_trace
} // namespace oglplus
