#!/bin/bash
# Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
mkdir -p out/doc/doxygen/oglplus/html/ &&
mkdir -p bld/doc/doxygen/ &&
mkdir -p bld/example/oglplus/ &&
cp -R doc/logo out/doc/doxygen/oglplus/html/ &&
cd doc/doxygen && (
	cat Doxyfile.oglplus &&
	echo "QUIET=YES" &&
	echo -n "PROJECT_NUMBER = " &&
	cat ../../VERSION
) | doxygen -
