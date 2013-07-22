/**
 *  @file oglplus/text/unicode.hpp
 *  @brief Unicode-related definitions used in text rendering
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXT_UNICODE_HPP
#define OGLPLUS_TEXT_UNICODE_HPP

#include <oglplus/config.hpp>

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/auxiliary/utf8/conversion.hpp>
#endif

#include <cassert>

namespace oglplus {
namespace text {


/// Unicode code-point type
/**
 *  @ingroup text_rendering
 */
typedef char32_t CodePoint;

/// A sequence of CodePoints
typedef std::vector<CodePoint> CodePoints;

/// Converts a UTF-8 range to a vector of unicode code points
/**
 *  @ingroup text_rendering
 */
OGLPLUS_LIB_FUNC void UTF8ToCodePoints(
	const char* begin,
	const char* end,
	CodePoints& result
)
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
{
	aux::ConvertUTF8ToCodePoints(begin, end-begin, result);
}
#else
;
#endif

/// Converts a UTF-8 range to a vector of unicode code points
/**
 *  @ingroup text_rendering
 */
OGLPLUS_LIB_FUNC void UTF8ToCodePoints(
	const char* c_str,
	std::size_t length,
	CodePoints& result
)
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
{
	aux::ConvertUTF8ToCodePoints(c_str, length, result);
}
#else
;
#endif

inline CodePoints UTF8ToCodePoints(
	const char* begin,
	const char* end
)
{
	CodePoints result;
	UTF8ToCodePoints(begin, end, result);
	return result;
}

inline CodePoints UTF8ToCodePoints(
	const char* c_str,
	std::size_t length
)
{
	CodePoints result;
	UTF8ToCodePoints(c_str, length, result);
	return result;
}

template <std::size_t N>
inline CodePoints UTF8ToCodePoints(const char (&c_str_lit)[N])
{
	CodePoints result;
	UTF8ToCodePoints(c_str_lit, N>0?N-1:0, result);
	return result;
}

/// Converts a range of unicode code points to a UTF8 sequence
/**
 *  @ingroup text_rendering
 */
OGLPLUS_LIB_FUNC void CodePointsToUTF8(
	const CodePoint* begin,
	const CodePoint* end,
	std::vector<char>& result
)
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
{
	aux::ConvertCodePointsToUTF8(begin, end-begin, result);
}
#else
;
#endif

/// Converts a range of unicode code points to a UTF8 sequence
/**
 *  @ingroup text_rendering
 */
OGLPLUS_LIB_FUNC void CodePointsToUTF8(
	const CodePoint* c_str,
	std::size_t length,
	std::vector<char>& result
)
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
{
	aux::ConvertCodePointsToUTF8(c_str, length, result);
}
#else
;
#endif

inline std::vector<char> CodePointsToUTF8(
	const CodePoint* begin,
	const CodePoint* end
)
{
	std::vector<char> result;
	CodePointsToUTF8(begin, end, result);
	return result;
}

inline std::vector<char> CodePointsToUTF8(
	const CodePoint* c_str,
	std::size_t length
)
{
	std::vector<char> result;
	CodePointsToUTF8(c_str, length, result);
	return result;
}

} // namespace text
} // namespace oglplus

#endif // include guard
