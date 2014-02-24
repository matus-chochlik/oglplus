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

#include "render_data.hpp"
#include "cloud_data.hpp"
#include "programs.hpp"
#include "textures.hpp"

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

	unsigned i, j, w, h;

	CloudData cloud_data;
	CloudTexture cloud_tex;
	RaytraceProg raytrace_prog;

	shapes::ShapeWrapper screen;
public:
	Renderer(RenderData& data);

	void InitFrame(RenderData&, unsigned);
	double Render(RenderData&);
};

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
