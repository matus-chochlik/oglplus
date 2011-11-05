#!/bin/bash
# Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
example_wc="example/oglplus/${1}*"
count=$(ls -l ${example_wc} 2> /dev/null | wc -l)
if [ ${count} -eq 0 ]
then echo "Example '${1}*' not found!" && exit 1;
elif [ ${count} -gt 1 ]
then echo "Multiple examples match: [$(echo ${example_wc})]. Specify one." && exit 2;
fi

example_src="$(echo ${example_wc})"
example="out/${example_src%.cpp}"
clear
make -f Makefile.full ${example} && ${example}
