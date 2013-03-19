/**
 *  @file oglplus/bitfield.hpp
 *  @brief OpenGL bitfield-related helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BITFIELD_1107121519_HPP
#define OGLPLUS_BITFIELD_1107121519_HPP

#include <oglplus/config.hpp>

#if !OGLPLUS_NO_INITIALIZER_LISTS
#include <initializer_list>
#endif

namespace oglplus {

/// This template serves as a wrapper for OpenGL bitfields
/**
 *  Applications rarely need to use this class directly. Instantiations of this
 *  template are used as types for parameters in functions taking bitfields based
 *  on strongly-type enumerations. When constructing a bitfield the application
 *  simply passes the enumerated value or a combination of enumerated values using
 *  the bitwise-or operator or initializer list. For example:
 *
 *  @code
 *  Context gl;
 *  gl.Clear(ClearBit::ColorBuffer);
 *  gl.Clear(ClearBit::ColorBuffer|ClearBit::DepthBuffer|ClearBit::StencilBuffer);
 *  gl.Clear({ClearBit::ColorBuffer});
 *  gl.Clear({ClearBit::ColorBuffer, ClearBit::DepthBuffer});
 *  gl.Clear({ClearBit::ColorBuffer, ClearBit::StencilBuffer});
 *  @endcode
 */
template <typename Bit, typename BF = GLbitfield>
class Bitfield
{
private:
	BF _bits;
public:
	/// Construct a bitfield from a single strongly-typed enumeration value
	Bitfield(Bit _bit)
	OGLPLUS_NOEXCEPT_IF(BF(_bit))
	 : _bits(BF(_bit))
	{ }

	Bitfield(Bit _bit_a, Bit _bit_b)
	OGLPLUS_NOEXCEPT_IF(BF(_bit_a) | BF(_bit_b))
	 : _bits(BF(_bit_a) | BF(_bit_b))
	{ }

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_INITIALIZER_LISTS
	/// Construct a bitfield from an initializer list of enumeration values
	Bitfield(const std::initializer_list<Bit>& bits)
	OGLPLUS_NOEXCEPT_IF(std::declval<BF&>() |= BF(std::declval<Bit>()))
	 : _bits(BF(0))
	{
		for(auto i=bits.begin(),e=bits.end(); i!=e; ++i)
			_bits |= BF(*i);
	}
#endif

	/// Bitwise or operator for combining enumeration values into a bitfield
	friend Bitfield operator | (Bitfield bf, Bit b)
	OGLPLUS_NOEXCEPT_IF(std::declval<BF&>() |= BF(std::declval<Bit>()))
	{
		bf._bits |= BF(b);
		return bf;
	}

	/// Bitwise or operator for combining enumeration values into a bitfield
	Bitfield& operator |= (Bit b)
	OGLPLUS_NOEXCEPT_IF(std::declval<BF&>() |= BF(std::declval<Bit>()))
	{
		this->_bits |= BF(b);
		return *this;
	}

#if !OGLPLUS_NO_EXPLICIT_CONVERSION_OPERATORS
	explicit operator BF (void) const
#else
	operator BF (void) const
#endif
	OGLPLUS_NOEXCEPT(true)
	{
		return _bits;
	}
};

// helper macro used to define bitfield-related functions
#define OGLPLUS_MAKE_BITFIELD(BITS) \
template <> struct EnumBaseType<BITS> { typedef GLbitfield Type; }; \
inline oglplus::Bitfield<BITS> operator | (BITS b1, BITS b2) \
OGLPLUS_NOEXCEPT_IF(Bitfield<BITS>(std::declval<BITS>(), std::declval<BITS>()))\
{ \
	return Bitfield<BITS>(b1, b2); \
}


} // namespace oglplus

#endif // include guard
