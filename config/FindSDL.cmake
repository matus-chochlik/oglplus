#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# try to find SDL/SDL.h
find_path(
	SDL_INCLUDE_DIRS SDL/SDL.h
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT EXISTS ${SDL_INCLUDE_DIRS})
	find_path(SDL_INCLUDE_DIRS SDL/SDL.h)
endif()

# try to find the SDL library
find_library(
	SDL_LIBRARIES NAMES SDL
	PATHS ${LIBRARY_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
if(NOT SDL_LIBRARIES)
	find_library(SDL_LIBRARIES SDL)
endif()

if(EXISTS ${SDL_INCLUDE_DIRS})
	set(SDL_FOUND 1)
else()
	set(SDL_FOUND 0)
endif()

