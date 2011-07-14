/**
 *  @file oglplus/framebuffer.hpp
 *  @brief Framebuffer object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_FRAMEBUFFER_1107121519_HPP
#define OGLPLUS_FRAMEBUFFER_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

class FramebufferOps
{
protected:
	GLuint _name;

	FramebufferOps(void)
	{ }

	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenFramebuffers(count, &_name);
		ThrowOnError();
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteFramebuffers(count, &_name);
	}
public:
	FramebufferOps(GLuint _n)
	 : _name(_n)
	{ }

	enum class Target {
		Draw = GL_DRAW_FRAMEBUFFER,
		Read = GL_READ_FRAMEBUFFER
	};

	void Bind(Target target) const
	{
		::glBindFramebuffer(GLenum(target), _name);
		AssertNoError();
	}

	static void Unbind(Target target)
	{
		::glBindFramebuffer(GLenum(target), 0);
		AssertNoError();
	}
};

typedef Object<FramebufferOps> Framebuffer;

} // namespace oglplus

#endif // include guard
