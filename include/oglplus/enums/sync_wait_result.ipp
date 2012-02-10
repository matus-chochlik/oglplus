/*
 *  .file oglplus/enums/sync_wait_result.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/sync_wait_result.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
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

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_CONDITION_SATISFIED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
ConditionSatisfied = GL_CONDITION_SATISFIED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ALREADY_SIGNALED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
AlreadySignaled = GL_ALREADY_SIGNALED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TIMEOUT_EXPIRED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TimeoutExpired = GL_TIMEOUT_EXPIRED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_WAIT_FAILED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
WaitFailed = GL_WAIT_FAILED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

