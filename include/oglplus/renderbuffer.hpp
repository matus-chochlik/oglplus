/**
 *  @file oglplus/renderbuffer.hpp
 *  @brief Renderbuffer object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_RENDERBUFFER_1107121519_HPP
#define OGLPLUS_RENDERBUFFER_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

class RenderbufferOps
{
protected:
	GLuint _name;

	RenderbufferOps(void)
	{ }

	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenRenderbuffers(count, &_name);
		ThrowOnError();
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteRenderbuffers(count, &_name);
	}
public:
	RenderbufferOps(GLuint _n)
	 : _name(_n)
	{ }

	enum class Kind {
		Default = GL_RENDERBUFFER
	};

	void Bind(Kind target = Kind::Default) const
	{
		::glBindRenderbuffer(GLenum(target), _name);
	}
};

typedef Object<RenderbufferOps> Renderbuffer;

} // namespace oglplus

#endif // include guard
