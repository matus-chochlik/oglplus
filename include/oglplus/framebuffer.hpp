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
#include <oglplus/one_of.hpp>
#include <cassert>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY
/// Type for the framebuffer color attachment (implementation-dependent) number
class FramebufferColorAttachmentNumber
 : public LimitedCount
{
public:
	FramebufferColorAttachmentNumber(GLuint count);
};
#else
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	FramebufferColorAttachmentNumber,
	MAX_COLOR_ATTACHMENTS
)
#endif

/// Framebuffer attachment points
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(FramebufferAttachment, GLenum)
#include <oglplus/enums/framebuffer_attachment.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	FramebufferAttachment*,
	EnumBaseType<FramebufferAttachment>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/framebuffer_attachment.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif

/// Framebuffer color attachment points
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(FramebufferColorAttachment, GLenum)
#include <oglplus/enums/framebuffer_color_attachment.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	FramebufferColorAttachment*,
	EnumBaseType<FramebufferColorAttachment>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/framebuffer_color_attachment.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif

/// Framebuffer status enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(FramebufferStatus, GLenum)
#include <oglplus/enums/framebuffer_status.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	FramebufferStatus*,
	EnumBaseType<FramebufferStatus>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/framebuffer_status.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif

/// Framebuffer bind target
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(FramebufferTarget, GLenum)
#include <oglplus/enums/framebuffer_target.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_LIB_FUNC StrLit EnumValueName(
	FramebufferTarget*,
	EnumBaseType<FramebufferTarget>::Type value
) OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/framebuffer_target.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}
#endif
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
public:
	/// Framebuffer bind targets
	typedef FramebufferTarget Target;
protected:
	static void _init(GLsizei count, GLuint* _name, std::true_type)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		try{OGLPLUS_GLFUNC(GenFramebuffers)(count, _name);}
		catch(...){ }
	}

	static void _init(GLsizei count, GLuint* _name, std::false_type)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenFramebuffers)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenFramebuffers));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteFramebuffers)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsFramebuffer)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

	static void _bind(GLuint _name, Target target)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindFramebuffer)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindFramebuffer,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	friend class FriendOf<FramebufferOps>;

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
		typedef OneOf<
			GLenum,
			std::tuple<
				FramebufferAttachment,
				FramebufferColorAttachment
			>
		> Attachment;

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
		_bind(_name, target);
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
			EnumValueName(target),
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
		Property::Attachment attachment,
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
			EnumValueName(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}

	/// Attach a @p renderbuffer to the color @p attachment_no of @p target
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
		FramebufferColorAttachmentNumber attachment_no,
		const RenderbufferOps& renderbuffer
	)
	{
		OGLPLUS_GLFUNC(FramebufferRenderbuffer)(
			GLenum(target),
			GL_COLOR_ATTACHMENT0 + GLuint(attachment_no),
			GL_RENDERBUFFER,
			FriendOf<RenderbufferOps>::GetName(renderbuffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferRenderbuffer,
			Framebuffer,
			EnumValueName(target),
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
		Property::Attachment attachment,
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
			EnumValueName(target),
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
			EnumValueName(target),
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
		Property::Attachment attachment,
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
			EnumValueName(target),
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
		Property::Attachment attachment,
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
			EnumValueName(target),
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
		Property::Attachment attachment,
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
			EnumValueName(target),
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
		Property::Attachment attachment,
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
			EnumValueName(target),
			BindingQuery<FramebufferOps>::QueryBinding(target)
		));
	}
};

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
OGLPLUS_OBJECT_TYPE_ID(Framebuffer, 2)
#endif

} // namespace oglplus

#endif // include guard
