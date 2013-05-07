#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
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
					"because '${DEPENDENCY}' not found."
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
					"because '${REQUIREMENT}' not implemented properly."
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
	if("${ARGN}" STREQUAL "")
		set(TARGET_NAME "${EXE_NAME}")
	else()
		set(TARGET_NAME "${ARGN}")
	endif()
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${EXE_NAME}.txt")
		file(STRINGS
			"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${EXE_NAME}.txt"
			EXE_DEPENDENCIES
		)
		foreach(DEPENDENCY ${EXE_DEPENDENCIES})
			if(${DEPENDENCY}_LIBRARIES)
				target_link_libraries(${TARGET_NAME} ${${DEPENDENCY}_LIBRARIES})
			endif()
		endforeach()
	endif()

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources/${EXE_NAME}.tex.txt")
		file(STRINGS
			"${CMAKE_CURRENT_SOURCE_DIR}/resources/${EXE_NAME}.tex.txt"
			EXE_TEXTURES
		)
		foreach(TEXTURE ${EXE_TEXTURES})
			add_dependencies("${TARGET_NAME}" "texture-${TEXTURE}")
		endforeach()
	endif()

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources/${EXE_NAME}.model.txt")
		file(STRINGS
			"${CMAKE_CURRENT_SOURCE_DIR}/resources/${EXE_NAME}.model.txt"
			EXE_MODELS
		)
		foreach(MODEL ${EXE_MODELS})
			add_dependencies("${TARGET_NAME}" "model-${MODEL}")
		endforeach()
	endif()
endmacro(add_all_dependencies)

