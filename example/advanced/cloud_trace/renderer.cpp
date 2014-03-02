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
#include <oglplus/opt/list_init.hpp>

#include <cassert>

namespace oglplus {
namespace cloud_trace {

Renderer::Renderer(RenderData& data, ResourceAllocator&)
 : gl()
 , render_prog(data)
 , screen(List("Position")("TexCoord").Get(), shapes::Screen(), render_prog)
{
}

void Renderer::Use(RenderData&)
{
	Framebuffer::BindDefault(FramebufferTarget::Draw);
	render_prog.Use();
	screen.Use();
}

void Renderer::Render(RenderData& data, Raytracer& raytracer)
{
	gl.Viewport(0, 0, data.render_width, data.render_height);
	render_prog.raytrace_size.Set(data.raytrace_width, data.raytrace_height);
	render_prog.raytrace_output.Set(raytracer.FrontTexUnit());

	screen.Draw();
}

} // namespace cloud_trace
} // namespace oglplus

