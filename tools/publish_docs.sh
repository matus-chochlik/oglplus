#!/bin/bash
# Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# the remote documentation host computer data
doc_user=${USER}
doc_host="kifri.fri.uniza.sk"

for lib_name in oglplus oalplus
do
	doc_home="./public_html/${lib_name}"
	doc_base="${doc_home}/html"
	# local path to docs
	doc_src="$(dirname $0)/../_build/doc/doxygen/${lib_name}/html"
	#
	(cd _build && make doc -j 4) &&
	(cd _build && make rebuild-doc) &&
	# remove the old files
	ssh ${doc_user}@${doc_host} "rm -rf ${doc_base}/*" &&
	# tar stream and untar the new files
	(cd ${doc_src} && tar -c . | ssh ${doc_user}@${doc_host} "mkdir -p ${doc_base} && cd ${doc_base} && tar -x && echo 'AddCharset UTF-8 .html' > .htaccess")
done

