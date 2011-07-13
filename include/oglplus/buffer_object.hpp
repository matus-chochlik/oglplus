/**
 *  @file oglplus/buffer_object.hpp
 *  @brief Buffer object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BUFFER_OBJECT_1107121519_HPP
#define OGLPLUS_BUFFER_OBJECT_1107121519_HPP

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
		ThrowOnError();
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteBuffers(count, &_name);
	}
public:
	BufferOps(GLuint _n)
	 : _name(_n)
	{ }

	enum class Kind {
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

	void Bind(Kind target) const
	{
		::glBindBuffer(GLenum(target), _name);
	}
};

typedef Object<BufferOps> Buffer;

} // namespace oglplus

#endif // include guard
