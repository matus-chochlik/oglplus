#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
include(FindGLUT)

set(GLUT_LIBRARIES ${GLUT_glut_LIBRARY})

if(
	"${GLUT_INCLUDE_DIR}" STREQUAL  "GLUT_INCLUDE_DIR-NOTFOUND" OR
	"${GLUT_glut_LIBRARY}" STREQUAL "GLUT_glut_LIBRARY-NOTFOUND"
)

	find_path(
		GLUT_INCLUDE_DIR NAMES GL/freeglut.h GL/glut.h
		PATHS ${HEADER_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)

	if(NOT EXISTS ${GLUT_INCLUDE_DIR})
		find_path(
			GLUT_INCLUDE_DIR NAMES GL/freeglut.h GL/glut.h
		)
	endif()

	# try to find the GLUT library
	find_library(
		GLUT_LIBRARIES NAMES glut freeglut freeglut_static
		PATHS ${LIBRARY_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)

	if("${GLUT_LIBRARIES}" STREQUAL "GLUT_LIBRARIES-NOTFOUND")
		find_library(GLUT_LIBRARIES NAMES glut freeglut freeglut_static)
	endif()

	if(NOT EXISTS ${GLUT_INCLUDE_DIR})
		set(GLUT_FOUND false)
		message(STATUS "GLUT header file not found")
	elseif(NOT EXISTS ${GLUT_LIBRARIES})
		set(GLUT_FOUND false)
		message(STATUS "GLUT library not found")
	else()
		set(GLUT_FOUND true)
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
