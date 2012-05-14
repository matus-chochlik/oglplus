/**
 *  @file oglplus/matrix.hpp
 *  @brief A matrix class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_MATRIX_1107121519_HPP
#define OGLPLUS_MATRIX_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/angle.hpp>

#if !OGLPLUS_NO_INITIALIZER_LISTS
#include <initializer_list>
#endif

#include <algorithm>

#include <cassert>
#include <cmath>

namespace oglplus {

/// Basic template for matrix types
/**
 *  @tparam T the matrix element value type
 *  @tparam Rows the number of rows of the matrix
 *  @tparam Cols the number of columns of the matrix
 *
 *  @ingroup math_utils
 */
template <typename T, size_t Rows, size_t Cols>
class Matrix
{
private:
	static const Matrix& _that(void);

protected:
	union {
		T _data[Rows * Cols];
		T _elem[Rows][Cols];
	} _m;
private:

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

	struct _op_multiply { };

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

	template <size_t R>
	inline void _init_row(const Vector<T, Cols>& row)
	{
		for(size_t c=0; c!=Cols; ++c)
			this->_m._elem[R][c] = row.At(c);
	}

	template <size_t R>
	inline void _init_rows(void) const
	{ }

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <size_t R, size_t ... C>
	inline void _init_rows(
		const Vector<T, Cols>& row,
		const Vector<T, C>&... rows
	)
	{
		_init_row<R>(row);
		_init_rows<R+1>(rows...);
	}
#else
	inline void _init_rows(
		const Vector<T, Cols>& row0,
		const Vector<T, Cols>& row1
	)
	{
		static_assert(
			Rows == 2,
			"Invalid number of rows for this matrix type"
		);
		_init_row<0>(row0);
		_init_row<1>(row1);
	}

	inline void _init_rows(
		const Vector<T, Cols>& row0,
		const Vector<T, Cols>& row1,
		const Vector<T, Cols>& row2
	)
	{
		static_assert(
			Rows == 3,
			"Invalid number of rows for this matrix type"
		);
		_init_row<0>(row0);
		_init_row<1>(row1);
		_init_row<2>(row2);
	}

	inline void _init_rows(
		const Vector<T, Cols>& row0,
		const Vector<T, Cols>& row1,
		const Vector<T, Cols>& row2,
		const Vector<T, Cols>& row3
	)
	{
		static_assert(
			Rows == 4,
			"Invalid number of rows for this matrix type"
		);
		_init_row<0>(row0);
		_init_row<1>(row1);
		_init_row<2>(row2);
		_init_row<3>(row3);
	}
#endif

