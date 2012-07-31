
/**
 *  @file oglplus/bound/framebuffer.hpp
 *  @brief Specialization of BoundTemplate for Framebuffer.
 *
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef OGLPLUS_BOUND_FRAMEBUFFER_1107121519_HPP
#define OGLPLUS_BOUND_FRAMEBUFFER_1107121519_HPP

#include <oglplus/framebuffer.hpp>
#include <oglplus/bound.hpp>
#include <oglplus/auto_bind.hpp>
#include <utility>

namespace oglplus {

/** Specialization of the BoundTemplate for Framebuffer.
 *
 *  @see Bind
 *  @see Bound
 *
 *  @ingroup utility_classes
 */
template <template <class> class Base, class BaseParam>
class BoundTemplate<Base, BaseParam, FramebufferOps>
 : public Base<BaseParam>
{
public:
	BoundTemplate(
		const FramebufferOps& bindable,
		FramebufferOps::Target target
	): Base<FramebufferOps>(bindable, target)
	{ }

	BoundTemplate(
		FramebufferOps::Target target
	): Base<BaseParam>(target)
	{ }


	/** Wrapper for Framebuffer::BindDefault()
	 *  @see Framebuffer::BindDefault()
	 */
	void BindDefault(void) const
	{
		FramebufferOps::BindDefault(
			this->BindTarget()
		);
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


	/** Wrapper for Framebuffer::AttachRenderbuffer()
	 *  @see Framebuffer::AttachRenderbuffer()
	 */
	void AttachRenderbuffer(
		FramebufferAttachment attachment,
		const RenderbufferOps & renderbuffer
	) const
	{
		FramebufferOps::AttachRenderbuffer(
			this->BindTarget(),
			attachment,
			renderbuffer
		);
	}


	/** Wrapper for Framebuffer::AttachColorRenderbuffer()
	 *  @see Framebuffer::AttachColorRenderbuffer()
	 */
	void AttachColorRenderbuffer(
		FramebufferColorAttachment attachment,
		const RenderbufferOps & renderbuffer
	) const
	{
		FramebufferOps::AttachColorRenderbuffer(
			this->BindTarget(),
			attachment,
			renderbuffer
		);
	}


	/** Wrapper for Framebuffer::AttachTexture()
	 *  @see Framebuffer::AttachTexture()
	 */
	void AttachTexture(
		FramebufferAttachment attachment,
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
	}


	/** Wrapper for Framebuffer::AttachColorTexture()
	 *  @see Framebuffer::AttachColorTexture()
	 */
	void AttachColorTexture(
		FramebufferColorAttachment attachment,
		const TextureOps & texture,
		GLint level
	) const
	{
		FramebufferOps::AttachColorTexture(
			this->BindTarget(),
			attachment,
			texture,
			level
		);
	}


	/** Wrapper for Framebuffer::AttachTexture1D()
	 *  @see Framebuffer::AttachTexture1D()
	 */
	void AttachTexture1D(
		FramebufferAttachment attachment,
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
	}


	/** Wrapper for Framebuffer::AttachTexture2D()
	 *  @see Framebuffer::AttachTexture2D()
	 */
	void AttachTexture2D(
		FramebufferAttachment attachment,
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
	}


	/** Wrapper for Framebuffer::AttachTexture3D()
	 *  @see Framebuffer::AttachTexture3D()
	 */
	void AttachTexture3D(
		FramebufferAttachment attachment,
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
	}


	/** Wrapper for Framebuffer::AttachTextureLayer()
	 *  @see Framebuffer::AttachTextureLayer()
	 */
	void AttachTextureLayer(
		FramebufferAttachment attachment,
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
	}


}; // class BoundTemplate

} // namespace oglplus

#endif // include guard
