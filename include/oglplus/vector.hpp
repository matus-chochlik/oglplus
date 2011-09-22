/**
 *  @file oglplus/vector.hpp
 *  @brief A vector class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_VECTOR_1107121519_HPP
#define OGLPLUS_VECTOR_1107121519_HPP

#include <cassert>
#include <cmath>
#include <type_traits>

namespace oglplus {

template <typename T, size_t Rows, size_t Cols>
class Matrix;

/// Basic template for vector types
/**
 *  @tparam T the coordinate value type
 *  @tparam N the dimension of the Vector
 *
 *  @see Matrix
 *
 *  @ingroup math_utils
 */
template <typename T, size_t N>
class Vector
{
private:
	T _elem[N];

	struct _op_negate
	{
		void operator()(Vector& t, const Vector& a)
		{
			for(size_t i=0; i!=N; ++i)
				t._elem[i] = -a._elem[i];
		}
	};

	struct _op_add
	{
		void operator()(Vector& t, const Vector& a, const Vector& b)
		{
			for(size_t i=0; i!=N; ++i)
				t._elem[i] = a._elem[i] + b._elem[i];
		}
	};

	struct _op_subtract
	{
		void operator()(Vector& t, const Vector& a, const Vector& b)
		{
			for(size_t i=0; i!=N; ++i)
				t._elem[i] = a._elem[i] - b._elem[i];
		}
	};

	struct _op_multiply
	{ };

	struct _op_mult_c
	{
		void operator()(Vector& t, const Vector& a, T v)
		{
			for(size_t i=0; i!=N; ++i)
				t._elem[i] = a._elem[i] * v;
		}
	};

	struct _op_perpend
	{
		static void _c(
			Vector<T, 2>& t,
			const Vector<T, 2>& a
		)
		{
			t._elem[0] = -a._elem[1];
			t._elem[1] =  a._elem[0];
		}

		static void _c(
			Vector<T, 3>& t,
			const Vector<T, 3>& a,
			const Vector<T, 3>& b
		)
		{
			t._elem[0] =
				a._elem[1] * b._elem[2]-
				a._elem[2] * b._elem[1];
			t._elem[1] =
				a._elem[2] * b._elem[0]-
				a._elem[0] * b._elem[2];
			t._elem[2] =
				a._elem[0] * b._elem[1]-
				a._elem[1] * b._elem[0];
		}

		template <size_t ... M>
		void operator()(Vector& t, const Vector<T, M>&... p)
		{
			_c(t, p...);
		}
	};

	template <typename Op>
	Vector(const Vector& a, Op init)
	{
		init(*this, a);
	}

	template <typename Op>
	Vector(const Vector& a, const Vector& b, Op init)
	{
		init(*this, a, b);
	}

	template <typename Op>
	Vector(const Vector& a, T v, Op init)
	{
		init(*this, a, v);
	}

	template <size_t Rows>
	inline Vector(
		const Vector<T, Rows>&,
		const Matrix<T, Rows, N>&,
		_op_multiply
	);

	template <size_t Cols>
	inline Vector(
		const Matrix<T, N, Cols>&,
		const Vector<T, Cols>&,
		_op_multiply
	);

	template <size_t I>
	inline void _init(T v)
	{
		static_assert(
			N == (I + 1),
			"Implementation error"
		);
		_elem[I] = v;
	}

	template <size_t I, typename ... P>
	inline void _init(T v, P ... p)
	{
		_elem[I] = v;
		_init<I + 1>(p...);
	}

public:
	/// Initializes the vector to [0, 0, ..., 0]
	Vector(void)
	{
		for(size_t i=0; i!=N; ++i)
			_elem[i] = 0;
	}

	/// Copy constructor
	Vector(const Vector&) = default;

	template <typename U>
	Vector(const Vector<U, N>& vector)
	{
		for(size_t i=0; i!=N; ++i)
			_elem[i] = T(vector.At(i));
	}

	Vector(const T* v, size_t n)
	{
		assert(n >= N);
		for(size_t i=0; i!=N; ++i)
			_elem[i] = v[i];
	}

