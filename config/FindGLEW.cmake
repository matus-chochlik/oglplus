#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# try to find GL/glew.h
find_path(
	GLEW_INCLUDE_DIR glew.h
	PATH_SUFFIXES GL
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT EXISTS ${GLEW_INCLUDE_DIR})
	find_path(GLEW_INCLUDE_DIR glew.h PATH_SUFFIXES GL)
endif()

# try to find the GLEW library
find_library(
	GLEW_LIBRARIES NAMES GLEW glew32
	PATHS ${LIBRARY_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if("${GLEW_LIBRARIES}" STREQUAL "GLEW_LIBRARIES-NOTFOUND")
	find_library(GLEW_LIBRARIES GLEW)
endif()

if(EXISTS ${GLEW_INCLUDE_DIR})
	set(GLEW_FOUND true)
else()
	set(GLEW_FOUND false)
endif()

