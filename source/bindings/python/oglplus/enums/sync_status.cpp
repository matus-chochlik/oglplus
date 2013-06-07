/*
 *  .file oglplus/enums/sync_status.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/sync_status.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/sync.hpp>

#include <boost/python.hpp>

void oglplus_py_sync_status(void)
{
	boost::python::enum_<oglplus::SyncStatus>("SyncStatus")
#if defined GL_SIGNALED
# if defined Signaled
#  pragma push_macro("Signaled")
#  undef Signaled
	.value("Signaled", oglplus::SyncStatus::Signaled)
#  pragma pop_macro("Signaled")
# else
	.value("Signaled", oglplus::SyncStatus::Signaled)
# endif
#endif
#if defined GL_UNSIGNALED
# if defined Unsignaled
#  pragma push_macro("Unsignaled")
#  undef Unsignaled
	.value("Unsignaled", oglplus::SyncStatus::Unsignaled)
#  pragma pop_macro("Unsignaled")
# else
	.value("Unsignaled", oglplus::SyncStatus::Unsignaled)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::SyncStatus) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
