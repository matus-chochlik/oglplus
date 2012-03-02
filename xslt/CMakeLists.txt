#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

set(OGLPLUS_BINDABLE_OBJECTS buffer texture renderbuffer framebuffer)

set(OGLPLUS_SRC_XML ${PROJECT_BINARY_DIR}/doc/doxygen/xml/oglplus.xml)
set(BOUND_HEADER_XSLT ${PROJECT_SOURCE_DIR}/xslt/bound_hpp.xsl)

add_custom_target(auto_generated_headers ALL)

add_custom_target(bound_object_headers)
add_dependencies(auto_generated_headers bound_object_headers)

find_program(XSLTPROC_EXECUTABLE xsltproc)

foreach(BINDABLE ${OGLPLUS_BINDABLE_OBJECTS})

	set(PREBUILT_HEADER ${PROJECT_SOURCE_DIR}/prebuilt/include/oglplus/bound/${BINDABLE}.hpp)
	set(HEADER_FILE ${CMAKE_CURRENT_BINARY_DIR}/bound/${BINDABLE}.hpp)

	# if this header is pre-built
	if(EXISTS ${PREBUILT_HEADER})
		# just copy it
		configure_file(${PREBUILT_HEADER} ${HEADER_FILE} COPYONLY)
	else()
		# otherwise do the whole Doxygen->XSLT->hpp dance

		# TODO make this portable/usable with other XSLT processors

		add_custom_command(
			OUTPUT ${HEADER_FILE}
			COMMAND ${XSLTPROC_EXECUTABLE}
				--output bound/${BINDABLE}.hpp
				--stringparam object ${BINDABLE}
				${BOUND_HEADER_XSLT}
				${OGLPLUS_SRC_XML}
			MAIN_DEPENDENCY ${OGLPLUS_SRC_XML}
			DEPENDS ${BOUND_HEADER_XSLT}
		)
		set_source_files_properties(${OGLPLUS_SRC_XML} PROPERTIES GENERATED 1)
		add_custom_target(bound_${BINDABLE}_hpp DEPENDS ${HEADER_FILE})
		add_dependencies(bound_${BINDABLE}_hpp oglplus_xml_src)
		add_dependencies(bound_object_headers bound_${BINDABLE}_hpp)
		install(FILES ${HEADER_FILE} DESTINATION include/oglplus/bound)
	endif()
endforeach(BINDABLE)


