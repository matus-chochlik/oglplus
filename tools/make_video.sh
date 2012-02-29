#!/bin/bash
# Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
if [ "${1}" == "" ]
then echo "No example specified" && exit 1
fi

if [ ! -f ${1}.cpp ]
then echo "Unable to find source for example '${1}'" && exit 1
fi
#
# re-build the example with the frame_dump "harness"
(
	rm -f out/${1}
	export EXAMPLE_HARNESS=frame_dump
	make -f Makefile.full out/${1}
)
#
function convert_single_frame()
{
	convert -depth 8 -size 852x480 ${1} -flip -quality 95 ${1%.rgba}.jpeg && rm -f ${1}
}
# start the example
prefix="/tmp/oglplus-$(basename ${1})"
out/${1} ${prefix}- |
while read framepath
do convert_single_frame "${framepath}"
done

for job in $(jobs -p)
do wait ${job}
done

ffmpeg -f image2 -i "${prefix}-%06d.jpeg" -r 25 -vcodec mpeg4 -b 4000k ${prefix}.avi
rm -f ${prefix}-*.jpeg

