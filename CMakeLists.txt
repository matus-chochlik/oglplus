#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

project(OGLplus)

option(OGLPLUS_WITHOUT_GLEW "Don't use GLEW even if available" Off)

option(OGLPLUS_NO_EXAMPLES "Don't build examples and textures" Off)
option(OGLPLUS_NO_SCREENSHOTS "Don't make example screenshots for the docs" Off)
option(OGLPLUS_NO_DOCS "Don't build and install the documentation" Off)

if(OGLPLUS_NO_EXAMPLES)
	set(OGLPLUS_NO_SCREENSHOTS On)
endif()

if(NOT OGLPLUS_NO_SCREENSHOTS)
	include(FindImageMagick)
endif()

include(config/FindOpenGL3.cmake)
include(config/FindGLEW.cmake)
include(config/FindGLUT.cmake)

#
#if we have found gl3.h
if(OPENGL3_FOUND)
	set(OGLPLUS_USE_GL3H 1)
else()
	set(OGLPLUS_USE_GL3H 0)
endif()
#
# if we have found GLEW
if(GLEW_FOUND)
	set(OGLPLUS_USE_GLEW 1)
else()
	set(OGLPLUS_USE_GLEW 0)
endif()

if(${OGLPLUS_USE_GLEW} AND NOT ${OGLPLUS_WITHOUT_GLEW})
	set(OGLPLUS_USE_GL3H 0)

	include_directories(BEFORE SYSTEM ${GLEW_INCLUDE_DIR})
	set(OGLPLUS_GL_LIB ${OPENGL3_LIBRARIES} ${GLEW_LIBRARIES})

	message("Using GLEW")

	if(NOT ${GLUT_FOUND})
		message(FATAL_ERROR "GLUT is also required")
		return()
	endif()
	include_directories(${GLUT_INCLUDE_DIR})
elseif(${OGLPLUS_USE_GL3H})
	set(OGLPLUS_USE_GLEW 0)

	include_directories(BEFORE SYSTEM ${OPENGL3_INCLUDE_DIR})
	set(OGLPLUS_GL_LIB ${OPENGL3_LIBRARIES})

	message("Using GL3")
else()
	message(FATAL_ERROR "GL3 or GLEW is required for OGLplus")
	return()
endif()

# now create the site-configuration header
configure_file(
	${PROJECT_SOURCE_DIR}/config/oglplus/site_config.hpp.in
	${PROJECT_BINARY_DIR}/include/oglplus/site_config.hpp
)

install(
	FILES ${PROJECT_BINARY_DIR}/include/oglplus/site_config.hpp
	DESTINATION include/oglplus
)

add_subdirectory("doc/doxygen")
add_subdirectory("xslt" "include/oglplus")
add_subdirectory("source/textures" "textures")

# include the oglplus headers
include_directories(${PROJECT_SOURCE_DIR}/include)
# include the generated headers
include_directories(${PROJECT_BINARY_DIR}/include)

include(config/CPP11.cmake)

add_subdirectory("example/oglplus")
add_subdirectory("example/standalone")

# install the "regular" headers
install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/include/
	DESTINATION include
)

if(NOT OGLPLUS_NO_DOCS)
	# install the docs
	install(
		DIRECTORY ${PROJECT_BINARY_DIR}/doc/doxygen/html
		DESTINATION share/oglplus/doc
	)
endif()
