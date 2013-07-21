#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# enable warnings on gcc
if(${CMAKE_COMPILER_IS_GNUCXX})
	add_definitions(-pedantic -Wall -Wextra -Wshadow)
endif()

add_definitions(-D_USE_MATH_DEFINES)

