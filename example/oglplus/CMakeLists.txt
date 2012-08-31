#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

if(OGLPLUS_USE_GLEW)
	set(OGLPLUS_EXAMPLE_HARNESS "glut_glew")
elseif(OGLPLUS_FRAMEDUMP)
	set(OGLPLUS_EXAMPLE_HARNESS "frame_dump")
else()
	set(OGLPLUS_EXAMPLE_HARNESS "glx")
endif()

# now setup the harness dependencies
if(
	("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "glut_glew") OR
	("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "glut_glew_cxx03")
)
	if(NOT GLUT_FOUND)
		message(FATAL_ERROR "GLUT is required for this build configuration")
		return()
	endif()

	include_directories(${GLUT_INCLUDE_DIRS})
	set(OGLPLUS_EXAMPLE_HARNESS_LIBS ${GLUT_LIBRARIES})
elseif(
	("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "glx") OR
	("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "frame_dump")
)
	find_package(X11)
	if(NOT X11_FOUND)
		message(FATAL_ERROR "X11 is required for this build configuration")
		return()
	endif()

	include_directories(${X11_INCLUDE_DIR})
	set(OGLPLUS_EXAMPLE_HARNESS_LIBS ${X11_LIBRARIES})
endif()

include_directories(${PROJECT_SOURCE_DIR}/utils)

# add a target for the examples
if(OGLPLUS_NO_EXAMPLES)
	add_custom_target(oglplus-examples)
else()
	add_custom_target(oglplus-examples ALL)
endif()

# add a target for the screenshots
add_custom_target(oglplus-examples-screenshots)

add_definitions(-DOGLPLUS_LINK_LIBRARY=1)

# build the code common to all the examples into this library
add_library(
	oglplus_example_harness STATIC
	EXCLUDE_FROM_ALL
	${CMAKE_CURRENT_SOURCE_DIR}/${OGLPLUS_EXAMPLE_HARNESS}_main.cpp
)

# make a list of libraries that we're going to link to
set(EXAMPLE_LIBS
	oglplus_example_harness
	${OGLPLUS_EXAMPLE_HARNESS_LIBS}
	${OGLPLUS_GL_LIBS}
)

# add oglplus examples
add_examples("[0-9][0-9][0-9]*" oglplus-examples "${EXAMPLE_LIBS}")

if(NOT OGLPLUS_NO_DOCS)
	if(NOT OGLPLUS_NO_SCREENSHOTS)
		add_dependencies(doc oglplus-examples-screenshots)
	endif()
endif()

