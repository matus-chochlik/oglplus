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

#include <oglplus/binding.hpp>
#include <oglplus/plane.hpp>
#include <oglplus/shapes/screen.hpp>
#include <oglplus/images/image_spec.hpp>

#include <cassert>

namespace oglplus {
namespace cloud_trace {

RaytracerData::RaytracerData(const AppData& app_data)
 : cloud_data(app_data)
 , cloud_vol(app_data)
{ }

RaytracerResources::RaytracerResources(
	const AppData& app_data,
	const RaytracerData& rt_data,
	ResourceAllocator& alloc
): cloud_buf(app_data, rt_data.cloud_data, alloc)
 , cloud_tex(app_data, rt_data.cloud_vol, alloc)
 , raytrace_prog(app_data)
{ }

void RaytracerResources::Use(void)
{
	cloud_buf.Use();
	cloud_tex.Use();
	raytrace_prog.Use();
	raytrace_prog.cloud_tex.Set(cloud_tex.tex_unit);
	raytrace_prog.cloud_count.Set(cloud_buf.count);
	raytrace_prog.cloud_block.Binding(cloud_buf.ub_idx);
}

RaytracerTarget::RaytracerTarget(
	AppData& app_data,
	ResourceAllocator& alloc
): tex_unit(alloc.GetNextTexUnit())
{
	AutoRebind<Framebuffer> rebind_fb(FramebufferTarget::Draw);
	Texture::Active(tex_unit);

	tex	<< TextureTarget::Rectangle
		<< TextureFilter::Nearest
		<< TextureWrap::ClampToBorder
		<< images::ImageSpec(
			app_data.raytrace_width,
			app_data.raytrace_height,
			Format::RGBA,
			InternalFormat::RGBA32F,
			DataType::Float
		);

	fbo	<< FramebufferTarget::Draw
		<< FramebufferAttachment::Color << tex;
}

void RaytracerTarget::Clear(AppData& app_data)
{
	AutoRebind<Framebuffer> rebind_fb(FramebufferTarget::Draw);
	fbo << FramebufferTarget::Draw;

	gl.Viewport(0, 0, app_data.raytrace_width, app_data.raytrace_height);
	gl.ClearColor(1.0, 1.0, 1.0, 0.5);
	gl.Clear().ColorBuffer();
}

Raytracer::Raytracer(AppData& app_data, RaytracerResources& res)
 : gl()
 , w(app_data.cols())
 , h(app_data.rows())
 , resources(res)
 , screen("Position", shapes::Screen(), resources.raytrace_prog)
{
	rbo	<< RenderbufferTarget::Renderbuffer
		<< images::ImageSpec(
			app_data.raytrace_width,
			app_data.raytrace_height,
			InternalFormat::RGBA32F
		);

	fbo	<< FramebufferTarget::Draw
		<< FramebufferAttachment::Color << rbo;
}

void Raytracer::Use(AppData&)
{
	fbo << FramebufferTarget::Draw;
	resources.Use();
	screen.Use();
}

void Raytracer::InitFrame(AppData& app_data, unsigned face)
{
	gl.Viewport(0, 0, app_data.raytrace_width, app_data.raytrace_height);
	gl.ClearColor(0.0, 0.0, 0.0, 0.0);
	gl.Clear().ColorBuffer();

	resources.raytrace_prog.SetRayMatrix(app_data, face);
}

void Raytracer::Raytrace(AppData& app_data, unsigned tile)
{
	unsigned i = tile % w;
	unsigned j = tile / w;
	assert(j*h+i < w*h);

	int sx = app_data.tile*i;
	int sy = app_data.tile*(h-j-1);
	int ss = app_data.tile;
	float iw = 2.0f/app_data.raytrace_width;
	float ih = 2.0f/app_data.raytrace_height;

	gl.Enable(Capability::ScissorTest);
	gl.Enable(Functionality::ClipDistance, 0);
	gl.Enable(Functionality::ClipDistance, 1);
	gl.Enable(Functionality::ClipDistance, 2);
	gl.Enable(Functionality::ClipDistance, 3);

	gl.Scissor(sx, sy, ss, ss);

	resources.raytrace_prog.clip_plane0.Set(
		Planef::FromPointAndNormal(
			Vec3f((sx-1)*iw-1, 0, 1),
			Vec3f( 1, 0, 0)
		).Equation()
	);

	resources.raytrace_prog.clip_plane1.Set(
		Planef::FromPointAndNormal(
			Vec3f((sx+ss+1)*iw-1, 0, 1),
			Vec3f(-1, 0, 0)
		).Equation()
	);

	resources.raytrace_prog.clip_plane2.Set(
		Planef::FromPointAndNormal(
			Vec3f(0, (sy-1)*ih-1, 1),
			Vec3f( 0, 1, 0)
		).Equation()
	);

	resources.raytrace_prog.clip_plane3.Set(
		Planef::FromPointAndNormal(
			Vec3f(0, (sy+ss+1)*ih-1, 1),
			Vec3f( 0,-1, 0)
		).Equation()
	);

	screen.Draw();

	gl.Disable(Capability::ScissorTest);
	gl.Disable(Functionality::ClipDistance, 0);
	gl.Disable(Functionality::ClipDistance, 1);
	gl.Disable(Functionality::ClipDistance, 2);
	gl.Disable(Functionality::ClipDistance, 3);
}

} // namespace cloud_trace
} // namespace oglplus

