/**
 *  @file oglplus/sync.hpp
 *  @brief Sync object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SYNC_1107121519_HPP
#define OGLPLUS_SYNC_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/enumerations.hpp>
#include <cassert>

namespace oglplus {

// NOTE: Xlib.h defines this symbol
// using the preprocessor. To avoid any sort of
// problems here it is necessary to observe correct order
// of header includes or you gotta keep 'em separated
// (in different translation units)
#ifdef Status
#undef Status
#endif

/// The synchronization condition enumeration
/**
 *  @ingroup enumerations
 *
 *  @see Sync::Condition()
 */
OGLPLUS_ENUM_CLASS_BEGIN(SyncCondition, GLenum)
#include <oglplus/enums/sync_condition.ipp>
OGLPLUS_ENUM_CLASS_END(SyncCondition)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/sync_condition_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/sync_condition_range.ipp>
#endif


/// The synchronization object type enumeration
/**
 *  @ingroup enumerations
 *
 *  @see Sync::Type()
 */
OGLPLUS_ENUM_CLASS_BEGIN(SyncType, GLenum)
#include <oglplus/enums/sync_type.ipp>
OGLPLUS_ENUM_CLASS_END(SyncType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/sync_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/sync_type_range.ipp>
#endif


/// The synchronization object status enumeration
/**
 *  @ingroup enumerations
 *
 *  @see Sync::Status()
 */
OGLPLUS_ENUM_CLASS_BEGIN(SyncStatus, GLenum)
#include <oglplus/enums/sync_status.ipp>
OGLPLUS_ENUM_CLASS_END(SyncStatus)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/sync_status_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/sync_status_range.ipp>
#endif

/// The wait result enumeration
/**
 *  @ingroup enumerations
 *
 *  @see Sync::ClientWait
 */
OGLPLUS_ENUM_CLASS_BEGIN(SyncWaitResult, GLenum)
#include <oglplus/enums/sync_wait_result.ipp>
OGLPLUS_ENUM_CLASS_END(SyncWaitResult)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/sync_wait_result_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/sync_wait_result_range.ipp>
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2 || GL_ARB_sync

/// Encapsulates sync object and fence functionality
/**
 *
 *  @glvoereq{3,2,ARB,sync}
 */
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
	 *
	 * 	Sync objects are non-copyable
	 *
	 *  @glsymbols
	 *  @glfunref{FenceSync}
	 */
	Sync(SyncCondition condition = SyncCondition::GPUCommandsComplete)
	 : _sync(OGLPLUS_GLFUNC(FenceSync)(GLenum(condition), 0))
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(FenceSync));
	}

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	Sync(const Sync&) = delete;
#else
private:
	Sync(const Sync&);
public:
#endif

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
