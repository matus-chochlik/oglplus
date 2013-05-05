
/**
 *  @file oglplus/bound/buffer.hpp
 *  @brief Specialization of BoundTemplate for Buffer.
 *
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef OGLPLUS_BOUND_BUFFER_1107121519_HPP
#define OGLPLUS_BOUND_BUFFER_1107121519_HPP

#include <oglplus/buffer.hpp>
#include <oglplus/bound.hpp>
#include <oglplus/auto_bind.hpp>
#include <utility>

namespace oglplus {

/// Specialization of the BoundTemplate for BufferOps, implements Bound < Buffer  >.
/** This template implements wrappers around the member functions
 *  of Buffer, which have
 *  a BufferOps::Target parameter
 *  specifying the binding point on which they should operate.
 *
 *  @note Do not use this template class directly use
 *  Bound < Buffer > or the Bind()
 *  function instead.
 *
 *  @see Bind()
 *  @see Bound
 *  @see AutoBind
 *
 *  @ingroup utility_classes
 */
template <template <class> class Base, class BaseParam>
class BoundTemplate<Base, BaseParam, BufferOps>
 : public Base<BaseParam>
{
public:
	BoundTemplate(
		const BufferOps& bindable,
		BufferOps::Target target
	): Base<BufferOps>(bindable, target)
	{ }

	BoundTemplate(
		BufferOps::Target target
	): Base<BaseParam>(target)
	{ }


	/** Wrapper for Buffer::Mapped()
	 *  @see Buffer::Mapped()
	 */
	bool Mapped(void) const
	{
		return BufferOps::Mapped(
			this->BindTarget()
		);
	}


	/** Wrapper for Buffer::Data()
	 *  @see Buffer::Data()
	 */
	template <typename GLtype>
	void Data(
		GLsizei count,
		GLtype * data,
		BufferUsage usage = BufferUsage::StaticDraw
	) const
	{
		BufferOps::Data(
			this->BindTarget(),
			count,
			data,
			usage
		);
	}


	/** Wrapper for Buffer::Data()
	 *  @see Buffer::Data()
	 */
	template <typename GLtype, std::size_t Count>
	void Data(
		GLtype (&data)[Count],
		BufferUsage usage = BufferUsage::StaticDraw
	) const
	{
		BufferOps::Data(
			this->BindTarget(),
			data,
			usage
		);
	}


	/** Wrapper for Buffer::Data()
	 *  @see Buffer::Data()
	 */
	template <typename GLtype>
	void Data(
		const std::vector< GLtype > & data,
		BufferUsage usage = BufferUsage::StaticDraw
	) const
	{
		BufferOps::Data(
			this->BindTarget(),
			data,
			usage
		);
	}


	/** Wrapper for Buffer::Data()
	 *  @see Buffer::Data()
	 */
	template <typename GLtype, std::size_t N>
	void Data(
		const std::vector< Vector< GLtype, N > > & data,
		BufferUsage usage = BufferUsage::StaticDraw
	) const
	{
		BufferOps::Data(
			this->BindTarget(),
			data,
			usage
		);
	}


	/** Wrapper for Buffer::SubData()
	 *  @see Buffer::SubData()
	 */
	template <typename GLtype>
	void SubData(
		GLintptr offset,
		GLsizei count,
		GLtype * data
	) const
	{
		BufferOps::SubData(
			this->BindTarget(),
			offset,
			count,
			data
		);
	}


	/** Wrapper for Buffer::SubData()
	 *  @see Buffer::SubData()
	 */
	template <typename GLtype, std::size_t Count>
	void SubData(
		GLintptr offset,
		GLtype (&data)[Count]
	) const
	{
		BufferOps::SubData(
			this->BindTarget(),
			offset,
			data
		);
	}


	/** Wrapper for Buffer::SubData()
	 *  @see Buffer::SubData()
	 */
	template <typename GLtype>
	void SubData(
		GLintptr offset,
		const std::vector< GLtype > & data
	) const
	{
		BufferOps::SubData(
			this->BindTarget(),
			offset,
			data
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3

	/** Wrapper for Buffer::ClearData()
	 *  @see Buffer::ClearData()
	 */
	template <typename GLtype>
	void ClearData(
		PixelDataInternalFormat internal_format,
		PixelDataFormat format,
		const std::vector< GLtype > & data
	) const
	{
		BufferOps::ClearData(
			this->BindTarget(),
			internal_format,
			format,
			data
		);
	}
#endif // GL_VERSION_4_3

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3

	/** Wrapper for Buffer::ClearSubData()
	 *  @see Buffer::ClearSubData()
	 */
	template <typename GLtype>
	void ClearSubData(
		PixelDataInternalFormat internal_format,
		GLintptr offset,
		GLsizeiptr size,
		PixelDataFormat format,
		const std::vector< GLtype > & data
	) const
	{
		BufferOps::ClearSubData(
			this->BindTarget(),
			internal_format,
			offset,
			size,
			format,
			data
		);
	}
#endif // GL_VERSION_4_3


	/** Wrapper for Buffer::Size()
	 *  @see Buffer::Size()
	 */
	GLsizei Size(void) const
	{
		return BufferOps::Size(
			this->BindTarget()
		);
	}


	/** Wrapper for Buffer::Usage()
	 *  @see Buffer::Usage()
	 */
	BufferUsage Usage(void) const
	{
		return BufferOps::Usage(
			this->BindTarget()
		);
	}


	/** Wrapper for Buffer::Access()
	 *  @see Buffer::Access()
	 */
	BufferMapAccess Access(void) const
	{
		return BufferOps::Access(
			this->BindTarget()
		);
	}


}; // class BoundTemplate

} // namespace oglplus

#endif // include guard
