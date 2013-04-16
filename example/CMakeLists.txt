#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include(../config/ExeRequirements.cmake)

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


add_subdirectory("oglplus")
add_subdirectory("standalone")
add_subdirectory("advanced")
