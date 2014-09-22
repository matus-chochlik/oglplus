/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_enums_functions
namespace oglplus {

template <typename Enumeration>
__Range<Enumeration> EnumValueRange(void); /*<
Returns a __Range of values in a OGLplus enum value.
This template function is overloaded for the enumerated types defined by
OGLplus and returns a __Range which allows to traverse all values of
a particular [^Enumeration] type.
The result of this function is influenced by the __OGLPLUS_NO_ENUM_VALUE_RANGES
preprocessor-symbol. If it is set to a nonzero value then [^EnumValueRange<Enum>()]
returns an empty range.
>*/

template <typename Enumeration>
__StrCRef EnumValueName(Enumeration enum_value); /*<
Returns the name of the GL enumerated value for an OGLplus enum value.
This function is overloaded for the enumerated types defined by OGLplus
and returns the GL constant name (without the "GL_" prefix) as managed
const string reference.
The result of this function is influenced by the __OGLPLUS_NO_ENUM_VALUE_NAMES
preprocessor-symbol. If it is set to a nonzero value then
[^EnumValueName(enum_value)] returns an empty string.
>*/
//]
//[oglplus_enums_Bitfield

template <typename Bits>
class Bitfield
{
public:
	Bitfield(void); /*<
	Constructs an empty (zero) bitfield.
	>*/
	Bitfield(Bits _bit); /*<
	Construct a bitfield from a single strongly-typed enumeration value.
	>*/
	Bitfield(Bits _bit_a, Bits _bit_b); /*<
	Construct a bitfield from a pair of strongly-typed enumeration values.
	>*/

#if !__OGLPLUS_NO_INITIALIZER_LISTS
	Bitfield(const std::initializer_list<Bits>& bits); /*<
	Construct a bitfield from an initializer list of enumeration values.
	>*/
#endif
	template <typename Iter>
	Bitfield(Iter pos, Iter end); /*<
	Construction from a pair of iterators through [^Bits].
	>*/

	friend Bitfield operator | (Bitfield bf, Bits b); /*<
	Bitwise-or operator for combining enumeration values into a bitfield.
	>*/
	Bitfield& operator |= (Bits b); /*<
	Bitwise-or operator for combining enumeration values into a bitfield.
	>*/

	bool Test(Bits b) const; /*<
	Tests if a specified bit is set.
	>*/
};

template <typename Bits>
__Bitfield<Bits> operator | (Bits b1, Bits b2);

//]
//[oglplus_enums_EnumArray

template <typename Enum>
class EnumArray
{
public:
	template <std::size_t N>
	EnumArray(const Enum (&enums)[N]);
	EnumArray(const std::vector<Enum>& enums);
	EnumArray(size_t count, const Enum* enums);
};
//]

//[oglplus_enums_OneOf
template <typename ... Enum>
class OneOf
{
public:
	OneOf(Enum)...; /*<
	(['Pseudocode]) - [^OneOf] has a constructor for each enumeration
	type passed in the template argument pack.
	>*/
};

} // namespace oglplus
//]

