/**
 *  .file oglplus/auxiliary/clr_bits.hpp
 *  .brief Helper class used by Context::Clear
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_CLR_BITS_1107121519_HPP
#define OGLPLUS_AUX_CLR_BITS_1107121519_HPP

#include <cassert>

namespace oglplus {

class Context;

namespace aux {

class ClrBits
{
private:
	GLbitfield bits;

	GLbitfield _forward(void)
	{
		GLbitfield res = bits;
		bits = 0;
		return res;
	}

	friend class oglplus::Context;

	ClrBits(void) = delete;
	ClrBits(const ClrBits&) = delete;
	ClrBits(GLbitfield bit)
	 : bits(bit)
	{ }

	inline ClrBits _make(GLbitfield bit)
	{
		return ClrBits(_forward() | bit);
	}
public:
	inline ClrBits ColorBuffer(void)
	{
		return _make(GL_COLOR_BUFFER_BIT);
	}

	inline ClrBits DepthBuffer(void)
	{
		return _make(GL_DEPTH_BUFFER_BIT);
	}

	inline ClrBits StencilBuffer(void)
	{
		return _make(GL_STENCIL_BUFFER_BIT);
	}

	inline ClrBits(ClrBits&& temp)
	 : bits(temp._forward())
	{ }

	inline ~ClrBits(void)
	{
		if(bits)
		{
			::glClear(bits);
			assert(::glGetError() == GL_NO_ERROR);
		}
	}
};

} // namespace aux

} // namespace oglplus

#endif // include guard
