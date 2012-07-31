
/**
 *  @file oglplus/bound/buffer.hpp
 *  @brief Specialization of BoundTemplate for Buffer.
 *
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
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

/** Specialization of the BoundTemplate for Buffer.
 *
 *  @see Bind
 *  @see Bound
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
	template <typename GLtype, size_t N>
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
