
/**
 *  @file oglplus/bound/renderbuffer.hpp
 *  @brief Specialization of BoundTemplate for Renderbuffer.
 *
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef OGLPLUS_BOUND_RENDERBUFFER_1107121519_HPP
#define OGLPLUS_BOUND_RENDERBUFFER_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/renderbuffer.hpp>
#include <utility>

namespace oglplus {

/// Specialization of the BoundTemplate for RenderbufferOps, implements Bound < Renderbuffer  >.
/** This template implements wrappers around the member functions
 *  of Renderbuffer, which have
 *  a RenderbufferOps::Target parameter
 *  specifying the binding point on which they should operate.
 *
 *  @note Do not use this template class directly use
 *  Bound < Renderbuffer > or the Bind()
 *  function instead.
 *
 *  @see Bind()
 *  @see Bound
 *
 *  @ingroup utility_classes
 */
template <template <class, class> class Base, class BaseParam>
class BoundTemplate<Base, BaseParam, RenderbufferOps>
 : public Base<BaseParam, RenderbufferOps>
{
private:
	typedef Base<
		BaseParam,
		RenderbufferOps
	> _base;
public:
	BoundTemplate(
		const RenderbufferOps& bindable,
		RenderbufferOps::Target target
	): _base(bindable, target)
	{ }

	BoundTemplate(
		RenderbufferOps::Target target
	): _base(target)
	{ }


	/** Wrapper for Renderbuffer::Storage()
	 *  @see Renderbuffer::Storage()
	 */
	const BoundTemplate& Storage(
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
		return *this;
	}


	/** Wrapper for Renderbuffer::Storage()
	 *  @see Renderbuffer::Storage()
	 */
	const BoundTemplate& Storage(
		const images::ImageSpec & image_spec
	) const
	{
		RenderbufferOps::Storage(
			this->BindTarget(),
			image_spec
		);
		return *this;
	}


	/** Wrapper for Renderbuffer::StorageMultisample()
	 *  @see Renderbuffer::StorageMultisample()
	 */
	const BoundTemplate& StorageMultisample(
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
		return *this;
	}


	/** Wrapper for Renderbuffer::Width()
	 *  @see Renderbuffer::Width()
	 */
	GLsizei Width(void) const
	{
		return RenderbufferOps::Width(
			this->BindTarget()
		);
	}


	/** Wrapper for Renderbuffer::Height()
	 *  @see Renderbuffer::Height()
	 */
	GLsizei Height(void) const
	{
		return RenderbufferOps::Height(
			this->BindTarget()
		);
	}


	/** Wrapper for Renderbuffer::RedSize()
	 *  @see Renderbuffer::RedSize()
	 */
	GLsizei RedSize(void) const
	{
		return RenderbufferOps::RedSize(
			this->BindTarget()
		);
	}


	/** Wrapper for Renderbuffer::GreenSize()
	 *  @see Renderbuffer::GreenSize()
	 */
	GLsizei GreenSize(void) const
	{
		return RenderbufferOps::GreenSize(
			this->BindTarget()
		);
	}


	/** Wrapper for Renderbuffer::BlueSize()
	 *  @see Renderbuffer::BlueSize()
	 */
	GLsizei BlueSize(void) const
	{
		return RenderbufferOps::BlueSize(
			this->BindTarget()
		);
	}


	/** Wrapper for Renderbuffer::AlphaSize()
	 *  @see Renderbuffer::AlphaSize()
	 */
	GLsizei AlphaSize(void) const
	{
		return RenderbufferOps::AlphaSize(
			this->BindTarget()
		);
	}


	/** Wrapper for Renderbuffer::DepthSize()
	 *  @see Renderbuffer::DepthSize()
	 */
	GLsizei DepthSize(void) const
	{
		return RenderbufferOps::DepthSize(
			this->BindTarget()
		);
	}


	/** Wrapper for Renderbuffer::StencilSize()
	 *  @see Renderbuffer::StencilSize()
	 */
	GLsizei StencilSize(void) const
	{
		return RenderbufferOps::StencilSize(
			this->BindTarget()
		);
	}


	/** Wrapper for Renderbuffer::Samples()
	 *  @see Renderbuffer::Samples()
	 */
	GLsizei Samples(void) const
	{
		return RenderbufferOps::Samples(
			this->BindTarget()
		);
	}


	/** Wrapper for Renderbuffer::InternalFormat()
	 *  @see Renderbuffer::InternalFormat()
	 */
	PixelDataInternalFormat InternalFormat(void) const
	{
		return RenderbufferOps::InternalFormat(
			this->BindTarget()
		);
	}


}; // class BoundTemplate

} // namespace oglplus

#endif // include guard
