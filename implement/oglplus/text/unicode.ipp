/**
 *  @file oglplus/text/unicode.ipp
 *  @brief Implementation of Unicode utilities used in text rendering
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
namespace text {

OGLPLUS_LIB_FUNC void UTF8ToCodePoints(
	const char* begin,
	const char* end,
	CodePoints& result
)
{
	aux::ConvertUTF8ToCodePoints(begin, end-begin, result);
}

OGLPLUS_LIB_FUNC void UTF8ToCodePoints(
	const char* c_str,
	std::size_t length,
	CodePoints& result
)
{
	aux::ConvertUTF8ToCodePoints(c_str, length, result);
}

OGLPLUS_LIB_FUNC void CodePointsToUTF8(
	const CodePoint* begin,
	const CodePoint* end,
	std::vector<char>& result
)
{
	aux::ConvertCodePointsToUTF8(begin, end-begin, result);
}

OGLPLUS_LIB_FUNC void CodePointsToUTF8(
	const CodePoint* c_str,
	std::size_t length,
	std::vector<char>& result
)
{
	aux::ConvertCodePointsToUTF8(c_str, length, result);
}

} // namespace text
} // namespace oglplus

