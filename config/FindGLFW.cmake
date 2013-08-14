#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# try to find GL/glfw.h
find_path(
	GLFW_INCLUDE_DIRS GL/glfw.h
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT EXISTS ${GLFW_INCLUDE_DIRS})
	find_path(GLFW_INCLUDE_DIRS GL/glfw.h)
endif()

# try to find the GLFW library
find_library(
	GLFW_LIBRARIES NAMES glfw GLFW
	PATHS ${LIBRARY_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT GLFW_LIBRARIES)
	find_library(GLFW_LIBRARIES glfw GLFW)
endif()

if(EXISTS ${GLFW_INCLUDE_DIRS})
	set(GLFW_FOUND 1)
else()
	set(GLFW_FOUND 0)
endif()

