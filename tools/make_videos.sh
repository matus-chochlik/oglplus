#!/bin/bash
# Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
(
	cd $(dirname $0)/../
	./configure.py \
		--from-scratch \
		--no-docs \
		--use-cxxflags \
		--use-ldflags \
		--use-glx \
		--use-glcorearb-h \
		--build
)

for example
do $(dirname $0)/make_video.sh ${example%.cpp}
done
