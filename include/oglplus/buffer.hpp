/**
 *  @file oglplus/buffer.hpp
 *  @brief Buffer wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BUFFER_1107121519_HPP
#define OGLPLUS_BUFFER_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

class BufferOps
{
protected:
	GLuint _name;

	BufferOps(void)
	{ }

	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenBuffers(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteBuffers(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		return ::glIsBuffer(_name);
	}
public:
	BufferOps(GLuint _n)
	 : _name(_n)
	{ }

	enum class Target {
		Array = GL_ARRAY_BUFFER,
		CopyRead = GL_COPY_READ_BUFFER,
		CopyWrite = GL_COPY_WRITE_BUFFER,
		DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
		ElementArray = GL_ELEMENT_ARRAY_BUFFER,
		PixelPack = GL_PIXEL_PACK_BUFFER,
		PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
		TextureBuffer = GL_TEXTURE_BUFFER,
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
		Uniform = GL_UNIFORM_BUFFER
	};

	enum class Usage {
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY,
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY
	};

	void Bind(Target target) const
	{
		::glBindBuffer(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	static void Unbind(Target target)
	{
		::glBindBuffer(GLenum(target), 0);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	static void Data(
		Target target,
		GLfloat* data,
		GLsizei count,
		Usage usage = Usage::StaticDraw
	)
	{
		::glBufferData(
			GLenum(target),
			count * sizeof(GLfloat),
			data,
			GLenum(usage)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void Data(
		Target target,
		const std::vector<GLfloat>& data,
		Usage usage = Usage::StaticDraw
	)
	{
		::glBufferData(
			GLenum(target),
			data.size() * sizeof(GLfloat),
			data.data(),
			GLenum(usage)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}
};

typedef Object<BufferOps> Buffer;

} // namespace oglplus

#endif // include guard
