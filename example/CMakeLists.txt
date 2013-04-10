#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# checks if an EXE can be built and adds required include directories
macro(require_all_dependencies EXE_NAME RESULT)

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${EXE_NAME}.txt")
		file(STRINGS
			"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${EXE_NAME}.txt"
			EXE_DEPENDENCIES
		)
		foreach(DEPENDENCY ${EXE_DEPENDENCIES})
			if(${${DEPENDENCY}_FOUND})
				if(${DEPENDENCY}_INCLUDE_DIRS)
					include_directories(${${DEPENDENCY}_INCLUDE_DIRS})
				endif()
				if(${DEPENDENCY}_DEFINITIONS)
					set_property(
						SOURCE "${EXE_NAME}.cpp" APPEND PROPERTY
						COMPILE_DEFINITIONS ${${DEPENDENCY}_DEFINITIONS}
					)
				endif()
				if(${DEPENDENCY}_CXX_FLAGS)
					set(CMAKE_CXXFLAGS ${CMAKE_CXX_FLAGS} ${${DEPENDENCY}_CXX_FLAGS})
				endif()
			else()
				message(
					STATUS
					"Skipping '${EXE_NAME}' "
					"because ${DEPENDENCY} not found"
				)
				set(${RESULT} false)
			endif()
			
		endforeach()
	endif()

	file(GLOB REQ_FILES "${CMAKE_CURRENT_SOURCE_DIR}/requirements/${EXE_NAME}.*.txt")

	foreach(REQ_FILE ${REQ_FILES})
		file(STRINGS "${REQ_FILE}" EXE_REQUIREMENTS)
		
		foreach(REQUIREMENT ${EXE_REQUIREMENTS})
			if(${OGLPLUS_NO_${REQUIREMENT}})
				message(
					STATUS
					"Skipping '${EXE_NAME}' "
					"because ${REQUIREMENT} not implemented"
				)
				set(${RESULT} false)
			endif()
		endforeach()
	endforeach()

endmacro(require_all_dependencies)

# adds all required libraries to an exe
# also creates a dependency between the exe
# and any textures it is using
macro(add_all_dependencies EXE_NAME)
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${EXE_NAME}.txt")
		file(STRINGS
			"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${EXE_NAME}.txt"
			EXE_DEPENDENCIES
		)
		foreach(DEPENDENCY ${EXE_DEPENDENCIES})
			if(${DEPENDENCY}_LIBRARIES)
				target_link_libraries(${EXE_NAME} ${${DEPENDENCY}_LIBRARIES})
			endif()
		endforeach()
	endif()

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources/${EXE_NAME}.tex.txt")
		file(STRINGS
			"${CMAKE_CURRENT_SOURCE_DIR}/resources/${EXE_NAME}.tex.txt"
			EXE_TEXTURES
		)
		foreach(TEXTURE ${EXE_TEXTURES})
			add_dependencies("${EXE_NAME}" "texture-${TEXTURE}")
		endforeach()
	endif()
endmacro(add_all_dependencies)

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
