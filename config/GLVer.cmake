#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

function(gl_lib_ver_detection GL_LIB VERSION)
	# if there is a specific file for the detection of extension availability
	if(EXISTS ${PROJECT_SOURCE_DIR}/config/gl_ver/has_${GL_LIB}_${VERSION}.cpp)
		# use it
		configure_file(
			${PROJECT_SOURCE_DIR}/config/gl_ver/has_${GL_LIB}_${VERSION}.cpp
			${PROJECT_BINARY_DIR}/gl_ver/has_${GL_LIB}_${VERSION}.cpp
		)
	else()
		# otherwise use the generic template
		set(OGLPLUS_CONFIG_QUERY_GL_VER ${GL_LIB}_VERSION_${VERSION})

		configure_file(
			${PROJECT_SOURCE_DIR}/config/gl_ver/has_${GL_LIB}_VER.cpp.in
			${PROJECT_BINARY_DIR}/gl_ver/has_${GL_LIB}_${VERSION}.cpp
		)
		unset(OGLPLUS_CONFIG_QUERY_GL_VER)
	endif()

	try_compile(
		HAS_${GL_LIB}_${VERSION}
		${PROJECT_BINARY_DIR}/gl_ver
		${PROJECT_BINARY_DIR}/gl_ver/has_${GL_LIB}_${VERSION}.cpp
		COMPILE_DEFINITIONS
			${OGLPLUS_CPP11_COMPILER_SWITCH}
			-I${OGLPLUS_GL_INCLUDE_DIRS}
			-I${PROJECT_SOURCE_DIR}/include
			-I${PROJECT_BINARY_DIR}/include
	)
endfunction()

foreach(GL_VERSION 4_3 4_2 4_1 4_0 3_3 3_2 3_1)
	gl_lib_ver_detection(GL ${GL_VERSION})
	if(${HAS_GL_${GL_VERSION}})
		string(REPLACE "_" ";" GL_VER_LIST ${GL_VERSION})
		list(GET GL_VER_LIST 0 OGLPLUS_GL_VERSION_MAJOR)
		list(GET GL_VER_LIST 1 OGLPLUS_GL_VERSION_MINOR)
		break()
	else()
		set(OGLPLUS_NO_GL_VERSION_${GL_VERSION} true)
	endif()
endforeach()

if(OGLPLUS_GL_VERSION_MAJOR AND OGLPLUS_GL_VERSION_MINOR)
	message(STATUS "Found GL version ${OGLPLUS_GL_VERSION_MAJOR}.${OGLPLUS_GL_VERSION_MINOR}")
else()
	message("Could not detect GL version, assuming 3.0")
	set(OGLPLUS_GL_VERSION_MAJOR 3)
	set(OGLPLUS_GL_VERSION_MINOR 0)
endif()
