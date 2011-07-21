/**
 *  @file oglplus/matrix.hpp
 *  @brief A matrix class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_MATRIX_1107121519_HPP
#define OGLPLUS_MATRIX_1107121519_HPP

#include <oglplus/vector.hpp>
#include <cassert>
#include <cmath>

namespace oglplus {

/// Basic template for matrix types
/**
 *  @tparam T the matrix element value type
 *  @tparam Rows the number of rows of the matrix
 *  @tparam Cols the number of columns of the matrix
 */
template <typename T, size_t Rows, size_t Cols>
class Matrix
{
private:
	static const Matrix& _that(void);

	union {
		T _data[Rows * Cols];
		T _elem[Rows][Cols];
	} _m;

	static_assert(
		sizeof(_that()._m) == sizeof(_that()._m._data) &&
		sizeof(_that()._m) == sizeof(_that()._m._elem),
		"Matrix implementation error"
	);

	struct _op_negate
	{
		void operator()(Matrix& t, const Matrix& a)
		{
			for(size_t i=0; i!=Rows; ++i)
			for(size_t j=0; j!=Cols; ++j)
				t._m._elem[i][j] = -a._m._elem[i][j];
		}
	};

	struct _op_add
	{
		void operator()(Matrix& t, const Matrix& a, const Matrix& b)
		{
			for(size_t i=0; i!=Rows; ++i)
			for(size_t j=0; j!=Cols; ++j)
				t._m._elem[i][j] =
					a._m._elem[i][j]+
					b._m._elem[i][j];
		}
	};

	struct _op_subtract
	{
		void operator()(Matrix& t, const Matrix& a, const Matrix& b)
		{
			for(size_t i=0; i!=Rows; ++i)
			for(size_t j=0; j!=Cols; ++j)
				t._m._elem[i][j] =
					a._m._elem[i][j]-
					b._m._elem[i][j];
		}
	};

	struct _op_mult_c
	{
		void operator()(Matrix& t, const Matrix& a, const T& v)
		{
			for(size_t i=0; i!=Rows; ++i)
			for(size_t j=0; j!=Cols; ++j)
				t._m._elem[i][j] = a._m._elem[i][j] * v;
		}
	};

	struct _op_transpose
	{
		void operator()(Matrix& t, const Matrix& a)
		{
			for(size_t i=0; i!=Rows; ++i)
			for(size_t j=0; j!=Cols; ++j)
				t._m._elem[i][j] = a._m._elem[j][i];
		}
	};

	struct _op_translate
	{
		void operator()(Matrix& t, const Matrix& a, const T* dv)
		{
			if(&t != &a) t = a;
			for(size_t i=0; i!=(Rows-1); ++i)
				t._m._elem[i][Cols-1] =
					a._m._elem[i][Cols-1] + dv[i];
		}
	};

	struct _op_scale
	{
		void operator()(Matrix& t, const Matrix& a, const T* dv)
		{
			if(&t != &a) t = a;
			for(size_t i=0; i!=(Rows-1) && i!=(Cols-1); ++i)
				t._m._elem[i][i] =
					a._m._elem[i][i] * dv[i];
		}
	};

	struct _op_multiply
	{ };

	template <typename Op>
	inline Matrix(const Matrix& a, Op init)
	{
		init(*this, a);
	}

	template <typename Op>
	inline Matrix(const Matrix& a, T v, Op init)
	{
		init(*this, a, v);
	}

	template <typename Op>
	inline Matrix(const Matrix& a, const T* dv, Op init)
	{
		init(*this, a, dv);
	}

	template <typename Op>
	inline Matrix(const Matrix& a, const Matrix& b, Op init)
	{
		init(*this, a, b);
	}

	inline Matrix(const Matrix<T, Cols, Rows>& a, _op_transpose init)
	{
		init(*this, a);
	}

