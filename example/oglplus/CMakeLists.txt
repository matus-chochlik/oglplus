#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

#TODO auto-detect or allow the caller to set this
if(OGLPLUS_USE_GLEW)
	set(OGLPLUS_EXAMPLE_HARNESS "glut_glew")
else()
	set(OGLPLUS_EXAMPLE_HARNESS "glx")
endif()

# now setup the harness dependencies
if("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "glut_glew")
	set(OGLPLUS_EXAMPLE_HARNESS_LIBS ${GLUT_LIBRARIES})
elseif(
	("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "glx") OR
	("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "frame_dump")
)
	# include the X11/GLX utility headers
	include_directories(${PROJECT_SOURCE_DIR}/utils)

	find_package(X11)
	set(OGLPLUS_EXAMPLE_HARNESS_LIBS X11)
endif()

# add a target for the examples
if(OGLPLUS_NO_EXAMPLES)
add_custom_target(oglplus-examples)
else()
add_custom_target(oglplus-examples ALL)
endif()

# add a target for the screenshots
add_custom_target(oglplus_example_screenshots)

# build the code common to all the examples into this library
add_library(
	oglplus_example_harness STATIC
	EXCLUDE_FROM_ALL
	./${OGLPLUS_EXAMPLE_HARNESS}_main.cpp
)

# get a list of all oglplus examples
file(GLOB OGLPLUS_EXAMPLES "./[0-9][0-9][0-9]_*.cpp")

# make the instructions for compiling and linking of the examples
foreach(EXAMPLE ${OGLPLUS_EXAMPLES})
	get_filename_component(EXE_NAME "${EXAMPLE}" NAME_WE)
	add_executable(${EXE_NAME} EXCLUDE_FROM_ALL ${EXAMPLE})
	add_dependencies(${EXE_NAME} oglplus_textures)
	target_link_libraries(
		${EXE_NAME}
		oglplus_example_harness
		${OGLPLUS_EXAMPLE_HARNESS_LIBS}
		${OGLPLUS_GL_LIBS}
		# TODO detect and link only what is necessary
		png
	)
	add_dependencies(oglplus-examples ${EXE_NAME})

	if(NOT OGLPLUS_NO_SCREENSHOTS)
		add_custom_command(
			OUTPUT ${EXE_NAME}.rgb
			COMMAND ${EXE_NAME} --screenshot ${EXE_NAME}.rgb
			DEPENDS ${EXE_NAME}
		)

		if(${ImageMagick_convert_FOUND})
			add_custom_command(
				OUTPUT ${EXE_NAME}.png
				COMMAND ${ImageMagick_convert_EXECUTABLE}
					-depth 8
					-size 800x600
					${EXE_NAME}.rgb
					-flip
					-adaptive-resize 400x300
					${EXE_NAME}.png
				DEPENDS ${EXE_NAME}.rgb
			)

			add_custom_target(${EXE_NAME}-screenshot DEPENDS ${EXE_NAME}.png)
			add_dependencies(oglplus_example_screenshots ${EXE_NAME}-screenshot)
		endif()

	endif()
endforeach()

if(NOT OGLPLUS_NO_DOCS)
	if(NOT OGLPLUS_NO_SCREENSHOTS)
		add_dependencies(doc oglplus_example_screenshots)
	endif()
endif()

