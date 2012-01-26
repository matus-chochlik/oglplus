#!/bin/bash
# Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
lock=/tmp/.${USER}.oglplus-$(basename $0 .sh).lock
title="oglplus example window"
# wait for any other running instances of this script to finish
while ! mkdir ${lock} 2> /dev/null
do sleep 1
done
# wait for any example windows to close
while true
do
	count=$(xwininfo -name "${title}" 2> /dev/null | grep -c -e "${title}")
	if [ ${count} -ne 0 ]
	then sleep 1
	else break
	fi
done
#
# start the example on the background
${1} &
# remember its PID
child=$!
# wait for a while and make a screenshot
case "$(basename ${1})" in
	005_mandelbrot) sleep_period=2;;
	018_particle_system) sleep_period=5;;
	021_cloud) sleep_period=3;;
	021_wooden_crate) sleep_period=2;;
	024_particle_trails) sleep_period=4;;
	025_rendered_texture) sleep_period=2;;
	026_clouds) sleep_period=5;;
	026_torus_halo) sleep_period=2;;
	027_depth_of_field) sleep_period=5;;
	027_smoke_trails) sleep_period=7;;
	031_sketch) sleep_period=3;;
	033_metal_and_glass) sleep_period=7;;
	034_billiard_balls) sleep_period=8;;
	*)sleep_period=1;;
esac
sleep ${sleep_period} && xwd -name "${title}" -out ${2}
# terminate the example process and wait for it
kill -TERM ${child} 2> /dev/null && wait ${child}
# remove the lock
rm -rf ${lock}
exit 0

