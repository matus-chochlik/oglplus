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

/// The synchronization condition enumeration
/**
 *  @ingroup enumerations
 *
 *  @see Sync::Condition()
 */
enum class SyncCondition : GLenum {
#include <oglplus/enums/sync_condition.ipp>
};

inline const GLchar* EnumValueName(SyncCondition value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/sync_condition.ipp>
#endif
	return "";
}


/// The synchronization object type enumeration
/**
 *  @ingroup enumerations
 *
 *  @see Sync::Type()
 */
enum class SyncType : GLenum {
#include <oglplus/enums/sync_type.ipp>
};

inline const GLchar* EnumValueName(SyncType value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/sync_type.ipp>
#endif
	return "";
}


/// The synchronization object status enumeration
/**
 *  @ingroup enumerations
 *
 *  @see Sync::Status()
 */
enum class SyncStatus : GLenum {
#include <oglplus/enums/sync_status.ipp>
};

inline const GLchar* EnumValueName(SyncStatus value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/sync_status.ipp>
#endif
	return "";
}


/// The wait result enumeration
enum class SyncWaitResult : GLenum {
#include <oglplus/enums/sync_wait_result.ipp>
};

inline const GLchar* EnumValueName(SyncWaitResult value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/sync_wait_result.ipp>
#endif
	return "";
}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2 || GL_ARB_sync

/// Encapsulates sync object and fence functionality
class Sync
{
private:
	GLsync _sync;
public:
	/// Types related to Sync
	struct Property
	{
		/// The synchronization condition
		typedef SyncCondition Condition;

		/// Synchronization object type
		typedef SyncType Type;

		/// Synchronization object status
		typedef SyncStatus Status;

		/// Synchronization wait result
		typedef SyncWaitResult WaitResult;
	};

	/// Creates a new sync object for the specified @p condition
	/**
	 *  @glsymbols
	 *  @glfunref{FenceSync}
	 */
	Sync(SyncCondition condition = SyncCondition::GPUCommandsComplete)
	 : _sync(OGLPLUS_GLFUNC(FenceSync)(GLenum(condition), 0))
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(FenceSync));
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

	/// Returns true if this Sync object is in signaled status
	/**
	 *  @glsymbols
	 *  @glfunref{GetSync}
	 *  @gldefref{SYNC_STATUS}
	 *  @gldefref{SIGNALED}
	 */
	bool Signaled(void) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetSynciv)(
			_sync,
			GL_SYNC_STATUS,
			1,
			nullptr,
			&result
		);
		return result == GL_SIGNALED;
	}

	/// Returns the type of this Sync object
	/**
	 *  @glsymbols
	 *  @glfunref{GetSync}
	 *  @gldefref{OBJECT_TYPE}
	 */
	SyncType Type(void) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetSynciv)(
			_sync,
			GL_OBJECT_TYPE,
			1,
			nullptr,
			&result
		);
		return SyncType(result);
	}

	/// Returns the condition of this Sync object
	/**
	 *  @glsymbols
	 *  @glfunref{GetSync}
	 *  @gldefref{SYNC_CONDITION}
	 */
	SyncCondition Condition(void) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetSynciv)(
			_sync,
			GL_SYNC_CONDITION,
			1,
			nullptr,
			&result
		);
		return SyncCondition(result);
	}

	/// Returns the status of this Sync object
	/**
	 *  @glsymbols
	 *  @glfunref{GetSync}
	 *  @gldefref{SYNC_STATUS}
	 */
	SyncStatus Status(void) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetSynciv)(
			_sync,
			GL_SYNC_STATUS,
			1,
			nullptr,
			&result
		);
		return SyncStatus(result);
	}

	/// Wait for the condition to be satisfied
	/**
	 *  @glsymbols
	 *  @glfunref{ClientWaitSync}
	 */
	SyncWaitResult ClientWait(GLuint64 timeout) const
	{
		GLenum result = OGLPLUS_GLFUNC(ClientWaitSync)(
			_sync,
			0,
			timeout
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ClientWaitSync));
		return SyncWaitResult(result);
	}

	/// Wait for the condition to be satisfied
	/**
	 *  @glsymbols
	 *  @glfunref{WaitSync}
	 */
	void Wait(GLuint64 timeout = GL_TIMEOUT_IGNORED) const
	{
		OGLPLUS_GLFUNC(WaitSync)(_sync, 0, timeout);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(WaitSync));
	}
};

#endif // sync

} // namespace oglplus

#endif // include guard
