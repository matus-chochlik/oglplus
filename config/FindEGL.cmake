#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
unset(EGL_INCLUDE_DIRS)
set(EGL_FOUND 0)
#
# try to find EGL/egl.h
find_path(
	EGL_EGL_H_DIR EGL/egl.h
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
# if that didn't work try the system directories
if((NOT EGL_EGL_H_DIR) OR (NOT EXISTS ${EGL_EGL_H_DIR}))
	find_path(EGL_EGL_H_DIR EGL/egl.h)
endif()
# if found append it to the include directories
if((EGL_EGL_H_DIR) AND (EXISTS ${EGL_EGL_H_DIR}))
	set(EGL_INCLUDE_DIRS ${EGL_INCLUDE_DIRS} ${EGL_EGL_H_DIR})
	set(EGL_EGL_H_FOUND 1)
endif()
#
# try to find the EGL library
find_library(
	EGL_LIBRARY NAMES EGL
	PATHS ${LIBRARY_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT EGL_LIBRARY)
	find_library(EGL_LIBRARY NAMES EGL)
endif()

set(EGL_LIBRARIES "")
if(EGL_LIBRARY AND EXISTS ${EGL_LIBRARY})
	set(EGL_LIBRARIES ${EGL_LIBRARIES} ${EGL_LIBRARY})
endif()

if(EGL_EGL_H_FOUND AND EGL_LIBRARY)
	if(${EGL_EGL_H_FOUND} AND EXISTS ${EGL_LIBRARY})
		set(EGL_FOUND 1)
	endif()
endif()
