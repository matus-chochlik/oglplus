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

namespace oglplus {

class Context
{
public:
	static void ClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		::glClearColor(r, g, b, a);
		ThrowOnError();
	}

	static void ClearDepth(GLclampd d)
	{
		::glClearDepth(d);
		ThrowOnError();
	}

	static void ClearStencil(GLint s)
	{
		::glClearStencil(s);
		ThrowOnError();
	}

	static aux::ClrBits Clear(void)
	{
		return aux::ClrBits(0);
	}

	static void Viewport(GLint x, GLint y, GLsizei w, GLsizei h)
	{
		::glViewport(x, y, w, h);
		ThrowOnError();
	}

	static void Viewport(GLsizei w, GLsizei h)
	{
		::glViewport(0, 0, w, h);
		ThrowOnError();
	}
};

} // namespace oglplus

#endif // include guard
