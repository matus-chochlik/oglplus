#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

# get a list of all svg textures
file(GLOB OGLPLUS_SVG_TEXTURES "./*.svg")

unset(PNG_TEXTURE_FILES)
foreach(SVG_FILE ${OGLPLUS_SVG_TEXTURES})
	get_filename_component(TEXTURE_NAME ${SVG_FILE} NAME_WE)
	set(PNG_FILE ${TEXTURE_NAME}.png)

	set(PREBUILT_PNG ${PROJECT_SOURCE_DIR}/prebuilt/textures/${PNG_FILE})

	if(EXISTS ${PREBUILT_PNG})
		configure_file(
			${PREBUILT_PNG}
			${CMAKE_CURRENT_BINARY_DIR}/${PNG_FILE}
			COPYONLY
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
		)
		set(
			PNG_TEXTURE_FILES
			${PNG_TEXTURE_FILES}
			${CMAKE_CURRENT_BINARY_DIR}/${PNG_FILE}
		)
	endif()
endforeach(SVG_FILE)

add_custom_target(oglplus_textures ALL DEPENDS ${PNG_TEXTURE_FILES})

unset(PNG_TEXTURE_FILES)

