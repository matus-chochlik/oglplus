/**
 *  @file advanced/cloud_trace/renderer.cpp
 *  @brief Implements the renderer class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "renderer.hpp"

#include <oglplus/shapes/screen.hpp>

#include <cassert>

namespace oglplus {
namespace cloud_trace {

Renderer::Renderer(RenderData& data)
 : gl()
 , w(data.cols())
 , h(data.rows())
 , cloud_data(data)
 , cloud_tex(data)
 , raytrace_prog(data)
 , screen("Position", shapes::Screen(), raytrace_prog)
{
	raytrace_prog.cloud_count.Set(cloud_data.CloudCount());

	gl.Viewport(0, 0, data.width, data.height);
	gl.Enable(Capability::Blend);
	gl.BlendFunc(BlendFn::SrcAlpha, BlendFn::OneMinusSrcAlpha);

	raytrace_prog.Use();
	screen.Use();
}

void Renderer::InitFrame(RenderData& data, unsigned cube_face)
{
	i = 0;
	j = 0;
	gl.Disable(Capability::ScissorTest);
	gl.ClearColor(0.4, 0.4, 0.8, 0.0);
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
			cx = +Vec3f::Unit(0);
			cy = +Vec3f::Unit(2);
			cz = +Vec3f::Unit(1);
			break;
		}
		case 3: // -Y
		{
			cx = +Vec3f::Unit(0);
			cy = +Vec3f::Unit(2);
			cz = -Vec3f::Unit(1);
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

double Renderer::Render(RenderData& data)
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

} // namespace cloud_trace
} // namespace oglplus

