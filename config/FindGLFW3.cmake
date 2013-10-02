#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
if(PKG_CONFIG_FOUND)
	pkg_check_modules(GLFW3 glfw3)
	find_library(
		TMP_FULL_LIB_PATH NAMES ${GLFW3_LIBRARIES}
		PATHS ${GLFW3_LIBRARY_DIRS}
		NO_DEFAULT_PATH
	)
	if("${TMP_FULL_LIB_PATH}" MATCHES "${CMAKE_STATIC_LIBRARY_SUFFIX}$")
		set(GLFW3_LIBRARIES "${GLFW3_STATIC_LIBRARIES}")
	else()
	endif()
endif()

# try to find GL/glfw3.h
if(NOT EXISTS ${GLFW3_INCLUDE_DIRS})
	find_path(
		GLFW3_INCLUDE_DIRS GLFW/glfw3.h
		PATHS ${HEADER_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)
endif()
if(NOT EXISTS ${GLFW3_INCLUDE_DIRS})
	find_path(GLFW3_INCLUDE_DIRS GLFW/glfw3.h)
endif()

# try to find the GLFW3 library
if(NOT GLFW3_LIBRARIES)
	find_library(
		GLFW3_LIBRARIES NAMES glfw3 GLFW3
		PATHS ${LIBRARY_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)
endif()
if(NOT GLFW3_LIBRARIES)
	find_library(GLFW3_LIBRARIES glfw3 GLFW3)
endif()

if(EXISTS ${GLFW3_INCLUDE_DIRS})
	set(GLFW3_FOUND 1)
else()
	set(GLFW3_FOUND 0)
endif()
