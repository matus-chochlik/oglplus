/**
 *  @file oglplus/ext/EXT_direct_state_access/framebuffer.hpp
 *  @brief Framebuffer object wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FRAMEBUFFER_DSA_1310090720_HPP
#define OGLPLUS_FRAMEBUFFER_DSA_1310090720_HPP

#include <oglplus/framebuffer.hpp>
#include <oglplus/color_buffer.hpp>
#include <oglplus/ext/EXT_direct_state_access/renderbuffer.hpp>
#include <oglplus/ext/EXT_direct_state_access/texture.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Wrapper for OpenGL framebuffer operations
/**
 *  @note Do not use this class directly, use DSAFrameBufferEXT instead
 *
 *  @see Framebuffer
 *
 *  @glsymbols
 *  @glfunref{GenFramebuffers}
 *  @glfunref{DeleteFramebuffers}
 *  @glfunref{IsFramebuffer}
 */
class DSAFramebufferEXTOps
 : public Named
 , public BaseObject<true>
 , public FriendOf<DSARenderbufferEXTOps>
 , public FriendOf<DSATextureEXTOps>
{
public:
	/// Framebuffer bind target
	typedef FramebufferTarget Target;
	Target target;
protected:
	static void _init(GLsizei count, GLuint* _name)
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

#ifdef GL_FRAMEBUFFER
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::Framebuffer;
	}
