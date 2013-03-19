#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# try to find GL/glew.h
find_path(
	GLEW_INCLUDE_DIRS GL/glew.h
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT EXISTS ${GLEW_INCLUDE_DIRS})
	find_path(GLEW_INCLUDE_DIRS GL/glew.h)
endif()

# try to find the GLEW library
find_library(
	GLEW_LIBRARIES NAMES GLEW glew32
	PATHS ${LIBRARY_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT GLEW_LIBRARIES)
	find_library(GLEW_LIBRARIES GLEW glew32)
endif()

if(EXISTS ${GLEW_INCLUDE_DIRS})
	set(GLEW_FOUND true)
else()
	set(GLEW_FOUND false)
endif()

