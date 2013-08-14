#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

string(TOLOWER ${OGLPLUS_GL_INIT_LIB} OGLPLUS_EXAMPLE_HARNESS)

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

add_definitions(-DOGLPLUS_LINK_LIBRARY=${OGLPLUS_LINK_LIBRARY})

if("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "qtgl")
	QT4_WRAP_CPP(
		OGLPLUS_EXAMPLE_HARNESS_ADDITIONAL_SOURCES
		"${CMAKE_CURRENT_SOURCE_DIR}/${OGLPLUS_EXAMPLE_HARNESS}_main.hpp"
	)
else()
	set(OGLPLUS_EXAMPLE_HARNESS_ADDITIONAL_SOURCES "")
endif()


# build the code common to all the examples into this library
add_library(
	oglplus_example_harness STATIC
	EXCLUDE_FROM_ALL
	"${CMAKE_CURRENT_SOURCE_DIR}/${OGLPLUS_EXAMPLE_HARNESS}_main.cpp"
	"${OGLPLUS_EXAMPLE_HARNESS_ADDITIONAL_SOURCES}"
)
# add the dependencies for the harness
add_all_dependencies(${OGLPLUS_EXAMPLE_HARNESS}_main oglplus_example_harness)

# TODO: try to find some better solution for this
if("${OGLPLUS_EXAMPLE_HARNESS}" STREQUAL "glx")
	target_link_libraries(oglplus_example_harness pthread)
endif()

# helper function used in the directories containing examples
function(add_examples EXAMPLE_PATTERN PARENT_TARGET COMMON_LIBS)

	file(GLOB EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_PATTERN}.cpp")

	if(${WIN32})
		set(SCREENSHOT_MAKER "${PROJECT_SOURCE_DIR}/config/make_screenshot.bat")
	else()
		set(SCREENSHOT_MAKER "${PROJECT_SOURCE_DIR}/config/make_screenshot.sh")
	endif()

	if(${ImageMagick_convert_FOUND})
		set(SCREENSHOT_CONVERT ${ImageMagick_convert_EXECUTABLE})
	else()
		set(SCREENSHOT_CONVERT "")
	endif()

	foreach(EXAMPLE_PATH ${EXAMPLES})
		get_filename_component(EXAMPLE_NAME "${EXAMPLE_PATH}" NAME_WE)
		set(TARGET_NAME "${EXAMPLE_NAME}")

		set(EXAMPLE_CAN_BE_BUILT true)
		require_all_dependencies(${EXAMPLE_NAME} EXAMPLE_CAN_BE_BUILT)

		if(EXAMPLE_CAN_BE_BUILT)
			add_executable(${TARGET_NAME} EXCLUDE_FROM_ALL ${EXAMPLE_PATH})
			target_link_libraries(${TARGET_NAME} ${COMMON_LIBS})
			add_all_dependencies(${TARGET_NAME})
			add_dependencies("${PARENT_TARGET}" ${TARGET_NAME})
		endif()
		if(NOT OGLPLUS_NO_SCREENSHOTS AND EXISTS ${SCREENSHOT_MAKER})
			if(EXAMPLE_CAN_BE_BUILT)
				add_custom_command(
					OUTPUT ${EXAMPLE_NAME}.png
					COMMAND ${SCREENSHOT_MAKER}
						${EXAMPLE_NAME}
						${EXAMPLE_NAME}.png
						${SCREENSHOT_CONVERT}
					DEPENDS ${EXAMPLE_NAME}
				)
			else()
				add_custom_command(
					OUTPUT ${EXAMPLE_NAME}.png
					COMMAND ${SCREENSHOT_MAKER}
						${EXAMPLE_NAME}
						${EXAMPLE_NAME}.png
						${SCREENSHOT_CONVERT}
				)
			endif()

			add_custom_target("${EXAMPLE_NAME}-screenshot" DEPENDS ${EXAMPLE_NAME}.png)
			add_dependencies("${PARENT_TARGET}-screenshots" "${EXAMPLE_NAME}-screenshot")
		endif()
	endforeach()
endfunction(add_examples)

# make a list of libraries that we're going to link to
set(EXAMPLE_LIBS
	oglplus_example_harness
	${OGLPLUS_GL_LIBS}
)

# add oglplus examples
add_examples("[0-9][0-9][0-9]*" oglplus-examples "${EXAMPLE_LIBS}")

if(NOT OGLPLUS_NO_DOCS)
	if(NOT OGLPLUS_NO_SCREENSHOTS)
		add_dependencies(oglplus-doc oglplus-examples-screenshots)
	endif()
endif()

