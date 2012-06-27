/**
 *  .file oglplus/auxiliary/clr_bits.hpp
 *  .brief Helper class used by Context::Clear
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_CLR_BITS_1107121519_HPP
#define OGLPLUS_AUX_CLR_BITS_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>

namespace oglplus {
namespace context {

class ClearBuffers;

} // namespace context

namespace aux {

class ClrBits
{
private:
	GLbitfield _bits;

	GLbitfield _forward(void)
	OGLPLUS_NOEXCEPT(true)
	{
		GLbitfield res = _bits;
		_bits = 0;
		return res;
	}

	friend class oglplus::context::ClearBuffers;

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	ClrBits(void) = delete;
	ClrBits(const ClrBits&) = delete;
#else
	ClrBits(void);
	ClrBits(const ClrBits&);
#endif

	ClrBits(GLbitfield bit)
	OGLPLUS_NOEXCEPT(true)
	 : _bits(bit)
	{ }

	inline ClrBits _make(GLbitfield bit)
	OGLPLUS_NOEXCEPT(true)
	{
		return ClrBits(_forward() | bit);
	}
public:
	inline ClrBits ColorBuffer(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return _make(GL_COLOR_BUFFER_BIT);
	}

	inline ClrBits DepthBuffer(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return _make(GL_DEPTH_BUFFER_BIT);
	}

	inline ClrBits StencilBuffer(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return _make(GL_STENCIL_BUFFER_BIT);
	}

	inline ClrBits(ClrBits&& temp)
	OGLPLUS_NOEXCEPT(true)
	 : _bits(temp._forward())
	{ }

	inline ~ClrBits(void)
	OGLPLUS_NOEXCEPT(false)
	{
		if(_bits)
		{
			OGLPLUS_GLFUNC(Clear)(_bits);
			OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Clear));
		}
	}
};

} // namespace aux

} // namespace oglplus

#endif // include guard
