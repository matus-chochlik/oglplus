/**
 *  @file oglplus/vector.hpp
 *  @brief A vector class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_VECTOR_1107121519_HPP
#define OGLPLUS_VECTOR_1107121519_HPP

#include <oglplus/config.hpp>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <algorithm>
#include <type_traits>

namespace oglplus {

template <typename T, std::size_t Rows, std::size_t Cols>
class Matrix;

template<typename T, std::size_t R, std::size_t C>
T At(const Matrix<T, R, C>&, std::size_t r, std::size_t c)
OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()));

template <typename T, std::size_t N>
class Vector;

/// 1D float (degenerate) vector
/**
 *  @ingroup math_utils
 */
typedef Vector<GLfloat, 1> Vec1f;

/// 1D double-precision (degenerate) vector
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


/// Common base class for vectors
template <typename T, std::size_t N>
class VectorBase
{
protected:
	T _elem[N];

	VectorBase(std::nullptr_t)
	OGLPLUS_NOEXCEPT(true)
	{ }

	VectorBase(void)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = T(0))
	{
		std::fill(_elem, _elem+N, T(0));
	}

	VectorBase(T v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		std::fill(_elem, _elem+N, v);
	}

	VectorBase(const T (&v)[N])
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		std::copy(v, v+N, _elem);
	}

	VectorBase(const T* v, std::size_t n)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		OGLPLUS_FAKE_USE(n);
		assert(n >= N);

		std::copy(v, v+N, _elem);
	}

	template <typename U>
	VectorBase(const VectorBase<U, N>& vector)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = T(std::declval<U>()))
	{
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] = T(vector.At(i));
	}

	explicit VectorBase(const Matrix<T, 1, N>& matrix)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] = At(matrix, 0, i);
	}

	template <std::size_t M>
	explicit VectorBase(
		const Matrix<T, M, 1>& matrix,
		typename std::enable_if<M != 1 && M == N, void>::type* = nullptr
	)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	{
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] = At(matrix, i, 0);
	}
public:
#if !OGLPLUS_NO_DEFAULTED_FUNCTIONS
	VectorBase(const VectorBase&) = default;

	VectorBase(VectorBase&&) = default;

	VectorBase& operator = (const VectorBase&) = default;

	VectorBase& operator = (VectorBase&&) = default;
#endif

	/// The size (the number of components) of this vector
	static OGLPLUS_CONSTEXPR std::size_t Size(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return N;
	}

	/// Pointer to the components of this vector
	const T* Data(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return this->_elem;
	}
	/// Access to the i-th component of this vector
	/**
	 *  @pre (i < Size())
	 */
	T At(std::size_t i) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		assert(i < N);
		return _elem[i];
	}

	/// Access to the i-th component of this vector with a fallback
	/** Similar to At(i), but returns @c fallback if @c i is
	 *  greater than or equal to Size().
	 */
	T At(std::size_t i, T fallback) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T>()))
	{
		if(i < N) return _elem[i];
		else return fallback;
	}

	/// Access to the i-th component of this vector
	/**
	 *  @pre (i < Size())
	 */
	T& operator [](std::size_t i)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(i < N);
		return _elem[i];
	}

	/// Const access to the i-th component of this vector
	/**
	 *  @pre (i < Size())
	 */
	const T& operator [](std::size_t i) const
	OGLPLUS_NOEXCEPT(true)
	{
		assert(i < N);
		return _elem[i];
	}

	/// Equality comparison
	friend bool Equal(const VectorBase& a, const VectorBase& b)
	OGLPLUS_NOEXCEPT_IF(std::declval<T>() != std::declval<T>())
	{
		for(std::size_t i=0; i!=N; ++i)
			if(a._elem[i] != b._elem[i])
				return false;
		return true;
	}

	/// Adds @p v to this vector
	void Add(const VectorBase& v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() += std::declval<T>())
	{
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] += v._elem[i];
	}

	/// Subtracts @p v from this vector
	void Subtract(const VectorBase& v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() -= std::declval<T>())
	{
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] -= v._elem[i];
	}

	/// Multiplies this vector by a scalar value
	void MultiplyBy(T v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() *= std::declval<T>())
	{
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] *= v;
	}

	/// Divides this vector by a scalar value
	void DivideBy(T v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() *= std::declval<T>())
	{
		for(std::size_t i=0; i!=N; ++i)
			_elem[i] /= v;
	}

	/// Computes the dot product of vectors @p a and @p b
	static T DotProduct(const VectorBase& a, const VectorBase& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		T result = (a._elem[0] * b._elem[0]);
		for(std::size_t i=1; i!=N; ++i)
			result += (a._elem[i] * b._elem[i]);
		return result;
	}
};


