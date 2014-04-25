/**
 *  @file oglplus/native/context_glx.hpp
 *  @brief Wrapper for native current GLX/OpenGL context
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_NATIVE_CONTEXT_1404232057_HPP
#define OGLPLUS_NATIVE_CONTEXT_1404232057_HPP
// NOTE: the include guard is intentionally without the _GLX suffix so that
// different native context implementation cannot be included simultaneously.

#include <oglplus/native/surface_glx.hpp>

namespace oglplus {
namespace native {

/// Wrapper for GLX context handle
class ContextGLX
{
private:
	::Display* _display;
	::GLXContext _context;

	struct Current_ { };

	ContextGLX(Current_)
	 : _display(::glXGetCurrentDisplay())
	 , _context(::glXGetCurrentContext())
	{ }
public:
	/// Returns a wrapper for the currently bound GLX context
	static ContextGLX Current(void)
	{
		return ContextGLX(Current_());
	}
};

typedef ContextGLX Context;

} // namespace native
} // namespace oglplus

#endif // include guard
