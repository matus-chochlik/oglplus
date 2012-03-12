#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
include(FindGLUT)

set(GLUT_LIBRARIES ${GLUT_glut_LIBRARY})

if("${GLUT_glut_LIBRARY}" STREQUAL "GLUT_glut_LIBRARY-NOTFOUND")
	message("GLUT library not found")
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

