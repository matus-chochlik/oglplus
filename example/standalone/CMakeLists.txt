#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

#TODO
if(NOT(${CMAKE_COMPILER_IS_GNUCXX}))
	return()
endif()

add_custom_target(standalone-examples ALL)

function(standalone_example_common EXAMPLE_NAME)
	add_executable(
		${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		${EXAMPLE_NAME}.cpp
	)
	add_dependencies(standalone-examples ${EXAMPLE_NAME})
	target_link_libraries(${EXAMPLE_NAME} ${OPENGL_LIBRARIES} ${ARGN})
endfunction()

if(GLUT_FOUND AND GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	include_directories(${GLUT_INCLUDE_DIRS})

	standalone_example_common(
		001_triangle_glut_glew
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	standalone_example_common(
		001_program_resources
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	if(HAS_GLEW_ATI_meminfo)
		standalone_example_common(
			001_ati_meminfo
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()

	if(HAS_GLEW_AMD_performance_monitor)
		standalone_example_common(
			002_amd_perf_monitor
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()

	if(HAS_GLEW_ARB_compatibility AND HAS_GLEW_ARB_debug_output)
		standalone_example_common(
			002_triangle_compatibility
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()

	if(HAS_GLEW_ARB_compatibility AND HAS_GLEW_NV_path_rendering)
		standalone_example_common(
			002_simple_path
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)

		if(HAS_GLEW_EXT_direct_state_access)
			standalone_example_common(
				003_simple_text
				${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
			)

			standalone_example_common(
				004_text_rendering
				${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
			)
		endif()
	endif()

	if(GLM_FOUND)
		include_directories(${GLM_INCLUDE_DIRS})
		standalone_example_common(
			007_glm_boxes
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()
endif()
