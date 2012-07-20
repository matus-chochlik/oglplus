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
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(ConditionSatisfied)
#  pragma push_macro("ConditionSatisfied")
#  undef ConditionSatisfied
   OGLPLUS_ENUM_CLASS_VALUE(ConditionSatisfied, GL_CONDITION_SATISFIED)
#  pragma pop_macro("ConditionSatisfied")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ConditionSatisfied, GL_CONDITION_SATISFIED)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ALREADY_SIGNALED
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(AlreadySignaled)
#  pragma push_macro("AlreadySignaled")
#  undef AlreadySignaled
   OGLPLUS_ENUM_CLASS_VALUE(AlreadySignaled, GL_ALREADY_SIGNALED)
#  pragma pop_macro("AlreadySignaled")
# else
   OGLPLUS_ENUM_CLASS_VALUE(AlreadySignaled, GL_ALREADY_SIGNALED)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TIMEOUT_EXPIRED
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(TimeoutExpired)
#  pragma push_macro("TimeoutExpired")
#  undef TimeoutExpired
   OGLPLUS_ENUM_CLASS_VALUE(TimeoutExpired, GL_TIMEOUT_EXPIRED)
#  pragma pop_macro("TimeoutExpired")
# else
   OGLPLUS_ENUM_CLASS_VALUE(TimeoutExpired, GL_TIMEOUT_EXPIRED)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_WAIT_FAILED
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(WaitFailed)
#  pragma push_macro("WaitFailed")
#  undef WaitFailed
   OGLPLUS_ENUM_CLASS_VALUE(WaitFailed, GL_WAIT_FAILED)
#  pragma pop_macro("WaitFailed")
# else
   OGLPLUS_ENUM_CLASS_VALUE(WaitFailed, GL_WAIT_FAILED)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

