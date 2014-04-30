/**
 *  @file oglplus/string.ipp
 *  @brief Implementation of String functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/auxiliary/utf8.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {

OGLPLUS_LIB_FUNC
const String& EmptyString(void)
OGLPLUS_NOEXCEPT(true)
{
	static String empty;
	return empty;
}

OGLPLUS_LIB_FUNC
bool ValidString(const GLchar* begin, const GLchar* end)
{
	return aux::ValidUTF8(begin, end);
}

} // namespace oglplus

