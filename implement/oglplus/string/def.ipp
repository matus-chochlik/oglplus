/**
 *  @file oglplus/string/def.ipp
 *  @brief Implementation of String functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <eagine/base/utf8.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {

OGLPLUS_LIB_FUNC
bool ValidString(const char* begin, const char* end)
{
	return eagine::base::valid_utf8(begin, end);
}

} // namespace oglplus

