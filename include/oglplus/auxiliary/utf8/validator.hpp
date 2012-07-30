/**
 *  .file oglplus/auxiliary/utf8.hpp
 *  .brief Helper utf8-related tools
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2011-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef __OGLPLUS_AUX_UTF8_VALIDATOR_1102101236_HPP
#define __OGLPLUS_AUX_UTF8_VALIDATOR_1102101236_HPP

#include <iterator>
#include <cassert>

namespace oglplus {
namespace aux {

template <typename Iterator>
class UTF8Validator
{
protected:
	template <typename I>
	static I nulliter(I)
	{
		return I();
	}

	static const char* nulliter(const char*)
	{
		return nullptr;
	}

	static unsigned char byte(Iterator _i)
	{
		assert(_S_is_valid_iterator(_i));
		return static_cast<unsigned char>(*_i);
	}

	template <int N>
	static void _S_check_seq_tail(Iterator _s)
	{
		for(int i=1; i!=N; ++i)
		{
			assert(byte(_s) != 0x00);
			assert(byte(_s) != 0x80);
			++_s;
		}
	}

	template <typename I>
	static bool _S_is_valid_iterator(I)
	{
		return true;
	}

	static bool _S_is_valid_iterator(const char* _s)
	{
		return _s != nullptr;
	}

	// Validates the utf8 string, returns _end or nullptr
	static Iterator _S_validate(Iterator _s, Iterator _end)
	{
		unsigned short bytes = 0;
		assert(_S_is_valid_iterator(_s));
		while((_s != _end) && (byte(_s) != 0x00))
		{
			// there are remaining bytes in the sequence
			if(bytes)
			{
				// the byte must be 10xxxxxx
				if((byte(_s) & 0xC0) != 0x80)
					return nulliter(_s);
				// but not 10000000
				if(byte(_s) == 0x80)
					return nulliter(_s);
				--bytes;
			}
			// this is _a beginning of a new sequence
			else if(byte(_s) & 0x80)
			{
				// 110xxxxx
				if((byte(_s) & 0xE0) == 0xC0)
				{
					// but not 11000000
					if(byte(_s) == 0xC0)
						return nulliter(_s);
					bytes = 1;
				}
				// 1110xxxx
				else if((byte(_s) & 0xF0) == 0xE0)
				{
					// but not 11100000
					if(byte(_s) == 0xE0)
						return nulliter(_s);
					bytes = 2;
				}
				// 11110xxx
				else if((byte(_s) & 0xF8) == 0xF0)
				{
					// but not 11110000
					if(byte(_s) == 0xF0)
						return nulliter(_s);
					bytes = 3;
				}
				// 111110xx
				else if((byte(_s) & 0xFC) == 0xF8)
				{
					// but not 11111000
					if(byte(_s) == 0xF8)
						return nulliter(_s);
					bytes = 4;
				}
				// 1111110x
				else if((byte(_s) & 0xFE) == 0xFC)
				{
					// but not 11111100
					if(byte(_s) == 0xFC)
						return nulliter(_s);
					bytes = 5;
				}
			}
			++_s;
		}
		return _s;
	}
public:
	bool operator()(Iterator begin, Iterator end) const
	{
		return _S_validate(begin, end) == end;
	}
};

} // namespace aux
} // namespace oglplus

#endif // include guard
