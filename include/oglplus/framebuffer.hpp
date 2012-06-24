/**
 *  @file oglplus/framebuffer.hpp
 *  @brief Framebuffer object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_FRAMEBUFFER_1107121519_HPP
#define OGLPLUS_FRAMEBUFFER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/auxiliary/binding_query.hpp>
#include <oglplus/renderbuffer.hpp>
#include <oglplus/texture.hpp>
#include <cassert>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY
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

/// Framebuffer renderbuffer attachment points
enum class FramebufferAttachment : GLenum {
#include <oglplus/enums/framebuffer_attachment.ipp>
};

inline const GLchar* EnumValueName(FramebufferAttachment value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/framebuffer_attachment.ipp>
#endif
	return "";
}

/// Framebuffer status enumeration
enum class FramebufferStatus : GLenum {
#include <oglplus/enums/framebuffer_status.ipp>
};

inline const GLchar* EnumValueName(FramebufferStatus value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/framebuffer_status.ipp>
#endif
	return "";
}

/// Wrapper for OpenGL framebuffer operations
/**
 *  @note Do not use this class directly, use FrameBuffer instead
 *
 *  @see Framebuffer
 *
 *  @glsymbols
 *  @glfunref{GenFramebuffers}
 *  @glfunref{DeleteFramebuffers}
 *  @glfunref{IsFramebuffer}
 */
class FramebufferOps
 : public Named
 , public BaseObject<true>
 , public FriendOf<RenderbufferOps>
 , public FriendOf<TextureOps>
{
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenFramebuffers)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenFramebuffers));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		OGLPLUS_GLFUNC(DeleteFramebuffers)(count, _name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsFramebuffer)(_name);
	}

	friend class FriendOf<FramebufferOps>;
public:
	/// Framebuffer bind targets
	enum class Target : GLenum {
#include <oglplus/enums/framebuffer_target.ipp>
	};
protected:
	static GLenum _binding_query(Target target)
	{
		switch(GLenum(target))
		{
#include <oglplus/enums/framebuffer_target_bq.ipp>
			default:;
		}
		return 0;
	}
	friend class BindingQuery<FramebufferOps>;
