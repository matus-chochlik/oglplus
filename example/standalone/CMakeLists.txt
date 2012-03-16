#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

add_custom_target(standalone_examples ALL)

function(standalone_example_common EXAMPLE_NAME)
	add_executable(
		${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		${EXAMPLE_NAME}.cpp
	)
	add_dependencies(${EXAMPLE_NAME} auto_generated_headers)
	add_dependencies(standalone_examples ${EXAMPLE_NAME})
	target_link_libraries(${EXAMPLE_NAME} GL ${ARGN})
endfunction()

if(GLUT_FOUND AND GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIR})
	include_directories(${GLUT_INCLUDE_DIR})

	standalone_example_common(
		001_triangle_glut_glew
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	standalone_example_common(
		001_ati_meminfo
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	standalone_example_common(
		002_triangle_compatibility
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	standalone_example_common(
		002_simple_path
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)
endif()
