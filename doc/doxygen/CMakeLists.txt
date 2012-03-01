#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.6)

find_package(Doxygen)
if(DOXYGEN_FOUND)

	set(DOXYFILE ${PROJECT_BINARY_DIR}/Doxyfile.xml)
	set(DOXYGEN_WD ${CMAKE_CURRENT_SOURCE_DIR})

	file(WRITE ${DOXYFILE} "@INCLUDE = ${DOXYGEN_WD}/Doxyfile.autohdr\n")
	file(APPEND ${DOXYFILE} "OUTPUT_DIRECTORY = ${CMAKE_CURRENT_BINARY_DIR}\n")
	file(APPEND ${DOXYFILE} "QUIET = YES\n")

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

	unset(DOXYFILE)

	#TODO: HTML docs
endif()

message(${CMAKE_CURRENT_BINARY_DIR}/xml/oglplus.xml)

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

