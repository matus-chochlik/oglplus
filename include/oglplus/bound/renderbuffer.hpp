
/**
 *  @file oglplus/bound/renderbuffer.hpp
 *  @brief BoundTemplate Renderbuffer wrapper
 *
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef OGLPLUS_BOUND_RENDERBUFFER_1107121519_HPP
#define OGLPLUS_BOUND_RENDERBUFFER_1107121519_HPP

#include <oglplus/renderbuffer.hpp>
#include <oglplus/bound.hpp>
#include <oglplus/auto_bind.hpp>
#include <utility>

namespace oglplus {

template <template <class> class Base, class BaseParam>
class BoundTemplate<Base, BaseParam, RenderbufferOps>
 : public Base<BaseParam>
{
public:
	BoundTemplate(
		const RenderbufferOps& bindable,
		RenderbufferOps::Target target
	): Base<RenderbufferOps>(bindable, target)
	{ }

	BoundTemplate(
		RenderbufferOps::Target target
	): Base<BaseParam>(target)
	{ }

	void Storage(
		PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	) const
	{
		RenderbufferOps::Storage(
			this->BindTarget(),
			internalformat,
			width,
			height
		);
	}

	void StorageMultisample(
		GLsizei samples,
		PixelDataInternalFormat internalformat,
		GLsizei width,
		GLsizei height
	) const
	{
		RenderbufferOps::StorageMultisample(
			this->BindTarget(),
			samples,
			internalformat,
			width,
			height
		);
	}

	GLsizei Width(void) const
	{
		return RenderbufferOps::Width(
			this->BindTarget()
		);
	}

	GLsizei Height(void) const
	{
		return RenderbufferOps::Height(
			this->BindTarget()
		);
	}

	GLsizei RedSize(void) const
	{
		return RenderbufferOps::RedSize(
			this->BindTarget()
		);
	}

	GLsizei GreenSize(void) const
	{
		return RenderbufferOps::GreenSize(
			this->BindTarget()
		);
	}

	GLsizei BlueSize(void) const
	{
		return RenderbufferOps::BlueSize(
			this->BindTarget()
		);
	}

	GLsizei AlphaSize(void) const
	{
		return RenderbufferOps::AlphaSize(
			this->BindTarget()
		);
	}

	GLsizei DepthSize(void) const
	{
		return RenderbufferOps::DepthSize(
			this->BindTarget()
		);
	}

	GLsizei StencilSize(void) const
	{
		return RenderbufferOps::StencilSize(
			this->BindTarget()
		);
	}

	GLsizei Samples(void) const
	{
		return RenderbufferOps::Samples(
			this->BindTarget()
		);
	}

	PixelDataInternalFormat InternalFormat(void) const
	{
		return RenderbufferOps::InternalFormat(
			this->BindTarget()
		);
	}


}; // class BoundTemplate

} // namespace oglplus

#endif // include guard
