#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

configure_file(
	${PROJECT_SOURCE_DIR}/config/oglplus/can_build_lib.cpp.in
	${PROJECT_BINARY_DIR}/config/can_build_lib.cpp
)

set(OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS
	"${OGLPLUS_GL_INCLUDE_DIRS};"
	"${PROJECT_SOURCE_DIR}/include;"
	"${PROJECT_SOURCE_DIR}/implement;"
	"${PROJECT_SOURCE_DIR}/third_party/include;"
	"${PROJECT_BINARY_DIR}/include"
)

set(OGLPLUS_CONFIG_REQUIRED_LIBRARIES
	"${OGLPLUS_GL_LIBS}"
)
if(PNG_FOUND)
	set(OGLPLUS_CONFIG_REQUIRED_LIBRARIES
		"${OGLPLUS_CONFIG_REQUIRED_LIBRARIES}"
		"${PNG_LIBRARIES}"
	)
endif()

try_run(
	RUNS_WITH_OGLPLUS_LIB COMPILED_WITH_OGLPLUS_LIB
	"${PROJECT_BINARY_DIR}/config"
	"${PROJECT_BINARY_DIR}/config/can_build_lib.cpp"
	COMPILE_DEFINITIONS ${OGLPLUS_CPP11_COMPILER_SWITCH}
	CMAKE_FLAGS
		"-DINCLUDE_DIRECTORIES:STRING=${OGLPLUS_CONFIG_REQUIRED_INCLUDE_DIRS} "
		"-DLINK_LIBRARIES:STRING=${OGLPLUS_CONFIG_REQUIRED_LIBRARIES} "
)

if((COMPILED_WITH_OGLPLUS_LIB) AND (RUNS_WITH_OGLPLUS_LIB EQUAL 0))
	set(OGLPLUS_LINK_LIBRARY 1)
	message(STATUS "OGLplus library can be built")
else()
	set(OGLPLUS_LINK_LIBRARY 0)
	message(WARNING "OGLplus library cannot be built!")
endif()
unset(RUNS_WITH_OGLPLUS_LIB)
unset(COMPILED_WITH_OGLPLUS_LIB)