	friend class Vector<T, Rows>;
	friend class Vector<T, Cols>;


#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <typename X>
	static void _eat(const X&...)
	{ }
#endif

protected:


#if !OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX && \
	!OGLPLUS_NO_INITIALIZER_LISTS
	void _init_data(std::initializer_list<T> data)
	{
		std::copy(data.begin(), data.end(), this->_m._data);
	}
#define OGLPLUS_AUX_MATRIX_INIT_DATA(...) \
	this->_init_data(__VA_ARGS__);
#else
	void _init_data(const T* data, size_t size)
	{
		std::copy(data, data+size, this->_m._data);
	}
#define OGLPLUS_AUX_MATRIX_INIT_DATA(...) \
	const T __LINE__ ## data[] = __VA_ARGS__; \
	this->_init_data( \
		__LINE__ ## data, \
		sizeof(__LINE__ ## data)/  \
		sizeof(__LINE__ ## data[0])\
	);
#endif

public:
	struct NoInit { };

	/// Constructs an uninitialized matrix
	Matrix(NoInit)
	{ }

	struct Zero { };

	/// Constructs zero a matrix
	Matrix(Zero)
	{
		for(size_t r=0; r!=Rows; ++r)
			for(size_t c=0; c!=Cols; ++c)
				this->_m._elem[r][c] = T(0);
	}

	/// Constructs a identity matrix
	Matrix(void)
	{
		for(size_t r=0; r!=Rows; ++r)
			for(size_t c=0; c!=Cols; ++c)
				this->_m._elem[r][c] = r == c ? T(1) : T(0);
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Initializing constructor
	/** Allows to explicitly initialize all elements of the matrix.
	 *  The number of parameters of this constructor must be Rows * Cols.
	 */
	template <typename ... P>
	Matrix(T v, P ... p);
#endif

#if !OGLPLUS_NO_VARIADIC_TEMPLATES && \
	!OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX
	template <typename ... P>
	Matrix(T v, P ... p)
	{
		static_assert(
			Rows * Cols == sizeof...(P) + 1,
			"Invalid number of elements for this matrix type"
		);
		OGLPLUS_AUX_MATRIX_INIT_DATA({v, T(p)...});
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Initializing from row vectors
	/** Allows to initialize all rows of the matrix from individual
	 *  vectors. The number of vectors must be Rows and each vector
	 *  must have exactly Cols elements.
	 */
	template <size_t ... C>
	Matrix(const Vector<T, C>& ... rows);
#endif

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <size_t ... C>
	Matrix(const Vector<T, C>& ... rows)
	{
		static_assert(
			sizeof...(C) == Rows,
			"Invalid number of rows for this matrix type"
		);
		this->_init_rows<0>(rows...);
	}
#else
	Matrix(
		const Vector<T, Cols>& row0,
		const Vector<T, Cols>& row1
	)
	{
		this->_init_rows(row0, row1);
	}

	Matrix(
		const Vector<T, Cols>& row0,
		const Vector<T, Cols>& row1,
		const Vector<T, Cols>& row2
	)
	{
		this->_init_rows(row0, row1, row2);
	}

	Matrix(
		const Vector<T, Cols>& row0,
		const Vector<T, Cols>& row1,
		const Vector<T, Cols>& row2,
		const Vector<T, Cols>& row3
	)
	{
		this->_init_rows(row0, row1, row2, row3);
	}
#endif

	template <size_t I, size_t J, size_t R, size_t C>
	Matrix(
		std::integral_constant<size_t, I>,
		std::integral_constant<size_t, J>,
		const Matrix<T, R, C>& source
	)
	{
		static_assert(I+Rows <= R, "Invalid row for this matrix type");
		static_assert(J+Cols <= C, "Invalid column for this matrix type");
		for(size_t i=0; i!=Rows; ++i)
			for(size_t j=0; j!=Cols; ++j)
				this->_m._elem[i][j] = source.At(I+i, J+j);
	}

	/// Returns a vector containing the matrix elements in row major order
	friend const T* Data(const Matrix& matrix)
	{
		return matrix._m._data;
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
	friend T ElementAt(const Matrix& matrix)
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
		static_assert(
			I < Rows &&
			J < Cols,
			"Invalid value of I or J for this matrix type"
		);
		return this->_m._elem[I][J];
	}

	/// Returns the value of the element at position i,j
	T At(size_t i, size_t j) const
	{
		assert((i < Rows) && (j < Cols));
		return this->_m._elem[i][j];
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

	/// Swaps two rows of the Matrix
	friend Matrix& RowSwap(Matrix& m, size_t a, size_t b)
	{
		assert(a < Rows);
		assert(b < Rows);
		::std::swap_ranges(
			m._m._elem[a],
			m._m._elem[a]+Cols,
			m._m._elem[b]
		);
		return m;
	}

	/// Multiplies row @a i with coeficient @a k
	friend Matrix& RowMultiply(Matrix& m, size_t i, T k)
	{
		assert(i < Rows);
		for(size_t j=0; j!=Cols; ++j)
			m._m._elem[i][j] *= k;
		return m;
	}

	/// Adds row @a b multipled by coeficient @a k to row @a a
	friend Matrix RowAdd(Matrix& m, size_t a, size_t b, T k)
	{
		assert(a < Rows);
		assert(b < Rows);
		for(size_t j=0; j!=Cols; ++j)
			m._m._elem[a][j] += m._m._elem[b][j] * k;
		return m;
	}

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <size_t ... C>
	friend bool Gauss(Matrix& a, Matrix<T, Rows, C>&... b)
	{
		const T zero(0), one(1);
		for(size_t i=0; i!=Rows; ++i)
		{
			T d = a._m._elem[i][i];
			if(d == zero)
			{
				for(size_t k=i+1; k!=Rows; ++k)
				{
					if(a._m._elem[k][i] != zero)
					{
						RowSwap(a, i, k);
						_eat(RowSwap(b, i, k)...);
						break;
					}
				}
				d = a._m._elem[i][i];
			}
			if(d == zero) return false;

			RowMultiply(a, i, one / d);
			_eat(RowMultiply(b, i, one / d)...);

			for(size_t k=i+1; k!=Rows; ++k)
			{
				T c = a._m._elem[k][i];
				if(c != zero)
				{
					RowAdd(a, k, i, -c);
					_eat(RowAdd(b, k, i, -c)...);
				}
			}
		}
		return true;
	}
#else
	template <size_t C>
	friend bool Gauss(Matrix& a, Matrix<T, Rows, C>& b)
	{
		const T zero(0), one(1);
		for(size_t i=0; i!=Rows; ++i)
		{
			T d = a._m._elem[i][i];
			if(d == zero)
			{
				for(size_t k=i+1; k!=Rows; ++k)
				{
					if(a._m._elem[k][i] != zero)
					{
						RowSwap(a, i, k);
						RowSwap(b, i, k);
						break;
					}
				}
				d = a._m._elem[i][i];
			}
			if(d == zero) return false;

			RowMultiply(a, i, one / d);
			RowMultiply(b, i, one / d);

			for(size_t k=i+1; k!=Rows; ++k)
			{
				T c = a._m._elem[k][i];
				if(c != zero)
				{
					RowAdd(a, k, i, -c);
					RowAdd(b, k, i, -c);
				}
			}
		}
		return true;
	}
#endif

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <size_t ... C>
	friend bool GaussJordan(Matrix& a, Matrix<T, Rows, C>&... b)
	{
		if(!Gauss(a, b...)) return false;
		const T zero(0);
		for(size_t i=Rows-1; i!=0; --i)
		{
			for(size_t k=0; k!=i; ++k)
			{
				T c = a._m._elem[k][i];
				if(c != zero)
				{
					RowAdd(a, k, i, -c);
					_eat(RowAdd(b, k, i, -c)...);
				}
			}
		}
		return true;
	}
#else
	template <size_t  C>
	friend bool GaussJordan(Matrix& a, Matrix<T, Rows, C>& b)
	{
		if(!Gauss(a, b)) return false;
		const T zero(0);
		for(size_t i=Rows-1; i!=0; --i)
		{
			for(size_t k=0; k!=i; ++k)
			{
				T c = a._m._elem[k][i];
				if(c != zero)
				{
					RowAdd(a, k, i, -c);
					RowAdd(b, k, i, -c);
				}
			}
		}
		return true;
	}
#endif

	/// Finds inverse matrix if m is square matrix and T supports fractions
	friend Matrix Inverse(Matrix m)
	{
		Matrix i;
		if(GaussJordan(m, i)) return i;
		else return Matrix(Zero());
	}

	template <size_t I>
	Vector<T, Cols> Row(void) const
	{
		static_assert(I < Rows, "Invalid index for this matrix");
		return Vector<T, Cols>(this->_m._elem[I], Cols);
	}

	/// Row vector getter
	template <size_t I>
	friend Vector<T, Cols> Row(const Matrix& m)
	{
		return m.template Row<I>();
	}

	template <size_t J>
	Vector<T, Rows> Col(void) const
	{
		static_assert(J < Cols, "Invalid index for this matrix");
		T v[Rows];
		for(size_t i=0; i!= Rows; ++i)
			v[i] = this->_m._elem[i][J];
		return Vector<T, Rows>(v, Rows);
	}

	/// Column vector getter
	template <size_t J>
	friend Vector<T, Rows> Col(const Matrix& m)
	{
		return m.template Col<J>();
	}

	template <size_t I, size_t J, size_t R, size_t C>
	Matrix<T, R, C> Submatrix(void) const
	{
		static_assert(I < Rows, "Invalid row for this matrix");
		static_assert(J < Cols, "Invalid column for this matrix");
		static_assert(I+R <= Rows, "Invalid number of rows");
		static_assert(J+C <= Cols, "Invalid number of columns");

		typedef Matrix<T, R, C> Result;
		return Result(
			std::integral_constant<size_t, I>(),
			std::integral_constant<size_t, J>(),
			*this
		);
	}

	/// Submatrix getter
	template <size_t I, size_t J, size_t R, size_t C>
	friend Matrix<T, R, C> Submatrix(const Matrix& m)
	{
		return m.template Submatrix<I, J, R, C>();
	}

	/// Submatrix 2x2
	friend Matrix<T, 2, 2> Sub2x2(const Matrix& m)
	{
		return m.template Submatrix<0, 0, 2, 2>();
	}

	/// Submatrix 3x3
	friend Matrix<T, 3, 3> Sub3x3(const Matrix& m)
	{
		return m.template Submatrix<0, 0, 3, 3>();
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

/// 2x2 float matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 2, 2> Mat2f;

/// 2x3 float matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 2, 3> Mat2x3f;

/// 2x4 float matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 2, 4> Mat2x4f;

/// 3x2 float matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 3, 2> Mat3x2f;

/// 3x3 float matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 3, 3> Mat3f;

/// 3x4 float matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 3, 4> Mat3x4f;

/// 4x2 float matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 4, 2> Mat4x2f;

/// 4x3 float matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 4, 3> Mat4x3f;

/// 4x4 float matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 4, 4> Mat4f;


/// 2x2 double-precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 2, 2> Mat2d;

/// 2x3 double-precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 2, 3> Mat2x3d;

/// 2x4 double-precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 2, 4> Mat2x4d;

/// 3x2 double-precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 3, 2> Mat3x2d;

/// 3x3 double-precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 3, 3> Mat3d;

/// 3x4 double-precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 3, 4> Mat3x4d;

/// 4x2 double-precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 4, 2> Mat4x2d;

/// 4x3 double-precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 4, 3> Mat4x3d;

/// 4x4 double-precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 4, 4> Mat4d;

/// Class implementing model transformation matrix named constructors
/** The static member functions of this class can be used to construct
 *  various model transformation matrices.
 *
 *  @ingroup math_utils
 */
template <typename T>
class ModelMatrix
 : public Matrix<T, 4, 4>
{
private:
	typedef Matrix<T, 4, 4> Base;
public:
	/// Constructs an identity matrix
	ModelMatrix(void)
	 : Base()
	{ }

	ModelMatrix(const Base& base)
	 : Base(base)
	{ }

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	/// Initializing constructor
	template <typename ... P>
	ModelMatrix(T v, P ... p)
	 : Base(v, T(p)...)
	{
		static_assert(
			sizeof...(P) + 1 == 4*4,
			"Invalid number of values for 4x4 matrix initialation"
		);
	}
#endif

	struct _Translation { };

	ModelMatrix(_Translation, T dx, T dy, T dz)
	 : Base(typename Base::NoInit())
	{
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			T(1), T(0), T(0),   dx,
			T(0), T(1), T(0),   dy,
			T(0), T(0), T(1),   dz,
			T(0), T(0), T(0), T(1)
		});
	}

	/// Constructs a translation matrix
	static inline ModelMatrix Translation(T dx, T dy, T dz)
	{
		return ModelMatrix(_Translation(), dx, dy, dz);
	}

	/// Constructs a translation matrix
	static inline ModelMatrix Translation(const Vector<T, 3>& dp)
	{
		return ModelMatrix(_Translation(), dp.x(), dp.y(), dp.z());
	}

	struct _Scale { };

	ModelMatrix(_Scale, T sx, T sy, T sz)
	 : Base(typename Base::NoInit())
	{
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			  sx, T(0), T(0), T(0),
			T(0),   sy, T(0), T(0),
			T(0), T(0),   sz, T(0),
			T(0), T(0), T(0), T(1)
		});
	}

	/// Constructs a scale matrix
	static inline ModelMatrix Scale(T sx, T sy, T sz)
	{
		return ModelMatrix(_Scale(), sx, sy, sz);
	}

	struct _Reflection { };

	ModelMatrix(_Reflection, bool rx, bool ry, bool rz)
	 : Base(typename Base::NoInit())
	{
		const T _rx = rx ?-T(1):T(1);
		const T _ry = ry ?-T(1):T(1);
		const T _rz = rz ?-T(1):T(1);
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			 _rx, T(0), T(0), T(0),
			T(0),  _ry, T(0), T(0),
			T(0), T(0),  _rz, T(0),
			T(0), T(0), T(0), T(1)
		});
	}

	/// Constructs a reflection matrix
	static inline ModelMatrix Reflection(bool rx, bool ry, bool rz)
	{
		return ModelMatrix(_Reflection(), rx, ry, rz);
	}

	struct _RotationX { };

	ModelMatrix(_RotationX, Angle<T> angle)
	 : Base(typename Base::NoInit())
	{
		const T cosx = Cos(angle);
		const T sinx = Sin(angle);
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			 T(1),  T(0),  T(0),  T(0),
			 T(0),  cosx, -sinx,  T(0),
			 T(0),  sinx,  cosx,  T(0),
			 T(0),  T(0),  T(0),  T(1)
		});
	}

	/// Constructs a X-axis rotation matrix
	static inline ModelMatrix RotationX(Angle<T> angle)
	{
		return ModelMatrix(_RotationX(), angle);
	}

	struct _RotationY { };

	ModelMatrix(_RotationY, Angle<T> angle)
	 : Base(typename Base::NoInit())
	{
		const T cosx = Cos(angle);
		const T sinx = Sin(angle);
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			 cosx,  T(0),  sinx,  T(0),
			 T(0),  T(1),  T(0),  T(0),
			-sinx,  T(0),  cosx,  T(0),
			 T(0),  T(0),  T(0),  T(1)
		});
	}

	/// Constructs a Y-axis rotation matrix
	static inline ModelMatrix RotationY(Angle<T> angle)
	{
		return ModelMatrix(_RotationY(), angle);
	}

	struct _RotationZ { };

	ModelMatrix(_RotationZ, Angle<T> angle)
	 : Base(typename Base::NoInit())
	{
		const T cosx = Cos(angle);
		const T sinx = Sin(angle);
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			 cosx, -sinx,  T(0),  T(0),
			 sinx,  cosx,  T(0),  T(0),
			 T(0),  T(0),  T(1),  T(0),
			 T(0),  T(0),  T(0),  T(1)
		});
	}

	/// Constructs a Z-axis rotation matrix
	static inline ModelMatrix RotationZ(Angle<T> angle)
	{
		return ModelMatrix(_RotationZ(), angle);
	}

	struct _RotationA { };

	ModelMatrix(_RotationA, const Vector<T,3>& axis, Angle<T> angle)
	 : Base(typename Base::NoInit())
	{
		const Vector<T, 3> a = Normalized(axis);
		const T sf = Sin(angle);
		const T cf = Cos(angle);
		const T _cf = T(1) - cf;
		const T x = a.At(0), y = a.At(1), z = a.At(2);
		const T xx= x*x, xy= x*y, xz= x*z, yy= y*y, yz= y*z, zz= z*z;
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			cf + xx*_cf,    xy*_cf - z*sf,  xz*_cf + y*sf,  T(0),
			xy*_cf + z*sf,  cf + yy*_cf,    yz*_cf - x*sf,  T(0),
			xz*_cf - y*sf,  yz*_cf + x*sf,  cf + zz*_cf,    T(0),
			T(0),           T(0),           T(0),           T(1)
		});
	}

	/// Constructs a rotation matrix from a vector and angle
	static inline ModelMatrix RotationA(
		const Vector<T,3>& axis,
		Angle<T> angle
	)
	{
		return ModelMatrix(_RotationA(), axis, angle);
	}

};

