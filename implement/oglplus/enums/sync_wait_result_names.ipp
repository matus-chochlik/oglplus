//  File implement/oglplus/enums/sync_wait_result_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/sync_wait_result.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	SyncWaitResult*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_SYNCWAITRESULT)
#define OGLPLUS_IMPL_EVN_SYNCWAITRESULT
{
switch(value)
{
#if defined GL_CONDITION_SATISFIED
	case GL_CONDITION_SATISFIED: return CStrRef("CONDITION_SATISFIED");
#endif
#if defined GL_ALREADY_SIGNALED
	case GL_ALREADY_SIGNALED: return CStrRef("ALREADY_SIGNALED");
#endif
#if defined GL_TIMEOUT_EXPIRED
	case GL_TIMEOUT_EXPIRED: return CStrRef("TIMEOUT_EXPIRED");
#endif
#if defined GL_WAIT_FAILED
	case GL_WAIT_FAILED: return CStrRef("WAIT_FAILED");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

