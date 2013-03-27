#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

enable_testing()
include(CTest)

if(OGLPLUS_USE_WXGL)
	set(OGLPLUS_TEST_FIXTURE "wxgl")
elseif(OGLPLUS_USE_GLUT)
	set(OGLPLUS_TEST_FIXTURE "glut")
elseif(OGLPLUS_USE_GLFW)
	set(OGLPLUS_TEST_FIXTURE "glfw")
elseif(OGLPLUS_USE_SDL)
	set(OGLPLUS_TEST_FIXTURE "sdl")
elseif(OGLPLUS_USE_GLX)
	set(OGLPLUS_TEST_FIXTURE "glx")
endif()

#
# GLUT
if(("${OGLPLUS_TEST_FIXTURE}" STREQUAL "glut"))
	if(NOT GLUT_FOUND)
		message(FATAL_ERROR "GLUT is required")
		return()
	endif()

	include_directories(${GLUT_INCLUDE_DIRS})
	set(OGLPLUS_TEST_FIXTURE_LIBS ${GLUT_LIBRARIES})

# WXGL
elseif(("${OGLPLUS_TEST_FIXTURE}" STREQUAL "wxgl"))
	# TODO
	message(FATAL_ERROR "wxGL fixture is not implemented")

	if(NOT wxWidgets_FOUND)
		message(FATAL_ERROR "wxGL is required")
		return()
	endif()

	include(${wxWidgets_USE_FILE})
	set(OGLPLUS_TEST_FIXTURE_LIBS ${wxWidgets_LIBRARIES})

# GLFW
elseif(("${OGLPLUS_TEST_FIXTURE}" STREQUAL "glfw"))
	if(NOT GLFW_FOUND)
		message(FATAL_ERROR "GLFW is required")
		return()
	endif()

	include_directories(${GLFW_INCLUDE_DIRS})
	set(OGLPLUS_TEST_FIXTURE_LIBS ${GLFW_LIBRARIES})

# SDL
elseif(("${OGLPLUS_TEST_FIXTURE}" STREQUAL "sdl"))
	if(NOT SDL_FOUND)
		message(FATAL_ERROR "SDL is required")
		return()
	endif()

	include_directories(${SDL_INCLUDE_DIRS})
	set(OGLPLUS_TEST_FIXTURE_LIBS ${SDL_LIBRARIES})

# X11/GLX
elseif(("${OGLPLUS_TEST_FIXTURE}" STREQUAL "glx"))
	if(NOT X11_FOUND)
		message(FATAL_ERROR "X11 is required")
		return()
	endif()

	include_directories(${X11_INCLUDE_DIR})
	set(OGLPLUS_TEST_FIXTURE_LIBS ${X11_LIBRARIES} pthread)
endif()

include_directories(${PROJECT_SOURCE_DIR}/utils)

add_library(
	oglplus_test_fixture
	STATIC
	EXCLUDE_FROM_ALL
	${CMAKE_CURRENT_SOURCE_DIR}/fixture_${OGLPLUS_TEST_FIXTURE}.cpp
)

set(OGLPLUS_TEST_LIBS
	oglplus_test_fixture
	${OGLPLUS_TEST_FIXTURE_LIBS}
	${OGLPLUS_GL_LIBS}
)


function(add_oglplus_test TEST_NAME TEST_LIBRARIES BUILD_ONLY)

	add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_NAME}.cpp)
	target_link_libraries(${TEST_NAME} ${TEST_LIBRARIES})

	if(NOT BUILD_ONLY)
		target_link_libraries(
			${TEST_NAME}
			${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
			oglplus_test_fixture
		)
	endif()

	add_test(
		build-test-${TEST_NAME}
		"${CMAKE_COMMAND}"
		--build ${CMAKE_BINARY_DIR}
		--target ${TEST_NAME}
	)

	if(NOT BUILD_ONLY)
		add_test(exec-test-${TEST_NAME} ${TEST_NAME})
		set_tests_properties(
			exec-test-${TEST_NAME}
			PROPERTIES DEPENDS
			build-test-${TEST_NAME}
		)
	endif()
endfunction()

function(oglplus_build_test TEST_NAME TEST_LIBRARIES)
	add_oglplus_test(${TEST_NAME} "${TEST_LIBRARIES}" TRUE)
endfunction()

function(oglplus_build_test_no_fixture TEST_NAME)
	add_oglplus_test(${TEST_NAME} "" TRUE)
endfunction()

function(oglplus_exec_test TEST_NAME TEST_LIBRARIES)
	add_oglplus_test(${TEST_NAME} "${TEST_LIBRARIES}" FALSE)
endfunction()

function(oglplus_exec_test_no_fixture TEST_NAME)
	add_oglplus_test(${TEST_NAME} "" FALSE)
endfunction()
