/**
 *  @file oglplus/dsa/framebuffer.hpp
 *  @brief Framebuffer object wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DSA_FRAMEBUFFER_1310090720_HPP
#define OGLPLUS_DSA_FRAMEBUFFER_1310090720_HPP

#include <oglplus/framebuffer.hpp>
#include <oglplus/color_buffer.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Class wrapping renderbuffer-related functionality with direct state access
/** @note Do not use this class directly, use DSARenderbuffer instead.
 *
 */
template <>
class ObjectOps<tag::DirectState, tag::Framebuffer>
 : public ObjZeroOps<tag::DirectState, tag::Framebuffer>
{
protected:
	ObjectOps(void){ }
public:
	/// Used as the default value for functions taking Target arguments
	Target default_target;

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
	FramebufferStatus Status(Target target) const
	{
		GLenum result = OGLPLUS_GLFUNC(CheckNamedFramebufferStatusEXT)(
			_name,
			GLenum(target)
		);
		if(result == 0) OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CheckNamedFramebufferStatusEXT,
			Framebuffer,
			nullptr,
			_name
		));
		return FramebufferStatus(result);
	}

	FramebufferStatus Status(void) const
	{
		return Status(default_target);
	}

	/// Returns true if the framebuffer is complete
	/**
	 *  @see FramebufferStatus
	 *  @see Status()
	 *
	 *  @glsymbols
	 *  @glfunref{CheckFramebufferStatus}
	 */
	bool IsComplete(Target target) const
	{
		return Status(target) == FramebufferStatus::Complete;
	}

	bool IsComplete(void) const
	{
		return IsComplete(default_target);
	}

	void HandleIncompleteError(FramebufferStatus status) const;

	/// Throws an exception if the framebuffer is not complete
	void Complete(Target target) const
	{
		FramebufferStatus status = Status(target);
		if(OGLPLUS_IS_ERROR(status != FramebufferStatus::Complete))
			HandleIncompleteError(status);
	}

	void Complete(void) const
	{
		Complete(default_target);
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
		const ObjectName<tag::Renderbuffer>& renderbuffer
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferRenderbufferEXT)(
			_name,
			GLenum(attachment),
			GL_RENDERBUFFER,
			GetGLName(renderbuffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferRenderbufferEXT,
			Framebuffer,
			nullptr,
			_name
		));
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
		const ObjectName<tag::Renderbuffer>& renderbuffer
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferRenderbufferEXT)(
			_name,
			GL_COLOR_ATTACHMENT0 + GLuint(attachment_no),
			GL_RENDERBUFFER,
			GetGLName(renderbuffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferRenderbufferEXT,
			Framebuffer,
			nullptr,
			_name
		));
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
		const ObjectName<tag::Texture>& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTextureEXT)(
			_name,
			GLenum(attachment),
			GetGLName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTextureEXT,
			Framebuffer,
			nullptr,
			_name
		));
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
		const ObjectName<tag::Texture>& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTextureEXT)(
			_name,
			GL_COLOR_ATTACHMENT0 + GLenum(attachment_no),
			GetGLName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTextureEXT,
			Framebuffer,
			nullptr,
			_name
		));
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
		TextureTarget textarget,
		const ObjectName<tag::Texture>& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTexture1DEXT)(
			_name,
			GLenum(attachment),
			GLenum(textarget),
			GetGLName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTexture1DEXT,
			Framebuffer,
			nullptr,
			_name
		));
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
		TextureTarget textarget,
		const ObjectName<tag::Texture>& texture,
		GLint level
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTexture2DEXT)(
			_name,
			GLenum(attachment),
			GLenum(textarget),
			GetGLName(texture),
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTexture2DEXT,
			Framebuffer,
			nullptr,
			_name
		));
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
		TextureTarget textarget,
		const ObjectName<tag::Texture>& texture,
		GLint level,
		GLint layer
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTexture3DEXT)(
			_name,
			GLenum(attachment),
			GLenum(textarget),
			GetGLName(texture),
			level,
			layer
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTexture3DEXT,
			Framebuffer,
			nullptr,
			_name
		));
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
		const ObjectName<tag::Texture>& texture,
		GLint level,
		GLint layer
	)
	{
		OGLPLUS_GLFUNC(NamedFramebufferTextureLayerEXT)(
			_name,
			GLenum(attachment),
			GetGLName(texture),
			level,
			layer
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedFramebufferTextureLayerEXT,
			Framebuffer,
			nullptr,
			_name
		));
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
			nullptr,
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
			nullptr,
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
			nullptr,
			_name
		));
	}
};

/// Framebuffer operations with direct state access
typedef ObjectOps<tag::DirectState, tag::Framebuffer>
	DSAFramebufferOps;

// Helper class for syntax-sugar operators
struct DSAFramebufferOpsAndAttch
{
	typedef DSAFramebufferOps::Property::Attachment Attachment;

	DSAFramebufferOps& fbo;
	Attachment attachment;

	DSAFramebufferOpsAndAttch(DSAFramebufferOps& f, Attachment a)
	 : fbo(f)
	 , attachment(a)
	{ }
};

inline DSAFramebufferOpsAndAttch operator << (
	DSAFramebufferOps& fbo,
	DSAFramebufferOps::Property::Attachment attch
)
{
	return DSAFramebufferOpsAndAttch(fbo, attch);
}

// Bind
inline DSAFramebufferOps& operator << (
	DSAFramebufferOps& fbo,
	FramebufferTarget target
)
{
	fbo.Bind(target);
	return fbo;
}

// AttachTexture
inline DSAFramebufferOps& operator << (
	DSAFramebufferOpsAndAttch&& faa,
	const ObjectName<tag::Texture>& tex
)
{
	faa.fbo.AttachTexture(faa.attachment, tex, 0);
	return faa.fbo;
}

// AttachRenderbuffer
inline DSAFramebufferOps& operator << (
	DSAFramebufferOpsAndAttch&& faa,
	const ObjectName<tag::Renderbuffer>& rbo
)
{
	faa.fbo.AttachRenderbuffer(faa.attachment, rbo);
	return faa.fbo;
}

// Complete
inline DSAFramebufferOps& operator << (
	DSAFramebufferOps& fbo,
	FramebufferComplete
)
{
	fbo.Complete();
	return fbo;
}

/// An @ref oglplus_object encapsulating the OpenGL framebuffer functionality
/**
 *  @ingroup oglplus_objects
 */
typedef Object<DSAFramebufferOps> DSAFramebuffer;

#else
#error Direct State Access Framebuffers not available
#endif // GL_EXT_direct_state_access

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/dsa/framebuffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
