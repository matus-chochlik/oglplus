/**
 *  @file oglplus/vector.hpp
 *  @brief A vector class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_VECTOR_1107121519_HPP
#define OGLPLUS_VECTOR_1107121519_HPP

#include <oglplus/config.hpp>
#include <cassert>
#include <cstddef>
#include <cmath>
#include <type_traits>
#include <algorithm>

namespace oglplus {

template <typename T, std::size_t Rows, std::size_t Cols>
class Matrix;

template <typename T, std::size_t N>
class Vector;

/// Basic template for vector types
/**
 *  @tparam T the coordinate value type
 *  @tparam N the dimension of the Vector
 *
 *  @see Matrix
 *
 *  @ingroup math_utils
 */
template <typename T, std::size_t N>
class Vector
{
private:
	T _elem[N];

	struct _op_negate
	{
		void operator()(
			Vector& t,
			const Vector& a
		) const
		OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = -std::declval<T>())
		{
			for(std::size_t i=0; i!=N; ++i)
				t._elem[i] = -a._elem[i];
		}
	};

	struct _op_add
	{
		void operator()(
			Vector& t,
			const Vector& a,
			const Vector& b
		) const
		OGLPLUS_NOEXCEPT_IF(
			std::declval<T&>()=
			std::declval<T>()+
			std::declval<T>()
		)
		{
			for(std::size_t i=0; i!=N; ++i)
				t._elem[i] = a._elem[i] + b._elem[i];
		}
	};

	struct _op_subtract
	{
		void operator()(
			Vector& t,
			const Vector& a,
			const Vector& b
		) const
		OGLPLUS_NOEXCEPT_IF(
			std::declval<T&>()=
			std::declval<T>()-
			std::declval<T>()
		)
		{
			for(std::size_t i=0; i!=N; ++i)
				t._elem[i] = a._elem[i] - b._elem[i];
		}
	};

	struct _op_multiply
	{ };

	struct _op_mult_c
	{
		void operator()(
			Vector& t,
			const Vector& a,
			T v
		) const
		OGLPLUS_NOEXCEPT_IF(
			std::declval<T&>()=
			std::declval<T>()*
			std::declval<T>()
		)
		{
			for(std::size_t i=0; i!=N; ++i)
				t._elem[i] = a._elem[i] * v;
		}
	};

	struct _op_perpend
	{
		void operator()(
			Vector<T, 2>& t,
			const Vector<T, 2>& a
		) const
		OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = -std::declval<T>())
		{
			t._elem[0] = -a._elem[1];
			t._elem[1] =  a._elem[0];
		}

		void operator()(
			Vector<T, 3>& t,
			const Vector<T, 3>& a,
			const Vector<T, 3>& b
		) const
		OGLPLUS_NOEXCEPT_IF(
			std::declval<T&>() =
				std::declval<T>() * std::declval<T>()-
				std::declval<T>() * std::declval<T>()
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
	};

	template <typename Op>
	Vector(const Vector& a, Op init)
	OGLPLUS_NOEXCEPT_IF(init(
		std::declval<Vector&>(),
		std::declval<Vector>()
	))
	{
		init(*this, a);
	}

	template <typename Op>
	Vector(const Vector& a, const Vector& b, Op init)
	OGLPLUS_NOEXCEPT_IF(init(
		std::declval<Vector&>(),
		std::declval<Vector>(),
		std::declval<Vector>()
	))
	{
		init(*this, a, b);
	}

	template <typename Op>
	Vector(const Vector& a, T v, Op init)
	OGLPLUS_NOEXCEPT_IF(init(
		std::declval<Vector&>(),
		std::declval<Vector>(),
		std::declval<T>()
	))
	{
		init(*this, a, v);
	}

	template <std::size_t Rows>
	inline Vector(
		const Vector<T, Rows>&,
		const Matrix<T, Rows, N>&,
		_op_multiply
	) OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>() =
		std::declval<T>()*
		std::declval<T>()
	);

	template <std::size_t Cols>
	inline Vector(
		const Matrix<T, N, Cols>&,
		const Vector<T, Cols>&,
		_op_multiply
	) OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>() =
		std::declval<T>()*
		std::declval<T>()
	);

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <std::size_t I>
	inline void _init(T v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		static_assert(
			N == (I + 1),
			"Implementation error"
		);
		_elem[I] = v;
	}

	template <std::size_t I, typename ... P>
	inline void _init(T v, P ... p)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		_elem[I] = v;
		_init<I + 1>(p...);
	}
#endif

public:
	/// Initializes the vector to [0, 0, ..., 0]
	Vector(void)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = T(0))
	{
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] = T(0);
	}

