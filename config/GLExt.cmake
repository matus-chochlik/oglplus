#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

function(gl_ext_detection EXTENSION_NAME)
	set(OGLPLUS_CONFIG_QUERY_GL_EXT GL_${EXTENSION_NAME})
	configure_file(
		${PROJECT_SOURCE_DIR}/config/has_GL_EXT.cpp.in
		${PROJECT_BINARY_DIR}/gl_ext/has_GL_${EXTENSION_NAME}.cpp
	)
	unset(OGLPLUS_CONFIG_QUERY_GL_EXT)

	try_compile(
		HAS_GL_${EXTENSION_NAME}
		${PROJECT_BINARY_DIR}/gl_ext
		${PROJECT_BINARY_DIR}/gl_ext/has_GL_${EXTENSION_NAME}.cpp
		COMPILE_DEFINITIONS
			-I${OGLPLUS_GL_INCLUDE_DIR}
			-I${PROJECT_SOURCE_DIR}/include
			-I${PROJECT_BINARY_DIR}/include
	)
endfunction()

function(glew_ext_detection EXTENSION_NAME)
	if(GLEW_FOUND)
		set(OGLPLUS_CONFIG_QUERY_GL_EXT GL_${EXTENSION_NAME})
		configure_file(
			${PROJECT_SOURCE_DIR}/config/has_GLEW_EXT.cpp.in
			${PROJECT_BINARY_DIR}/gl_ext/has_GLEW_${EXTENSION_NAME}.cpp
		)
		unset(OGLPLUS_CONFIG_QUERY_GL_EXT)
	
		try_compile(
			HAS_GLEW_${EXTENSION_NAME}
			${PROJECT_BINARY_DIR}/gl_ext
			${PROJECT_BINARY_DIR}/gl_ext/has_GLEW_${EXTENSION_NAME}.cpp
			COMPILE_DEFINITIONS
				-I${OGLPLUS_GL_INCLUDE_DIR}
				-I${PROJECT_SOURCE_DIR}/include
				-I${PROJECT_BINARY_DIR}/include
		)
	endif()
endfunction()

glew_ext_detection(ARB_compatibility)
glew_ext_detection(ARB_debug_output)
glew_ext_detection(ATI_meminfo)
glew_ext_detection(NV_path_rendering)
