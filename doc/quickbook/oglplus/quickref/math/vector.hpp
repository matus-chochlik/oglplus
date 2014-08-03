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

//[oglplus_math_vector_swizzle
	T x(void) const; /*<
	Returns the [^0]th component of the vector.
	This function is available in all specializations of [^Vector].
	>*/
	T y(void) const; /*<
	Returns the [^1]st component of the vector.
	This function is available only if [^N >= 2].
	>*/
	T z(void) const; /*<
	Returns the [^2]nd component of the vector.
	This function is available only if [^N >= 3].
	>*/
	T w(void) const; /*<
	Returns the [^3]rd component of the vector.
	This function is available only if [^N >= 4].
	>*/

	Vector<T, 2> xy(void) const; /*<
	Returns a subvector with the first two components.
	This function is available only if [^N >= 2].
	>*/
	Vector<T, 3> xyz(void) const; /*<
	Returns a subvector with the first three components.
	This function is available only if [^N >= 3].
>*/
//]
//[oglplus_math_vector_ops
	Vector& operator += (const Vector& a);
	Vector& operator -= (const Vector& a);
	Vector& operator *= (T c);
	Vector& operator *= (const Vector& a); /*<
	Per-component multiplication.
>*/
	Vector& operator /= (T c);
//]
//[oglplus_math_vector_friend_ops
	friend Vector operator + (const Vector& a);
	friend Vector operator - (const Vector& a);
	friend Vector operator + (const Vector& a, const Vector& b);
	friend Vector operator - (const Vector& a, const Vector& b);
	friend Vector operator * (const Vector& a, T c);
	friend Vector operator * (T c, const Vector& a);
	friend Vector operator / (const Vector& a, T c);

	template <size_t Cols>
	friend Vector<T, Cols> operator * (const Vector& v, const __Matrix<T, N, Cols>& m); /*<
	__Vector __times__  __Matrix multiplication.
	>*/
	template <size_t Rows>
	friend Vector<T, Rows> operator * (const __Matrix<T, Rows, N>& m, const Vector& v); /*<
	__Matrix __times__  __Vector multiplication.
>*/
//]
//[oglplus_math_vector_fns
	Vector& operator Add(const Vector& a); /*<
	Adds [^a] to [^this].
	>*/
	Vector& operator Subtract(const Vector& a); /*<
	Subtracts [^a] from [^this].
	>*/
	Vector& operator MultiplyBy(T c); /*<
	Multiplies [^this] by [^c].
	>*/
	Vector& operator DivideBy(T c); /*<
	Divides [^this] by [^c].
>*/
//]
//[oglplus_math_vector_friend_fns
	friend Vector Negated(const Vector& a);
	friend Vector Added(const Vector& a, const Vector& b);
	friend Vector Subtracted(const Vector& a, const Vector& b);
	friend Vector Multiplied(const Vector& a, T c);
	friend Vector Divided(const Vector& a, T c);

	friend T Dot(const Vector& a, const Vector& b); /*<
	Dot product of two vectors.
	>*/
	friend T Length(const Vector& a); /*<
	The length (magnitude) of a vector.
	>*/
	friend T Distance(const Vector& a, const Vector& b); /*<
	The distance between two vectors.
	>*/

	friend Vector Normalized(Vector a); /*<
	Returns a normalized vector pointing in the same direction as the vector
	passed as argument.
>*/
//]
//[oglplus_math_vector_end
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

