#!/bin/bash
# Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
oglplus_archive_items="
	auto_header
	doc
	example
	include
	source
	tools/make_screenshot.sh
	tools/make_gallery_html.sh
	tools/make_enum_headers.sh
	utils
	xslt
	out
	install.sh
	Makefile
	CHANGELOG
	LICENSE_1_0.txt
	VERSION
"

make clean
make textures
make auto_headers

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