#endif

	friend class FriendOf<DSAFramebufferEXTOps>;
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
	void Bind(void)
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

	/// Bind this framebuffer to the specified target
	/**
	 *  @throws Error
	 */
	void Bind(Target new_target)
	{
		target = new_target;
		Bind();
	}

	/// Binds the default framebuffer to this Framebuffer's target
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{BindFramebuffer}
	 */
	void BindDefault(void) const
	{
		OGLPLUS_GLFUNC(BindFramebuffer)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindFramebuffer,
			Framebuffer,
			EnumValueName(target),
			0
		));
	}

	/// Binds the default framebuffer to this Framebuffer's target
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{BindFramebuffer}
	 */
	void Unbind(void) const
	{
		BindDefault();
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
	FramebufferStatus Status(void) const
	{
		GLenum result = OGLPLUS_GLFUNC(CheckNamedFramebufferStatusEXT)(
			_name,
			GLenum(target)
		);
		if(result == 0) OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CheckNamedFramebufferStatusEXT,
			Framebuffer,
			EnumValueName(target),
			_name
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
	bool IsComplete(void) const
	{
		return Status() == FramebufferStatus::Complete;
	}

	void HandleIncompleteError(FramebufferStatus status) const;

	/// Throws an exception if the framebuffer is not complete
	void Complete(void) const
	{
		FramebufferStatus status = Status();
		if(OGLPLUS_IS_ERROR(status != FramebufferStatus::Complete))
			HandleIncompleteError(status);
	}

	/// Attach a @p renderbuffer to the @p attachment point of this FBO
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
	void AttachRenderbuffer(
		Property::Attachment attachment,
		const DSARenderbufferEXTOps& renderbuffer
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferRenderbufferEXT)(
			_name,
			GLenum(attachment),
			GL_RENDERBUFFER,
			FriendOf<DSARenderbufferEXTOps>::GetName(renderbuffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferRenderbufferEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	void AttachRenderbuffer(
		Property::Attachment attachment,
		const RenderbufferOps& renderbuffer
	)
	{
		AttachRenderbuffer(
			attachment,
			Managed<DSARenderbufferEXTOps>(renderbuffer)
		);
	}

	/// Attach a @p renderbuffer to the color @p attachment_no of this FBO
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
	void AttachColorRenderbuffer(
		FramebufferColorAttachmentNumber attachment_no,
		const DSARenderbufferEXTOps& renderbuffer
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferRenderbufferEXT)(
			_name,
			GL_COLOR_ATTACHMENT0 + GLuint(attachment_no),
			GL_RENDERBUFFER,
			FriendOf<DSARenderbufferEXTOps>::GetName(renderbuffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferRenderbufferEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	void AttachColorRenderbuffer(
		FramebufferColorAttachmentNumber attachment_no,
		const RenderbufferOps& renderbuffer
	)
	{
		AttachColorRenderbuffer(
			attachment_no,
			Managed<DSARenderbufferEXTOps>(renderbuffer)
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2
	/// Attach a @p texture to the @p attachment point of this FBO
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
	void AttachTexture(
		Property::Attachment attachment,
		const DSATextureEXTOps& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTextureEXT)(
			_name,
			GLenum(attachment),
			FriendOf<DSATextureEXTOps>::GetName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTextureEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	void AttachTexture(
		Property::Attachment attachment,
		const TextureOps& texture,
		GLint level
	)
	{
		AttachTexture(
			attachment,
			Managed<DSATextureEXTOps>(texture),
			level
		);
	}

	/// Attach a @p texture to the color @p attachment point of this FBO
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
	void AttachColorTexture(
		FramebufferColorAttachmentNumber attachment_no,
		const DSATextureEXTOps& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTextureEXT)(
			_name,
			GL_COLOR_ATTACHMENT0 + GLenum(attachment_no),
			FriendOf<DSATextureEXTOps>::GetName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTextureEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	void AttachColorTexture(
		FramebufferColorAttachmentNumber attachment_no,
		const TextureOps& texture,
		GLint level
	)
	{
		AttachColorTexture(
			attachment_no,
			Managed<DSATextureEXTOps>(texture),
			level
		);
	}
#endif

	/// Attach a 1D @p texture to the @p attachment point of this FBO
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
	 *  @glfunref{FramebufferTexture1D}
	 */
	void AttachTexture1D(
		Property::Attachment attachment,
		Texture::Target textarget,
		const DSATextureEXTOps& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTexture1DEXT)(
			_name,
			GLenum(attachment),
			GLenum(textarget),
			FriendOf<DSATextureEXTOps>::GetName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTexture1DEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	void AttachTexture1D(
		Property::Attachment attachment,
		const DSATextureEXTOps& texture,
		GLint level
	)
	{
		AttachTexture1D(
			attachment,
			texture.target,
			texture,
			level
		);
	}

	void AttachTexture1D(
		Property::Attachment attachment,
		Texture::Target textarget,
		const TextureOps& texture,
		GLint level
	)
	{
		AttachTexture1D(
			attachment,
			textarget,
			Managed<DSATextureEXTOps>(texture),
			level
		);
	}

	/// Attach a 2D @p texture to the @p attachment point of this FBO
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
	 *  @glfunref{FramebufferTexture2D}
	 */
	void AttachTexture2D(
		Property::Attachment attachment,
		Texture::Target textarget,
		const DSATextureEXTOps& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTexture2DEXT)(
			_name,
			GLenum(attachment),
			GLenum(textarget),
			FriendOf<DSATextureEXTOps>::GetName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTexture2DEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	void AttachTexture2D(
		Property::Attachment attachment,
		const DSATextureEXTOps& texture,
		GLint level
	)
	{
		AttachTexture2D(
			attachment,
			texture.target,
			texture,
			level
		);
	}

	void AttachTexture2D(
		Property::Attachment attachment,
		Texture::Target textarget,
		const TextureOps& texture,
		GLint level
	)
	{
		AttachTexture2D(
			attachment,
			textarget,
			Managed<DSATextureEXTOps>(texture),
			level
		);
	}

	/// Attach a 3D @p texture to the @p attachment point of this FBO
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
	 *  @glfunref{FramebufferTexture3D}
	 */
	void AttachTexture3D(
		Property::Attachment attachment,
		Texture::Target textarget,
		const DSATextureEXTOps& texture,
		GLint level,
		GLint layer
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTexture3DEXT)(
			_name,
			GLenum(attachment),
			GLenum(textarget),
			FriendOf<DSATextureEXTOps>::GetName(texture),
			level,
			layer
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTexture3DEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	void AttachTexture3D(
		Property::Attachment attachment,
		const DSATextureEXTOps& texture,
		GLint level,
		GLint layer
	)
	{
		AttachTexture3D(
			attachment,
			texture.target,
			texture,
			level,
			layer
		);
	}

	void AttachTexture3D(
		Property::Attachment attachment,
		Texture::Target textarget,
		const TextureOps& texture,
		GLint level,
		GLint layer
	)
	{
		AttachTexture3D(
			attachment,
			textarget,
			Managed<DSATextureEXTOps>(texture),
			level,
			layer
		);
	}

	/// Attach a @p texture layer to the @p attachment point of this FBO
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
	void AttachTextureLayer(
		Property::Attachment attachment,
		const DSATextureEXTOps& texture,
		GLint level,
		GLint layer
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTextureLayerEXT)(
			_name,
			GLenum(attachment),
			FriendOf<DSATextureEXTOps>::GetName(texture),
			level,
			layer
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTextureLayerEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	void AttachTextureLayer(
		Property::Attachment attachment,
		const TextureOps& texture,
		GLint level,
		GLint layer
	)
	{
		AttachTextureLayer(
			attachment,
			Managed<DSATextureEXTOps>(texture),
			level,
			layer
		);
	}

	/// Color buffer specification type
	typedef OneOf<
		GLenum,
		std::tuple<
			oglplus::ColorBuffer,
			oglplus::FramebufferColorAttachment
		>
	> ColorBuffer;

	/// Sets the destination color buffer for draw operations
	/**
	 *  @glsymbols
	 *  @glfunref{DrawBuffer}
	 */
	void DrawBuffer(ColorBuffer buffer)
	{
		OGLPLUS_GLFUNC(FramebufferDrawBufferEXT)(
			_name,
			GLenum(buffer)
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferDrawBufferEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	/// Sets the destination color buffers for draw operations
	/**
	 *  @glsymbols
	 *  @glfunref{DrawBuffers}
	 */
	template <unsigned N>
	void DrawBuffers(const EnumArray<ColorBuffer>& buffers)
	{
		OGLPLUS_GLFUNC(FramebufferDrawBuffersEXT)(
			_name,
			buffers.Count(),
			buffers.Values()
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferDrawBuffersEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}

	/// Sets the source color buffer for read operations
	/**
	 *  @glsymbols
	 *  @glfunref{ReadBuffer}
	 */
	void ReadBuffer(ColorBuffer buffer)
	{
		OGLPLUS_GLFUNC(FramebufferReadBufferEXT)(_name, GLenum(buffer));
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			FramebufferReadBufferEXT,
			Framebuffer,
			EnumValueName(target),
			_name
		));
	}
};

// Helper class for syntax-sugar operators
struct DSAFramebufferEXTOpsAndAttch
{
	typedef DSAFramebufferEXTOps::Property::Attachment Attachment;

	DSAFramebufferEXTOps& fbo;
	Attachment attachment;

	DSAFramebufferEXTOpsAndAttch(DSAFramebufferEXTOps& f, Attachment a)
	 : fbo(f)
	 , attachment(a)
	{ }
};

inline DSAFramebufferEXTOpsAndAttch operator << (
	DSAFramebufferEXTOps& fbo,
	DSAFramebufferEXTOps::Property::Attachment attch
)
{
	return DSAFramebufferEXTOpsAndAttch(fbo, attch);
}

// Bind
inline DSAFramebufferEXTOps& operator << (
	DSAFramebufferEXTOps& fbo,
	FramebufferTarget target
)
{
	fbo.Bind(target);
	return fbo;
}

// AttachTexture
inline DSAFramebufferEXTOps& operator << (
	DSAFramebufferEXTOpsAndAttch&& faa,
	const DSATextureEXTOps& tex
)
{
	faa.fbo.AttachTexture(faa.attachment, tex, 0);
	return faa.fbo;
}

// AttachRenderbuffer
inline DSAFramebufferEXTOps& operator << (
	DSAFramebufferEXTOpsAndAttch&& faa,
	const DSARenderbufferEXTOps& rbo
)
{
	faa.fbo.AttachRenderbuffer(faa.attachment, rbo);
	return faa.fbo;
}

// Complete
inline DSAFramebufferEXTOps& operator << (
	DSAFramebufferEXTOps& fbo,
	FramebufferComplete
)
{
	fbo.Complete();
	return fbo;
}

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL framebuffer functionality
/**
 *  @ingroup oglplus_objects
 */
class DSAFramebufferEXT
 : public DSAFramebufferEXTOps
{ };
#else
typedef Object<DSAFramebufferEXTOps> DSAFramebufferEXT;
#endif

template <>
struct NonDSAtoDSA<FramebufferOps>
{
	typedef DSAFramebufferEXTOps Type;
};

template <>
struct DSAtoNonDSA<DSAFramebufferEXTOps>
{
	typedef FramebufferOps Type;
};

template <>
class ConvertibleObjectBaseOps<FramebufferOps, DSAFramebufferEXTOps>
 : public std::true_type
{ };

template <>
class ConvertibleObjectBaseOps<DSAFramebufferEXTOps, FramebufferOps>
 : public std::true_type
{ };

#endif // GL_EXT_direct_state_access

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/ext/EXT_direct_state_access/framebuffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
