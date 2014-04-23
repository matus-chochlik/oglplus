#  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

add_library(oglplus EXCLUDE_FROM_ALL
	string.cpp
	error.cpp
	obj_desc.cpp
	shader.cpp
	program.cpp
	object.cpp
	object_dsa.cpp
	images_load.cpp
	images_base.cpp
	shapes_blender.cpp
	shapes_utils.cpp
	shapes_base.cpp
	shapes_obj.cpp
	debug_output.cpp
	text.cpp
	opt.cpp
)
