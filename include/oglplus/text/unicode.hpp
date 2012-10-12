/**
 *  @file oglplus/text/unicode.hpp
 *  @brief Unicode-related definitions used in text rendering
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_TEXT_UNICODE_HPP
#define OGLPLUS_TEXT_UNICODE_HPP

#include <oglplus/config.hpp>
#include <oglplus/string.hpp>
#include <oglplus/auxiliary/utf8/conversion.hpp>

#include <cassert>

namespace oglplus {
namespace text {


/// Unicode code-point type
/**
 *  @ingroup text_rendering
 */
typedef oglplus::aux::UnicodeCP CodePoint;

/// Converts a UTF-8 range to a vector of unicode code points
/**
 *  @ingroup text_rendering
 */
OGLPLUS_LIB_FUNC void UTF8ToCodePoints(
	const GLchar* begin,
	const GLchar* end,
	std::vector<CodePoint>& result
)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
	aux::ConvertUTF8ToCodePoints(begin, end-begin, result);
}
#endif

/// Converts a UTF-8 range to a vector of unicode code points
/**
 *  @ingroup text_rendering
 */
OGLPLUS_LIB_FUNC void UTF8ToCodePoints(
	const GLchar* c_str,
	std::size_t length,
	std::vector<CodePoint>& result
)
#if OGLPLUS_LINK_LIBRARY
;
#else
{
	aux::ConvertUTF8ToCodePoints(c_str, length, result);
}
#endif

inline std::vector<CodePoint> UTF8ToCodePoints(
	const GLchar* begin,
	const GLchar* end
)
{
	std::vector<CodePoint> result;
	UTF8ToCodePoints(begin, end, result);
	return result;
}

inline std::vector<CodePoint> UTF8ToCodePoints(
	const GLchar* c_str,
	std::size_t length
)
{
	std::vector<CodePoint> result;
	UTF8ToCodePoints(c_str, length, result);
	return result;
}

} // namespace text
} // namespace oglplus

#endif // include guard
