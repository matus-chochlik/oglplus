#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

project(OGLplus)

option(OGLPLUS_FORCE_GL3_H "Force use of the GL3/gl3.h header" Off)
option(OGLPLUS_FORCE_GLCOREARB_H "Force use of the GL/glcorearb.h header" Off)
option(OGLPLUS_FORCE_GLEW "Force use of the GL/glew.h header" Off)
option(OGLPLUS_FORCE_GL3W "Force use of the GL/gl3w.h header" Off)

option(OGLPLUS_FORCE_WXGL "Force use of the wxGL library" Off)
option(OGLPLUS_FORCE_QTGL "Force use of the QtGL library" Off)
option(OGLPLUS_FORCE_GLUT "Force use of the GLUT library" Off)
option(OGLPLUS_FORCE_GLFW "Force use of the GLFW library" Off)
option(OGLPLUS_FORCE_SDL  "Force use of the SDL library" Off)
option(OGLPLUS_FORCE_GLX  "Force use of the GLX library" Off)

option(OGLPLUS_NO_EXAMPLES "Don't build examples and textures" Off)
option(OGLPLUS_NO_SCREENSHOTS "Don't make example screenshots for the docs" Off)
option(OGLPLUS_NO_DOCS "Don't build and install the documentation" Off)
option(OGLPLUS_NO_BINDINGS "Don't build python bindings" Off)

option(OGLPLUS_WITH_TESTS "Configure the testsuite" Off)

# The low-profile setting
option(OGLPLUS_CONFIG_SET_LOW_PROFILE "Set the OGLPLUS_LOW_PROFILE switch in site_config.hpp" Off)

if(OGLPLUS_CONFIG_SET_LOW_PROFILE)
	set(OGLPLUS_CONFIG_SET_LOW_PROFILE 1)
	if(${OGLPLUS_LOW_PROFILE})
		set(OGLPLUS_LOW_PROFILE 1)
	else()
		set(OGLPLUS_LOW_PROFILE 0)
	endif()
else()
	set(OGLPLUS_CONFIG_SET_LOW_PROFILE 0)
	set(OGLPLUS_LOW_PROFILE 0)
endif()

# the GL header and GL init lib
set(OGLPLUS_USE_GLCOREARB_H 0)
set(OGLPLUS_USE_GL3_H 0)
set(OGLPLUS_USE_GLEW 0)
set(OGLPLUS_USE_GLFW 0)
set(OGLPLUS_USE_GL3W 0)
set(OGLPLUS_USE_GLUT 0)
set(OGLPLUS_USE_QTGL 0)
set(OGLPLUS_USE_WXGL 0)
set(OGLPLUS_USE_GLX 0)
set(OGLPLUS_USE_SDL 0)

if(OGLPLUS_NO_EXAMPLES)
	set(OGLPLUS_NO_SCREENSHOTS On)
endif()

if(NOT OGLPLUS_NO_SCREENSHOTS)
	include(FindImageMagick)
endif()

include(config/FindOpenGL.cmake)
include(config/FindGLEW.cmake)
include(config/FindGL3W.cmake)
include(config/FindGLFW.cmake)
include(config/FindGLUT.cmake)
include(config/FindWXGL.cmake)
include(config/FindQTGL.cmake)
include(config/FindSDL.cmake)
include(config/FindGLX.cmake)

include(config/FindOpenAL.cmake)

include(config/FindEGL.cmake)

include(config/FindGLM.cmake)
include(config/FindPNG.cmake)
include(config/FindPangoCairo.cmake)

# enable warnings on gcc
if(${CMAKE_COMPILER_IS_GNUCXX})
	add_definitions(-pedantic -Wall -Wextra -Wshadow)
endif()
#
# we need one of the headers including the OpenGL C-API
#
# if GL/glcorearb.h was forced
if(${OGLPLUS_FORCE_GLCOREARB_H})
	if((OPENGL_FOUND) AND (EXISTS ${OPENGL_GLCOREARB_H_DIR}))
		set(OGLPLUS_USE_GLCOREARB_H 1)
	else()
		message(FATAL_ERROR "The GL/glcorearb.h header requested but not found!")
		return()
	endif()

# if GL3/gl3.h was forced
elseif(${OGLPLUS_FORCE_GL3_H})
	if((OPENGL_FOUND) AND (EXISTS ${OPENGL_GL3_H_DIR}))
		set(OGLPLUS_USE_GL3_H 1)
	else()
		message(FATAL_ERROR "The GL3/gl3.h header requested but not found!")
		return()
	endif()

# if GL/glew.h was forced
elseif(${OGLPLUS_FORCE_GLEW})
	if(GLEW_FOUND)
		set(OGLPLUS_USE_GLEW 1)
	else()
		message(FATAL_ERROR "The GLEW library requested but not found!")
		return()
	endif()

# if GL/gl3w.h was forced
elseif(${OGLPLUS_FORCE_GL3W})
	if(GL3W_FOUND)
		set(OGLPLUS_USE_GL3W 1)
	else()
		message(FATAL_ERROR "The GL3W library requested but not found!")
		return()
	endif()

