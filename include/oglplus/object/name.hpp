/**
 *  @file oglplus/object/name.hpp
 *  @brief Base class for OpenGL "named" objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_NAME_1107121519_HPP
#define OGLPLUS_OBJECT_NAME_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/object/name_tpl.hpp>
#include <oglplus/object/tags.hpp>

namespace oglplus {

using RenderbufferName = ObjectName<tag::Renderbuffer>;
using FramebufferName = ObjectName<tag::Framebuffer>;
using TextureName = ObjectName<tag::Texture>;
using BufferName = ObjectName<tag::Buffer>;
using QueryName = ObjectName<tag::Query>;
using ProgramPipelineName = ObjectName<tag::ProgramPipeline>;
using ProgramName = ObjectName<tag::Program>;
using TransformFeedbackName = ObjectName<tag::TransformFeedback>;
using SamplerName = ObjectName<tag::Sampler>;
using VertexArrayName = ObjectName<tag::VertexArray>;
using ShaderName = ObjectName<tag::Shader>;
using PerfMonitorAMDName = ObjectName<tag::PerfMonitorAMD>;
using PathNVName = ObjectName<tag::PathNV>;

/// Returns the GLuint OpenGL name assigned to @p named object
template <typename ObjTag>
inline GLuint GetGLName(ObjectName<ObjTag> named) noexcept {
    return GetName(named);
}

} // namespace oglplus

#endif // include guard
