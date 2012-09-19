/**
 *  .file oglplus/auxiliary/utf8/conversion.hpp
 *  .brief Helper utf8-conversion functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef __OGLPLUS_AUX_UTF8_CONVERSION_1102101236_HPP
#define __OGLPLUS_AUX_UTF8_CONVERSION_1102101236_HPP

#include <cassert>

namespace oglplus {
namespace aux {

typedef char32_t UnicodeCP;

inline void ConvertCodePointToUTF8(UnicodeCP cp, char* str, size_t& len)
{
	// 7-bits -> one byte
	if((cp & ~0x0000007F) == 0)
	{
		str[0] = char(cp);
		len = 1;
	}
	// 11-bits -> two bytes
	else if((cp & ~0x000007FF) == 0)
	{
		str[0] = char(((cp & 0x000007C0) >>  6) | 0xC0);
		str[1] = char(((cp & 0x0000003F) >>  0) | 0x80);
		len = 2;
	}
	// 16-bits -> three bytes
	else if((cp & ~0x0000FFFF) == 0)
	{
		str[0] = char(((cp & 0x0000F000) >> 12) | 0xE0);
		str[1] = char(((cp & 0x00000FC0) >>  6) | 0x80);
		str[2] = char(((cp & 0x0000003F) >>  0) | 0x80);
		len = 3;
	}
	// 21-bits -> four bytes
	else if((cp & ~0x001FFFFF) == 0)
	{
		str[0] = char(((cp & 0x001C0000) >> 18) | 0xF0);
		str[1] = char(((cp & 0x0003F000) >> 12) | 0x80);
		str[2] = char(((cp & 0x00000FC0) >>  6) | 0x80);
		str[3] = char(((cp & 0x0000003F) >>  0) | 0x80);
		len = 4;
	}
	// 26-bits -> five bytes
	else if((cp & ~0x03FFFFFF) == 0)
	{
		str[0] = char(((cp & 0x03000000) >> 24) | 0xF8);
		str[1] = char(((cp & 0x00FC0000) >> 18) | 0x80);
		str[2] = char(((cp & 0x0003F000) >> 12) | 0x80);
		str[3] = char(((cp & 0x00000FC0) >>  6) | 0x80);
		str[4] = char(((cp & 0x0000003F) >>  0) | 0x80);
		len = 5;
	}
	// 31-bits -> six bytes
	else if((cp & ~0x7FFFFFFF) == 0)
	{
		str[0] = char(((cp & 0x40000000) >> 30) | 0xFC);
		str[1] = char(((cp & 0x3F000000) >> 24) | 0x80);
		str[2] = char(((cp & 0x00FC0000) >> 18) | 0x80);
		str[3] = char(((cp & 0x0003F000) >> 12) | 0x80);
		str[4] = char(((cp & 0x00000FC0) >>  6) | 0x80);
		str[5] = char(((cp & 0x0000003F) >>  0) | 0x80);
		len = 6;
	}
	else assert(!"Invalid code point");
}


inline UnicodeCP ConvertUTF8ToCodePoint(const char* str, size_t len)
{
	// 0xxxxxxx
	if((*(str+0) & 0x80) == 0x00)
	{
		assert(len >= 1);
		return UnicodeCP(*(str+0));
	}
	// 110xxxxx
	else if((*(str+0) & 0xE0) == 0xC0)
	{
		// but not 11000000
		assert(*(str+0) != 0xC0);
		assert(len >= 2);
		return UnicodeCP(
			(((*(str+0) & ~0xE0) <<  6) & 0x00000FC0)|
			(((*(str+1) & ~0xC0) <<  0) & 0x0000003F)
		);
	}
	// 1110xxxx
	else if((*(str+0) & 0xF0) == 0xE0)
	{
		// but not 11100000
		assert(*(str+0) != 0xE0);
		assert(len >= 3);
		return UnicodeCP(
			(((*(str+0) & ~0xF0) << 12) & 0x0003F000)|
			(((*(str+1) & ~0xC0) <<  6) & 0x00000FC0)|
			(((*(str+2) & ~0xC0) <<  0) & 0x0000003F)
		);
	}
	// 111110xx
	else if((*(str+0) & 0xFC) == 0xF8)
	{
		// but not 11111000
		assert(*(str+0) != 0xF8);
		assert(len >= 5);
		return UnicodeCP(
			(((*(str+0) & ~0xFC) << 24) & 0x3F000000)|
			(((*(str+1) & ~0xC0) << 18) & 0x00FC0000)|
			(((*(str+2) & ~0xC0) << 12) & 0x0003F000)|
			(((*(str+3) & ~0xC0) <<  6) & 0x00000FC0)|
			(((*(str+4) & ~0xC0) <<  0) & 0x0000003F)
		);
	}
	// 1111110x
	else if((*(str+0) & 0xFE) == 0xFC)
	{
		// but not 11111100
		assert(*(str+0) != 0xFC);
		assert(len >= 6);
		return UnicodeCP(
			(((*(str+0) & ~0xFE) << 30) & 0xC0000000)|
			(((*(str+1) & ~0xC0) << 24) & 0x3F000000)|
			(((*(str+2) & ~0xC0) << 18) & 0x00FC0000)|
			(((*(str+3) & ~0xC0) << 12) & 0x0003F000)|
			(((*(str+4) & ~0xC0) <<  6) & 0x00000FC0)|
			(((*(str+5) & ~0xC0) <<  0) & 0x0000003F)
		);
	}
	else assert(!"Invalid UTF8 sequence");
}

} // namespace aux
} // namespace oglplus

#endif // include guard