	/// Initializes the vector with the given values
	/** Constructs a new N-dimensional vector from the values
	 *  passed as arguments. The number of arguments for this
	 *  constructor must match the vectors dimension.
	 */
	template <typename ... P>
	Vector(T v, P ... p)
	{
		static_assert(
			sizeof...(P) + 1 == N,
			"Invalid number of values for this vector type"
		);
		this->_elem = {v, T(p)...};
	}

	/// Initializes the vector from a sub-vector and additional coordinates
	template <size_t M, typename ... P>
	Vector(const Vector<T, M>& a, P ... p)
	{
		static_assert(
			M + sizeof...(P) == N,
			"Invalid number of additional values for this vector type"
		);
		for(size_t i=0; i!=M; ++i)
			_elem[i] = Data(a)[i];
		_init<M>(p...);
	}

	/// Construction from to Matrix-1xN
	template <size_t M>
	explicit inline Vector(
		const typename ::std::enable_if<
			(M == N && N > 1),
			Matrix<T, 1, M>
		>::type& matrix
	);
	/// Construction from to Matrix-Nx1
	template <size_t M>
	explicit inline Vector(
		const typename ::std::enable_if<
			(M == N && N > 1),
			Matrix<T, M, 1>
		>::type& matrix
	);

	/// Returns the dimension of the vector
	friend size_t Size(const Vector& a)
	{
		return N;
	}

	/// Returns the dimension of the vector
	static size_t Size(void)
	{
		return N;
	}

	/// Returns a pointer to an array containing the vectors coordinates
	friend const T* Data(const Vector& vector)
	{
		return vector._elem;
	}

	/// Returns the value of the I-th coordinate of the vector
	/**
	 *  @tparam I the index of the coordinate to be retrieved
	 *  @param a the vector from which the coordinate is retrieved
	 */
	template <size_t I>
	static T At(const Vector& a)
	{
		static_assert(I < N, "Index too high for this vector type");
		return a._elem[I];
	}

	/// Returns the value of the I-th coordinate of the vector with fallback
	/** This function returns either the value of the I-th cooordinate of
	 *  the vector if I is between 0 and N-1 or the fallback @c value
	 *  otherwise.
	 *
	 *  @tparam I the index of the coordinate to be retrieved
	 *  @param a the vector from which the coordinate is retrieved
	 *  @param value the fallback value if I is not between 0 and N-1
	 */
	template <size_t I>
	static T At(const Vector& a, T value)
	{
		if(I < N) return a._elem[I];
		else return value;
	}

	/// Returns the value of the I-th coordinate of the vector
	/**
	 *  @tparam I the index of the coordinate to be retrieved
	 */
	template <size_t I>
	T At(void) const
	{
		return Vector::At<I>(*this);
	}

	/// Returns the value of the I-th coordinate of the vector
	/**
	 *  @param i the index of the coordinate to be retrieved
	 */
	T At(size_t i) const
	{
		assert(i < N);
		return _elem[i];
	}


	/// Returns a reference to the I-th coordinate of the vector
	template <size_t I>
	static T& Ref(Vector& a)
	{
		static_assert(I < N, "Index too high for this vector type");
		return a._elem[I];
	}

	/// Equality comparison
	friend bool Equal(const Vector& a, const Vector& b)
	{
		for(size_t i=0; i!= N; ++i)
			if(a._elem[i] != b._elem[i])
				return false;
		return true;
	}

	/// Equality comparison operator
	friend bool operator == (const Vector& a, const Vector& b)
	{
		return Equal(a, b);
	}

	/// Inequality comparison operator
	friend bool operator != (const Vector& a, const Vector& b)
	{
		return !Equal(a, b);
	}

	/// Returns the vector passed as argument negated
	friend Vector Negated(const Vector& a)
	{
		return Vector(a, _op_negate());
	}

	/// Negation operator
	friend Vector operator - (const Vector& a)
	{
		return Negated(a);
	}

	/// Vector addition
	friend Vector Add(const Vector& a, const Vector& b)
	{
		return Vector(a, b, _op_add());
	}

	/// Vector addition operator
	friend Vector operator + (const Vector& a, const Vector& b)
	{
		return Add(a, b);
	}

