/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_math_vector
namespace oglplus {

template <typename T, size_t N>
class Vector
{
public:
//]
//[oglplus_math_vector_ctrs

	Vector(const Vector&); /*<
	Vectors are copy-constructible.
	>*/
	Vector(void); /*<
	Constructs a vector with all components initialized to zero.
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
	Vector(P ... p);  /*<
	Constructs a vector having its components initialized by the
	values [^p] from the parameter pack. Available only if the number
	of arguments in the pack equals [^N] and all types in [^P] are
	convertible to [^T].
	>*/

	template <size_t N>
	Vector(const T (&v)[N]); /*<
	Construction from a const C-array of [^T] with known size.
	>*/

	template <typename U, size_t M>
	Vector(const Vector<U, M>& v) /*<
	Truncation of a vector of higher or equal dimension possibly with
	a different underlying type.
	The resulting [^Vector] has the same coordinates as the first
	[^N] coordinates of the vector [^v] passed as argument converted
	to [^T].
	>*/

	template <typename U, size_t M, typename ... P>
	Vector(const Vector<U, M>& v, P ... p);  /*<
	Construction from a vector of smaller dimension and a pack of
	values. The resulting vector has the first M components initialized
	from the vector [^m] and the remaining [^N-M] values from the
	pack [^p]. This constructor is available only if [^M < N] and the number
	of arguments in the pack equals [^N - M] and all types in [^P] are
	convertible to [^T].
	>*/


	struct Unit_ { }; /*<
	Helper structure for dispatching the following constructor.
	>*/
	Vector(Unit_, size_t i); /*<
	Constructs a vector with all components set to zero except
	for the [^i]th coordinate, which is set to one. The value of
	[^i] must be less than [^N].
	>*/
	static __Vector Unit(size_t i); /*<
	Returns a vector with all components set to zero except
	for the [^i]th coordinate, which is set to one. Equal to calling
	[^Vector(Vector::Unit_(), i)]. The value of [^i] must be less than [^N].
	>*/

	explicit Vector(const __Matrix<T, 1, N>& matrix); /*<
	Construction from a single row __Matrix.
	>*/
	explicit Vector(const __Matrix<T, N, 1>& matrix); /*<
	Construction from a single column __Matrix.
>*/
//]
//[oglplus_math_vector_bla


}; // class Vector
//]

//[oglplus_math_vector_typedefs

#ifdef GL_INT
typedef Vector<GLint, 1> Vec1i; /*<
Vectors with signed integer components.
>*/
typedef Vector<GLint, 2> Vec2i;
typedef Vector<GLint, 3> Vec3i;
typedef Vector<GLint, 4> Vec4i;
#endif

#ifdef GL_FLOAT
typedef Vector<GLfloat, 1> Vec1f; /*<
Vectors with floating-point number components.
>*/
typedef Vector<GLfloat, 2> Vec2f;
typedef Vector<GLfloat, 3> Vec3f;
typedef Vector<GLfloat, 4> Vec4f;
#endif

#ifdef GL_DOUBLE
typedef Vector<GLdouble, 1> Vec1d; /*<
Vectors with double precision floating-point components.
>*/
typedef Vector<GLdouble, 2> Vec2d;
typedef Vector<GLdouble, 3> Vec3d;
typedef Vector<GLdouble, 4> Vec4d;
#endif

} // namespace oglplus
//]

