/**
 *  @file oglplus/string.ipp
 *  @brief Implementation of String functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/auxiliary/utf8.hpp>

namespace oglplus {

OGLPLUS_LIB_FUNC bool ValidString(const GLchar* begin, const GLchar* end)
{
	return aux::ValidUTF8(begin, end);
}

} // namespace oglplus

