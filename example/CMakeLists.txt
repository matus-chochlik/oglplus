#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# tests if THE_STRING is in THE_LIST
macro(string_in_list THE_STRING THE_LIST VARIABLE)

	list(FIND ${THE_LIST} "${THE_STRING}" ${VARIABLE})
	set(${VARIABLE} NOT(${${VARIABLE}} LESS 0))
endmacro(string_in_list)

# fetches the list of examples depending on DEPENDENCY from a file
macro(fetch_dependent_examples DEPENDENCY)

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${DEPENDENCY}.txt")
		file(STRINGS
			"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${DEPENDENCY}.txt"
			DEPENDING_ON_${DEPENDENCY}
		)
	else()
		set(DEPENDING_ON_${DEPENDENCY} "")
	endif()
endmacro(fetch_dependent_examples)


# fetches the list of examples requiring a C++11 feature from a file
macro(fetch_cxx11_using_examples CXX11_FEATURE)

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/requirements/${CXX11_FEATURE}.txt")
		file(STRINGS
			"${CMAKE_CURRENT_SOURCE_DIR}/requirements/${CXX11_FEATURE}.txt"
			REQUIRING_${CXX11_FEATURE}
		)
	else()
		set(REQUIRING_${CXX11_FEATURE} "")
	endif()
endmacro(fetch_cxx11_using_examples)


# checks if an EXE can be built and adds required include directories
macro(require_dependency EXE_NAME RESULT DEPENDENCY)

	if(${${RESULT}})
		string_in_list(
			"${EXE_NAME}.cpp"
			DEPENDING_ON_${DEPENDENCY}
			EXE_NEEDS_${DEPENDENCY}
		)
		if((${${DEPENDENCY}_FOUND}) OR (NOT(${EXE_NEEDS_${DEPENDENCY}})))
			if(${EXE_NEEDS_${DEPENDENCY}})
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
			endif()
			set(${RESULT} true)
		else()
			message(
				STATUS
				"Skipping '${EXE_NAME}' "
				"because ${DEPENDENCY} not found"
			)
			set(${RESULT} false)
		endif()
	endif()
endmacro(require_dependency)

# checks if an EXE can be built
macro(require_cxx11_feature EXE_NAME RESULT CXX11_FEATURE)
	if(${${RESULT}})
		string_in_list(
			"${EXE_NAME}.cpp"
			REQUIRING_${CXX11_FEATURE}
			EXE_NEEDS_${CXX11_FEATURE}
		)
		if((NOT(${OGLPLUS_NO_${CXX11_FEATURE}})) OR (NOT(${EXE_NEEDS_${CXX11_FEATURE}})))
			set(${RESULT} true)
		else()
			message(
				STATUS
				"Skipping '${EXE_NAME}' "
				"because ${CXX11_FEATURE} not implemented"
			)
			set(${RESULT} false)
		endif()
	endif()
endmacro(require_cxx11_feature)


# adds DEPENDENCY's libraries to an exe if necessary
macro(add_dep_link_library TARGET_NAME DEPENDENCY)

	if(${EXE_NEEDS_${DEPENDENCY}})
		if(${DEPENDENCY}_LIBRARIES)
			target_link_libraries(${TARGET_NAME} ${${DEPENDENCY}_LIBRARIES})
		endif()
	endif()
endmacro()


# TODO reimplement when EVAL is available
# fetches the lists of examples depending on all dependencies from files
macro(fetch_all_dependent_examples)

	fetch_dependent_examples(PNG)

	fetch_cxx11_using_examples(LAMBDAS)
	fetch_cxx11_using_examples(INITIALIZER_LISTS)
	fetch_cxx11_using_examples(VARIADIC_TEMPLATES)
	fetch_cxx11_using_examples(FUNCTION_TEMPLATE_DEFAULT_ARGS)
endmacro(fetch_all_dependent_examples)

# checks if an EXE can be built and adds required include directories
macro(require_all_dependencies EXE_NAME RESULT)

	require_dependency(${EXE_NAME} ${RESULT} PNG)

	require_cxx11_feature(${EXE_NAME} ${RESULT} LAMBDAS)
	require_cxx11_feature(${EXE_NAME} ${RESULT} INITIALIZER_LISTS)
	require_cxx11_feature(${EXE_NAME} ${RESULT} VARIADIC_TEMPLATES)
	require_cxx11_feature(${EXE_NAME} ${RESULT} FUNCTION_TEMPLATE_DEFAULT_ARGS)
endmacro(require_all_dependencies)

# adds all required libraries to an exe
macro(add_all_dep_link_libraries EXE_NAME)

	add_dep_link_library(${EXE_NAME} PNG)
endmacro(add_all_dep_link_libraries)

# helper function used in the directories containing examples
function(add_examples EXAMPLE_PATTERN PARENT_TARGET COMMON_LIBS)

	file(GLOB EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_PATTERN}.cpp")

	fetch_all_dependent_examples()

	foreach(EXAMPLE_PATH ${EXAMPLES})
		get_filename_component(EXAMPLE_NAME "${EXAMPLE_PATH}" NAME_WE)
		set(TARGET_NAME "${EXAMPLE_NAME}")

		set(EXAMPLE_CAN_BE_BUILT true)
		require_all_dependencies(${EXAMPLE_NAME} EXAMPLE_CAN_BE_BUILT)

		if(EXAMPLE_CAN_BE_BUILT)
			add_executable(${TARGET_NAME} EXCLUDE_FROM_ALL ${EXAMPLE_PATH})
			target_link_libraries(${TARGET_NAME} ${COMMON_LIBS})
			add_all_dep_link_libraries(${TARGET_NAME})
			add_dependencies("${PARENT_TARGET}" ${TARGET_NAME})

			add_dependencies(${TARGET_NAME} oglplus-textures)

			if(NOT OGLPLUS_NO_SCREENSHOTS)
				add_custom_command(
					OUTPUT ${EXAMPLE_NAME}.rgb
					COMMAND ${EXAMPLE_NAME} --screenshot ${EXAMPLE_NAME}.rgb
					DEPENDS ${EXAMPLE_NAME}
				)

				if(${ImageMagick_convert_FOUND})
					add_custom_command(
						OUTPUT ${EXAMPLE_NAME}.png
						COMMAND ${ImageMagick_convert_EXECUTABLE}
							-depth 8
							-size 800x600
							${EXAMPLE_NAME}.rgb
							-flip
							-adaptive-resize 400x300
							${EXAMPLE_NAME}.png
						DEPENDS ${EXAMPLE_NAME}.rgb
					)

					add_custom_target("${EXAMPLE_NAME}-screenshot" DEPENDS ${EXAMPLE_NAME}.png)
					add_dependencies("${PARENT_TARGET}-screenshots" "${EXAMPLE_NAME}-screenshot")
				endif()
			endif()
		endif()
	endforeach()
endfunction(add_examples)


add_subdirectory("oglplus")
add_subdirectory("standalone")
