/**
 *  @file eglplus/bitfield.hpp
 *  @brief EGL bitfield-related helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_BITFIELD_1107121519_HPP
#define EGLPLUS_BITFIELD_1107121519_HPP

#include <eglplus/config.hpp>

#if !EGLPLUS_NO_INITIALIZER_LISTS
#include <initializer_list>
#endif

namespace eglplus {

/// This template serves as a wrapper for EGL bitfields
/**
 */
template <typename Bit, typename BF = EGLenum>
class Bitfield
{
private:
	BF _bits;
public:
	/// Construct a bitfield from the underlying type
	Bitfield(BF bits)
	 : _bits(bits)
	{ }

	/// Construct a bitfield from a single strongly-typed enumeration value
	Bitfield(Bit _bit)
	 : _bits(BF(_bit))
	{ }

	Bitfield(Bit _bit_a, Bit _bit_b)
	 : _bits(BF(_bit_a) | BF(_bit_b))
	{ }

#if EGLPLUS_DOCUMENTATION_ONLY || !EGLPLUS_NO_INITIALIZER_LISTS
	/// Construct a bitfield from an initializer list of enumeration values
	Bitfield(const std::initializer_list<Bit>& bits)
	 : _bits(BF(0))
	{
		for(auto i=bits.begin(),e=bits.end(); i!=e; ++i)
			_bits |= BF(*i);
	}
#endif

	/// Bitwise or operator for combining enumeration values into a bitfield
	friend Bitfield operator | (Bitfield bf, Bit b)
	{
		bf._bits |= BF(b);
		return bf;
	}

	/// Bitwise or operator for combining enumeration values into a bitfield
	Bitfield& operator |= (Bit b)
	{
		this->_bits |= BF(b);
		return *this;
	}

	/// Test if a specified bit is set
	bool Test(Bit b) const
	{
		return (this->_bits & BF(b)) == BF(b);
	}
#if !EGLPLUS_NO_EXPLICIT_CONVERSION_OPERATORS
	explicit operator BF (void) const
#else
	operator BF (void) const
#endif
	{
		return _bits;
	}
};

// helper macro used to define bitfield-related functions
#define EGLPLUS_MAKE_BITFIELD(BITS) \
} namespace oglplus { \
namespace enums { \
template <> struct EnumBaseType<eglplus::BITS> { typedef EGLenum Type; }; \
} } namespace eglplus { \
inline eglplus::Bitfield<BITS> operator | (BITS b1, BITS b2) \
{ \
	return Bitfield<BITS>(b1, b2); \
}


} // namespace eglplus

#endif // include guard
