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
#include <oglplus/angle.hpp>

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

	template <size_t R, size_t ... C>
	inline void _init_rows(
		const Vector<T, Cols>& row,
		const Vector<T, C>&... rows
	)
	{
		_init_row<R>(row);
		_init_rows<R+1>(rows...);
	}

	friend class Vector<T, Rows>;
	friend class Vector<T, Cols>;

	template <typename X>
	static void _eat(const X&...)
	{ }
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
		this->_m._data = {v, T(p)...};
	}

	/// Initializing from row vectors
	/** Allows to initialize all rows of the matrix from individual
	 *  vectors. The number of vectors must be Rows and each vector
	 *  must have exactly Cols elements.
	 */
	template <size_t ... C>
	Matrix(const Vector<T, C>& ... rows)
	{
		static_assert(
			sizeof...(C) == Rows,
			"Invalid number of rows for this matrix type"
		);
		this->_init_rows<0>(rows...);
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

	/// Finds inverse matrix if m is square matrix and T supports fractions
	friend Matrix Inverse(
		typename ::std::enable_if<
			(Rows > 1)&&(Rows == Cols),
			Matrix
		>::type m
	)
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
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLfloat, 4, 4> Matrix4f;

/// 4x4 double precision matrix
/**
 *  @ingroup math_utils
 */
typedef Matrix<GLdouble, 4, 4> Matrix4d;

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

	struct _Translation { };

	ModelMatrix(_Translation, T dx, T dy, T dz)
	 : Base(typename Base::NoInit())
	{
		this->_m._data = {
			T(1), T(0), T(0),   dx,
			T(0), T(1), T(0),   dy,
			T(0), T(0), T(1),   dz,
			T(0), T(0), T(0), T(1)
		};
	}

	/// Constructs a translation matrix
	static inline ModelMatrix Translation(T dx, T dy, T dz)
	{
		return ModelMatrix(_Translation(), dx, dy, dz);
	}

	struct _Scale { };

	ModelMatrix(_Scale, T sx, T sy, T sz)
	 : Base(typename Base::NoInit())
	{
		this->_m._data = {
			  sx, T(0), T(0), T(0),
			T(0),   sy, T(0), T(0),
			T(0), T(0),   sz, T(0),
			T(0), T(0), T(0), T(1)
		};
	}

	/// Constructs a scale matrix
	static inline ModelMatrix Scale(T sx, T sy, T sz)
	{
		return ModelMatrix(_Scale(), sx, sy, sz);
	}

	struct _RotationX { };

	ModelMatrix(_RotationX, Angle<T> angle)
	 : Base(typename Base::NoInit())
	{
		const T cosx = Cos(angle);
		const T sinx = Sin(angle);
		this->_m._data = {
			 T(1),  T(0),  T(0),  T(0),
			 T(0),  cosx, -sinx,  T(0),
			 T(0),  sinx,  cosx,  T(0),
			 T(0),  T(0),  T(0),  T(1)
		};
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
		this->_m._data = {
			 cosx,  T(0),  sinx,  T(0),
			 T(0),  T(1),  T(0),  T(0),
			-sinx,  T(0),  cosx,  T(0),
			 T(0),  T(0),  T(0),  T(1)
		};
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
		this->_m._data = {
			 cosx, -sinx,  T(0),  T(0),
			 sinx,  cosx,  T(0),  T(0),
			 T(0),  T(0),  T(1),  T(0),
			 T(0),  T(0),  T(0),  T(1)
		};
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
		this->_m._data = {
			cf + xx*_cf,    xy*_cf - z*sf,  xz*_cf + y*sf,  T(0),
			xy*_cf + z*sf,  cf + yy*_cf,    yz*_cf - x*sf,  T(0),
			xz*_cf - y*sf,  yz*_cf + x*sf,  cf + zz*_cf,    T(0),
			T(0),           T(0),           T(0),           T(1)
		};
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
	/// Constructs an identity matrix
	CameraMatrix(void) = default;

	CameraMatrix(const Base& base)
	 : Base(base)
	{ }

	Vector<T, 3> Position(void) const
	{
		return Inverse(*this).template Col<3>().xyz();
	}

	struct _Perspective { };

	CameraMatrix(_Perspective, Angle<T> fov, T aspect, T z_near, T z_far)
	 : Base(typename Base::NoInit())
	{
		assert(aspect > T(0));
		assert(fov > Radians(T(0)));

		T xmax = z_near * Tan(fov * T(0.5));
		T xmin = -xmax;

		T ymin = xmin / aspect;
		T ymax = xmax / aspect;

		T m00 = (T(2) * z_near) / (xmax - xmin);
		T m11 = (T(2) * z_near) / (ymax - ymin);
		T m22 = -(z_far + z_near) / (z_far - z_near);

		T m20 = (xmax + xmin) / (xmax - xmin);
		T m21 = (ymax + ymin) / (ymax - ymin);
		T m23 = -T(1);

		T m32 = -(T(2) * z_far * z_near) / (z_far - z_near);

		this->_m._data = {
			 m00, T(0), T(0), T(0),
			T(0),  m11, T(0), T(0),
			 m20,  m21,  m22,  m32,
			T(0), T(0),  m32, T(0),
		};
	}

	/// Constructs a perspective prohection matrix from a vector and angle
	static inline CameraMatrix Perspective(
		Angle<T> fov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		return CameraMatrix(_Perspective(), fov, aspect, z_near, z_far);
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
		this->_m._data = {
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
		};
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

		this->_m._data = {
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
		};

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
		this->_m._data = {
			 T(1),  T(0),  T(0),  T(0),
			 T(0),  cosx, -sinx,  T(0),
			 T(0),  sinx,  cosx,  T(0),
			 T(0),  T(0),  T(0),  T(1)
		};
	}

	/// Constructs a X-axis rotation (Pitch/Elevation) matrix
	/** The initial heading is the negative Z-axix, top is the Y-axis,
	 *  right is X-axis.
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
		this->_m._data = {
			 cosx,  T(0),  sinx,  T(0),
			 T(0),  T(1),  T(0),  T(0),
			-sinx,  T(0),  cosx,  T(0),
			 T(0),  T(0),  T(0),  T(1)
		};
	}

	/// Constructs a Y-axis rotation (Heading/Yaw) matrix
	/** The initial heading is the negative Z-axix, top is the Y-axis,
	 *  right is X-axis.
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
		this->_m._data = {
			 cosx, -sinx,  T(0),  T(0),
			 sinx,  cosx,  T(0),  T(0),
			 T(0),  T(0),  T(1),  T(0),
			 T(0),  T(0),  T(0),  T(1)
		};
	}

	/// Constructs a Z-axis rotation (Bank/Roll) matrix
	/** The initial position is that top is the Y-axis,
	 *  heading in the negative Z-axis direction, right is X-axis.
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
