#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

find_package(Doxygen)
if(DOXYGEN_FOUND)

	set(DOXYGEN_WD ${CMAKE_CURRENT_SOURCE_DIR})
	set(DOXYFILE ${PROJECT_BINARY_DIR}/Doxyfile.xml)

	file(WRITE ${DOXYFILE} "@INCLUDE = ${DOXYGEN_WD}/Doxyfile.autohdr\n")
	file(APPEND ${DOXYFILE} "OUTPUT_DIRECTORY = ${CMAKE_CURRENT_BINARY_DIR}\n")
	file(APPEND ${DOXYFILE} "QUIET = YES\n")

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

	unset(DOXYFILE)

	set(DOXYFILE ${PROJECT_BINARY_DIR}/Doxyfile.html)
	file(WRITE ${DOXYFILE} "@INCLUDE = ${DOXYGEN_WD}/Doxyfile.oglplus\n")
	file(APPEND ${DOXYFILE} "IMAGE_PATH = ../logo/ \n")
	file(APPEND ${DOXYFILE} "INPUT += ${PROJECT_BINARY_DIR}/include/bound \n")
	file(APPEND ${DOXYFILE} "OUTPUT_DIRECTORY = ${CMAKE_CURRENT_BINARY_DIR}\n")
	file(APPEND ${DOXYFILE} "GENERATE_TAGFILE = ${CMAKE_CURRENT_BINARY_DIR}/oglplus.doxygen.tags\n")
	file(APPEND ${DOXYFILE} "QUIET = YES\n")

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	if(OGLPLUS_NO_DOCS)
	add_custom_target(doc DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)
	else()
	add_custom_target(doc ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)
	endif()

	add_dependencies(doc auto_generated_headers)
	unset(DOXYFILE)
endif()

find_program(XSLTPROC_EXECUTABLE xsltproc)
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/xml/oglplus.xml
	COMMAND ${XSLTPROC_EXECUTABLE}
		--output ${CMAKE_CURRENT_BINARY_DIR}/xml/oglplus.xml
		${CMAKE_CURRENT_BINARY_DIR}/xml/combine.xslt
		${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml
	MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml
)

add_custom_target(oglplus_xml_src DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/xml/oglplus.xml)

