#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

unset(PANGO_CAIRO_FOUND)

if(PKG_CONFIG_FOUND)
	pkg_check_modules(PANGO_CAIRO pangocairo)

	if(PANGO_CAIRO_FOUND)
		message(STATUS "Found Pango/Cairo")
	endif()
endif(PKG_CONFIG_FOUND)
