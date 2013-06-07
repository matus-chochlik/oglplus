/*
 *  .file oglplus/enums/sync_condition.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/sync_condition.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/sync.hpp>

#include <boost/python.hpp>

void oglplus_py_sync_condition(void)
{
	boost::python::enum_<oglplus::SyncCondition>("SyncCondition")
#if defined GL_SYNC_GPU_COMMANDS_COMPLETE
# if defined GPUCommandsComplete
#  pragma push_macro("GPUCommandsComplete")
#  undef GPUCommandsComplete
	.value("GPUCommandsComplete", oglplus::SyncCondition::GPUCommandsComplete)
#  pragma pop_macro("GPUCommandsComplete")
# else
	.value("GPUCommandsComplete", oglplus::SyncCondition::GPUCommandsComplete)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::SyncCondition) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
