#  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

add_library(oglplus EXCLUDE_FROM_ALL
	native.cpp
	string.cpp
	enums.cpp
	error.cpp
	object.cpp
	program.cpp
	prog_var.cpp
	extension.cpp
	debug_output.cpp
	images_base.cpp
	images_load.cpp
	shapes_base.cpp
	shapes_utils.cpp
	shapes_blender.cpp
	shapes_obj.cpp
	text.cpp
	opt.cpp
)
