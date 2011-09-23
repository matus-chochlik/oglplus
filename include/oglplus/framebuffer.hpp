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
#include <oglplus/renderbuffer.hpp>
#include <cassert>

namespace oglplus {

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// Type for the framebuffer color attachment (implementation-dependent) number
class FramebufferColorAttachment
 : public LimitedCount
{
public:
	FramebufferColorAttachment(GLuint count);
};
#else
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	FramebufferColorAttachment,
	MAX_COLOR_ATTACHMENTS
)
#endif

/// Wrapper for OpenGL framebuffer operations
/**
 *  @note Do not use this class directly, use FrameBuffer instead
 *
 *  @see Framebuffer
 */
class FramebufferOps
 : public Named
 , public FriendOf<Renderbuffer>
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
	/// Framebuffer renderbuffer attachment points
	enum class Attachment : GLenum {
		/// COLOR_ATTACHMENT0
		Color = GL_COLOR_ATTACHMENT0,
		/// COLOR_ATTACHMENT1
		Color1 = GL_COLOR_ATTACHMENT1,
		/// COLOR_ATTACHMENT2
		Color2 = GL_COLOR_ATTACHMENT2,
		/// COLOR_ATTACHMENT3
		Color3 = GL_COLOR_ATTACHMENT3,
		/// COLOR_ATTACHMENT4
		Color4 = GL_COLOR_ATTACHMENT4,
		/// COLOR_ATTACHMENT5
		Color5 = GL_COLOR_ATTACHMENT5,
		/// COLOR_ATTACHMENT6
		Color6 = GL_COLOR_ATTACHMENT6,
		/// COLOR_ATTACHMENT7
		Color7 = GL_COLOR_ATTACHMENT7,
		/// COLOR_ATTACHMENT8
		Color8 = GL_COLOR_ATTACHMENT8,
		/// COLOR_ATTACHMENT9
		Color9 = GL_COLOR_ATTACHMENT9,
		/// COLOR_ATTACHMENT10
		Color10 = GL_COLOR_ATTACHMENT10,
		/// COLOR_ATTACHMENT11
		Color11 = GL_COLOR_ATTACHMENT11,
		/// COLOR_ATTACHMENT12
		Color12 = GL_COLOR_ATTACHMENT12,
		/// COLOR_ATTACHMENT13
		Color13 = GL_COLOR_ATTACHMENT13,
		/// COLOR_ATTACHMENT14
		Color14 = GL_COLOR_ATTACHMENT14,
		/// COLOR_ATTACHMENT15
		Color15 = GL_COLOR_ATTACHMENT15,
		/// DEPTH_ATTACHMENT
		Depth = GL_DEPTH_ATTACHMENT,
		/// STENCIL_ATTACHMENT
		Stencil = GL_STENCIL_ATTACHMENT,
		/// DEPTH_STENCIL_ATTACHMENT
		DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT
	};

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

	/// Attach a @p renderbuffer to the @p attachment point of @p target
	static void AttachRenderbuffer(
		Target target,
		Attachment attachment,
		const Renderbuffer& renderbuffer
	)
	{
		::glFramebufferRenderbuffer(
			GLenum(target),
			GLenum(attachment),
			GL_RENDERBUFFER,
			FriendOf<Renderbuffer>::GetName(renderbuffer)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferRenderbuffer,
			Framebuffer,
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

	/// Attach a @p renderbuffer to the color @p attachment of @p target
	static void AttachColorRenderbuffer(
		Target target,
		FramebufferColorAttachment attachment,
		const Renderbuffer& renderbuffer
	)
	{
		::glFramebufferRenderbuffer(
			GLenum(target),
			GL_COLOR_ATTACHMENT0 + GLuint(attachment),
			GL_RENDERBUFFER,
			FriendOf<Renderbuffer>::GetName(renderbuffer)
		);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferRenderbuffer,
			Framebuffer,
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL framebuffer functionality
/**
 *  @ingroup objects
 */
class Framebuffer
 : public FramebufferOps
{ };
#else
typedef Object<FramebufferOps, true> Framebuffer;
#endif

} // namespace oglplus

#endif // include guard
