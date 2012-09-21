/**
 *  .file oglplus/auxiliary/filesystem.hpp
 *  .brief Helper filesystem-related utilities
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2011-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef __OGLPLUS_AUX_FILESYSTEM_1102101236_HPP
#define __OGLPLUS_AUX_FILESYSTEM_1102101236_HPP

#include <oglplus/config.hpp>
#include <string>
#include <cassert>

namespace oglplus {
namespace aux {

inline std::string FilesysPathSep(void)
{
	// TODO
	return std::string("/");
}

inline bool IsFilesysPathSep(const char* str, size_t size)
{
	assert(size > 0);
	assert(str);
	// TODO
	return *str == '/';
}

} // namespace aux
} // namespace oglplus

#endif
