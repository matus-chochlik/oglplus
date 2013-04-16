#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

if(OGLPLUS_USE_WXGL)
	set(OGLPLUS_EXAMPLE_HARNESS "wxgl")
elseif(OGLPLUS_USE_GLUT)
	set(OGLPLUS_EXAMPLE_HARNESS "glut")
elseif(OGLPLUS_USE_GLFW)
	set(OGLPLUS_EXAMPLE_HARNESS "glfw")
elseif(OGLPLUS_USE_SDL)
	set(OGLPLUS_EXAMPLE_HARNESS "sdl")
elseif(OGLPLUS_USE_GLX)
	set(OGLPLUS_EXAMPLE_HARNESS "glx")
endif()

# check the harness dependencies and requirements
set(HARNESS_CAN_BE_BUILT true)
require_all_dependencies(${OGLPLUS_EXAMPLE_HARNESS}_main HARNESS_CAN_BE_BUILT)
if(NOT ${HARNESS_CAN_BE_BUILT})
	message(
		FATAL_ERROR 
		"Some of the requirements for the '${OGLPLUS_EXAMPLE_HARNESS}' "
		"example harness were not met. Please choose a different build "
		"configuration or install the required libraries or use "
		"a different compiler."
	)
	return()
endif()
	
include_directories(${PROJECT_SOURCE_DIR}/utils)

# add a target for the examples
add_custom_target(oglplus-examples ALL)

# add a target for the screenshots
add_custom_target(oglplus-examples-screenshots)

add_definitions(-DOGLPLUS_LINK_LIBRARY=1)

# build the code common to all the examples into this library
add_library(
	oglplus_example_harness STATIC
	EXCLUDE_FROM_ALL
	${CMAKE_CURRENT_SOURCE_DIR}/${OGLPLUS_EXAMPLE_HARNESS}_main.cpp
)
# add the dependencies for the harness
add_all_dependencies(${OGLPLUS_EXAMPLE_HARNESS}_main oglplus_example_harness)

# make a list of libraries that we're going to link to
set(EXAMPLE_LIBS
	oglplus_example_harness
	${OGLPLUS_GL_LIBS}
)

# add oglplus examples
add_examples("[0-9][0-9][0-9]*" oglplus-examples "${EXAMPLE_LIBS}")

if(NOT OGLPLUS_NO_DOCS)
	if(NOT OGLPLUS_NO_SCREENSHOTS)
		add_dependencies(doc oglplus-examples-screenshots)
	endif()
endif()

