#!/bin/bash
# Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
oglplus_example_dir=./$(dirname $0)/../example/oglplus
oglplus_examples=${oglplus_example_dir}/[0-9][0-9][0-9]*.cpp
cxx_feat_tag="@oglplus_example_uses_cxx11"

cxx_feats=$(
	grep -e"${cxx_feat_tag}" ${oglplus_examples} |
	sed -e's/.*{\([^}]\+\)}/\1/' |
	sort | uniq
)

for cxx_feat in ${cxx_feats}
do
	echo ${cxx_feat}

	req_file=${oglplus_example_dir}/requirements/${cxx_feat}.txt
	for example in ${oglplus_examples}
	do
		if [ "${example:0:3}" != "000" ]
		then
			feat_required=$(grep -c -e"${cxx_feat_tag}{${cxx_feat}}"<${example})
			if [ ${feat_required} -ne 0 ]
			then echo $(basename ${example})
			fi
		fi
	done | sort > ${req_file}
	git add ${req_file}
done

$(dirname $0)/make_example_dep_list.sh png.h libpng