	Vector& operator += (const Vector& v)
	{
		*this = Add(*this, v);
		return *this;
	}

	/// Vector subtration
	friend Vector Subtract(const Vector& a, const Vector& b)
	{
		return Vector(a, b, _op_subtract());
	}

	/// Vector subtration operator
	friend Vector operator - (const Vector& a, const Vector& b)
	{
		return Subtract(a, b);
	}

	/// Vector by Matrix multiplication
	template <size_t Cols>
	friend Vector<T, Cols> Multiply(
		const Vector& v,
		const Matrix<T, N, Cols>& m
	)
	{
		return Vector<T, Cols>(v, m, _op_multiply());
	}

	/// Vector by Matrix multiplication operator
	template <size_t Cols>
	friend Vector<T, Cols> operator * (
		const Vector& v,
		const Matrix<T, N, Cols>& m
	)
	{
		return Vector<T, Cols>(v, m, _op_multiply());
	}

	/// Matrix by Vector multiplication
	template <size_t Rows>
	friend Vector<T, Rows> Multiply(
		const Matrix<T, Rows, N>& m,
		const Vector& v
	)
	{
		return Vector<T, Rows>(m, v, _op_multiply());
	}

	/// Matrix by Vector multiplication operator
	template <size_t Rows>
	friend Vector<T, Rows> operator * (
		const Matrix<T, Rows, N>& m,
		const Vector& v
	)
	{
		return Vector<T, Rows>(m, v, _op_multiply());
	}

	/// Multiplication by a scalar value
	friend Vector Multiply(const Vector& a, T v)
	{
		return Vector(a, v, _op_mult_c());
	}

	/// Operator for multiplication by a scalar value
	friend Vector operator * (const Vector& a, T v)
	{
		return Multiply(a, v);
	}

	/// Operator for multiplication by a scalar value
	friend Vector operator * (T v, const Vector& a)
	{
		return Multiply(a, v);
	}

	Vector& operator *= (T v)
	{
		*this = Multiply(*this, v);
		return *this;
	}

	/// Dot product of two vectors
	friend T Dot(const Vector& a, const Vector& b)
	{
		T result = a._elem[0]*b._elem[0];
		for(size_t i=1; i!=N; ++i)
			result += a._elem[i] * b._elem[i];
		return result;
	}

	/// Cross product
	template <size_t ... M>
	friend Vector Cross(const Vector& v, const Vector<T, M>&... p)
	{
		return Vector(v, p..., _op_perpend());
	}

	/// Returns the length of a vector
	friend T Length(const Vector& a)
	{
		return std::sqrt(Dot(a, a));
	}

	/// Returns the distance between two vectors
	friend T Distance(const Vector& a, const Vector& b)
	{
		return Length(Subtract(a, b));
	}

	/// Returns a normalized version of the vector passed as argument
	friend Vector Normalized(const Vector& a)
	{
		T l = Length(a);
		if(l == T(0) || l == T(1)) return a;
		else return Multiply(a, T(1) / l);
	}

	/// Returns a vector composed from coordinates of this vector
	/** This function return a vector of arbitrary dimension composed
	 *  of the values of the coordinates of the vector passed as the
	 *  @c a argument. The coordinates to be picked are specified
	 *  by the @c Dims template parameter pack.
	 *
	 *  There are also named convenience extractor function like
	 *  xyz(), xxy(), zyx(), xy(), yz(), zz(), etc. allowing to get
	 *  2 and 3-dimensional subvectors composed of the x, y and z
	 *  coordinate of this vector.
	 *
	 *  For example:
	 *  @code
	 *  Vector<float, 4> v(1.0f, 2.0f, 3.0f, 4.0f);
	 *  Vector::Extract<0, 0, 0, 0>(v); // [1, 1, 1, 1]
	 *  Vector::Extract<2, 2, 2, 2>(v); // [3, 3, 3, 3]
	 *  Vector::Extract<1, 2, 3, 0>(v); // [2, 3, 4, 1]
	 *  Vector::Extract<3, 2, 1, 0>(v); // [4, 3, 2, 1]
	 *  Vector::Extract<1, 1, 2>(v);    // [2, 2, 3]
	 *  Vector::Extract<0, 1>(v);       // [1, 2]
	 *  v.xyz();                        // [1, 2, 3]
	 *  v.yyy();                        // [2, 2, 2]
	 *  v.xxz();                        // [1, 1, 3]
	 *  v.zy();                         // [3, 2]
	 *  @endcode
	 */
	template <size_t ... Dims>
	static Vector<T, sizeof...(Dims)> Extract(const Vector& a)
	{
		return Vector<T, sizeof...(Dims)>(At<Dims>(a)...);
	}

