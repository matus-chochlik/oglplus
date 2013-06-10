/*
 *  .file oglplus/enums/object_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/object_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/object.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_object_type(void)
{
	boost::python::enum_<oglplus::ObjectType>("ObjectType")
#if defined GL_BUFFER
# if defined Buffer
#  pragma push_macro("Buffer")
#  undef Buffer
	.value("Buffer", oglplus::ObjectType::Buffer)
#  pragma pop_macro("Buffer")
# else
	.value("Buffer", oglplus::ObjectType::Buffer)
# endif
#endif
#if defined GL_FRAMEBUFFER
# if defined Framebuffer
#  pragma push_macro("Framebuffer")
#  undef Framebuffer
	.value("Framebuffer", oglplus::ObjectType::Framebuffer)
#  pragma pop_macro("Framebuffer")
# else
	.value("Framebuffer", oglplus::ObjectType::Framebuffer)
# endif
#endif
#if defined GL_PROGRAM_PIPELINE
# if defined ProgramPipeline
#  pragma push_macro("ProgramPipeline")
#  undef ProgramPipeline
	.value("ProgramPipeline", oglplus::ObjectType::ProgramPipeline)
#  pragma pop_macro("ProgramPipeline")
# else
	.value("ProgramPipeline", oglplus::ObjectType::ProgramPipeline)
# endif
#endif
#if defined GL_PROGRAM
# if defined Program
#  pragma push_macro("Program")
#  undef Program
	.value("Program", oglplus::ObjectType::Program)
#  pragma pop_macro("Program")
# else
	.value("Program", oglplus::ObjectType::Program)
# endif
#endif
#if defined GL_QUERY
# if defined Query
#  pragma push_macro("Query")
#  undef Query
	.value("Query", oglplus::ObjectType::Query)
#  pragma pop_macro("Query")
# else
	.value("Query", oglplus::ObjectType::Query)
# endif
#endif
#if defined GL_RENDERBUFFER
# if defined Renderbuffer
#  pragma push_macro("Renderbuffer")
#  undef Renderbuffer
	.value("Renderbuffer", oglplus::ObjectType::Renderbuffer)
#  pragma pop_macro("Renderbuffer")
# else
	.value("Renderbuffer", oglplus::ObjectType::Renderbuffer)
# endif
#endif
#if defined GL_SAMPLER
# if defined Sampler
#  pragma push_macro("Sampler")
#  undef Sampler
	.value("Sampler", oglplus::ObjectType::Sampler)
#  pragma pop_macro("Sampler")
# else
	.value("Sampler", oglplus::ObjectType::Sampler)
# endif
#endif
#if defined GL_SHADER
# if defined Shader
#  pragma push_macro("Shader")
#  undef Shader
	.value("Shader", oglplus::ObjectType::Shader)
#  pragma pop_macro("Shader")
# else
	.value("Shader", oglplus::ObjectType::Shader)
# endif
#endif
#if defined GL_TEXTURE
# if defined Texture
#  pragma push_macro("Texture")
#  undef Texture
	.value("Texture", oglplus::ObjectType::Texture)
#  pragma pop_macro("Texture")
# else
	.value("Texture", oglplus::ObjectType::Texture)
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK
# if defined TransformFeedback
#  pragma push_macro("TransformFeedback")
#  undef TransformFeedback
	.value("TransformFeedback", oglplus::ObjectType::TransformFeedback)
#  pragma pop_macro("TransformFeedback")
# else
	.value("TransformFeedback", oglplus::ObjectType::TransformFeedback)
# endif
#endif
#if defined GL_VERTEX_ARRAY
# if defined VertexArray
#  pragma push_macro("VertexArray")
#  undef VertexArray
	.value("VertexArray", oglplus::ObjectType::VertexArray)
#  pragma pop_macro("VertexArray")
# else
	.value("VertexArray", oglplus::ObjectType::VertexArray)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::ObjectType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::ObjectType
		>
	>("aux_CastIterRange_ObjectType");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::ObjectType
	> (*PEnumValueRange)(oglplus::ObjectType) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
