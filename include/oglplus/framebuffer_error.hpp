/**
 *  @file oglplus/framebuffer_error.hpp
 *  @brief Framebuffer exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FRAMEBUFFER_ERROR_1405022241_HPP
#define OGLPLUS_FRAMEBUFFER_ERROR_1405022241_HPP

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/framebuffer_status.hpp>

namespace oglplus {

// NOTE: Xlib.h defines this symbol
// using the preprocessor.
#ifdef Status
#undef Status
#endif

/// Incomplete framebuffer exception class
/**
 *  @ingroup error_handling
 */
class IncompleteFramebuffer
 : public Error
{
private:
	FramebufferStatus _status;
public:
	IncompleteFramebuffer(
		FramebufferStatus status,
		const char* msg,
		const ErrorInfo& info
	): Error(GL_INVALID_FRAMEBUFFER_OPERATION, msg, info)
	 , _status(status)
	{ }

	~IncompleteFramebuffer(void) throw()
	{ }

	FramebufferStatus Status(void) const
	{
		return _status;
	}
};

} // namespace oglplus

#endif // include guard
