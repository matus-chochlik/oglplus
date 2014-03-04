#  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

if((GLX_FOUND) OR (GLFW_FOUND))
	add_custom_target(oglplus-advanced-example-cloud_trace)
	set_property(
		TARGET oglplus-advanced-example-cloud_trace
		PROPERTY FOLDER "Example/Advanced/cloud_trace"
	)
	add_resource_directory(glsl oglplus-advanced-example-cloud_trace)

	include_directories(${PROJECT_SOURCE_DIR}/utils)

	if("${OGLPLUS_GL_INIT_LIB}" STREQUAL "GLX")
		set(CLOUD_TRACE_GL_INIT GLX)
	elseif("${OGLPLUS_GL_INIT_LIB}" STREQUAL "GLFW")
		set(CLOUD_TRACE_GL_INIT GLFW)
	else()
		if(GLX_FOUND)
			set(CLOUD_TRACE_GL_INIT GLX)
		elseif(GLFW_FOUND)
			set(CLOUD_TRACE_GL_INIT GLFW)
		endif()
	endif()

	set(CLOUD_TRACE_GL_INIT GLFW) # TODO

	do_use_single_dependency(${CLOUD_TRACE_GL_INIT})

	add_executable(
		cloud_trace	
		EXCLUDE_FROM_ALL
			main_${CLOUD_TRACE_GL_INIT}.cpp
			main_common.cpp
			app_data.cpp
			cloud_data.cpp
			resources.cpp
			textures.cpp
			programs.cpp
			raytracer.cpp
			renderer.cpp
			saver.cpp
			threads.cpp
	)
	if("${CLOUD_TRACE_GL_INIT}" STREQUAL "GLX")
		target_link_libraries(cloud_trace pthread)
	endif()

	if(${WIN32})
		set_property(TARGET cloud_trace PROPERTY WIN32_EXECUTABLE true)
	endif()
	set_property(
		TARGET cloud_trace
		PROPERTY FOLDER "Example/Advanced/cloud_trace"
	)

	target_link_libraries(cloud_trace ${${CLOUD_TRACE_GL_INIT}_LIBRARIES})
	target_link_libraries(cloud_trace ${OGLPLUS_GL_LIBS})
	add_dependencies(oglplus-advanced-example-cloud_trace cloud_trace)
	add_dependencies(oglplus-advanced-examples oglplus-advanced-example-cloud_trace)
endif()
