/**
 *  @file oglplus/sync.hpp
 *  @brief Sync object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SYNC_1107121519_HPP
#define OGLPLUS_SYNC_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <cassert>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2 || GL_ARB_sync

/// Encapsulates sync object and fence functionality
class Sync
{
private:
	GLsync _sync;
public:
	/// The synchronization condition enumeration
	enum class Condition : GLenum {
#include <oglplus/enums/sync_condition.ipp>
	};

	/// The wait result enumeration
	enum class WaitResult : GLenum {
#include <oglplus/enums/sync_wait_result.ipp>
	};

	/// Creates a new sync object for the specified @p condition
	/**
	 *  @glsymbols
	 *  @glfunref{FenceSync}
	 */
	Sync(Condition condition = Condition::GPUCommandsComplete)
	 : _sync(OGLPLUS_GLFUNC(FenceSync)(GLenum(condition), 0))
	{
		HandleIfError(OGLPLUS_ERROR_INFO(FenceSync));
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
		if(_sync != 0) OGLPLUS_GLFUNC(DeleteSync)(_sync);
	}

	/// Wait for the condition to be satisfied
	/**
	 *  @glsymbols
	 *  @glfunref{ClientWaitSync}
	 */
	WaitResult ClientWait(GLuint64 timeout) const
	{
		GLenum result = OGLPLUS_GLFUNC(ClientWaitSync)(
			_sync,
			0,
			timeout
		);
		HandleIfError(OGLPLUS_ERROR_INFO(ClientWaitSync));
		return WaitResult(result);
	}

	/// Wait for the condition to be satisfied
	/**
	 *  @glsymbols
	 *  @glfunref{WaitSync}
	 */
	void Wait(GLuint64 timeout) const
	{
		OGLPLUS_GLFUNC(WaitSync)(_sync, 0, timeout);
		HandleIfError(OGLPLUS_ERROR_INFO(WaitSync));
	}
};

#endif // sync

} // namespace oglplus

#endif // include guard
