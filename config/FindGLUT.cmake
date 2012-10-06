#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
include(FindGLUT)

if(GLUT_INCLUDE_DIR)
	set(GLUT_INCLUDE_DIRS ${GLUT_INCLUDE_DIR})
endif()

if((NOT GLUT_INCLUDE_DIRS) OR (NOT GLUT_LIBRARIES))

	find_path(
		GLUT_INCLUDE_DIRS NAMES GL/freeglut.h GL/glut.h
		PATHS ${HEADER_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)

	if(NOT EXISTS ${GLUT_INCLUDE_DIRS})
		find_path(GLUT_INCLUDE_DIRS NAMES GL/freeglut.h GL/glut.h)
	endif()

	# try to find the GLUT library
	find_library(
		GLUT_LIBRARIES NAMES glut freeglut freeglut_static
		PATHS ${LIBRARY_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)

	if(NOT GLUT_LIBRARIES)
		find_library(GLUT_LIBRARIES NAMES glut freeglut freeglut_static)
	endif()

	if((NOT GLUT_INCLUDE_DIRS) OR (NOT EXISTS ${GLUT_INCLUDE_DIRS}))
		set(GLUT_FOUND false)
		message(STATUS "GLUT header file not found")
	elseif((NOT GLUT_LIBRARIES) OR (NOT EXISTS ${GLUT_LIBRARIES}))
		set(GLUT_FOUND false)
		message(STATUS "GLUT library not found")
	else()
		set(GLUT_FOUND true)
	endif()
endif()

if(GLUT_LIBRARIES)

	set(TMP_GLUT_LIBRARIES ${GLUT_LIBRARIES})
	set(GLUT_LIBRARIES "")
	foreach(LIB ${TMP_GLUT_LIBRARIES})
		if(EXISTS ${LIB})
			list(APPEND GLUT_LIBRARIES ${LIB})
		endif()
	endforeach()

	if(NOT GLUT_LIBRARIES)
		message(WARNING "GLUT library detection error")
		set(GLUT_FOUND false)
	endif()

	unset(TMP_GLUT_LIBRARIES)
endif()
