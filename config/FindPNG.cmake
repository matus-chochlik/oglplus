#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# try to find png.h and related lib
find_path(
	PNG_INCLUDE_DIRS png.h
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT EXISTS ${PNG_INCLUDE_DIRS})
	find_path(PNG_INCLUDE_DIRS png.h)
endif()

# try to find the PNG library
find_library(
	PNG_LIBRARIES NAMES png
	PATHS ${LIBRARY_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT PNG_LIBRARIES)
	find_library(PNG_LIBRARIES NAMES png)
endif()

if(EXISTS ${PNG_INCLUDE_DIRS})
	set(PNG_FOUND true)
else()
	set(PNG_FOUND false)
endif()

