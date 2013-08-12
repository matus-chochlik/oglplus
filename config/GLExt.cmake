#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

function(gl_lib_ext_detection GL_LIB EXTENSION_VENDOR EXTENSION_NAME)
	if(NOT DEFINED OGLPLUS_CONFIG_STRICT_VERSION_CHECK)
		set(OGLPLUS_CONFIG_STRICT_VERSION_CHECK 1)
	endif()

	set(GL_LIB_EXTENSION ${GL_LIB}_${EXTENSION_VENDOR}_${EXTENSION_NAME})

	if(NOT DEFINED HAS_${GL_LIB_EXTENSION})
		# if there is a specific file for the detection of extension availability
		if(EXISTS ${PROJECT_SOURCE_DIR}/config/gl_ext/has_${GL_LIB_EXTENSION}.cpp)
			# use it
			configure_file(
				${PROJECT_SOURCE_DIR}/config/gl_ext/has_${GL_LIB_EXTENSION}.cpp
				${PROJECT_BINARY_DIR}/gl_ext/has_${GL_LIB_EXTENSION}.cpp
			)
		else()
			# otherwise use the generic template
			set(OGLPLUS_CONFIG_QUERY_GL_EXT GL_${EXTENSION_VENDOR}_${EXTENSION_NAME})

			configure_file(
				${PROJECT_SOURCE_DIR}/config/gl_ext/has_${GL_LIB}_EXT.cpp.in
				${PROJECT_BINARY_DIR}/gl_ext/has_${GL_LIB_EXTENSION}.cpp
			)
			unset(OGLPLUS_CONFIG_QUERY_GL_EXT)
		endif()

		set(OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS
			"${OGLPLUS_GL_INCLUDE_DIRS};"
			"${PROJECT_SOURCE_DIR}/include;"
			"${PROJECT_BINARY_DIR}/include"
		)
		set(OGLPLUS_CONFIG_REQUIRED_LIBRARIES
			"${OGLPLUS_GL_LIBS}"
		)
		if(GLUT_FOUND)
			set(OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS
				"${OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS};"
				"${GLUT_INCLUDE_DIRS}"
			)
			set(OGLPLUS_CONFIG_REQUIRED_LIBRARIES
				"${OGLPLUS_CONFIG_REQUIRED_LIBRARIES};"
				"${GLUT_LIBRARIES}"
			)
		endif()

		try_run(
			RUNS_WITH_${GL_LIB_EXTENSION} COMPILED_WITH_${GL_LIB_EXTENSION}
			"${PROJECT_BINARY_DIR}/gl_ext"
			"${PROJECT_BINARY_DIR}/gl_ext/has_${GL_LIB_EXTENSION}.cpp"
			COMPILE_DEFINITIONS ${OGLPLUS_CPP11_COMPILER_SWITCH}
			CMAKE_FLAGS
				"-DINCLUDE_DIRECTORIES:STRING=${OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS} "
				"-DLINK_LIBRARIES:STRING=${OGLPLUS_CONFIG_REQUIRED_LIBRARIES} "
		)
		if((COMPILED_WITH_${GL_LIB_EXTENSION}) AND (RUNS_WITH_${GL_LIB_EXTENSION} EQUAL 0))
			set(HAS_${GL_LIB_EXTENSION} 1 PARENT_SCOPE)
			message(STATUS "Found ${GL_LIB} extension: ${EXTENSION_VENDOR}_${EXTENSION_NAME}")
		else()
			set(OGLPLUS_NO_${GL_LIB_EXTENSION} true)
		endif()
		unset(RUNS_WITH_${GL_LIB_EXTENSION})
		unset(COMPILED_WITH_${GL_LIB_EXTENSION})
	endif()

endfunction()


gl_lib_ext_detection(GL ARB separate_shader_objects)
gl_lib_ext_detection(GL ARB transform_feedback2)
gl_lib_ext_detection(GL ARB viewport_array)
gl_lib_ext_detection(GL ARB compatibility)
gl_lib_ext_detection(GL EXT direct_state_access)


function(glew_ext_detection EXTENSION_VENDOR EXTENSION_NAME)
	if(GLEW_FOUND)
		gl_lib_ext_detection(GLEW ${EXTENSION_VENDOR} ${EXTENSION_NAME})
	endif()
endfunction()

glew_ext_detection(ARB compatibility)
glew_ext_detection(EXT direct_state_access)
glew_ext_detection(ARB debug_output)
glew_ext_detection(ATI meminfo)
glew_ext_detection(NV path_rendering)
glew_ext_detection(AMD performance_monitor)
