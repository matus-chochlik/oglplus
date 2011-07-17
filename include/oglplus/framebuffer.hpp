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
#include <oglplus/friend_of.hpp>
#include <cassert>

namespace oglplus {

class FramebufferOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenFramebuffers(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteFramebuffers(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsFramebuffer(_name);
	}

	friend class FriendOf<FramebufferOps>;
public:
	enum class Target {
		Draw = GL_DRAW_FRAMEBUFFER,
		Read = GL_READ_FRAMEBUFFER
	};

	void Bind(Target target) const
	{
		assert(_name != 0);
		::glBindFramebuffer(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	static void Unbind(Target target)
	{
		::glBindFramebuffer(GLenum(target), 0);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}
};

typedef Object<FramebufferOps, true> Framebuffer;

} // namespace oglplus

#endif // include guard
