/**
 *  @file advanced/cloud_trace/raytracer.cpp
 *  @brief Implements the raytracer class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "raytracer.hpp"

#include <oglplus/shapes/screen.hpp>
#include <oglplus/images/image_spec.hpp>

#include <cassert>

namespace oglplus {
namespace cloud_trace {

RaytracerResources::RaytracerResources(
	AppData& app_data,
	ResourceAllocator& alloc
): cloud_data(app_data)
 , cloud_tex(app_data, alloc)
 , raytrace_prog(app_data)
 , dest_tex_unit(alloc.GetNextTexUnit())
{
	raytrace_prog.cloud_count.Set(cloud_data.CloudCount());

	Texture::Active(dest_tex_unit);

	dest_tex<< TextureTarget::Rectangle
		<< TextureFilter::Linear
		<< TextureWrap::ClampToBorder
		<< images::ImageSpec(
			app_data.raytrace_width,
			app_data.raytrace_height,
			Format::RGBA,
			InternalFormat::RGBA32F,
			DataType::Float
		);
}

Raytracer::Raytracer(AppData& app_data, RaytracerResources& res)
 : gl()
 , w(app_data.cols())
 , h(app_data.rows())
 , resources(res)
 , screen("Position", shapes::Screen(), resources.raytrace_prog)
{
	gl.Disable(Capability::ScissorTest);
	gl.Viewport(0, 0, app_data.raytrace_width, app_data.raytrace_height);

	rbo	<< RenderbufferTarget::Renderbuffer
		<< images::ImageSpec(
			app_data.raytrace_width,
			app_data.raytrace_height,
			InternalFormat::RGBA32F
		);

	rt_fbo	<< FramebufferTarget::Draw
		<< FramebufferAttachment::Color << rbo;

	gl.ClearColor(0.0, 0.0, 0.0, 0.0);
	gl.Clear().ColorBuffer();

	cp_fbo	<< FramebufferTarget::Draw
		<< FramebufferAttachment::Color << res.dest_tex;

	gl.ClearColor(1.0, 1.0, 1.0, 1.0);
	gl.Clear().ColorBuffer();
}

void Raytracer::Use(AppData& app_data)
{
	rt_fbo << FramebufferTarget::Draw;
	gl.Viewport(0, 0, app_data.raytrace_width, app_data.raytrace_height);
	resources.raytrace_prog.Use();
	screen.Use();
}


void Raytracer::Raytrace(AppData& app_data, unsigned face, unsigned tile)
{
	unsigned i = tile % w;
	unsigned j = tile / w;
	assert(j*h+i < w*h);

	gl.Disable(Capability::ScissorTest);
	gl.ClearColor(0.0, 0.0, 0.0, 0.0);
	gl.Clear().ColorBuffer();
	gl.Enable(Capability::ScissorTest);

	Vec3f cx, cy, cz;

	switch(face)
	{
		case 0: // +X
		{
			cx = +Vec3f::Unit(2);
			cy = +Vec3f::Unit(1);
			cz = -Vec3f::Unit(0);
			break;
		}
		case 1: // -X
		{
			cx = -Vec3f::Unit(2);
			cy = +Vec3f::Unit(1);
			cz = +Vec3f::Unit(0);
			break;
		}
		case 2: // +Y
		{
			cx = -Vec3f::Unit(0);
			cy = +Vec3f::Unit(2);
			cz = +Vec3f::Unit(1);
			break;
		}
		case 3: // -Y
		{
			cx = -Vec3f::Unit(0);
			cy = -Vec3f::Unit(2);
			cz = -Vec3f::Unit(1);
			break;
		}
		case 4: // +Z
		{
			cx = -Vec3f::Unit(0);
			cy = +Vec3f::Unit(1);
			cz = -Vec3f::Unit(2);
			break;
		}
		case 5: // -Z
		{
			cx = +Vec3f::Unit(0);
			cy = +Vec3f::Unit(1);
			cz = +Vec3f::Unit(2);
			break;
		}
		default: assert(!"Invalid cube face");
	}

	resources.raytrace_prog.SetRayMatrix(
		CamMatrixf::PerspectiveX(
			RightAngle(), 1,
			app_data.cam_near,
			app_data.cam_far
		)* Mat4f(
			Vec4f(cx, 0),
			Vec4f(cy, 0),
			Vec4f(cz, 0),
			Vec4f::Unit(3)
		)
	);

	gl.Scissor(
		app_data.tile*i,
		app_data.tile*(h-j-1),
		app_data.tile,
		app_data.tile
	);

	screen.Draw();
}

void Raytracer::BlitBuffers(AppData& app_data, unsigned tile)
{
	unsigned i = tile % w;
	unsigned j = tile / w;
	assert(j*h+i < w*h);

	j = h-j-1;

	rt_fbo << FramebufferTarget::Read;
	cp_fbo << FramebufferTarget::Draw;

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

	rt_fbo << FramebufferTarget::Draw;
}

} // namespace cloud_trace
} // namespace oglplus

