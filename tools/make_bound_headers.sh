#!/bin/bash
# Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
RootDir=${1:-${PWD}}
InputDir="${RootDir}/source/enums"
TempDir=$(mktemp -d)

OGLplusBindableObjects="buffer texture renderbuffer framebuffer"

function PrintFileHeader()
{
	echo "/*"
	echo " *  .file ${2}"
	echo " *"
	echo " *  Automatically generated header file. DO NOT modify manually,"
	echo " *  edit '${1##${RootDir}/}' instead."
	echo " *"
	echo " *  Copyright 2010-$(date +%Y) Matus Chochlik. Distributed under the Boost"
	echo " *  Software License, Version 1.0. (See accompanying file"
	echo " *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)"
	echo " */"
	echo
}

DoxygenWD="${RootDir}/doc/doxygen"
Doxyfile="${TempDir}/Doxyfile-xml"

# make the temporary doxyfile
(
exec > ${Doxyfile}
echo "@INCLUDE = ${DoxygenWD}/Doxyfile.autohdr"
echo "OUTPUT_DIRECTORY = ${TempDir}"
echo "QUIET = YES"
)

# run doxygen to get the xml representation of headers
(
cd ${DoxygenWD}
doxygen ${Doxyfile}
)

# build one big xml file from the xml "docs"
# which is used to generate additional headers
xsltproc \
	--output ${TempDir}/xml/oglplus.xml \
	${TempDir}/xml/combine.xslt \
	${TempDir}/xml/index.xml

HeaderDir="${RootDir}/include/oglplus/bound"
mkdir -p ${HeaderDir}

for Bindable in ${OGLplusBindableObjects}
do
	Header="${HeaderDir}/${Bindable}.hpp"
	xsltproc \
		--output ${Header} \
		--stringparam object ${Bindable} \
		--stringparam year $(date +%Y) \
		${RootDir}/xslt/bound_hpp.xsl \
		${TempDir}/xml/oglplus.xml

	git add ${Header}
done

rm -rf ${TempDir}
