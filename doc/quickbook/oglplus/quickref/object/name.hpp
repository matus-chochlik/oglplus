/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_object_name

template <typename __ObjTag>
class ObjectName {
public:
    ObjectName() noexcept; /*<
    Constructs a wrapper for object
    with name [^0] (zero).
    >*/

    explicit ObjectName(GLuint name) noexcept; /*<
    Constructs a wrapper for an object
    with the specified [^name].
    >*/

    ObjectName(const ObjectName&) noexcept;
    ObjectName(ObjectName&&) noexcept;

    ObjectName& operator=(const ObjectName&) noexcept;
    ObjectName& operator=(ObjectName&&) noexcept;

    friend bool operator==(ObjectName, ObjectName);
    friend bool operator!=(ObjectName, ObjectName);
    friend bool operator<(ObjectName, ObjectName);
};

template <typename ObjTag>
GLuint GetGLName(__ObjectName<__ObjTag> named); /*<
    Allows to access the 'raw' GL object name.
>*/

//]
//[oglplus_object_name_type_aliases

using RenderbufferName = __ObjectName<tag::Renderbuffer>;
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

//]
