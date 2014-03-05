/**
 *  @file advanced/cloud_trace/copier_default.hpp
 *  @brief Declares the default class that handles copying of raytrace output
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_ADVANCED_CLOUD_TRACE_COPIER_DEFAULT_1119071146_HPP
#define OGLPLUS_ADVANCED_CLOUD_TRACE_COPIER_DEFAULT_1119071146_HPP

#include "app_data.hpp"
#include "raytracer.hpp"

#include <oglplus/gl.hpp>
#include <oglplus/fix_gl_version.hpp>

#include <oglplus/context.hpp>
#include <oglplus/framebuffer.hpp>

namespace oglplus {
namespace cloud_trace {

class RaytraceCopier
{
private:
	RaytraceTarget& rt_target;

	Context gl;
	Framebuffer fbo;
public:
	RaytraceCopier(AppData&, RaytraceTarget&);

	void Copy(AppData&, Raytracer&, unsigned tile);
};

} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
