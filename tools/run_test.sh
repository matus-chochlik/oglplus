#!/bin/bash
# Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
test_exe=out/devel/test${1}
rm -f ${test_exe}
clear
pidfile=$(mktemp)
make -f Makefile.full ${test_exe} || exit $?
(
	sleep 50
	if [ -d /proc/$(< ${pidfile}) ]
	then kill -TERM $(< ${pidfile})
	fi
	rm ${pidfile}
) &
nice -n 19 ./${test_exe} &
echo $$ > ${pidfile}
wait %nice
