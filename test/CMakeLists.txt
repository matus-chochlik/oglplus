#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

include(./oglplus_testing.cmake)

oglplus_exec_test(boost_utfw)
oglplus_build_test(config)
oglplus_exec_test(math)
oglplus_exec_test(angle)
oglplus_exec_test(vector)
oglplus_exec_test(matrix)
