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

Raytracer::Raytracer(RenderData& data, ResourceAllocator& alloc)
 : gl()
 , w(data.cols())
 , h(data.rows())
 , cloud_data(data)
 , cloud_tex(data, alloc)
 , raytrace_prog(data)
 , screen("Position", shapes::Screen(), raytrace_prog)
 , front(0)
 , back(1)
 , fbos(2)
 , texs(2)
{
	raytrace_prog.cloud_count.Set(cloud_data.CloudCount());

	gl.Viewport(0, 0, data.raytrace_width, data.raytrace_height);
	gl.Disable(Capability::ScissorTest);
	gl.ClearColor(1.0, 1.0, 1.0, 0.0);

	for(GLuint b=0; b!=2; ++b)
	{
		tex_units[b] = alloc.GetNextTexUnit();

		Texture::Active(tex_units[b]);

		texs[b]	<< TextureTarget::Rectangle
			<< TextureFilter::Linear
			<< TextureWrap::ClampToEdge
			<< images::ImageSpec(
				data.raytrace_width,
				data.raytrace_height,
				Format::RGBA,
				InternalFormat::RGBA32F,
				DataType::Float
			);

		fbos[b]	<< FramebufferTarget::Draw
			<< FramebufferAttachment::Color << texs[b];

		gl.Clear().ColorBuffer();
	}
}

void Raytracer::Use(RenderData& data)
{
	gl.Viewport(0, 0, data.raytrace_width, data.raytrace_height);
	fbos[back] << FramebufferTarget::Draw;
	raytrace_prog.Use();
	screen.Use();
}

void Raytracer::InitFrame(RenderData& data, unsigned cube_face)
{
	i = 0;
	j = 0;
	gl.Disable(Capability::ScissorTest);
	gl.ClearColor(1.0, 1.0, 1.0, 0.0); // TODO
	gl.Clear().ColorBuffer();
	gl.Enable(Capability::ScissorTest);

	Vec3f cx, cy, cz;

	switch(cube_face)
	{
		case 0: // +X
		{
			cx = +Vec3f::Unit(2);
			cy = +Vec3f::Unit(1);
			cz = +Vec3f::Unit(0);
			break;
		}
		case 1: // -X
		{
			cx = -Vec3f::Unit(2);
			cy = +Vec3f::Unit(1);
			cz = -Vec3f::Unit(0);
			break;
		}
		case 2: // +Y
		{
			cx = -Vec3f::Unit(0);
			cy = +Vec3f::Unit(2);
			cz = -Vec3f::Unit(1);
			break;
		}
		case 3: // -Y
		{
			cx = -Vec3f::Unit(0);
			cy = -Vec3f::Unit(2);
			cz = +Vec3f::Unit(1);
			break;
		}
		case 4: // +Z
		{
			cx = -Vec3f::Unit(0);
			cy = +Vec3f::Unit(1);
			cz = +Vec3f::Unit(2);
			break;
		}
		case 5: // -Z
		{
			cx = +Vec3f::Unit(0);
			cy = +Vec3f::Unit(1);
			cz = -Vec3f::Unit(2);
			break;
		}
		default: assert(!"Invalid cube face");
	}

	raytrace_prog.SetCamera(cx, cy, cz, data.cam_near, data.cam_far);
}

double Raytracer::Raytrace(RenderData& data)
{
	assert(i*j < w*h);

	gl.Scissor(i*data.tile, (h-j-1)*data.tile, data.tile, data.tile);

	if(++i >= w)
	{
		++j;
		i = 0;
	}

	screen.Draw();

	return double(j*h+i)/double(w*h);
}

void Raytracer::SwapBuffers(RenderData& data)
{
	fbos[back] << FramebufferTarget::Read;
	fbos[front] << FramebufferTarget::Draw;

	gl.Flush();
	gl.BlitFramebuffer(
		0, 0, data.raytrace_width, data.raytrace_height,
		0, 0, data.raytrace_width, data.raytrace_height,
		BufferSelectBit::ColorBuffer,
		BlitFilter::Nearest
	);

	front = (front+1)%2;
	back = (back+1)%2;

	fbos[back] << FramebufferTarget::Draw;
}

GLuint Raytracer::FrontTexUnit(void) const
{
	return tex_units[front];
}

} // namespace cloud_trace
} // namespace oglplus

