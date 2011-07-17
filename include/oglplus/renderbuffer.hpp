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
#include <oglplus/friend_of.hpp>
#include <cassert>

namespace oglplus {

class RenderbufferOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenRenderbuffers(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteRenderbuffers(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsRenderbuffer(_name);
	}

	friend class FriendOf<RenderbufferOps>;
public:
	enum class Target {
		Default = GL_RENDERBUFFER
	};

	void Bind(Target target = Target::Default) const
	{
		assert(_name != 0);
		::glBindRenderbuffer(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	static void Unbind(Target target = Target::Default)
	{
		::glBindRenderbuffer(GLenum(target), 0);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}
};

typedef Object<RenderbufferOps, true> Renderbuffer;

} // namespace oglplus

#endif // include guard
