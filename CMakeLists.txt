#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.6)

project(OGLplus)

# TODO as command line option
set(HEADER_SEARCH_PATHS /opt/inst/include $ENV{HOME}/include)

# try to find GL3/gl3.h
find_path(GL3_GL3_H_DIR gl3.h PATH_SUFFIXES GL3 PATHS ${HEADER_SEARCH_PATHS})
# try to find GL/glew.h
find_path(GL_GLEW_H_DIR glew.h PATH_SUFFIXES GL PATHS ${HEADER_SEARCH_PATHS})

# no gl3.h nor glew.h => no OGLplus
if(GL_GLEW_H_DIR-NOTFOUND AND GL3_GL3_H_DIR-NOTFOUND)
	message("GL/glew.h or GL3/gl3.h required" FATAL_ERROR)
endif()

# if we have found GLEW
if(EXISTS ${GL_GLEW_H_DIR})
	# TODO set to 1 when a glew-based harness is ready
	set(OGLPLUS_USE_GLEW 0)
endif()
#if we have found gl3.h
if(EXISTS ${GL3_GL3_H_DIR})
	set(OGLPLUS_USE_GL3H 1)
endif()

# TODO update OGLPLUS_USE_* on caller preferences

if(OGLPLUS_USE_GLEW)
	set(OGLPLUS_USE_GL3H 0)

	include_directories(BEFORE SYSTEM ${GL_GLEW_H_DIR})
	find_package(OpenGL)
	set(OGLPLUS_GL_LIB GLEW)

	message("Using GLEW")
elseif(OGLPLUS_USE_GL3H)
	set(OGLPLUS_USE_GLEW 0)

	include_directories(BEFORE SYSTEM ${GL3_GL3_H_DIR})
	find_package(OpenGL)
	set(OGLPLUS_GL_LIB GL)

	message("Using GL3")
else()
	# something went very wrong
	message("Internal error" FATAL_ERROR)
endif()

# now create the site-configuration header
configure_file(
	${PROJECT_SOURCE_DIR}/config/oglplus/site_config.hpp.in
	${PROJECT_BINARY_DIR}/include/oglplus/site_config.hpp
)

add_custom_target(auto_generated_headers ALL)

add_subdirectory("doc/doxygen")
add_subdirectory("xslt" "include/oglplus")
add_subdirectory("source/textures" "textures")

# include the oglplus headers
include_directories(${PROJECT_SOURCE_DIR}/include)
# include the generated headers
include_directories(${PROJECT_BINARY_DIR}/include)

add_subdirectory("example/oglplus")