	template <size_t N>
	inline Matrix(
		const Matrix<T, Rows, N>& a,
		const Matrix<T, N, Cols>& b,
		_op_multiply,
		_op_multiply
	)
	{
		for(size_t i=0; i!=Rows; ++i)
		for(size_t j=0; j!=Cols; ++j)
		{
			_m._elem[i][j] = a.At(i, 0)* b.At(0, j);
			for(size_t k=1; k!=N; ++k)
				_m._elem[i][j] += a.At(i, k)* b.At(k, j);
		}
	}

	inline Matrix(T* data, size_t size)
	{
		assert(size == Rows*Cols);
		for(size_t k=0; k!=Rows*Cols; ++k)
			_m._data[k] = data[k];
	}

	template <size_t I, size_t J>
	inline void _init(T v)
	{
		static_assert(
			Rows * Cols == (I + 1) * (J + 1),
			"Implementation error"
		);
		_m._elem[I][J] = v;
	}

	template <size_t I, size_t J, typename ... P>
	inline void _init(T v, P ... p)
	{
		_m._elem[I][J] = v;
		_init<I + (J + 1) / Cols, (J + 1) % Cols>(p...);
	}

	friend class Vector<T, Rows>;
	friend class Vector<T, Cols>;
public:
	/// Constructs a identity matrix
	Matrix(void)
	{
		for(size_t i=0; i!=Rows; ++i)
		for(size_t j=0; j!=Cols; ++j)
			_m._elem[i][j] = (i == j ? 1 : 0);
	}

	/// Initializing constructor
	/** Allows to explicitly initialize all elements of the matrix.
	 *  The number of parameters of this constructor must be Rows * Cols.
	 */
	template <typename ... P>
	Matrix(T v, P ... p)
	{
		static_assert(
			Rows * Cols == sizeof...(P) + 1,
			"Invalid number of elements for this matrix type"
		);
		_init<0, 0>(v, p...);
	}

	/// Equality comparison function
	friend bool Equal(const Matrix& a, const Matrix& b)
	{
		for(size_t i=0; i!=Rows; ++i)
		for(size_t j=0; j!=Cols; ++j)
			if(a._m._elem[i][j] != b._m._elem[i][j])
				return false;
		return true;
	}

	/// Equality comparison operator
	friend bool operator == (const Matrix& a, const Matrix& b)
	{
		return Equal(a, b);
	}

	/// Inequality comparison operator
	friend bool operator != (const Matrix& a, const Matrix& b)
	{
		return !Equal(a, b);
	}

	/// Returns the value of the element at position I,J
	template <size_t I, size_t J>
	friend T At(const Matrix& matrix)
	{
		static_assert(
			I < Rows &&
			J < Cols,
			"Invalid value of I or J for this matrix type"
		);
		return matrix._m._elem[I][J];
	}

	/// Returns the value of the element at position I,J
	template <size_t I, size_t J>
	T At(void) const 
	{
		return At(*this);
	}

	/// Returns the value of the element at position i,j
	T At(size_t i, size_t j) const
	{
		assert(i < Rows && j < Cols);
		return _m._elem[i][j];
	}

	/// Element negation function
	friend Matrix Negated(const Matrix& a)
	{
		return Matrix(a, _op_negate());
	}

	/// Element negation operator
	friend Matrix operator - (const Matrix& a)
	{
		return Negated(a);
	}

	/// Matrix addition
	friend Matrix Add(const Matrix& a, const Matrix& b)
	{
		return Matrix(a, b, _op_add());
	}

	/// Matrix addition operator
	friend Matrix operator + (const Matrix& a, const Matrix& b)
	{
		return Add(a, b);
	}

	/// Matrix subtraction
	friend Matrix Subtract(const Matrix& a, const Matrix& b)
	{
		return Matrix(a, b, _op_subtract());
	}

	/// Matrix subtraction operator
	friend Matrix operator - (const Matrix& a, const Matrix& b)
	{
		return Subtract(a, b);
	}

