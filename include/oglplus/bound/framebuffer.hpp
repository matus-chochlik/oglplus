
/**
 *  @file oglplus/bound/framebuffer.hpp
 *  @brief Specialization of BoundTemplate for Framebuffer.
 *
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef OGLPLUS_BOUND_FRAMEBUFFER_1107121519_HPP
#define OGLPLUS_BOUND_FRAMEBUFFER_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/framebuffer.hpp>
#include <utility>

namespace oglplus {

/// Specialization of the BoundTemplate for FramebufferOps, implements Bound < Framebuffer  >.
/** This template implements wrappers around the member functions
 *  of Framebuffer, which have
 *  a FramebufferOps::Target parameter
 *  specifying the binding point on which they should operate.
 *
 *  @note Do not use this template class directly use
 *  Bound < Framebuffer > or the Bind()
 *  function instead.
 *
 *  @see Bind()
 *  @see Bound
 *
 *  @ingroup utility_classes
 */
template <template <class, class> class Base, class BaseParam>
class BoundTemplate<Base, BaseParam, FramebufferOps>
 : public Base<BaseParam, FramebufferOps>
{
private:
	typedef Base<
		BaseParam,
		FramebufferOps
	> _base;
public:
	BoundTemplate(
		const FramebufferOps& bindable,
		FramebufferOps::Target target
	): _base(bindable, target)
	{ }

	BoundTemplate(
		FramebufferOps::Target target
	): _base(target)
	{ }


	/** Wrapper for Framebuffer::BindDefault()
	 *  @see Framebuffer::BindDefault()
	 */
	const BoundTemplate& BindDefault(void) const
	{
		FramebufferOps::BindDefault(
			this->BindTarget()
		);
		return *this;
	}


	/** Wrapper for Framebuffer::Status()
	 *  @see Framebuffer::Status()
	 */
	FramebufferStatus Status(void) const
	{
		return FramebufferOps::Status(
			this->BindTarget()
		);
	}


	/** Wrapper for Framebuffer::IsComplete()
	 *  @see Framebuffer::IsComplete()
	 */
	bool IsComplete(void) const
	{
		return FramebufferOps::IsComplete(
			this->BindTarget()
		);
	}


	/** Wrapper for Framebuffer::HandleIncompleteError()
	 *  @see Framebuffer::HandleIncompleteError()
	 */
	const BoundTemplate& HandleIncompleteError(
		FramebufferStatus status
	) const
	{
		FramebufferOps::HandleIncompleteError(
			this->BindTarget(),
			status
		);
		return *this;
	}


	/** Wrapper for Framebuffer::Complete()
	 *  @see Framebuffer::Complete()
	 */
	const BoundTemplate& Complete(void) const
	{
		FramebufferOps::Complete(
			this->BindTarget()
		);
		return *this;
	}


	/** Wrapper for Framebuffer::AttachRenderbuffer()
	 *  @see Framebuffer::AttachRenderbuffer()
	 */
	const BoundTemplate& AttachRenderbuffer(
		FramebufferOps::Property::Attachment attachment,
		const RenderbufferOps & renderbuffer
	) const
	{
		FramebufferOps::AttachRenderbuffer(
			this->BindTarget(),
			attachment,
			renderbuffer
		);
		return *this;
	}


	/** Wrapper for Framebuffer::AttachColorRenderbuffer()
	 *  @see Framebuffer::AttachColorRenderbuffer()
	 */
	const BoundTemplate& AttachColorRenderbuffer(
		FramebufferColorAttachmentNumber attachment_no,
		const RenderbufferOps & renderbuffer
	) const
	{
		FramebufferOps::AttachColorRenderbuffer(
			this->BindTarget(),
			attachment_no,
			renderbuffer
		);
		return *this;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2

	/** Wrapper for Framebuffer::AttachTexture()
	 *  @see Framebuffer::AttachTexture()
	 */
	const BoundTemplate& AttachTexture(
		FramebufferOps::Property::Attachment attachment,
		const TextureOps & texture,
		GLint level
	) const
	{
		FramebufferOps::AttachTexture(
			this->BindTarget(),
			attachment,
			texture,
			level
		);
		return *this;
	}
#endif // GL_VERSION_3_2


	/** Wrapper for Framebuffer::AttachColorTexture()
	 *  @see Framebuffer::AttachColorTexture()
	 */
	const BoundTemplate& AttachColorTexture(
		FramebufferColorAttachmentNumber attachment_no,
		const TextureOps & texture,
		GLint level
	) const
	{
		FramebufferOps::AttachColorTexture(
			this->BindTarget(),
			attachment_no,
			texture,
			level
		);
		return *this;
	}


	/** Wrapper for Framebuffer::AttachTexture1D()
	 *  @see Framebuffer::AttachTexture1D()
	 */
	const BoundTemplate& AttachTexture1D(
		FramebufferOps::Property::Attachment attachment,
		Texture::Target textarget,
		const TextureOps & texture,
		GLint level
	) const
	{
		FramebufferOps::AttachTexture1D(
			this->BindTarget(),
			attachment,
			textarget,
			texture,
			level
		);
		return *this;
	}


	/** Wrapper for Framebuffer::AttachTexture2D()
	 *  @see Framebuffer::AttachTexture2D()
	 */
	const BoundTemplate& AttachTexture2D(
		FramebufferOps::Property::Attachment attachment,
		Texture::Target textarget,
		const TextureOps & texture,
		GLint level
	) const
	{
		FramebufferOps::AttachTexture2D(
			this->BindTarget(),
			attachment,
			textarget,
			texture,
			level
		);
		return *this;
	}


	/** Wrapper for Framebuffer::AttachTexture3D()
	 *  @see Framebuffer::AttachTexture3D()
	 */
	const BoundTemplate& AttachTexture3D(
		FramebufferOps::Property::Attachment attachment,
		Texture::Target textarget,
		const TextureOps & texture,
		GLint level,
		GLint layer
	) const
	{
		FramebufferOps::AttachTexture3D(
			this->BindTarget(),
			attachment,
			textarget,
			texture,
			level,
			layer
		);
		return *this;
	}


	/** Wrapper for Framebuffer::AttachTextureLayer()
	 *  @see Framebuffer::AttachTextureLayer()
	 */
	const BoundTemplate& AttachTextureLayer(
		FramebufferOps::Property::Attachment attachment,
		const TextureOps & texture,
		GLint level,
		GLint layer
	) const
	{
		FramebufferOps::AttachTextureLayer(
			this->BindTarget(),
			attachment,
			texture,
			level,
			layer
		);
		return *this;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_invalidate_subdata

	/** Wrapper for Framebuffer::Invalidate()
	 *  @see Framebuffer::Invalidate()
	 */
	const BoundTemplate& Invalidate(
		const EnumArray< FramebufferOps::Property::Buffer > & buffers
	) const
	{
		FramebufferOps::Invalidate(
			this->BindTarget(),
			buffers
		);
		return *this;
	}
#endif // GL_VERSION_4_3 GL_ARB_invalidate_subdata

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_invalidate_subdata

	/** Wrapper for Framebuffer::Invalidate()
	 *  @see Framebuffer::Invalidate()
	 */
	template <typename N>
	const BoundTemplate& Invalidate(
		GLsizei count,
		const FramebufferOps::Property::Buffer * buffers
	) const
	{
		FramebufferOps::Invalidate(
			this->BindTarget(),
			count,
			buffers
		);
		return *this;
	}
#endif // GL_VERSION_4_3 GL_ARB_invalidate_subdata

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_invalidate_subdata

	/** Wrapper for Framebuffer::Invalidate()
	 *  @see Framebuffer::Invalidate()
	 */
	const BoundTemplate& Invalidate(
		const EnumArray< FramebufferOps::Property::Buffer > & buffers,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	) const
	{
		FramebufferOps::Invalidate(
			this->BindTarget(),
			buffers,
			x,
			y,
			width,
			height
		);
		return *this;
	}
#endif // GL_VERSION_4_3 GL_ARB_invalidate_subdata

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_invalidate_subdata

	/** Wrapper for Framebuffer::Invalidate()
	 *  @see Framebuffer::Invalidate()
	 */
	const BoundTemplate& Invalidate(
		GLsizei count,
		const FramebufferOps::Property::Buffer * buffers,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	) const
	{
		FramebufferOps::Invalidate(
			this->BindTarget(),
			count,
			buffers,
			x,
			y,
			width,
			height
		);
		return *this;
	}
#endif // GL_VERSION_4_3 GL_ARB_invalidate_subdata


}; // class BoundTemplate

} // namespace oglplus

#endif // include guard
