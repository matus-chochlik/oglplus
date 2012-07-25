#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

#TODO auto-detect or allow the caller to set this
if(OGLPLUS_USE_GLEW)
	if(
		("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC") OR
		("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	)
		set(OGLPLUS_EXAMPLE_HARNESS "glut_glew_cxx03")
	else()
		set(OGLPLUS_EXAMPLE_HARNESS "glut_glew")
	endif()
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

# list of examples that need libpng
file(STRINGS "./requirements/libpng.txt" OGLPLUS_EXAMPLES_USING_LIBPNG)

# list of examples that need c++11 features
file(STRINGS "./requirements/LAMBDAS.txt" OGLPLUS_EXAMPLES_USING_LAMBDAS)
file(STRINGS "./requirements/INITIALIZER_LISTS.txt" OGLPLUS_EXAMPLES_USING_INITIALIZER_LISTS)

macro(example_in_list EXAMPLE EXE_LIST VARIABLE)
	list(FIND ${EXE_LIST} "${${EXAMPLE}}" ${VARIABLE})
	set(${VARIABLE} NOT(${${VARIABLE}} LESS 0))
endmacro()

if(${PNG_FOUND})
	include_directories(${PNG_INCLUDE_DIR})
	add_definitions(${PNG_DEFINITIONS})
endif()

# make the instructions for compiling and linking of the examples
foreach(EXAMPLE_PATH ${OGLPLUS_EXAMPLES})
	# example name
	get_filename_component(EXE_NAME "${EXAMPLE_PATH}" NAME_WE)
	set(EXAMPLE "${EXE_NAME}.cpp")

	# check if we need to link to libpng
	example_in_list(
		EXAMPLE
		OGLPLUS_EXAMPLES_USING_LIBPNG
		EXE_NEEDS_LIBPNG
	)

	# check if the example needs c++11 features
	example_in_list(
		EXAMPLE
		OGLPLUS_EXAMPLES_USING_LAMBDAS
		EXE_NEEDS_LAMBDAS
	)
	example_in_list(
		EXAMPLE
		OGLPLUS_EXAMPLES_USING_INITIALIZER_LISTS
		EXE_NEEDS_INITIALIZER_LISTS
	)

	# now check if the example can be built
	set(EXE_CAN_BE_BUILT
		((${PNG_FOUND}) OR (NOT(${EXE_NEEDS_LIBPNG}))) AND
		((NOT(${OGLPLUS_NO_LAMBDAS})) OR (NOT(${EXE_NEEDS_LAMBDAS}))) AND
		((NOT(${OGLPLUS_NO_INITIALIZER_LISTS})) OR (NOT(${EXE_NEEDS_INITIALIZER_LISTS})))
	)

	# if we have everything to build the executable
	if(${EXE_CAN_BE_BUILT})
		add_executable(${EXE_NAME} EXCLUDE_FROM_ALL ${EXAMPLE})
		add_dependencies(${EXE_NAME} oglplus_textures)

		# make a list of libraries that we're going to link to
		unset(EXE_LIBS)
		set(EXE_LIBS ${OGLPLUS_EXAMPLE_HARNESS_LIBS} ${OGLPLUS_GL_LIBS})

		# if this example needs lib png
		if(EXE_NEEDS_LIBPNG)
			set(EXE_LIBS ${EXE_LIBS} ${PNG_LIBRARIES})
		endif()


		# set the link libraries
		target_link_libraries(${EXE_NAME} oglplus_example_harness ${EXE_LIBS})
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
	endif()
endforeach()

if(NOT OGLPLUS_NO_DOCS)
	if(NOT OGLPLUS_NO_SCREENSHOTS)
		add_dependencies(doc oglplus_example_screenshots)
	endif()
endif()

