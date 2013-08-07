#!/bin/bash
# Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cd $(dirname ${0})/../_build/example/${2:-oglplus}/
for example in ./*${1}*
do echo "|$(basename ${example})|" && make ${example} && ${example}
done