	/// Returns a vector composed from coordinates of this vector
	/** This function return a vector of arbitrary dimension composed
	 *  of the values of the coordinates of the vector passed as the
	 *  @c a argument. The coordinates to be picked are specified
	 *  by the @c Dims template parameter pack.
	 *
	 *  This overload of Extract allows to specify a fallback value
	 *  (0 by default) that is used instead of a coordinate where
	 *  the values of Dims are not between 0 and N-1.
	 *
	 *  There are also named convenience extractor function like
	 *  xyz(), x_y(), zy_(), x_(), yz(), zz(), etc. allowing to get
	 *  2 and 3-dimensional subvectors composed of the x, y and z
	 *  coordinate of this vector or the fallback value _.
	 *
	 *  For example:
	 *  @code
	 *  Vector<float, 4> v(1.0f, 2.0f, 3.0f, 4.0f);
	 *  Vector::Extract<0, 0, 0, 0>(v, 0.0f); // [1, 1, 1, 1]
	 *  Vector::Extract<0, 1, 2, 4>(v, 0.0f); // [1, 2, 3, 0]
	 *  Vector::Extract<2, 1, 0, 4>(v, 9.0f); // [3, 2, 1, 9]
	 *  v.xxx(0.0f);                          // [1, 1, 1]
	 *  v.x__();                              // [1, 0, 0]
	 *  v.x__(0.0f);                          // [1, 0, 0]
	 *  v.y__(0.0f);                          // [2, 0, 0]
	 *  v.y__(1.0f);                          // [2, 1, 1]
	 *  v.__z();                              // [0, 0, 3]
	 *  @endcode
	 */
	template <size_t ... Dims>
	static Vector<T, sizeof...(Dims)> Extract(const Vector& a, T v)
	{
		return Vector<T, sizeof...(Dims)>(At<Dims>(a, v)...);
	}

// include the subvector extraction functions
#include <oglplus/auxiliary/vector_extr.ipp>

	T x(void) const
	{
		return At<0>(*this);
	}

	T y(void) const
	{
		return At<1>(*this);
	}

	T z(void) const
	{
		return At<2>(*this);
	}

	// TODO:
	template <typename Out>
	void _print(Out& out) const
	{
		out << _elem[0];
		for(size_t i=1; i!=N; ++i)
		{
			out << ", " << _elem[i];
		}
	}
};

/// 1D float vector
/**
 *  @ingroup math_utils
 */
typedef Vector<GLfloat, 1> Vec1f;

/// 1D double-precision vector
/**
 *  @ingroup math_utils
 */
typedef Vector<GLdouble, 1> Vec1d;

/// 2D float vector
/**
 *  @ingroup math_utils
 */
typedef Vector<GLfloat, 2> Vec2f;

/// 2D double-precision vector
/**
 *  @ingroup math_utils
 */
typedef Vector<GLdouble, 2> Vec2d;

/// 3D float vector
/**
 *  @ingroup math_utils
 */
typedef Vector<GLfloat, 3> Vec3f;

/// 3D double-precision vector
/**
 *  @ingroup math_utils
 */
typedef Vector<GLdouble, 3> Vec3d;

/// 4D float vector
/**
 *  @ingroup math_utils
 */
typedef Vector<GLfloat, 4> Vec4f;

/// 4D double-precision vector
/**
 *  @ingroup math_utils
 */
typedef Vector<GLdouble, 4> Vec4d;

} // namespace oglplus

#endif // include guard
