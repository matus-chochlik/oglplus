#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
include(FindGLUT)

set(GLUT_LIBRARIES ${GLUT_glut_LIBRARY})

if("${GLUT_glut_LIBRARY}" STREQUAL "GLUT_glut_LIBRARY-NOTFOUND")

	find_path(
		GLUT_INCLUDE_DIR freeglut.h
		PATH_SUFFIXES GL
		PATHS ${HEADER_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)

	# try to find the GLUT library
	find_library(
		GLUT_LIBRARIES NAMES glut freeglut freeglut_static
		PATHS ${LIBRARY_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)

	if(EXISTS ${GLUT_INCLUDE_DIR})
		set(GLUT_FOUND true)
	else()
		set(GLUT_FOUND false)
		message("GLUT library not found")
	endif()
else()
	if("${GLUT_Xi_LIBRARY}" STREQUAL "GLUT_Xi_LIBRARY-NOTFOUND")
		unset(GLUT_Xi_LIBRARY)
	else()
		set(GLUT_LIBRARIES ${GLUT_LIBRARIES} ${GLUT_Xi_LIBRARY})
	endif()

	if("${GLUT_Xmu_LIBRARY}" STREQUAL "GLUT_Xmu_LIBRARY-NOTFOUND")
		unset(GLUT_Xmu_LIBRARY)
	else()
		set(GLUT_LIBRARIES ${GLUT_LIBRARIES} ${GLUT_Xmu_LIBRARY})
	endif()
endif()

