#!/bin/bash
# Copyright 2013 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cube_side=${2:-512}
input_file=${1}

if [ ! -x $(which mincinfo) ] || [ ! -x $(which minctoraw) ]
then echo "minc-tools (mincinfo and minctoraw) are required!" && exit 1
fi

if [ ! -x $(dirname $0)/reshape_raw_cube ]
then (cd $(dirname $0) && make reshape_raw_cube > /dev/null) || exit 2
fi

if [ -f ${input_file} ] && [ -r ${input_file} ]
then
	input_dims=$(
		mincinfo \
			-dimlength xspace \
			-dimlength yspace \
			-dimlength zspace \
			${input_file} |
		xargs |
		tr ' ' 'x'
	)
	minctoraw -byte -normalize ${input_file} |
	$(dirname $0)/reshape_raw_cube \
		-ori-dim ${input_dims} \
		-new-dim ${cube_side}x${cube_side}x${cube_side}
else
	echo "'${input_file}' is not a readable file."
fi
