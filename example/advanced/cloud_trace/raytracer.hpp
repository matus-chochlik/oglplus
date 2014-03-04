/**
 *  @file advanced/cloud_trace/raytracer.hpp
 *  @brief Declares the raytracer class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_ADVANCED_CLOUD_TRACE_RAYTRACER_1119071146_HPP
#define OGLPLUS_ADVANCED_CLOUD_TRACE_RAYTRACER_1119071146_HPP

#include "app_data.hpp"
#include "cloud_data.hpp"
#include "programs.hpp"
#include "textures.hpp"

#include <oglplus/gl.hpp>
#include <oglplus/fix_gl_version.hpp>

#include <oglplus/context.hpp>
#include <oglplus/framebuffer.hpp>
#include <oglplus/renderbuffer.hpp>
#include <oglplus/shapes/wrapper.hpp>

#include <array>

namespace oglplus {
namespace cloud_trace {

struct RaytracerResources
{
	CloudData cloud_data;
	CloudTexture cloud_tex;

	RaytraceProg raytrace_prog;

	const GLuint dest_tex_unit;
	Texture dest_tex;

	RaytracerResources(AppData&, ResourceAllocator&);
};

class Raytracer
{
private:
	Context gl;

	const unsigned w, h;

	RaytracerResources& resources;

	shapes::ShapeWrapper screen;

	Renderbuffer rbo;
	Framebuffer rt_fbo, cp_fbo;
public:
	Raytracer(AppData&, RaytracerResources&);

	void Use(AppData&);
	void Raytrace(AppData&, unsigned face, unsigned tile);

	void BlitBuffers(AppData&, unsigned tile);
};

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
