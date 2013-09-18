/*
 *  .file oglplus/enums/sync_status_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/sync_status.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	SyncStatus*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_SYNCSTATUS)
#define OGLPLUS_IMPL_EVN_SYNCSTATUS
{
switch(value)
{
#if defined GL_SIGNALED
	case GL_SIGNALED: return StrLit("SIGNALED");
#endif
#if defined GL_UNSIGNALED
	case GL_UNSIGNALED: return StrLit("UNSIGNALED");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

