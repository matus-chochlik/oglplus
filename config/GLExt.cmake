#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

function(gl_lib_ext_detection GL_LIB EXTENSION_NAME)
	if(NOT DEFINED HAS_${GL_LIB}_${EXTENSION_NAME})
		# if there is a specific file for the detection of extension availability
		if(EXISTS ${PROJECT_SOURCE_DIR}/config/gl_ext/has_${GL_LIB}_${EXTENSION_NAME}.cpp)
			# use it
			configure_file(
				${PROJECT_SOURCE_DIR}/config/gl_ext/has_${GL_LIB}_${EXTENSION_NAME}.cpp
				${PROJECT_BINARY_DIR}/gl_ext/has_${GL_LIB}_${EXTENSION_NAME}.cpp
			)
		else()
			# otherwise use the generic template
			set(OGLPLUS_CONFIG_QUERY_GL_EXT GL_${EXTENSION_NAME})

			configure_file(
				${PROJECT_SOURCE_DIR}/config/gl_ext/has_${GL_LIB}_EXT.cpp.in
				${PROJECT_BINARY_DIR}/gl_ext/has_${GL_LIB}_${EXTENSION_NAME}.cpp
			)
			unset(OGLPLUS_CONFIG_QUERY_GL_EXT)
		endif()

		set(OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS
			"${OGLPLUS_GL_INCLUDE_DIRS};"
			"${PROJECT_SOURCE_DIR}/include;"
			"${PROJECT_BINARY_DIR}/include"
		)
		try_compile(
			HAS_${GL_LIB}_${EXTENSION_NAME}
			${PROJECT_BINARY_DIR}/gl_ext
			${PROJECT_BINARY_DIR}/gl_ext/has_${GL_LIB}_${EXTENSION_NAME}.cpp
			COMPILE_DEFINITIONS ${OGLPLUS_CPP11_COMPILER_SWITCH}
			CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS}"
		)
		if(HAS_GLEW_${EXTENSION_NAME})
			message(STATUS "Found ${GL_LIB} extension: ${EXTENSION_NAME}")
		endif()
	endif()
endfunction()

function(glew_ext_detection EXTENSION_NAME)
	if(GLEW_FOUND)
		gl_lib_ext_detection(GLEW ${EXTENSION_NAME})
	endif()
endfunction()

glew_ext_detection(ARB_compatibility)
glew_ext_detection(EXT_direct_state_access)
glew_ext_detection(ARB_debug_output)
glew_ext_detection(ATI_meminfo)
glew_ext_detection(NV_path_rendering)
glew_ext_detection(AMD_performance_monitor)