public:

	/// Types related to Framebuffer
	struct Property
	{
		/// Attachment of a Framebuffer
		typedef FramebufferAttachment Attachment;

		/// Status of a Framebuffer
		typedef FramebufferStatus Status;
	};

	/// Bind this framebuffer to the specified target
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{BindFramebuffer}
	 */
	void Bind(Target target) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindFramebuffer)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindFramebuffer,
			Framebuffer,
			EnumValueNameTpl(target),
			_name
		));
	}

	/// Binds the default framebuffer to the specified target
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{BindFramebuffer}
	 */
	static void BindDefault(Target target)
	{
		OGLPLUS_GLFUNC(BindFramebuffer)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindFramebuffer));
	}

	/// Checks the status of the framebuffer
	/** Returns one of the values in the @c FramebufferStatus enumeration.
	 *  For complete framebuffers this member function returns
	 *  Status::Complete.
	 *
	 *  @see IsComplete
	 *
	 *  @glsymbols
	 *  @glfunref{CheckFramebufferStatus}
	 */
	static FramebufferStatus Status(Target target)
	{
		GLenum result = OGLPLUS_GLFUNC(CheckFramebufferStatus)(
			GLenum(target)
		);
		if(result == 0) OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CheckFramebufferStatus,
			Framebuffer,
			EnumValueNameTpl(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
		return FramebufferStatus(result);
	}

	/// Returns true if the framebuffer is complete
	/**
	 *  @see FramebufferStatus
	 *  @see Status()
	 *
	 *  @glsymbols
	 *  @glfunref{CheckFramebufferStatus}
	 */
	static bool IsComplete(Target target)
	{
		return Status(target) == FramebufferStatus::Complete;
	}

	/// Attach a @p renderbuffer to the @p attachment point of @p target
	/**
	 *  @see AttachColorRenderbuffer
	 *  @see AttachTexture
	 *  @see AttachTextureLayer
	 *  @see AttachTexture1D
	 *  @see AttachTexture2D
	 *  @see AttachTexture3D
	 *  @see AttachColorTexture
	 *
	 *  @glsymbols
	 *  @glfunref{FramebufferRenderbuffer}
	 */
	static void AttachRenderbuffer(
		Target target,
		FramebufferAttachment attachment,
		const RenderbufferOps& renderbuffer
	)
	{
		OGLPLUS_GLFUNC(FramebufferRenderbuffer)(
			GLenum(target),
			GLenum(attachment),
			GL_RENDERBUFFER,
			FriendOf<RenderbufferOps>::GetName(renderbuffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferRenderbuffer,
			Framebuffer,
			EnumValueNameTpl(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

	/// Attach a @p renderbuffer to the color @p attachment of @p target
	/**
	 *  @see AttachRenderbuffer
	 *  @see AttachTexture
	 *  @see AttachTextureLayer
	 *  @see AttachTexture1D
	 *  @see AttachTexture2D
	 *  @see AttachTexture3D
	 *  @see AttachColorTexture
	 *
	 *  @glsymbols
	 *  @glfunref{FramebufferRenderbuffer}
	 */
	static void AttachColorRenderbuffer(
		Target target,
		FramebufferColorAttachment attachment,
		const RenderbufferOps& renderbuffer
	)
	{
		OGLPLUS_GLFUNC(FramebufferRenderbuffer)(
			GLenum(target),
			GL_COLOR_ATTACHMENT0 + GLuint(attachment),
			GL_RENDERBUFFER,
			FriendOf<RenderbufferOps>::GetName(renderbuffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferRenderbuffer,
			Framebuffer,
			EnumValueNameTpl(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

	/// Attach a @p texture to the @p attachment point of @p target
	/**
	 *  @see AttachRenderbuffer
	 *  @see AttachColorRenderbuffer
	 *  @see AttachTextureLayer
	 *  @see AttachTexture1D
	 *  @see AttachTexture2D
	 *  @see AttachTexture3D
	 *  @see AttachColorTexture
	 *
	 *  @glsymbols
	 *  @glfunref{FramebufferTexture}
	 */
	static void AttachTexture(
		Target target,
		FramebufferAttachment attachment,
		const TextureOps& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(FramebufferTexture)(
			GLenum(target),
			GLenum(attachment),
			FriendOf<TextureOps>::GetName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferTexture,
			Framebuffer,
			EnumValueNameTpl(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

	/// Attach a @p texture to the color @p attachment point of @p target
	/**
	 *  @see AttachRenderbuffer
	 *  @see AttachColorRenderbuffer
	 *  @see AttachTexture1D
	 *  @see AttachTexture2D
	 *  @see AttachTexture3D
	 *  @see AttachTexture
	 *  @see AttachTextureLayer
	 *
	 *  @glsymbols
	 *  @glfunref{FramebufferTexture}
	 */
	static void AttachColorTexture(
		Target target,
		FramebufferColorAttachment attachment,
		const TextureOps& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(FramebufferTexture)(
			GLenum(target),
			GL_COLOR_ATTACHMENT0 + GLenum(attachment),
			FriendOf<TextureOps>::GetName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferTexture,
			Framebuffer,
			EnumValueNameTpl(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

	/// Attach a 1D @p texture to the @p attachment point of @p target
	/**
	 *  @see AttachRenderbuffer
	 *  @see AttachColorRenderbuffer
	 *  @see AttachTexture2D
	 *  @see AttachTexture3D
	 *  @see AttachColorTexture
	 *  @see AttachTexture
	 *  @see AttachTextureLayer
	 *
	 *  @glsymbols
	 *  @glfunref{FramebufferTexture}
	 */
	static void AttachTexture1D(
		Target target,
		FramebufferAttachment attachment,
		Texture::Target textarget,
		const TextureOps& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(FramebufferTexture1D)(
			GLenum(target),
			GLenum(attachment),
			GLenum(textarget),
			FriendOf<TextureOps>::GetName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferTexture1D,
			Framebuffer,
			EnumValueNameTpl(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

	/// Attach a 2D @p texture to the @p attachment point of @p target
	/**
	 *  @see AttachRenderbuffer
	 *  @see AttachColorRenderbuffer
	 *  @see AttachTexture1D
	 *  @see AttachTexture3D
	 *  @see AttachColorTexture
	 *  @see AttachTexture
	 *  @see AttachTextureLayer
	 *
	 *  @glsymbols
	 *  @glfunref{FramebufferTexture}
	 */
	static void AttachTexture2D(
		Target target,
		FramebufferAttachment attachment,
		Texture::Target textarget,
		const TextureOps& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(FramebufferTexture2D)(
			GLenum(target),
			GLenum(attachment),
			GLenum(textarget),
			FriendOf<TextureOps>::GetName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferTexture2D,
			Framebuffer,
			EnumValueNameTpl(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

	/// Attach a 3D @p texture to the @p attachment point of @p target
	/**
	 *  @see AttachRenderbuffer
	 *  @see AttachColorRenderbuffer
	 *  @see AttachTexture1D
	 *  @see AttachTexture2D
	 *  @see AttachColorTexture
	 *  @see AttachTexture
	 *  @see AttachTextureLayer
	 *
	 *  @glsymbols
	 *  @glfunref{FramebufferTexture}
	 */
	static void AttachTexture3D(
		Target target,
		FramebufferAttachment attachment,
		Texture::Target textarget,
		const TextureOps& texture,
		GLint level,
		GLint layer
	)
	{
		OGLPLUS_GLFUNC(FramebufferTexture3D)(
			GLenum(target),
			GLenum(attachment),
			GLenum(textarget),
			FriendOf<TextureOps>::GetName(texture),
			level,
			layer
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferTexture3D,
			Framebuffer,
			EnumValueNameTpl(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

	/// Attach a @p texture layer to the @p attachment point of @p target
	/**
	 *  @see AttachRenderbuffer
	 *  @see AttachColorRenderbuffer
	 *  @see AttachTexture1D
	 *  @see AttachTexture2D
	 *  @see AttachTexture3D
	 *  @see AttachColorTexture
	 *  @see AttachTexture
	 *
	 *  @glsymbols
	 *  @glfunref{FramebufferTextureLayer}
	 */
	static void AttachTextureLayer(
		Target target,
		FramebufferAttachment attachment,
		const TextureOps& texture,
		GLint level,
		GLint layer
	)
	{
		OGLPLUS_GLFUNC(FramebufferTextureLayer)(
			GLenum(target),
			GLenum(attachment),
			FriendOf<TextureOps>::GetName(texture),
			level,
			layer
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferTextureLayer,
			Framebuffer,
			EnumValueNameTpl(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}
};

inline const GLchar* EnumValueName(FramebufferOps::Target value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/framebuffer_target.ipp>
#endif
	return "";
}

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL framebuffer functionality
/**
 *  @ingroup objects
 */
class Framebuffer
 : public FramebufferOps
{ };
#else
typedef Object<FramebufferOps> Framebuffer;
#endif

} // namespace oglplus

#endif // include guard
