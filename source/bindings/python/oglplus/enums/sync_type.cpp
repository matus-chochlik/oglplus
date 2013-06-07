/*
 *  .file oglplus/enums/sync_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/sync_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/sync.hpp>

#include <boost/python.hpp>

void oglplus_py_sync_type(void)
{
	boost::python::enum_<oglplus::SyncType>("SyncType")
#if defined GL_SYNC_FENCE
# if defined Fence
#  pragma push_macro("Fence")
#  undef Fence
	.value("Fence", oglplus::SyncType::Fence)
#  pragma pop_macro("Fence")
# else
	.value("Fence", oglplus::SyncType::Fence)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::SyncType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
