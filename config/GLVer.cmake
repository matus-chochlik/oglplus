#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

function(gl_lib_ver_detection GL_LIB VERSION)

	if(NOT DEFINED OGLPLUS_CONFIG_STRICT_VERSION_CHECK)
		set(OGLPLUS_CONFIG_STRICT_VERSION_CHECK 1)
	endif()

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
		string(REPLACE "_" ";" GL_VER_LIST ${VERSION})
		list(GET GL_VER_LIST 0 OGLPLUS_CONFIG_QUERY_GL_VER_MAJOR)
		list(GET GL_VER_LIST 1 OGLPLUS_CONFIG_QUERY_GL_VER_MINOR)

		configure_file(
			${PROJECT_SOURCE_DIR}/config/gl_ver/has_${GL_LIB}_VER.cpp.in
			${PROJECT_BINARY_DIR}/gl_ver/has_${GL_LIB}_${VERSION}.cpp
		)
		unset(OGLPLUS_CONFIG_QUERY_GL_VER)
		unset(OGLPLUS_CONFIG_QUERY_GL_VER_MAJOR)
		unset(OGLPLUS_CONFIG_QUERY_GL_VER_MINOR)
	endif()

	set(OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS
		"${OGLPLUS_GL_INCLUDE_DIRS};"
		"${PROJECT_SOURCE_DIR}/include;"
		"${PROJECT_SOURCE_DIR}/implement;"
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
		RUNS_WITH_${GL_LIB}_${VERSION} COMPILED_WITH_${GL_LIB}_${VERSION}
		"${PROJECT_BINARY_DIR}/gl_ver"
		"${PROJECT_BINARY_DIR}/gl_ver/has_${GL_LIB}_${VERSION}.cpp"
		COMPILE_DEFINITIONS ${OGLPLUS_CPP11_COMPILER_SWITCH}
		CMAKE_FLAGS
			"-DINCLUDE_DIRECTORIES:STRING=${OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS} "
			"-DLINK_LIBRARIES:STRING=${OGLPLUS_CONFIG_REQUIRED_LIBRARIES} "
	)
	if(COMPILED_WITH_${GL_LIB}_${VERSION})
		if(RUNS_WITH_${GL_LIB}_${VERSION} EQUAL 0)
			set(HAS_${GL_LIB}_${VERSION} TRUE PARENT_SCOPE)
		endif()
	endif()
	unset(RUNS_WITH_${GL_LIB}_${VERSION})
	unset(COMPILED_WITH_${GL_LIB}_${VERSION})
endfunction()

if(NOT(OGLPLUS_MAX_GL_VERSION))
	set(OGLPLUS_MAX_GL_VERSION 9_9)
endif()

foreach(GL_VERSION 4_4 4_3 4_2 4_1 4_0 3_3 3_2 3_1)
	if(NOT("${GL_VERSION}" STRGREATER "${OGLPLUS_MAX_GL_VERSION}"))
		gl_lib_ver_detection(GL ${GL_VERSION})
		if(${HAS_GL_${GL_VERSION}})
			string(REPLACE "_" ";" GL_VER_LIST ${GL_VERSION})
			list(GET GL_VER_LIST 0 OGLPLUS_GL_VERSION_MAJOR)
			list(GET GL_VER_LIST 1 OGLPLUS_GL_VERSION_MINOR)
			break()
		endif()
	endif()
	set(OGLPLUS_NO_GL_VERSION_${GL_VERSION} true)
endforeach()


if(OGLPLUS_GL_VERSION_MAJOR)
	message(STATUS "Found GL version ${OGLPLUS_GL_VERSION_MAJOR}.${OGLPLUS_GL_VERSION_MINOR}")
else()
	message("Could not detect GL version, assuming 3.0")
	set(OGLPLUS_GL_VERSION_MAJOR 3)
	set(OGLPLUS_GL_VERSION_MINOR 0)
endif()
