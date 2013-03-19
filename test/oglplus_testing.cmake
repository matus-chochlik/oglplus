#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

enable_testing()
include(CTest)

function(add_oglplus_test TEST_NAME BUILD_ONLY)

	add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_NAME}.cpp)

	if(NOT BUILD_ONLY)
		target_link_libraries(
			${TEST_NAME}
			${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
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

function(oglplus_build_test TEST_NAME)
	add_oglplus_test(${TEST_NAME} TRUE)
endfunction()

function(oglplus_exec_test TEST_NAME)
	add_oglplus_test(${TEST_NAME} FALSE)
endfunction()
