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
sleep 1 && xwd -name "${title}" -out ${2}
# terminate the example process and wait for it
kill -TERM ${child} 2> /dev/null && wait ${child}
# remove the lock
rm -rf ${lock}
exit 0

