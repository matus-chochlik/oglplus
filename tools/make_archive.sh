#!/bin/bash
# Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
oglplus_archive_items="
	_prebuilt
	config
	doc
	example
	include
	source
	utils
	xslt
	LICENSE_1_0.txt
	README.txt
	CHANGELOG
	VERSION
	CMakeLists.txt
	configure.sh
	configure-oglplus
"

if [ ! -f ./configure.sh ]
then echo "Run from the OGLplus root dir!" &&  exit 1
fi

rm -rf ./_prebuilt ./_build

./configure.sh --from-scratch --no-examples --no-docs --quiet
(cd ./_build && make oglplus-textures -j 4)

#
# move built files to the pre-built directory
function move_files()
{
	build_dir="./_build"
	prebuilt="./_prebuilt"

	mkdir -p ${prebuilt}/${1}
	mv ${build_dir}/${1}/*.${2} ${prebuilt}/${1}/
}
#
move_files textures png
#
#
file_basename="oglplus-$(< VERSION)"

fixlnpath_sed='s|\./||;s|[^/]\+/|../|g'

mkdir -p ${file_basename}
for item in ${oglplus_archive_items}
do
	mkdir -p $(dirname ${file_basename}/${item})
	ln -s ../$(echo "`dirname ${item}`/" | sed "${fixlnpath_sed}")${item} ${file_basename}/${item}
done
tar -hcf ${file_basename}.tar ${file_basename}
gzip -9 ${file_basename}.tar
rm -rf ${file_basename}