#if !OGLPLUS_NO_DEFAULTED_FUNCTIONS
	/// Copy constructor
	Vector(const Vector& other) = default;

	/// Move constructor
	Vector(Vector&& tmp) = default;
#endif

	template <typename U>
	Vector(const Vector<U, N>& vector)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>() =
		T(std::declval<Vector<U, N> >().At(std::declval<std::size_t>()))
	)
	{
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] = T(vector.At(i));
	}

	Vector(const T* v, std::size_t n)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		OGLPLUS_FAKE_USE(n);
		assert(n >= N);
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] = v[i];
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Initializes the vector with the given values
	/** Constructs a new N-dimensional vector from the values
	 *  passed as arguments. The number of arguments for this
	 *  constructor must match the vectors dimension.
	 */
	template <typename ... P>
	Vector(T v, P ... p);
#endif

#if !OGLPLUS_NO_VARIADIC_TEMPLATES && \
	!OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX

	template <typename ... P>
	Vector(T v, P ... p)
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	 : _elem {v, T(p)...}
	{
		static_assert(
			sizeof...(P) + 1 == N,
			"Invalid number of values for this vector type"
		);
	}

#else

	Vector(T v0, T v1)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		static_assert(N == 2, "Invalid number of values for this vector type");
		_elem[0] = v0;
		_elem[1] = v1;
	}

	Vector(T v0, T v1, T v2)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		static_assert(N == 3, "Invalid number of values for this vector type");
		_elem[0] = v0;
		_elem[1] = v1;
		_elem[2] = v2;
	}

	Vector(T v0, T v1, T v2, T v3)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		static_assert(N == 4, "Invalid number of values for this vector type");
		_elem[0] = v0;
		_elem[1] = v1;
		_elem[2] = v2;
		_elem[3] = v3;
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Initializes the vector from a sub-vector and additional coordinates
	template <std::size_t M, typename ... P>
	Vector(const Vector<T, M>& a, P ... p);
#endif

#if !OGLPLUS_NO_VARIADIC_TEMPLATES

	template <std::size_t M, typename ... P>
	Vector(const Vector<T, M>& a, P ... p)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		static_assert(
			M + sizeof...(P) == N,
			"Invalid number of additional values for this vector type"
		);
		for(std::size_t i=0; i!=M; ++i)
			_elem[i] = a.Data()[i];
		_init<M>(p...);
	}
#else
	Vector(const Vector<T, 2>& a, T v2)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		static_assert(
			N == 3,
			"Invalid number of additional values for this vector type"
		);
		_elem[0] = a.Data()[0];
		_elem[1] = a.Data()[1];
		_elem[2] = v2;
	}

	template <typename T>
	Vector(const Vector<T, 2>& a, T v2, T v3)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		static_assert(
			N == 4,
			"Invalid number of additional values for this vector type"
		);
		_elem[0] = a.Data()[0];
		_elem[1] = a.Data()[1];
		_elem[2] = v2;
		_elem[2] = v3;
	}

	Vector(const Vector<T, 3>& a, T v3)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		static_assert(
			N == 4,
			"Invalid number of additional values for this vector type"
		);
		_elem[0] = a.Data()[0];
		_elem[1] = a.Data()[1];
		_elem[2] = a.Data()[2];
		_elem[3] = v3;
	}
#endif

	/// Construction from to Matrix-1xN
	template <std::size_t M>
	explicit inline Vector(
		const typename ::std::enable_if<
			(M == N && N > 1),
			Matrix<T, 1, M>
		>::type& matrix
	) OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>());

	/// Construction from to Matrix-Nx1
	template <std::size_t M>
	explicit inline Vector(
		const typename ::std::enable_if<
			(M == N && N > 1),
			Matrix<T, M, 1>
		>::type& matrix
	) OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>());

	Vector& operator = (const Vector& other)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		std::copy(other._elem, other._elem+N, this->_elem);
		return *this;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Returns the dimension of the vector
	friend OGLPLUS_CONSTEXPR std::size_t Size(const Vector& a);
