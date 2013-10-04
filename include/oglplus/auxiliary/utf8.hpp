/**
 *  .file oglplus/auxiliary/utf8.hpp
 *  .brief Helper utf8-related tools
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2011-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef __OGLPLUS_AUX_UTF8_1102101236_HPP
#define __OGLPLUS_AUX_UTF8_1102101236_HPP

#if !OGLPLUS_NO_UTF8_CHECKS
#include <cassert>
#include <vector>
#endif

namespace oglplus {
namespace aux {

typedef char32_t UnicodeCP;

#if !OGLPLUS_NO_UTF8_CHECKS

size_t UTF8BytesRequired(const UnicodeCP* cp_str, size_t len);

void ConvertCodePointToUTF8(UnicodeCP cp, char* str, size_t& len);

void ConvertCodePointsToUTF8(
	const UnicodeCP* cps,
	size_t len,
	std::vector<char>& result
);

size_t CodePointsRequired(const char* str, size_t len);

UnicodeCP ConvertUTF8ToCodePoint(
	const char* str,
	size_t len,
	size_t& cp_len
);

void ConvertUTF8ToCodePoints(
	const char* str,
	size_t len,
	std::vector<UnicodeCP>& result
);

class UTF8Validator
{
protected:
	static bool _is_valid_ptr(const char* _s);
	static unsigned char byte(const char* _i);

	template <int N>
	static void _check_seq_tail(const char* _s)
	{
		for(int i=1; i!=N; ++i)
		{
			assert(byte(_s) != 0x00);
			assert(byte(_s) != 0x80);
			++_s;
		}
	}

	// Validates the utf8 string, returns _end or nullptr
	static const char* _validate(const char* _s, const char* _end);
public:
	bool operator()(const char* begin, const char* end) const
	{
		return _validate(begin, end) == end;
	}
};
#endif

inline bool ValidUTF8(const char* begin, const char* end)
{
#if !OGLPLUS_NO_UTF8_CHECKS
	UTF8Validator valid_utf8;
	return valid_utf8(begin, end);
#else
	OGLPLUS_FAKE_USE(begin);
	OGLPLUS_FAKE_USE(end);
	return true;
#endif
}

} // namespace aux
} // namespace oglplus

#if !OGLPLUS_NO_UTF8_CHECKS
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/auxiliary/utf8.ipp>
#endif // OGLPLUS_LINK_LIB
#endif // OGLPLUS_NO_UTF8_CHECKS

#endif
