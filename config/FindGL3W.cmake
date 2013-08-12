#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# try to find GL/gl3w.h
find_path(
	GL3W_INCLUDE_DIRS GL/gl3w.h
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT EXISTS ${GL3W_INCLUDE_DIRS})
	find_path(GL3W_INCLUDE_DIRS GL/gl3w.h)
endif()

# try to find the GL3W library
find_library(
	GL3W_LIBRARIES NAMES GL3W gl3w32
	PATHS ${LIBRARY_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT GL3W_LIBRARIES)
	find_library(GL3W_LIBRARIES GL3W gl3w32)
endif()

if(EXISTS ${GL3W_INCLUDE_DIRS})
	set(GL3W_FOUND 1)
else()
	set(GL3W_FOUND 0)
endif()

