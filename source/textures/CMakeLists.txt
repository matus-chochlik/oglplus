#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

# get a list of all svg textures
file(GLOB OGLPLUS_SVG_TEXTURES "./*.svg")

add_custom_target(oglplus_textures)

foreach(SVG_FILE ${OGLPLUS_SVG_TEXTURES})
	get_filename_component(TEXTURE_NAME ${SVG_FILE} NAME_WE)
	set(PNG_FILE ${TEXTURE_NAME}.png)

	set(PREBUILT_PNG ${PROJECT_SOURCE_DIR}/_prebuilt/textures/${PNG_FILE})

	if(EXISTS ${PREBUILT_PNG})
		add_custom_command(
			OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PNG_FILE}
			COMMAND ${CMAKE_COMMAND} copy
				"${PREBUILT_PNG}"
				"${CMAKE_CURRENT_BINARY_DIR}/${PNG_FILE}"
			COMMENT "Copying pre-built texture ${TEXTURE_NAME}"
		)
	else()
		find_program(INKSCAPE_EXECUTABLE inkscape)
		add_custom_command(
			OUTPUT ${PNG_FILE}
			COMMAND ${INKSCAPE_EXECUTABLE}
				--without-gui
				--file="${SVG_FILE}"
				--export-png="${PNG_FILE}"
			MAIN_DEPENDENCY ${SVG_FILE}
			COMMENT "Converting texture ${TEXTURE_NAME}"
		)

		add_custom_target(texture-${TEXTURE_NAME} DEPENDS ${PNG_FILE})
		add_dependencies(oglplus_textures texture-${TEXTURE_NAME})
	endif()
endforeach(SVG_FILE)
