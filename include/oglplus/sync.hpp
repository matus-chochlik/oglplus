/**
 *  @file oglplus/sync.hpp
 *  @brief Sync object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SYNC_1107121519_HPP
#define OGLPLUS_SYNC_1107121519_HPP

#include <oglplus/error.hpp>
#include <cassert>

namespace oglplus {

/// Encapsulates sync object and fence functionality
class Sync
{
private:
	GLsync _sync;
public:
	/// The synchronization condition enumeration
	enum class Condition : GLenum {
		GPUCommandsComplete = GL_SYNC_GPU_COMMANDS_COMPLETE
	};

	/// The wait result enumeration
	enum class WaitResult : GLenum {
		/// CONDITION_SATISFIED
		ConditionSatisfied = GL_CONDITION_SATISFIED,
		/// ALREADY_SIGNALED
		AlreadySignaled = GL_ALREADY_SIGNALED,
		/// TIMEOUT_EXPIRED
		TimeoutExpired = GL_TIMEOUT_EXPIRED,
		/// WAIT_FAILED
		WaitFailed = GL_WAIT_FAILED
	};

	/// Creates a new sync object for the specified @p condition
	Sync(Condition condition = Condition::GPUCommandsComplete)
	 : _sync(::glFenceSync(GLenum(condition), 0))
	{
		ThrowOnError(OGLPLUS_ERROR_INFO(FenceSync));
	}

	/// Sync objects are non-copyable
	Sync(const Sync&) = delete;

	/// Sync objects are moveable
	Sync(Sync&& temp)
	 : _sync(temp._sync)
	{
		temp._sync = 0;
	}

	~Sync(void)
	{
		if(_sync != 0) ::glDeleteSync(_sync);
	}

	/// Wait for the condition to be satisfied
	WaitResult ClientWait(GLuint64 timeout) const
	{
		GLenum result = ::glClientWaitSync(_sync, 0, timeout);
		ThrowOnError(OGLPLUS_ERROR_INFO(ClientWaitSync));
		return WaitResult(result);
	}

	/// Wait for the condition to be satisfied
	void Wait(GLuint64 timeout) const
	{
		::glWaitSync(_sync, 0, timeout);
		ThrowOnError(OGLPLUS_ERROR_INFO(WaitSync));
	}
};

} // namespace oglplus

#endif // include guard