#include <oglplus/auxiliary/vector_1.ipp>
#include <oglplus/auxiliary/vector_2.ipp>
#include <oglplus/auxiliary/vector_3.ipp>
#include <oglplus/auxiliary/vector_4.ipp>

#if OGLPLUS_DOCUMENTATION_ONLY || !OGLPLUS_NO_VARIADIC_TEMPLATES
#include <oglplus/auxiliary/vector_n.ipp>
#endif

#include <oglplus/auxiliary/vector_swizzle.ipp>

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

template <typename T, std::size_t N>
inline T At(const Vector<T, N>& a, std::size_t i)
OGLPLUS_NOEXCEPT_IF(T(std::declval<T&>()))
{
	return a.At(i);
}

template <typename T, std::size_t N>
inline T At(const Vector<T, N>& a, std::size_t i, T fallback)
OGLPLUS_NOEXCEPT_IF(T(std::declval<T&>()))
{
	return a.At(i, fallback);
}

template <typename T, std::size_t N>
inline Vector<T, 1> Extract(
	const Vector<T, N>& a,
	std::size_t d0
)
{
	return Vector<T, 1>(a[d0]);
}

template <typename T, std::size_t N>
inline Vector<T, 2> Extract(
	const Vector<T, N>& a,
	std::size_t d0,
	std::size_t d1
)
{
	return Vector<T, 2>(a[d0], a[d1]);
}

template <typename T, std::size_t N>
inline Vector<T, 3> Extract(
	const Vector<T, N>& a,
	std::size_t d0,
	std::size_t d1,
	std::size_t d2
)
{
	return Vector<T, 3>(a[d0], a[d1], a[d2]);
}

template <typename T, std::size_t N>
inline Vector<T, 4> Extract(
	const Vector<T, N>& a,
	std::size_t d0,
	std::size_t d1,
	std::size_t d2,
	std::size_t d3
)
{
	return Vector<T, 4>(a[d0], a[d1], a[d2], a[d3]);
}

template <typename T, std::size_t N>
inline T Dot(const Vector<T, N>& a, const Vector<T, N>& b)
OGLPLUS_NOEXCEPT_IF(
	std::declval<T&>()=
	std::declval<T>()*std::declval<T>()+
	std::declval<T>()*std::declval<T>()
)
{
	return Vector<T, N>::DotProduct(a, b);
}

template <typename T, std::size_t N>
inline T Length(const Vector<T, N>& a)
OGLPLUS_NOEXCEPT(
	OGLPLUS_NOEXCEPT(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	) && OGLPLUS_NOEXCEPT(sqrt(std::declval<T>()))
)
{
	return std::sqrt(Dot(a, a));
}


template <typename T, std::size_t N>
inline T Distance(const Vector<T, N>& a, const Vector<T, N>& b)
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
	return Length(Subtracted(a, b));
}

template <typename T, std::size_t N>
inline Vector<T, N> Normalized(Vector<T, N> a)
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
		a = Multiplied(a, T(1) / l);
	return a;
}

template <typename T>
inline Vector<T, 2> Perpendicular(const Vector<T, 2>& a)
OGLPLUS_NOEXCEPT_IF(
	std::declval<T&>() =
	std::declval<T>()*std::declval<T>()-
	std::declval<T>()*std::declval<T>()
)
{
	return Vector<T, 2>(-a[1], a[0]);
}

