#  Copyright 2014 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(EGLplus_EGL)

find_package(X11 REQUIRED)

#add_definitions(-std=c++0x)
add_definitions(-std=c++0x -g3)

include_directories(${X11_INCLUDE_DIRS})
include_directories(include)

add_library(EGL SHARED
	src/EGL/error.cpp
	src/EGL/api.cpp
	src/EGL/glx/display.cpp
	src/EGL/glx/configs.cpp
	src/EGL/glx/surface.cpp
	src/EGL/glx/context.cpp
	src/EGL/glx/threads.cpp
	src/EGL/glx/extensions.cpp
)
target_link_libraries(EGL ${X11_LIBRARIES})

install(TARGETS EGL LIBRARY DESTINATION lib)
install(DIRECTORY include/EGL DESTINATION include)
