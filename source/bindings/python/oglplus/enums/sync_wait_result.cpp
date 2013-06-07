/*
 *  .file oglplus/enums/sync_wait_result.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/sync_wait_result.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/sync.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_sync_wait_result(void)
{
	boost::python::enum_<oglplus::SyncWaitResult>("SyncWaitResult")
#if defined GL_CONDITION_SATISFIED
# if defined ConditionSatisfied
#  pragma push_macro("ConditionSatisfied")
#  undef ConditionSatisfied
	.value("ConditionSatisfied", oglplus::SyncWaitResult::ConditionSatisfied)
#  pragma pop_macro("ConditionSatisfied")
# else
	.value("ConditionSatisfied", oglplus::SyncWaitResult::ConditionSatisfied)
# endif
#endif
#if defined GL_ALREADY_SIGNALED
# if defined AlreadySignaled
#  pragma push_macro("AlreadySignaled")
#  undef AlreadySignaled
	.value("AlreadySignaled", oglplus::SyncWaitResult::AlreadySignaled)
#  pragma pop_macro("AlreadySignaled")
# else
	.value("AlreadySignaled", oglplus::SyncWaitResult::AlreadySignaled)
# endif
#endif
#if defined GL_TIMEOUT_EXPIRED
# if defined TimeoutExpired
#  pragma push_macro("TimeoutExpired")
#  undef TimeoutExpired
	.value("TimeoutExpired", oglplus::SyncWaitResult::TimeoutExpired)
#  pragma pop_macro("TimeoutExpired")
# else
	.value("TimeoutExpired", oglplus::SyncWaitResult::TimeoutExpired)
# endif
#endif
#if defined GL_WAIT_FAILED
# if defined WaitFailed
#  pragma push_macro("WaitFailed")
#  undef WaitFailed
	.value("WaitFailed", oglplus::SyncWaitResult::WaitFailed)
#  pragma pop_macro("WaitFailed")
# else
	.value("WaitFailed", oglplus::SyncWaitResult::WaitFailed)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::SyncWaitResult) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::SyncWaitResult
		>
	>("aux_CastIterRange_SyncWaitResult");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::SyncWaitResult
	> (*PEnumValueRange)(oglplus::SyncWaitResult) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
