#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.6)

#TODO auto-detect or allow the caller to set this
set(OGLPLUS_EXAMPLE_HARNESS "glx")

# now setup the harness dependencies
if(
	("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "glx") OR
	("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "frame_dump")
)
	find_package(X11)
	set(OGLPLUS_EXAMPLE_HARNESS_LIBS X11)
endif()

# we need C++11
# TODO add support for various compilers
add_definitions(-std=c++0x)

# add a target for the examples
add_custom_target(oglplus_examples ALL)

# build the code common to all the examples into this library
add_library(
	oglplus_example_harness STATIC
	EXCLUDE_FROM_ALL
	./${OGLPLUS_EXAMPLE_HARNESS}_main.cpp
)

# get a list of all oglplus examples
file(GLOB OGLPLUS_EXAMPLES "./[0-9][0-9][1-9]_*.cpp")

# make the instructions for compiling and linking of the examples
foreach(EXAMPLE ${OGLPLUS_EXAMPLES})
	get_filename_component(EXE_NAME "${EXAMPLE}" NAME_WE)
	add_executable(${EXE_NAME} EXCLUDE_FROM_ALL ${EXAMPLE})
	target_link_libraries(
		${EXE_NAME}
		oglplus_example_harness
		${OGLPLUS_GL_LIB}
		${OGLPLUS_EXAMPLE_HARNESS_LIBS}
	)
	add_dependencies(oglplus_examples ${EXE_NAME})
endforeach(EXAMPLE)

