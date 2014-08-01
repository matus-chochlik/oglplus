/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_math_vector_N
namespace oglplus {

template <typename T, size_t N>
class Vector
{
public:
//]
//[oglplus_math_vector_N_ctrs

	Vector(const Vector&); /*<
	Vectors are copy-constructible.
	>*/
	Vector(void); /*<
	Constructs a vector with all coordinates initialized to zero.
	>*/
	Vector(const T* v, size_t n); /*<
	Construction from a pointer to data and number of elements.
	The memory pointed-to by [^v] must hold at least [^n] valid instances
	of type [^T] and [^n] must be greater or equal to [^N] - the
	dimension of the vector.
	>*/
	Vector(const T* v, size_t n, T def); /*<
	Construction from a pointer to data, number of elements and a default.
	The first [^n] coordinates of the resulting vector are initialized
	by the first [^n] values from the memory pointed-to by [^v].
	If [^n] is less than [^N], then the remaining values are
	initialized to [^def].
	The memory pointed-to by [^v] must hold at least [^n] valid instances
	of type [^T].
	>*/

	explicit Vector(T v); /*<
	Constructs a vector having all coordinates initialized
	to the specified value [^v].
	>*/

	template <typename ... P>
	Vector(P ... v);  /*<
	Constructs a vector having its coordinates initialized from the
	values [^v] from the parameter pack. Available only if the number
	of arrguments in the pack equals [^N].
	>*/

	template <size_t N>
	Vector(const T (&v)[N]); /*<
	Construction from a const C-array of known size.
	>*/

	template <typename U, size_t M>
	Vector(const Vector<U, M>& v) /*<
	Truncation of a vector of higher or equal dimension possibly with
	a different underlying type.
	The resulting [^Vector] has the same coordinates as the first
	[^N] coordinates of the vector [^v] passed as argument converted
	to [^T].
	>*/


	struct Unit_ { }; /*<
	Helper structure for dispatching the following constructor.
	>*/
	Vector(Unit_, size_t i); /*<
	Constructs a vector with all coordinates set to zero except
	the [^i]th coordinate, which is set to one. The value of
	[^i] must be less than [^N].
	>*/
	static __Vector Unit(size_t i); /*<
	Returns [^Vector(Vector::Unit_(), i)].
>*/
//]
//[oglplus_math_vector_bla


};

} // namespace oglplus
//]

