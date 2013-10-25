#!/bin/bash
# Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cd $(dirname $0)/../
build_dir=${PWD}/_build
example="${1%.cpp}"
urllabel="http://oglplus.org/"
exelabel="$(basename ${example})"
width=852
height=480
[[ "${2}" == "--hd" ]] && width=1280 && height=720
#
rootdir="$(dirname $0)/.."
tmpdir=$(mktemp -d)
mkdir -p ${tmpdir}
#
prefix="${tmpdir}/oglplus-$(basename ${example})"
urllabelfile=${tmpdir}/url_label.png
exelabelfile=${tmpdir}/exe_label.png
logofile=${tmpdir}/logo.png
#
filelist=${tmpdir}/filelist
rm -f ${filelist}
mkfifo ${filelist}

# make the oglplus url label
convert \
	-size $[${width}/2]x28 xc:none \
	-background none \
	-pointsize 28 \
	-gravity center \
	-stroke black \
	-strokewidth 8 \
	-annotate 0 "${urllabel}" \
	-blur 0x4 \
	-shadow ${width}x7+2+2 \
	+repage \
	-stroke none \
	-strokewidth 1 \
	-fill white \
	-annotate 0 "${urllabel}" \
	${urllabelfile}

# make the example name label
convert \
	-size $[${width}/3+${#exelabel}*4]x90 xc:none \
	-background none \
	-pointsize 16 \
	-gravity center \
	-stroke black \
	-strokewidth 2 \
	-annotate 0 "${exelabel}" \
	-blur 0x4 \
	-shadow $((width/4))x4+1+1 \
	+repage \
	-stroke none \
	-strokewidth 1 \
	-fill white \
	-annotate 0 "${exelabel}" \
	${exelabelfile}

# make the logo
convert \
	-size 144x144 xc:none \
	-background none \
	-gravity center \
	-stroke black \
	-fill black \
	-draw 'circle 72,72, 72,144' \
	-blur 2x2 \
	-shadow ${width}x7 \
	+repage \
	"${rootdir}/doc/logo/oglplus_circular.png" \
	-composite \
	-adaptive-resize 72x72 \
	-border 16x0 \
	"${logofile}"


if [ "${example}" == "" ]
then echo "No example specified" && exit 1
fi

if [ ! -f "${build_dir}/${example}" ]
then echo "Unable to find built example '${example}' in '${PWD}'" && exit 1
fi
#
function convert_single_frame()
{
	convert \
		-size ${width}x${height} \
		-depth 8 \
		${1} \
		-flip \
		-alpha Off \
		-gravity SouthEast \
		${urllabelfile} \
		-composite \
		-gravity SouthEast \
		${exelabelfile} \
		-composite \
		-gravity SouthEast \
		${logofile} \
		-composite \
		-quality 100 \
		${1%.rgba}.jpeg
	if [ $? -ne 0 ]
	then
		frame_no=$(echo ${1} | sed "s/${prefix////\\/}-0*\([0-9]\+\).*/\1/")
		prev_frame_no=$[${frame_no}-1]
		prev_frame=$(printf "${prefix}-%06d.jpeg" ${prev_frame_no})
		cp ${prev_frame} ${1%.rgba}.jpeg
	fi
	rm -f ${1}
}
#
let frameno=0
# start the example
(
xkill &
xkill_pid=$!
cd ${build_dir}
echo "${prefix}-" > ${filelist} &
nice -19 ${build_dir}/${example} --frame-dump ${prefix}- --width ${width} --height ${height} < ${filelist} |
while read framepath
do
	echo "${framepath}"
	convert_single_frame "${framepath}" > /dev/null
done > ${filelist}
)
kill -INT ${xkill_pid}

for job in $(jobs -p)
do wait ${job}
done

avconv -y -f image2 -i "${prefix}-%06d.jpeg" -r 25 -vcodec mpeg4 -b 8000k ${prefix}.avi
mv ${prefix}.avi .
rm -rf ${tmpdir}
