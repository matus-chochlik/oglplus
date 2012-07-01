#!/bin/bash
# Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cd $(dirname $0)/../
build_dir=_build

if [ "${1}" == "" ]
then echo "No example specified" && exit 1
fi

if [ ! -f "${build_dir}/${1}" ]
then echo "Unable to find built example '${1}' in '${PWD}'" && exit 1
fi
#
function convert_single_frame()
{
	convert -depth 8 -size 852x480 ${1} -flip -quality 95 ${1%.rgba}.jpeg && rm -f ${1}
}
# start the example
prefix="/tmp/oglplus-$(basename ${1})"
${build_dir}/${1} ${prefix}- |
while read framepath
do convert_single_frame "${framepath}"
done

for job in $(jobs -p)
do wait ${job}
done

ffmpeg -f image2 -i "${prefix}-%06d.jpeg" -r 25 -vcodec mpeg4 -b 4000k ${prefix}.avi
rm -f ${prefix}-*.jpeg

