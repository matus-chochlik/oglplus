#  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL)

if(QT_FOUND)
	set(QT4GL_FOUND True)
endif()
