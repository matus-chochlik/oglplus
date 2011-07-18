#!/bin/bash
# Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# the remote documentation host computer data
doc_user=${USER}
doc_host="kifri.fri.uniza.sk"
doc_base="./public_html/oglplus/html"
# local path to docs
doc_src="$(dirname $0)/../out/doc/doxygen/oglplus/html"
#
# remove the old files
ssh ${doc_user}@${doc_host} "rm -rf ${doc_base}/*"
# tar stream and untar the new files
(cd ${doc_src} && tar -c . | ssh ${doc_user}@${doc_host} "mkdir -p ${doc_base} && cd ${doc_base} && tar -x")