/// Model transformation float matrix
/**
 *  @ingroup math_utils
 */
typedef ModelMatrix<GLfloat> ModelMatrixf;

/// Model transformation double precision matrix
/**
 *  @ingroup math_utils
 */
typedef ModelMatrix<GLdouble> ModelMatrixd;

/// Class implementing camera matrix named constructors
/** The static methods of this class can be used for the construction
 *  of various camera matrices.
 *
 *  @ingroup math_utils
 */
template <typename T>
class CameraMatrix
 : public Matrix<T, 4, 4>
{
private:
	typedef Matrix<T, 4, 4> Base;
public:

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Constructs an identity matrix
	CameraMatrix(void);
#endif

#if !OGLPLUS_NO_DEFAULTED_FUNCTIONS
	CameraMatrix(void) = default;
#else
	CameraMatrix(void){ }
#endif

	CameraMatrix(const Base& base)
	 : Base(base)
	{ }

	Vector<T, 3> Position(void) const
	{
		return Vector<T, 3>(Data(Inverse(*this).template Col<3>()),	3);
	}

	struct _Perspective { };

	CameraMatrix(
		_Perspective,
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	): Base(typename Base::NoInit())
	{
		T m00 = (T(2) * z_near) / (x_right - x_left);
		T m11 = (T(2) * z_near) / (y_top - y_bottom);
		T m22 = -(z_far + z_near) / (z_far - z_near);

		T m20 = (x_right + x_left) / (x_right - x_left);
		T m21 = (y_top + y_bottom) / (y_top - y_bottom);
		T m23 = -T(1);

		T m32 = -(T(2) * z_far * z_near) / (z_far - z_near);

		OGLPLUS_AUX_MATRIX_INIT_DATA({
			 m00, T(0), T(0), T(0),
			T(0),  m11, T(0), T(0),
			 m20,  m21,  m22,  m32,
			T(0), T(0),  m32, T(0),
		});
	}

	/// Constructs a perspective projection matrix
	/** Creates a new perspective matrix from x-axis @p xfov angle,
	 *  x/y @p aspect ratio and z-axis @p z_near and @p z_far planes
	 */
	static inline CameraMatrix PerspectiveX(
		Angle<T> xfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(xfov > Radians(T(0)));

		T x_right = z_near * Tan(xfov * T(0.5));
		T x_left = -x_right;

		T y_bottom = x_left / aspect;
		T y_top = x_right / aspect;

		return CameraMatrix(
			_Perspective(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	/// Constructs a perspective projection matrix
	/** Creates a new perspective matrix from y-axis @p yfov angle,
	 *  x/y @p aspect ratio and z-axis @p z_near and @p z_far planes
	 */
	static inline CameraMatrix PerspectiveY(
		Angle<T> yfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(yfov > Radians(T(0)));

		T y_top = z_near * Tan(yfov * T(0.5));
		T y_bottom = -y_top;

		T x_left = y_bottom * aspect;
		T x_right = y_top * aspect;

		return CameraMatrix(
			_Perspective(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	struct _Ortho { };

	CameraMatrix(
		_Ortho,
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	): Base(typename Base::NoInit())
	{
		T m00 =  T(2) / (x_right - x_left);
		T m11 =  T(2) / (y_top - y_bottom);
		T m22 = -T(2) / (z_far - z_near);

		T m30 = -(x_right + x_left) / (x_right - x_left);
		T m31 = -(y_top + y_bottom) / (y_top - y_bottom);
		T m32 = -(z_far + z_near)   / (z_far - z_near);

		OGLPLUS_AUX_MATRIX_INIT_DATA({
			 m00, T(0), T(0),  m30,
			T(0),  m11, T(0),  m31,
			T(0), T(0),  m22,  m32,
			T(0), T(0), T(0), T(1),
		});
	}

	/// Constructs an orthographic projection matrix
	/** Creates a new orthographic matrix from the x-axis @p x_left, @p x_right,
	 *  y-axis @p y_bottom, @p y_top and z-axis @p z_near and @p z_far values
	 */
	static inline CameraMatrix Ortho(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	)
	{
		return CameraMatrix(
			_Ortho(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	/// Constructs an orthographic projection matrix
	/** Creates a new orthographic matrix from x-axis @p width,
	 *  x/y @p aspect ratio and z-axis @p z_near and @p z_far planes
	 */
	static inline CameraMatrix OrthoX(
		T width,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(width > T(0));

		T x_right = width / T(2);
		T x_left = -x_right;

		T y_bottom = x_left / aspect;
		T y_top = x_right / aspect;

		return CameraMatrix(
			_Ortho(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	/// Constructs an orthographic projection matrix
	/** Creates a new orthographic matrix from y-axis @p height,
	 *  x/y @p aspect ratio and z-axis @p z_near and @p z_far planes
	 */
	static inline CameraMatrix OrthoY(
		T height,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(height > T(0));

		T y_top = height / T(2);
		T y_bottom = -y_top;

		T x_left = y_bottom * aspect;
		T x_right = y_top * aspect;

		return CameraMatrix(
			_Ortho(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	struct _LookingAt { };

	CameraMatrix(
		_LookingAt,
		const Vector<T, 3>& eye,
		const Vector<T, 3>& target
	): Base(typename Base::NoInit())
	{
		assert(eye != target);
		Vector<T, 3> z = Normalized(eye - target);
		Vector<T, 3> x(
			z.template At<2>(),
			T(0),
			-z.template At<0>()
		);
		Vector<T, 3> y = Cross(z, x);

		OGLPLUS_AUX_MATRIX_INIT_DATA({
			x.template At<0>(),
			x.template At<1>(),
			x.template At<2>(),
			-Dot(eye, x),

			y.template At<0>(),
			y.template At<1>(),
			y.template At<2>(),
			-Dot(eye, y),

			z.template At<0>(),
			z.template At<1>(),
			z.template At<2>(),
			-Dot(eye, z),

			T(0), T(0), T(0), T(1)
		});
	}

	/// Constructs a 'look-at' matrix from eye and target positions
	static inline CameraMatrix LookingAt(
		const Vector<T, 3>& eye,
		const Vector<T, 3>& target
	)
	{
		return CameraMatrix(_LookingAt(), eye, target);
	}

	struct _Orbiting { };

	CameraMatrix(
		_Orbiting,
		const Vector<T, 3>& target,
		T radius,
		Angle<T> azimuth,
		Angle<T> elevation
	)
	{
		Vector<T, 3> z(
			Cos(elevation) * Cos(azimuth),
			Sin(elevation),
			Cos(elevation) *-Sin(azimuth)
		);
		Vector<T, 3> x(
			-Sin(azimuth),
			T(0),
			-Cos(azimuth)
		);
		Vector<T, 3> y = Cross(z, x);

		OGLPLUS_AUX_MATRIX_INIT_DATA({
			x.template At<0>(),
			x.template At<1>(),
			x.template At<2>(),
			Dot(x, z) * -radius - Dot(x, target),

			y.template At<0>(),
			y.template At<1>(),
			y.template At<2>(),
			Dot(y, z) * -radius - Dot(y, target),

			z.template At<0>(),
			z.template At<1>(),
			z.template At<2>(),
			Dot(z, z) * -radius - Dot(z, target),

			T(0), T(0), T(0), T(1)
		});

	}

	/// Constructs a matrix from target, radius, azimuth and elevation
	static inline CameraMatrix Orbiting(
		const Vector<T, 3>& target,
		T radius,
		Angle<T> azimuth,
		Angle<T> elevation
	)
	{
		return CameraMatrix(
			_Orbiting(),
			target,
			radius,
			azimuth,
			elevation
		);
	}

	struct _Pitch { };

	CameraMatrix(_Pitch, Angle<T> angle)
	 : Base(typename Base::NoInit())
	{
		const T cosx = Cos(-angle);
		const T sinx = Sin(-angle);
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			 T(1),  T(0),  T(0),  T(0),
			 T(0),  cosx, -sinx,  T(0),
			 T(0),  sinx,  cosx,  T(0),
			 T(0),  T(0),  T(0),  T(1)
		});
	}

	/// Constructs a X-axis rotation (Pitch/Elevation) matrix
	/** The initial heading is the negative Z-axix, y_top is the Y-axis,
	 *  x_right is X-axis.
	 *  Positive angle values do counter-clockwise rotation (looking up),
	 *  negative angles cause clockwise changes in pitch (looking down).
	 */
	static inline CameraMatrix Pitch(Angle<T> angle)
	{
		return CameraMatrix(_Pitch(), angle);
	}

	struct _Yaw { };

	CameraMatrix(_Yaw, Angle<T> angle)
	 : Base(typename Base::NoInit())
	{
		const T cosx = Cos(-angle);
		const T sinx = Sin(-angle);
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			 cosx,  T(0),  sinx,  T(0),
			 T(0),  T(1),  T(0),  T(0),
			-sinx,  T(0),  cosx,  T(0),
			 T(0),  T(0),  T(0),  T(1)
		});
	}

	/// Constructs a Y-axis rotation (Heading/Yaw) matrix
	/** The initial heading is the negative Z-axix, y_top is the Y-axis,
	 *  x_right is X-axis.
	 *  Positive angle values do counter-clockwise rotation, negative
	 *  angles cause clockwise changes in heading.
	 */
	static inline CameraMatrix Yaw(Angle<T> angle)
	{
		return CameraMatrix(_Yaw(), angle);
	}

	struct _Roll { };

	CameraMatrix(_Roll, Angle<T> angle)
	 : Base(typename Base::NoInit())
	{
		const T cosx = Cos(-angle);
		const T sinx = Sin(-angle);
		OGLPLUS_AUX_MATRIX_INIT_DATA({
			 cosx, -sinx,  T(0),  T(0),
			 sinx,  cosx,  T(0),  T(0),
			 T(0),  T(0),  T(1),  T(0),
			 T(0),  T(0),  T(0),  T(1)
		});
	}

	/// Constructs a Z-axis rotation (Bank/Roll) matrix
	/** The initial position is that y_top is the Y-axis,
	 *  heading in the negative Z-axis direction, x_right is X-axis.
	 *  Positive angle values do counter-clockwise banking, negative
	 *  angles to clockwise banking.
	 */
	static inline CameraMatrix Roll(Angle<T> angle)
	{
		return CameraMatrix(_Roll(), angle);
	}
};

/// Camera matrix using float numbers
/**
 *  @ingroup math_utils
 */
typedef CameraMatrix<GLfloat> CamMatrixf;

/// Camera matrix using double precition numbers
/**
 *  @ingroup math_utils
 */
typedef CameraMatrix<GLdouble> CamMatrixd;

// implementation of Vector's constructors, conversions and operations
template <typename T, size_t N>
template <size_t M>
Vector<T, N>::Vector(
	const typename ::std::enable_if<
		(M == N && N > 1),
		Matrix<T, 1, M>
	>::type& matrix
)
{
	for(size_t i=0; i!=N; ++i)
		_elem[i] = matrix._m._elem[0][i];
}

template <typename T, size_t N>
template <size_t M>
Vector<T, N>::Vector(
	const typename ::std::enable_if<
		(M == N && N > 1),
		Matrix<T, M, 1>
	>::type& matrix
)
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
