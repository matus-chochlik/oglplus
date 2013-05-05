#!/bin/bash
# Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# re-build the example with the frame_dump "harness"
build_dir=_build
(
	cd $(dirname $0)/../
	./configure.py --from-scratch --use-cxxflags --use-ldflags --use-glx --use-glcorearb-h --build-dir ${build_dir}
	cd ./${build_dir}/ && make -j 4
)

for example
do $(dirname $0)/make_video.sh ${example%.cpp}
done
