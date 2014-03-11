#  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# we need C++11
if(${CMAKE_COMPILER_IS_GNUCXX})
	set(OGLPLUS_CPP_STD_COMPILER_SWITCH -std=c++0x)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(OGLPLUS_CPP_STD_COMPILER_SWITCH -std=c++0x -stdlib=libc++ -DOGLPLUS_NO_NOEXCEPT=1)
endif()
# TODO add support for other compilers

add_definitions(${OGLPLUS_CPP_STD_COMPILER_SWITCH})

function(cpp_feature_detection FEATURE_NAME)
	if(NOT DEFINED OGLPLUS_NO_${FEATURE_NAME})
		configure_file(
			${PROJECT_SOURCE_DIR}/config/cpp/has_${FEATURE_NAME}.cpp
			${PROJECT_BINARY_DIR}/cpp/has_${FEATURE_NAME}.cpp
		)

		try_compile(
			OGLPLUS_HAS_${FEATURE_NAME}
			${PROJECT_BINARY_DIR}/cpp
			${PROJECT_BINARY_DIR}/cpp/has_${FEATURE_NAME}.cpp
			COMPILE_DEFINITIONS ${OGLPLUS_CPP_STD_COMPILER_SWITCH}
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

cpp_feature_detection(SCOPED_ENUMS)
cpp_feature_detection(VARIADIC_MACROS)
cpp_feature_detection(VARIADIC_TEMPLATES)
cpp_feature_detection(UNIFIED_INITIALIZATION_SYNTAX)
cpp_feature_detection(INITIALIZER_LISTS)
cpp_feature_detection(DEFAULTED_FUNCTIONS)
cpp_feature_detection(DELETED_FUNCTIONS)
cpp_feature_detection(EXPLICIT_CONVERSION_OPERATORS)
cpp_feature_detection(FUNCTION_TEMPLATE_DEFAULT_ARGS)
cpp_feature_detection(UNICODE_LITERALS)
cpp_feature_detection(USER_DEFINED_LITERALS)
cpp_feature_detection(CONSTEXPR)
cpp_feature_detection(NOEXCEPT)
cpp_feature_detection(LAMBDAS)
cpp_feature_detection(NULLPTR)
cpp_feature_detection(CHRONO)
cpp_feature_detection(THREADS)

# explicit configuration
if(
	("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
)
	set(OGLPLUS_NO_CHRONO 1)
endif()
