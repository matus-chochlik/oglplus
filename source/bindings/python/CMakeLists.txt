#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

macro(add_python_module MODULE BASE_LIB)

	if(${BASE_LIB}_FOUND)
		if(${BASE_LIB}_USE_FILE)
			include(${${BASE_LIB}_INCLUDE_DIRS})
		endif()
		include_directories(${BASE_LIB}_INCLUDE_DIRS)

		file(
			GLOB MODULE_SOURCES
			"${MODULE}/*.cpp"
			"${MODULE}/enums/*.cpp"
		)

		set(MODULE_INT ${MODULE}_pymod)

		add_definitions("-DEGLPLUS_LINK_LIB=1")

		add_library(
			${MODULE_INT} SHARED
			${MODULE}.cpp
			${MODULE_SOURCES}
		)
		target_link_libraries(${MODULE}_pymod ${Boost_LIBRARIES})
		target_link_libraries(${MODULE}_pymod ${${BASE_LIB}_LIBRARIES})

		get_property(
			${MODULE}_lib_path
			TARGET ${MODULE_INT}
			PROPERTY LOCATION_${CMAKE_BUILD_TYPE}
		)
		set(MODULE_OUT ${MODULE}${CMAKE_SHARED_LIBRARY_SUFFIX})

		add_custom_command(
			OUTPUT ${MODULE_OUT}
			COMMAND ${CMAKE_COMMAND} -E copy ${${MODULE}_lib_path} ${MODULE_OUT}
			DEPENDS ${MODULE_INT}
		)
		add_custom_target(python-${MODULE} ALL DEPENDS ${MODULE_OUT})
	endif()

endmacro(add_python_module)

find_package(Boost)
IF(Boost_FOUND)

	set(Boost_USE_STATIC_LIBS OFF)
	set(Boost_USE_MULTITHREADED ON)
	set(Boost_USE_STATIC_RUNTIME OFF)
	find_package(Boost COMPONENTS python)
	include_directories(${Boost_INCLUDE_DIRS})

	find_package(PythonLibs)
	include_directories(${PYTHON_INCLUDE_DIRS})

	add_python_module(oglplus OPENGL)
	add_python_module(oalplus OPENAL)
	add_python_module(eglplus EGL)

else()
	message(WARNING "Unable to find Boost Python. Python bindings will not be built.")
endif()
