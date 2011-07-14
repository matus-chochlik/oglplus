/**
 *  @file oglplus/texture.hpp
 *  @brief Texture object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXTURE_1107121519_HPP
#define OGLPLUS_TEXTURE_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

class TextureOps
{
protected:
	GLuint _name;

	TextureOps(void)
	{ }

	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenTextures(count, &_name);
		ThrowOnError();
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteTextures(count, &_name);
	}
public:
	TextureOps(GLuint _n)
	 : _name(_n)
	{ }

	enum class Target {
		_1D = GL_TEXTURE_1D,
		_2D = GL_TEXTURE_2D,
		_3D = GL_TEXTURE_3D,
		_1DArray = GL_TEXTURE_1D_ARRAY,
		_2DArray = GL_TEXTURE_2D_ARRAY,
		Rectangle = GL_TEXTURE_RECTANGLE,
		Buffer = GL_TEXTURE_BUFFER,
		CubeMap = GL_TEXTURE_CUBE_MAP,
		//TODO: CubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
		_2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
		_2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
	};

	void Bind(Target target) const
	{
		::glBindTexture(GLenum(target), _name);
		AssertNoError();
	}

	static void Unbind(Target target)
	{
		::glBindTexture(GLenum(target), 0);
		AssertNoError();
	}
};

typedef Object<TextureOps> Texture;

} // namespace oglplus

#endif // include guard
