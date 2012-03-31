#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# we need C++11
# TODO add support for various compilers
add_definitions(-std=c++0x)

function(cpp11_feature_detection FEATURE_NAME)
	configure_file(
		${PROJECT_SOURCE_DIR}/config/cpp11/has_${FEATURE_NAME}.cpp
		${PROJECT_BINARY_DIR}/cpp11/has_${FEATURE_NAME}.cpp
	)

	try_compile(
		OGLPLUS_HAS_${FEATURE_NAME}
		${PROJECT_BINARY_DIR}/cpp11
		${PROJECT_BINARY_DIR}/cpp11/has_${FEATURE_NAME}.cpp
	)
	message(STATUS "Detecting support for c++11 feature '${FEATURE_NAME}': ${OGLPLUS_HAS_${FEATURE_NAME}}")
	if(OGLPLUS_HAS_${FEATURE_NAME})
		set(OGLPLUS_NO_${FEATURE_NAME} 0 PARENT_SCOPE)
	else()
		set(OGLPLUS_NO_${FEATURE_NAME} 1 PARENT_SCOPE)
	endif()
	unset(OGLPLUS_HAS_${FEATURE_NAME})
endfunction()

cpp11_feature_detection(NULLPTR)
