#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.6)

set(OGLPLUS_BINDABLE_OBJECTS buffer texture renderbuffer framebuffer)

find_package(Doxygen)
if(DOXYGEN_FOUND)

	set(DOXYFILE ${PROJECT_BINARY_DIR}/Doxyfile)

	file(WRITE ${DOXYFILE} "@INCLUDE = ${PROJECT_SOURCE_DIR}/doc/doxygen/Doxyfile.autohdr\n")
	file(APPEND ${DOXYFILE} "OUTPUT_DIRECTORY = ${PROJECT_BINARY_DIR}/\n")
	file(APPEND ${DOXYFILE} "INPUT = ${PROJECT_SOURCE_DIR}/include/oglplus\n")
	file(APPEND ${DOXYFILE} "QUIET = YES\n")

	add_custom_command(
		OUTPUT ${PROJECT_BINARY_DIR}/xml/index.xml
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc/doxygen
	)
endif()

find_program(XSLTPROC_EXECUTABLE xsltproc)
add_custom_command(
	OUTPUT ${PROJECT_BINARY_DIR}/xml/oglplus.xml
	COMMAND ${XSLTPROC_EXECUTABLE}
		--output ${PROJECT_BINARY_DIR}/xml/oglplus.xml
		${PROJECT_BINARY_DIR}/xml/combine.xslt
		${PROJECT_BINARY_DIR}/xml/index.xml
	MAIN_DEPENDENCY ${PROJECT_BINARY_DIR}/xml/index.xml
)

unset(BOUND_OBJECT_HEADERS)
foreach(BINDABLE ${OGLPLUS_BINDABLE_OBJECTS})

	set(HEADER_FILE ${CMAKE_CURRENT_BINARY_DIR}/bound/${BINDABLE}.hpp)

	# TODO make this portable/usable with other processors
	add_custom_command(
		OUTPUT ${HEADER_FILE}
		COMMAND ${XSLTPROC_EXECUTABLE}
			--output bound/${BINDABLE}.hpp
			--stringparam ${BINDABLE}
			${PROJECT_SOURCE_DIR}/xslt/bound_hpp.xsl
			${PROJECT_BINARY_DIR}/xml/oglplus.xml
		MAIN_DEPENDENCY ${PROJECT_BINARY_DIR}/xml/oglplus.xml
		DEPENDS ${PROJECT_SOURCE_DIR}/xslt/bound_hpp.xsl
	)
	set(BOUND_OBJECT_HEADERS ${BOUND_OBJECT_HEADERS} ${HEADER_FILE})
endforeach(BINDABLE)

add_custom_target(bound_object_headers ALL DEPENDS ${BOUND_OBJECT_HEADERS})

