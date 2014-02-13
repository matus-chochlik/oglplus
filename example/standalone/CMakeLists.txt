#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

#TODO
if(NOT(${CMAKE_COMPILER_IS_GNUCXX}))
	return()
endif()

add_custom_target(standalone-examples ALL)
set_property(TARGET standalone-examples PROPERTY FOLDER "Example/Standalone")

function(standalone_example_common EXAMPLE_NAME)
	add_executable(
		${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		${EXAMPLE_NAME}.cpp
	)
	add_dependencies(standalone-examples ${EXAMPLE_NAME})
	target_link_libraries(${EXAMPLE_NAME} ${OPENGL_LIBRARIES} ${ARGN})
	set_property(TARGET ${EXAMPLE_NAME} PROPERTY FOLDER "Example/Standalone")
endfunction()

if(EGL_FOUND AND OPENGL_FOUND)
	include_directories(${EGL_INCLUDE_DIRS})
	include_directories(${OPENGL_INCLUDE_DIRS})

	standalone_example_common(
		001_triangle_screenshot
		${EGL_LIBRARIES} ${OGLPLUS_GL_LIBS}
	)
endif()

standalone_example_common(001_text2d)

if(GLUT_FOUND AND GLES3_FOUND)
	include_directories(${GLES3_INCLUDE_DIRS})
	include_directories(${GLUT_INCLUDE_DIRS})

	standalone_example_common(
		001_triangle_glut_gles3
		${GLUT_LIBRARIES} ${GLES3_LIBRARIES}
	)
endif()

if(GLUT_FOUND AND GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	include_directories(${GLUT_INCLUDE_DIRS})

	standalone_example_common(
		001_gl_info
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	standalone_example_common(
		001_gl_limits
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	standalone_example_common(
		001_triangle_glut_glew
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	standalone_example_common(
		001_shape2dot
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	standalone_example_common(
		002_rectangle_glut_glew
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)

	if(HAS_GL_VERSION_4_3)
		standalone_example_common(
			001_program_resources
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()

	if(HAS_GLEW_ATI_meminfo)
		standalone_example_common(
			001_ati_meminfo
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()

	if(HAS_GLEW_AMD_performance_monitor)
		standalone_example_common(
			002_amd_perf_monitor
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()

	if(HAS_GLEW_ARB_compatibility AND HAS_GLEW_ARB_debug_output)
		standalone_example_common(
			002_triangle_compatibility
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()

	if(HAS_GLEW_EXT_direct_state_access)
		standalone_example_common(
			002_dsa_buffer
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)

		standalone_example_common(
			003_dsa_texture
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()

	if(HAS_GLEW_ARB_compatibility AND HAS_GLEW_NV_path_rendering)
		standalone_example_common(
			002_simple_path
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)

		if(HAS_GLEW_EXT_direct_state_access)
			standalone_example_common(
				003_simple_text
				${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
			)

			standalone_example_common(
				004_text_rendering
				${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
			)
		endif()
	endif()

	if(PNG_FOUND)
		include_directories(${PNG_INCLUDE_DIRS})
		standalone_example_common(
			004_bitmap_text_hello
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${PNG_LIBRARIES}
		)
		include_directories(${PNG_INCLUDE_DIRS})
		standalone_example_common(
			004_bitmap_text_rendering
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${PNG_LIBRARIES}
		)

		include_directories(${PNG_INCLUDE_DIRS})
		standalone_example_common(
			004_any_text_rendering
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${PNG_LIBRARIES}
		)

		include_directories(${PNG_INCLUDE_DIRS})
		standalone_example_common(
			004_stbttf_text_rendering
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${PNG_LIBRARIES}
		)
	endif()

	if(PANGO_CAIRO_FOUND)
		include_directories(${PANGO_CAIRO_INCLUDE_DIRS})
		add_definitions(${PANGO_CAIRO_CFLAGS_OTHER})
		add_definitions(${PANGO_CAIRO_LDFLAGS})
		standalone_example_common(
			004_pango_cairo_hello
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${PANGO_CAIRO_LIBRARIES}
		)
	endif()

	if(GLM_FOUND)
		include_directories(${GLM_INCLUDE_DIRS})
		standalone_example_common(
			007_glm_boxes
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
		)
	endif()

	standalone_example_common(010_blender2html)

	if(OPENAL_FOUND)
		include_directories(${OPENAL_INCLUDE_DIRS})
		standalone_example_common(
			020_oglplus_oalplus
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${OPENAL_LIBRARIES}
		)
	endif()

	if(PNG_FOUND)
		include_directories(${PNG_INCLUDE_DIRS})
		standalone_example_common(
			025_bitmap_font_text
			${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${PNG_LIBRARIES}
		)
	endif()

	standalone_example_common(
		026_blender_mesh_loader
		${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
	)
endif()

if(GLFW3_FOUND)
	include_directories(${GLFW3_INCLUDE_DIRS})
	standalone_example_common(
		029_mandelbrot_glfw3
		${GLFW3_LIBRARIES} ${OGLPLUS_GL_LIBS}
	)
endif()

