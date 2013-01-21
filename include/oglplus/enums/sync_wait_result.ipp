/*
 *  .file oglplus/enums/sync_wait_result.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/sync_wait_result.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// CONDITION_SATISFIED
ConditionSatisfied,
/// ALREADY_SIGNALED
AlreadySignaled,
/// TIMEOUT_EXPIRED
TimeoutExpired,
/// WAIT_FAILED
WaitFailed

#else // !OGLPLUS_DOCUMENTATION_ONLY

# if !OGLPLUS_NO_SCOPED_ENUMS
// native scoped enums
# include <oglplus/enums/sync_wait_result_nse.ipp>
# else
// emulated scoped enums
# include <oglplus/enums/sync_wait_result_ese.ipp>
# endif

#endif
