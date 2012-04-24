#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# try to find GL3/gl3.h
find_path(
	OPENGL3_INCLUDE_DIR GL3/gl3.h
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
#
# if that didn't work try the system directories
if(NOT EXISTS ${OPENGL3_INCLUDE_DIR})
	find_path(OPENGL3_INCLUDE_DIR GL3/gl3.h)
endif()

# try to find the GL library
find_library(
	OPENGL3_LIBRARIES NAMES GL OpenGL32
	PATHS ${LIBRARY_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if("${OPENGL3_LIBRARIES}" STREQUAL "OPENGL3_LIBRARIES-NOTFOUND")
	find_library(OPENGL3_LIBRARIES NAMES GL OpenGL32)
endif()

#if we have found gl3.h
if(EXISTS ${OPENGL3_INCLUDE_DIR})
	set(OPENGL3_FOUND true)
else()
	set(OPENGL3_FOUND false)
endif()