	/// Matrix multiplication
	template <size_t N>
	friend Matrix Multiply(
		const Matrix<T, Rows, N>& a,
		const Matrix<T, N, Cols>& b
	)
	{
		return Matrix(a, b, _op_multiply(), _op_multiply());
	}

	/// Matrix multiplication operator
	template <size_t N>
	friend Matrix operator * (
		const Matrix<T, Rows, N>& a,
		const Matrix<T, N, Cols>& b
	)
	{
		return Multiply(a, b);
	}

	/// Multiplication by scalar value
	friend Matrix Multiply(const Matrix& a, T m)
	{
		return Matrix(a, m, _op_mult_c());
	}

	/// Multiplication by scalar value operator
	friend Matrix operator * (const Matrix& a, T m)
	{
		return Multiply(a, m);
	}

	/// Multiplication by scalar value operator
	friend Matrix operator * (T m, const Matrix& a)
	{
		return Multiply(a, m);
	}

	/// Matrix transposition
	friend Matrix Transposed(const Matrix<T, Cols, Rows>& a)
	{
		return Matrix(a, _op_transpose());
	}

	template <typename ... P>
	friend Matrix Translation(const Matrix& a, P ... p)
	{
		static_assert(
			sizeof...(P) == Rows - 1 &&
			sizeof...(P) == Cols - 1,
			"Invalid number of values for translation"
		);
		T v[Rows-1] = {T(p)...};
		return Matrix(a, v, _op_translate());
	}

	template <typename ... P>
	friend Matrix Scale(const Matrix& a, P ... p)
	{
		static_assert(
			sizeof...(P) == Rows - 1 &&
			sizeof...(P) == Cols - 1,
			"Invalid number of values for scale"
		);
		T v[Rows-1] = {T(p)...};
		return Matrix(a, v, _op_scale());
	}

	/// Returns a vector containing the matrix elements in row major order
	friend const T* Data(const Matrix& matrix)
	{
		return matrix._m._data;
	}

	// TODO:
	template <typename Out>
	void _print(Out& out) const
	{
		for(size_t i=0; i!=Rows; ++i)
		{
			out << "|" << _m._elem[i][0];
			for(size_t j=1; j!= Cols; ++j)
				out << ", " << _m._elem[i][j];
			out << "|\n";
		}
	}
};

/// 4x4 float matrix
typedef Matrix<GLfloat, 4, 4> TransformMatrix;
/// 4x4 double-precision matrix
typedef Matrix<GLdouble, 4, 4> TransformMatrixd;


// implementation of Vector's constructors, conversions and operations
template <typename T, size_t N>
Vector<T, N>::Vector(const Matrix<T, 1, N>& matrix)
{
	for(size_t i=0; i!=N; ++i)
		_elem[i] = matrix._m._elem[0][i];
}

template <typename T, size_t N>
Vector<T, N>::Vector(const Matrix<T, N, 1>& matrix)
{
	for(size_t i=0; i!=N; ++i)
		_elem[i] = matrix._m._elem[i][0];
}

template <typename T, size_t N>
template <size_t Rows>
Vector<T, N>::Vector(
	const Vector<T, Rows>& v,
	const Matrix<T, Rows, N>& m,
	_op_multiply
)
{
	for(size_t j=0; j!=N; ++j)
	{
		_elem[j] = v._elem[0]*m._m._elem[0][j];
		for(size_t i=1; i!=Rows; ++i)
			_elem[j] += v._elem[i]*m._m._elem[i][j];
	}
}

template <typename T, size_t N>
template <size_t Cols>
Vector<T, N>::Vector(
	const Matrix<T, N, Cols>& m,
	const Vector<T, Cols>& v,
	_op_multiply
)
{
	for(size_t i=0; i!=N; ++i)
	{
		_elem[i] = m._m._elem[i][0]*v._elem[0];
		for(size_t j=1; j!=Cols; ++j)
			_elem[i] += m._m._elem[i][j]*v._elem[j];
	}
}

} // namespace oglplus

#endif // include guard
