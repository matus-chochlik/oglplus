#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
macro(gles3_detection VER_MINOR)
	unset(OPENGLES3${VER_MINOR}_INCLUDE_DIRS)
	set(OPENGLES3${VER_MINOR}_FOUND 0)
	#
	# try to find GLES3/gl3${VER_MINOR}.h
	find_path(
		OPENGLES3_GL3${VER_MINOR}_H_DIR GLES3/gl3${VER_MINOR}.h
		PATHS ${HEADER_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)
	# if that didn't work try the system directories
	if(
		(NOT OPENGLES3_GL3${VER_MINOR}_H_DIR) OR
		(NOT EXISTS ${OPENGLES3_GL3${VER_MINOR}_H_DIR})
	)
		find_path(
			OPENGLES3_GL3${VER_MINOR}_H_DIR
			NAMES GLES3/gl3${VER_MINOR}.h
		)
	endif()
	# if found append it to the include directories
	if(
		(OPENGLES3_GL3${VER_MINOR}_H_DIR) AND
		(EXISTS ${OPENGLES3_GL3${VER_MINOR}_H_DIR})
	)
		set(
			OPENGLES3${VER_MINOR}_INCLUDE_DIRS
			${OPENGLES3${VER_MINOR}_INCLUDE_DIRS}
			${OPENGLES3_GL3${VER_MINOR}_H_DIR}
		)
		set(OPENGLES3${VER_MINOR}_FOUND 1)
	endif()
	#
	# try to find the GLES3 library
	find_library(
		OPENGLES3${VER_MINOR}_LIBRARIES
		NAMES GLESv3${VER_MINOR} GLESv3 GLES3${VER_MINOR} GLES3 GL
		PATHS ${LIBRARY_SEARCH_PATHS}
		NO_DEFAULT_PATH
	)
	if(NOT OPENGLES3${VER_MINOR}_LIBRARIES)
		find_library(
			OPENGLES3${VER_MINOR}_LIBRARIES
			NAMES GLESv3${VER_MINOR} GLESv3 GLES3${VER_MINOR} GLES3 GL
		)
	else()
		get_filename_component(
			OPENGLES3${VER_MINOR}_LIBRARY_DIRS
			{OPENGLES3${VER_MINOR}_LIBRARIES} PATH
		)
	endif()

	#if we have not found the library
	if(NOT OPENGLES3${VER_MINOR}_LIBRARIES)
		set(OPENGLES3${VER_MINOR}_LIBRARIES "")
	endif()

	if(OPENGLES3${VER_MINOR}_FOUND AND ${OPENGLES3${VER_MINOR}_FOUND})
		message(STATUS "Found GLES3${VER_MINOR}: ${OPENGLES3${VER_MINOR}_INCLUDE_DIRS};${OPENGLES3${VER_MINOR}_LIBRARIES}")
		set(GLES3_GL3${VER_MINOR}_H_FOUND 1)
	else()
		set(GLES3_GL3${VER_MINOR}_H_FOUND 0)
	endif()
endmacro()

gles3_detection("")
gles3_detection("1")
gles3_detection("2")
