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
#include <oglplus/auxiliary/binding_query.hpp>
#include <cassert>

namespace oglplus {

/// Wrapper for OpenGL framebuffer operations
/**
 *  @note Do not use this class directly, use FrameBuffer instead
 *
 *  @see Framebuffer
 */
class FramebufferOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenFramebuffers(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(GenFramebuffers));
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
	/// Framebuffer bind targets
	enum class Target : GLenum {
		/// DRAW_FRAMEBUFFER
		Draw = GL_DRAW_FRAMEBUFFER,
		/// READ_FRAMEBUFFER
		Read = GL_READ_FRAMEBUFFER
	};
protected:
	static GLenum _binding_query(Target target)
	{
		switch(GLenum(target))
		{
			case GL_DRAW_FRAMEBUFFER:
				return GL_DRAW_FRAMEBUFFER_BINDING;
			case GL_READ_FRAMEBUFFER:
				return GL_READ_FRAMEBUFFER_BINDING;
			default:;
		}
		return 0;
	}
	friend class BindingQuery<FramebufferOps>;
public:

	/// Bind this framebuffer to the specified target
	/**
	 *  @throws Error
	 */
	void Bind(Target target) const
	{
		assert(_name != 0);
		::glBindFramebuffer(GLenum(target), _name);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			BindFramebuffer,
			Framebuffer,
			_name
		));
	}

	/// Unbinds the currently bound framebuffer from the specified target
	/**
	 *  @throws Error
	 */
	static void Unbind(Target target)
	{
		::glBindFramebuffer(GLenum(target), 0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindFramebuffer));
	}
};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL framebuffer functionality
class Framebuffer
 : public FramebufferOps
{ };
#else
typedef Object<FramebufferOps, true> Framebuffer;
#endif

} // namespace oglplus

#endif // include guard
