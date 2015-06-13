//  File doc/quickbook/oglplus/quickref/enums/object_type.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/object_type.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_object_type

enum class ObjectType : GLenum
{
	Buffer            = GL_BUFFER,
	Framebuffer       = GL_FRAMEBUFFER,
	ProgramPipeline   = GL_PROGRAM_PIPELINE,
	Program           = GL_PROGRAM,
	Query             = GL_QUERY,
	Renderbuffer      = GL_RENDERBUFFER,
	Sampler           = GL_SAMPLER,
	Shader            = GL_SHADER,
	Texture           = GL_TEXTURE,
	TransformFeedback = GL_TRANSFORM_FEEDBACK,
	VertexArray       = GL_VERTEX_ARRAY,
	None              = GL_NONE
};

template <>
__Range<ObjectType> __EnumValueRange<ObjectType>(void);

__StrCRef __EnumValueName(ObjectType);

//]
