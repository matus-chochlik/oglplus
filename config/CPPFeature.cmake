#  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED True)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	list(APPEND CMAKE_CXX_FLAGS --std=c++${CMAKE_CXX_STANDARD})
endif()

function(cpp_feature_detection FEATURE_NAME)
	if(NOT DEFINED OGLPLUS_NO_${FEATURE_NAME})
		configure_file(
			${PROJECT_SOURCE_DIR}/config/cpp/has_${FEATURE_NAME}.cpp
			${PROJECT_BINARY_DIR}/cpp/has_${FEATURE_NAME}.cpp
		)
		if(${${FEATURE_NAME}_FOUND})
			do_use_single_dependency(${FEATURE_NAME})
		endif()

		try_compile(
			OGLPLUS_HAS_${FEATURE_NAME}
			${PROJECT_BINARY_DIR}/cpp
			${PROJECT_BINARY_DIR}/cpp/has_${FEATURE_NAME}.cpp
			CMAKE_FLAGS
				-DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
				-DCMAKE_CXX_STANDARD_REQUIRED=True
			LINK_LIBRARIES ${THREADS_LIBRARIES}
		)
		message(STATUS
			"Detecting support for c++ feature '${FEATURE_NAME}': "
			"${OGLPLUS_HAS_${FEATURE_NAME}}"
		)
		if(OGLPLUS_HAS_${FEATURE_NAME})
			set(OGLPLUS_NO_${FEATURE_NAME} 0 CACHE INTERNAL "")
			set(HAS_CPP_${FEATURE_NAME} TRUE PARENT_SCOPE)
		else()
			set(OGLPLUS_NO_${FEATURE_NAME} 1 CACHE INTERNAL "")
		endif()
		unset(OGLPLUS_HAS_${FEATURE_NAME})
	elseif(NOT ${OGLPLUS_NO_${FEATURE_NAME}})
		set(HAS_CPP_${FEATURE_NAME} TRUE PARENT_SCOPE)
	endif()
endfunction()

function(require_cpp_feature FEATURE_NAME)
	cpp_feature_detection(${FEATURE_NAME})

	if(${OGLPLUS_NO_${FEATURE_NAME}})
		message(FATAL_ERROR
			"C++ feature '${FEATURE_NAME}' is required "
			"but not supported by the currently used compiler!"
		)
	endif()

endfunction()

require_cpp_feature(SCOPED_ENUMS)

cpp_feature_detection(SCOPED_ENUM_TEMPLATE_PARAMS)
cpp_feature_detection(VARIADIC_MACROS)
cpp_feature_detection(VARIADIC_TEMPLATES)
cpp_feature_detection(UNIFIED_INITIALIZATION_SYNTAX)
cpp_feature_detection(INITIALIZER_LISTS)
cpp_feature_detection(FUNCTION_TEMPLATE_DEFAULT_ARGS)
cpp_feature_detection(UNICODE_LITERALS)
cpp_feature_detection(USER_DEFINED_LITERALS)
cpp_feature_detection(INHERITED_CONSTRUCTORS)
cpp_feature_detection(GENERALIZED_ATTRIBUTES)
cpp_feature_detection(TEMPLATE_ALIASES)