template <typename T>
inline Vector<T, 3> Cross(const Vector<T, 3>& a, const Vector<T, 3>& b)
OGLPLUS_NOEXCEPT_IF(
	std::declval<T&>() =
	std::declval<T>()*std::declval<T>()-
	std::declval<T>()*std::declval<T>()
)
{
	return Vector<T, 3>(
		a[1] * b[2] - a[2] * b[1],
		a[2] * b[0] - a[0] * b[2],
		a[0] * b[1] - a[1] * b[0]
	);
}

template <typename T, std::size_t N>
inline bool operator == (const Vector<T, N>& a, const Vector<T, N>& b)
OGLPLUS_NOEXCEPT_IF(std::declval<T&>() == std::declval<T&>())
{
	return Equal(a, b);
}

template <typename T, std::size_t N>
inline bool operator != (const Vector<T, N>& a, const Vector<T, N>& b)
OGLPLUS_NOEXCEPT_IF(std::declval<T&>() != std::declval<T&>())
{
	return !Equal(a, b);
}

template <typename T, std::size_t N>
inline Vector<T, N> operator - (const Vector<T, N>& v)
OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = -std::declval<T>())
{
	return Negated(v);
}

template <typename T, std::size_t N>
inline Vector<T, N> operator + (const Vector<T, N>& a, const Vector<T, N>& b)
OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>() + std::declval<T>())
{
	return Added(a, b);
}

template <typename T, std::size_t N>
inline Vector<T, N> operator - (const Vector<T, N>& a, const Vector<T, N>& b)
OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>() - std::declval<T>())
{
	return Subtracted(a, b);
}

template <typename T, typename V, std::size_t N>
inline typename std::enable_if<
	std::is_convertible<V, T>::value,
	Vector<T, N>
>::type operator * (const Vector<T, N>& a, V v)
OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>() * T(std::declval<V>()))
{
	return Multiplied(a, T(v));
}

template <typename T, typename V, std::size_t N>
inline typename std::enable_if<
	std::is_convertible<V, T>::value,
	Vector<T, N>
>::type operator * (V v, const Vector<T, N>& a)
OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = T(std::declval<V>()) * std::declval<T>())
{
	return Multiplied(a, v);
}


template <typename T, typename V, std::size_t N>
inline typename std::enable_if<
	std::is_convertible<V, T>::value,
	Vector<T, N>
>::type operator / (const Vector<T, N>& a, V v)
OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>() / std::declval<T>())
{
	return Divided(a, v);
}

template <typename T, std::size_t N, std::size_t Cols>
inline Vector<T, Cols> operator * (
	const Vector<T, N>& v,
	const Matrix<T, N, Cols>& m
) OGLPLUS_NOEXCEPT(
	OGLPLUS_NOEXCEPT(
		std::declval<T&>() = std::declval<T>()*std::declval<T>()
	) && OGLPLUS_NOEXCEPT(std::declval<T&>() += std::declval<T>())
)
{
	T tmp[Cols];
	for(std::size_t c=0; c!=Cols; ++c)
	{
		tmp[c] = T(0);
		for(std::size_t r=0; r!=N; ++r)
		{
			tmp[c] += v.At(r) * m.At(r, c);
		}
	}
	return Vector<T, Cols>(tmp);
}

template <typename T, std::size_t N, std::size_t Rows>
inline Vector<T, Rows> operator * (
	const Matrix<T, Rows, N>& m,
	const Vector<T, N>& v
) OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>()* std::declval<T>())
{
	T tmp[Rows];
	for(std::size_t r=0; r!=Rows; ++r)
	{
		tmp[r] = T(0);
		for(std::size_t c=0; c!=N; ++c)
		{
			tmp[c] += m.At(r, c) * v.At(c);
		}
	}
	return Vector<T, Rows>(tmp);
}


} // namespace oglplus

#endif // include guard