# if the user didn't specify any preference
else()
	if((OPENGL_FOUND) AND (EXISTS ${OPENGL_GLCOREARB_H_DIR}))
		set(OGLPLUS_USE_GLCOREARB_H 1)
	elseif((OPENGL_FOUND) AND (EXISTS ${OPENGL_GL3_H_DIR}))
		set(OGLPLUS_USE_GL3_H 1)
	elseif(GLEW_FOUND)
		set(OGLPLUS_USE_GLEW 1)
	elseif(GL3W_FOUND)
		set(OGLPLUS_USE_GL3W 1)
	else()
		message(FATAL_ERROR "No OpenGL API library found!")
	endif()
endif()

#
# We'll also need a OpenGL context initialization/window-system library
#
# if GLUT was forced
if(${OGLPLUS_FORCE_GLUT})
	if(GLUT_FOUND)
		set(OGLPLUS_USE_GLUT 1)
	else()
		message(FATAL_ERROR "The GLUT library requested but not found!")
		return()
	endif()

# if QtGL was forced
elseif(${OGLPLUS_FORCE_QTGL})
	if(QT_FOUND)
		set(OGLPLUS_USE_QTGL 1)
	else()
		message(FATAL_ERROR "The QtGL library requested but not found!")
		return()
	endif()

# if wxGL was forced
elseif(${OGLPLUS_FORCE_WXGL})
	if(wxWidgets_FOUND)
		set(OGLPLUS_USE_WXGL 1)
	else()
		message(FATAL_ERROR "The wxGL library requested but not found!")
		return()
	endif()

# if GLFW was forced
elseif(${OGLPLUS_FORCE_GLFW})
	if(GLFW_FOUND)
		set(OGLPLUS_USE_GLFW 1)
	else()
		message(FATAL_ERROR "The GLFW library requested but not found!")
		return()
	endif()

# if SDL was forced
elseif(${OGLPLUS_FORCE_SDL})
	if(SDL_FOUND)
		set(OGLPLUS_USE_SDL 1)
	else()
		message(FATAL_ERROR "The SDL library requested but not found!")
		return()
	endif()

# if glX was forced
elseif(${OGLPLUS_FORCE_GLX})
	if(X11_FOUND)
		set(OGLPLUS_USE_GLX 1)
	else()
		message(FATAL_ERROR "The X11/GLX library requested but not found!")
		return()
	endif()

# if the user didn't specify any preference
else()
	if(GLUT_FOUND)
		set(OGLPLUS_USE_GLUT 1)
	elseif(GLFW_FOUND)
		set(OGLPLUS_USE_GLFW 1)
	elseif(QT_FOUND)
		set(OGLPLUS_USE_QTGL 1)
	elseif(wxWidgets_FOUND)
		set(OGLPLUS_USE_WXGL 1)
	elseif(SDL_FOUND)
		set(OGLPLUS_USE_SDL 1)
	elseif(X11_FOUND)
		set(OGLPLUS_USE_GLX 1)
	else()
		message(FATAL_ERROR "No OpenGL context initialization library found!")
	endif()
endif()



unset(OGLPLUS_GL_INCLUDE_DIRS)

if((${OGLPLUS_USE_GLCOREARB_H}) OR (${OGLPLUS_USE_GL3_H}))

	set(OGLPLUS_GL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIRS})
	include_directories(BEFORE SYSTEM ${OPENGL_INCLUDE_DIRS})
	set(OGLPLUS_GL_LIBS ${OPENGL_LIBRARIES})

	message(STATUS "Using native OpenGL")
elseif(${OGLPLUS_USE_GLEW})

	set(OGLPLUS_GL_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
	include_directories(BEFORE SYSTEM ${GLEW_INCLUDE_DIRS})
	set(OGLPLUS_GL_LIBS ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

	message(STATUS "Using GLEW")
else()
	message(FATAL_ERROR "A library including OpenGL symbols is required for OGLplus")
	return()
endif()

# check if Boost.Config is available
include(config/FindBoost.cmake)
if(${BoostConfig_FOUND})
	include_directories(BEFORE SYSTEM BoostConfig_INCLUDE_DIRS)
endif()

# c++11-related compiler flags
include(config/CPP11.cmake)

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
add_subdirectory("source/textures" "textures")
add_subdirectory("source/models" "models")

# include the oglplus headers
include_directories(${PROJECT_SOURCE_DIR}/include)
# include the generated headers
include_directories(${PROJECT_BINARY_DIR}/include)
# include the third party headers
include_directories(${PROJECT_SOURCE_DIR}/third_party/include)

# GL version detection
include(config/GLVer.cmake)
# GL extension detection
include(config/GLExt.cmake)

if(NOT OGLPLUS_NO_EXAMPLES)
	# add this to enable M_PI on some platforms
	add_definitions(-D_USE_MATH_DEFINES)
	add_subdirectory("example")
endif()

# bindings
if(NOT OGLPLUS_NO_BINDINGS)
	add_subdirectory("source/bindings" "bindings")
endif()

# install the "regular" headers
install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/include/
	DESTINATION include
)

if(OGLPLUS_WITH_TESTS)
	add_subdirectory("test")
endif()

if(NOT OGLPLUS_NO_DOCS)
	# install the docs
	install(
		DIRECTORY ${PROJECT_BINARY_DIR}/doc/doxygen/html
		DESTINATION share/oglplus/doc
	)
endif()