#endif

	/// Returns the dimension of the vector
	static OGLPLUS_CONSTEXPR std::size_t Size(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return N;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Returns a pointer to an array containing the vectors coordinates
	friend const T* Data(const Vector& vector)
#endif

	/// Returns a pointer to an array containing the vectors coordinates
	const T* Data(void) const
	{
		return this->_elem;
	}

	/// Returns the value of the I-th coordinate of the vector
	/**
	 *  @tparam I the index of the coordinate to be retrieved
	 *  @param a the vector from which the coordinate is retrieved
	 */
	template <std::size_t I>
	static T At(const Vector& a)
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
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
	template <std::size_t I>
	static T At(const Vector& a, T value)
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		if(I < N) return a._elem[I];
		else return value;
	}

	/// Returns the value of the I-th coordinate of the vector
	/**
	 *  @tparam I the index of the coordinate to be retrieved
	 */
	template <std::size_t I>
	T At(void) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return Vector::At<I>(*this);
	}

	/// Returns the value of the I-th coordinate of the vector
	/**
	 *  @param i the index of the coordinate to be retrieved
	 */
	T At(std::size_t i) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		assert(i < N);
		return _elem[i];
	}


	/// Returns a reference to the I-th coordinate of the vector
	template <std::size_t I>
	static T& Ref(Vector& a)
	OGLPLUS_NOEXCEPT(true)
	{
		static_assert(I < N, "Index too high for this vector type");
		return a._elem[I];
	}

	/// Equality comparison
	friend bool Equal(const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(std::declval<T>() != std::declval<T>())
	{
		for(std::size_t i=0; i!= N; ++i)
			if(a._elem[i] != b._elem[i])
				return false;
		return true;
	}

	/// Equality comparison operator
	friend bool operator == (const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(Equal(
		std::declval<Vector>(),
		std::declval<Vector>()
	))
	{
		return Equal(a, b);
	}

	/// Inequality comparison operator
	friend bool operator != (const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(!Equal(
		std::declval<Vector>(),
		std::declval<Vector>()
	))
	{
		return !Equal(a, b);
	}

	/// Returns the vector passed as argument negated
	friend Vector Negated(const Vector& a)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = -std::declval<T>())
	{
		return Vector(a, _op_negate());
	}

	/// Negation operator
	friend Vector operator - (const Vector& a)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = -std::declval<T>())
	{
		return Negated(a);
	}

	/// Vector addition
	friend Vector Add(const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()+
		std::declval<T>()
	)
	{
		return Vector(a, b, _op_add());
	}

	/// Vector addition operator
	friend Vector operator + (const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()+
		std::declval<T>()
	)
	{
		return Add(a, b);
	}

	Vector& operator += (const Vector& v)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()+
		std::declval<T>()
	)
	{
		*this = Add(*this, v);
		return *this;
	}

	/// Vector subtration
	friend Vector Subtract(const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()-
		std::declval<T>()
	)
	{
		return Vector(a, b, _op_subtract());
	}

	/// Vector subtration operator
	friend Vector operator - (const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()-
		std::declval<T>()
	)
	{
		return Subtract(a, b);
	}

	/// Vector by Matrix multiplication
	template <std::size_t Cols>
	friend Vector<T, Cols> Multiply(
		const Vector& v,
		const Matrix<T, N, Cols>& m
	) OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		return Vector<T, Cols>(v, m, _op_multiply());
	}

	/// Vector by Matrix multiplication operator
	template <std::size_t Cols>
	friend Vector<T, Cols> operator * (
		const Vector& v,
		const Matrix<T, N, Cols>& m
	) OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		return Vector<T, Cols>(v, m, _op_multiply());
	}

	/// Matrix by Vector multiplication
	template <std::size_t Rows>
	friend Vector<T, Rows> Multiply(
		const Matrix<T, Rows, N>& m,
		const Vector& v
	) OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		return Vector<T, Rows>(m, v, _op_multiply());
	}

	/// Matrix by Vector multiplication operator
	template <std::size_t Rows>
	friend Vector<T, Rows> operator * (
		const Matrix<T, Rows, N>& m,
		const Vector& v
	) OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		return Vector<T, Rows>(m, v, _op_multiply());
	}

	/// Multiplication by a scalar value
	friend Vector Multiply(const Vector& a, T v)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		return Vector(a, v, _op_mult_c());
	}

	/// Operator for multiplication by a scalar value
	friend Vector operator * (const Vector& a, T v)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		return Multiply(a, v);
	}

	/// Operator for multiplication by a scalar value
	friend Vector operator * (T v, const Vector& a)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		return Multiply(a, v);
	}

	Vector& operator *= (T v)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		*this = Multiply(*this, v);
		return *this;
	}

	/// Dot product of two vectors
	friend T Dot(const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		T result = a._elem[0]*b._elem[0];
		for(std::size_t i=1; i!=N; ++i)
			result += a._elem[i] * b._elem[i];
		return result;
	}

	template <std::size_t M>
	friend typename ::std::enable_if<M==2 && N==2, Vector>::type
	Perpendicular(const Vector<T, M>& a)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>() =
			std::declval<T>() * std::declval<T>()-
			std::declval<T>() * std::declval<T>()
	)
	{
		return Vector(a, _op_perpend());
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Cross product
	friend Vector Cross(const Vector<T, 3>& a, const Vector<T, 3>& b);
#endif

	template <std::size_t M>
	friend typename ::std::enable_if<M==3 && N==3, Vector>::type
	Cross(const Vector<T, M>& a, const Vector<T, M>& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>() =
			std::declval<T>() * std::declval<T>()-
			std::declval<T>() * std::declval<T>()
	)
	{
		return Vector(a, b, _op_perpend());
	}

	/// Returns the length of a vector
	friend T Length(const Vector& a)
	OGLPLUS_NOEXCEPT(
		OGLPLUS_NOEXCEPT(
			std::declval<T&>()=
			std::declval<T>()*
			std::declval<T>()
		) && OGLPLUS_NOEXCEPT(sqrt(std::declval<T>()))
	)
	{
		return sqrt(Dot(a, a));
	}

	/// Returns the distance between two vectors
	friend T Distance(const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT(
		OGLPLUS_NOEXCEPT(
			std::declval<T&>()=
			std::declval<T>()-
			std::declval<T>()
		) && OGLPLUS_NOEXCEPT(
			std::declval<T&>()=
			std::declval<T>()*
			std::declval<T>()
		) && OGLPLUS_NOEXCEPT(sqrt(std::declval<T>()))
	)
	{
		return Length(Subtract(a, b));
	}

	/// Returns a normalized version of the vector passed as argument
	friend Vector Normalized(Vector a)
	OGLPLUS_NOEXCEPT(
		OGLPLUS_NOEXCEPT(
			std::declval<T&>()=
			std::declval<T>()-
			std::declval<T>()
		) && OGLPLUS_NOEXCEPT(
			std::declval<T&>()=
			std::declval<T>()*
			std::declval<T>()
		) && OGLPLUS_NOEXCEPT(
			std::declval<T>()!=
			std::declval<T>()
		) && OGLPLUS_NOEXCEPT(sqrt(std::declval<T>()))
	)
	{
		T l = Length(a);
		if(l != T(0) && l != T(1))
			a = Multiply(a, T(1) / l);
		return a;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
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
	template <std::size_t ... Dims>
	static Vector<T, sizeof...(Dims)> Extract(const Vector<T, N>& a);
#endif

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <std::size_t ... Dims>
	static Vector<T, sizeof...(Dims)> Extract(const Vector<T, N>& a)
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return Vector<T, sizeof...(Dims)>(At<Dims>(a)...);
	}
#else
	template <std::size_t D0, std::size_t D1>
	static Vector<T, 2> Extract(const Vector<T, N>& a)
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return Vector<T, 2>(At<D0>(a), At<D1>(a));
	}

	template <std::size_t D0, std::size_t D1, std::size_t D2>
	static Vector<T, 3> Extract(const Vector<T, N>& a)
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return Vector<T, 3>(At<D0>(a), At<D1>(a), At<D2>(a));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
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
	template <std::size_t ... Dims>
	static Vector<T, sizeof...(Dims)> Extract(const Vector<T, N>& a, T v);
#endif

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <std::size_t ... Dims>
	static Vector<T, sizeof...(Dims)> Extract(const Vector<T, N>& a, T v)
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return Vector<T, sizeof...(Dims)>(At<Dims>(a, v)...);
	}
