
/**
 *  @file oglplus/bound/framebuffer.hpp
 *  @brief BoundTemplate Framebuffer wrapper
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

	void BindDefault(void) const
	{
		FramebufferOps::BindDefault(
			this->BindTarget()
		);
	}

	FramebufferStatus Status(void) const
	{
		return FramebufferOps::Status(
			this->BindTarget()
		);
	}

	bool IsComplete(void) const
	{
		return FramebufferOps::IsComplete(
			this->BindTarget()
		);
	}

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
