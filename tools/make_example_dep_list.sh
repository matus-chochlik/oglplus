#!/bin/bash
# Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
temp_file=$(mktemp)
search_include=${1}
dependency_name=${2}
dependency_file=example/oglplus/examples-with-${dependency_name}.txt
#
pushd ${PWD} > /dev/null
cd $(dirname $0)/../
#
echo ${dependency_name}
for example in example/oglplus/[0-9][0-9][0-9]*.cpp
do
	g++ --std=c++0x ${example} ${CXXFLAGS} -Iinclude -DOGLPLUS_NO_SITE_CONFIG=1 -E -M -o ${temp_file}
	if [ $(grep -c -e "${search_include}\>" < ${temp_file}) -gt 0 ]
	then echo $(basename ${example})
	fi
done > ${dependency_file}
git add ${dependency_file}
#
popd > /dev/null
#
rm -f ${temp_file}