#else
	template <std::size_t D0, std::size_t D1>
	static Vector<T, 2> Extract(const Vector<T, N>& a, T v)
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return Vector<T, 2>(At<D0>(a, v), At<D1>(a, v));
	}

	template <std::size_t D0, std::size_t D1, std::size_t D2>
	static Vector<T, 3> Extract(const Vector<T, N>& a, T v)
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return Vector<T, 3>(At<D0>(a, v), At<D1>(a, v), At<D2>(a, v));
	}
#endif

// include the subvector extraction functions
#include <oglplus/auxiliary/vector_extr.ipp>

	T x(void) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return At<0>(*this);
	}

	T y(void) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return At<1>(*this);
	}

	T z(void) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return At<2>(*this);
	}

	T w(void) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		return At<3>(*this);
	}

	// TODO:
	template <typename Out>
	void _print(Out& out) const
	{
		out << _elem[0];
		for(std::size_t i=1; i!=N; ++i)
		{
			out << ", " << _elem[i];
		}
	}
};

template <typename T, std::size_t N>
inline const T* Data(const Vector<T, N>& a)
OGLPLUS_NOEXCEPT(true)
{
	return a.Data();
}

template <typename T, std::size_t N>
inline OGLPLUS_CONSTEXPR std::size_t Size(const Vector<T, N>&)
OGLPLUS_NOEXCEPT(true)
{
	return N;
}

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
