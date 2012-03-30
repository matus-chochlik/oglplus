/**
 *  @file oglplus/bitfield.hpp
 *  @brief OpenGL bitfield-related helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BITFIELD_1107121519_HPP
#define OGLPLUS_BITFIELD_1107121519_HPP

#include <oglplus/config.hpp>

#include <initializer_list>

namespace oglplus {

template <typename Bit, typename BF = GLbitfield>
class Bitfield
{
private:
	BF _bits;
public:
	Bitfield(Bit _bit)
	 : _bits(BF(_bit))
	{ }

	Bitfield(Bit _bit_a, Bit _bit_b)
	 : _bits(BF(_bit_a) | BF(_bit_b))
	{ }

	Bitfield(const std::initializer_list<Bit>& bits)
	 : _bits(BF(0))
	{
		for(auto i=bits.begin(),e=bits.end(); i!=e; ++i)
			_bits |= BF(*i);
	}

	friend Bitfield operator | (Bitfield bf, Bit b)
	{
		bf._bits |= BF(b);
		return bf;
	}

	Bitfield& operator |= (Bit b)
	{
		this->_bits |= BF(b);
		return *this;
	}

	operator BF (void) const
	{
		return _bits;
	}
};

#define OGLPLUS_MAKE_BITFIELD(BITS) \
inline oglplus::Bitfield<BITS> operator | (BITS b1, BITS b2) \
{ \
	return Bitfield<BITS>(b1, b2); \
}


} // namespace oglplus

#endif // include guard
