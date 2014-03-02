/**
 *  @file advanced/cloud_trace/renderer.hpp
 *  @brief Declares the renderer class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_ADVANCED_CLOUD_TRACE_RENDERER_1119071146_HPP
#define OGLPLUS_ADVANCED_CLOUD_TRACE_RENDERER_1119071146_HPP

#include "raytracer.hpp"

#include <oglplus/gl.hpp>
#include <oglplus/fix_gl_version.hpp>

#include <oglplus/context.hpp>
#include <oglplus/shapes/wrapper.hpp>

namespace oglplus {
namespace cloud_trace {

class Renderer
{
private:
	Context gl;

	RenderProg render_prog;

	shapes::ShapeWrapper screen;
public:
	Renderer(RenderData&, ResourceAllocator&);

	void Use(RenderData&);
	void Render(RenderData&, Raytracer&);
};

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
