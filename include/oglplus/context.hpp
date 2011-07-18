/**
 *  @file oglplus/context.hpp
 *  @brief Declaration of OpenGL's state wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_1107121317_HPP
#define OGLPLUS_CONTEXT_1107121317_HPP

#include <oglplus/error.hpp>

#include <oglplus/auxiliary/clr_bits.hpp>
#include <oglplus/auxiliary/bitfield.hpp>

namespace oglplus {

enum class ClearBit : GLbitfield
{
	ColorBuffer = GL_COLOR_BUFFER_BIT,
	DepthBuffer = GL_DEPTH_BUFFER_BIT,
	StencilBuffer = GL_STENCIL_BUFFER_BIT
};

class Context
{
public:
	static void ClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		::glClearColor(r, g, b, a);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void ClearDepth(GLclampd d)
	{
		::glClearDepth(d);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void ClearStencil(GLint s)
	{
		::glClearStencil(s);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static aux::ClrBits Clear(void)
	{
		return aux::ClrBits(0);
	}

	static void Clear(const std::initializer_list<ClearBit>& bits)
	{
		::glClear(aux::MakeBitfield(bits));
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	static void Viewport(GLint x, GLint y, GLsizei w, GLsizei h)
	{
		::glViewport(x, y, w, h);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void Viewport(GLsizei w, GLsizei h)
	{
		::glViewport(0, 0, w, h);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}
};

} // namespace oglplus

#endif // include guard
