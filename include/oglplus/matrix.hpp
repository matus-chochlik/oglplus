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

	friend class Vector<T, Rows>;
	friend class Vector<T, Cols>;
public:
	struct NoInit { };

	/// Constructs an uninitialized matrix
	Matrix(NoInit)
	{ }

	struct Zero { };

	/// Constructs zero a matrix
	Matrix(Zero)
	{
		this->_m._data = {
			T(0), T(0), T(0), T(0),
			T(0), T(0), T(0), T(0),
			T(0), T(0), T(0), T(0),
			T(0), T(0), T(0), T(0)
		};
	}

	/// Constructs a identity matrix
	Matrix(void)
	{
		this->_m._data = {
			T(1), T(0), T(0), T(0),
			T(0), T(1), T(0), T(0),
			T(0), T(0), T(1), T(0),
			T(0), T(0), T(0), T(1)
		};
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

template <typename T>
class Matrix4x4
 : public Matrix<T, 4, 4>
{
private:
	typedef Matrix<T, 4, 4> Base;
public:
	/// Constructs an identity matrix
	Matrix4x4(void)
	 : Base()
	{ }

	/// Initializing constructor
	template <typename ... P>
	Matrix4x4(T v, P ... p)
	 : Base(v, T(p)...)
	{
		static_assert(
			sizeof...(P) + 1 == 4*4,
			"Invalid number of values for 4x4 matrix initialation"
		);
	}

	struct _Translation { };

	Matrix4x4(_Translation, T dx, T dy, T dz)
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
	static inline Matrix4x4 Translation(T dx, T dy, T dz)
	{
		return Matrix4x4(_Translation(), dx, dy, dz);
	}

	struct _Scale { };

	Matrix4x4(_Scale, T sx, T sy, T sz)
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
	static inline Matrix4x4 Scale(T sx, T sy, T sz)
	{
		return Matrix4x4(_Scale(), sx, sy, sz);
	}

	struct _RotationX { };

	Matrix4x4(_RotationX, Angle<T> angle)
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
	static inline Matrix4x4 RotationX(Angle<T> angle)
	{
		return Matrix4x4(_RotationX(), angle);
	}

	struct _RotationY { };

	Matrix4x4(_RotationY, Angle<T> angle)
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
	static inline Matrix4x4 RotationY(Angle<T> angle)
	{
		return Matrix4x4(_RotationY(), angle);
	}

	struct _RotationZ { };

	Matrix4x4(_RotationZ, Angle<T> angle)
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
	static inline Matrix4x4 RotationZ(Angle<T> angle)
	{
		return Matrix4x4(_RotationZ(), angle);
	}

	struct _RotationA { };

	Matrix4x4(_RotationA, const Vector<T,3>& axis, Angle<T> angle)
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
	static inline Matrix4x4 RotationA(
		const Vector<T,3>& axis,
		Angle<T> angle
	)
	{
		return Matrix4x4(_RotationA(), axis, angle);
	}


	struct _Perspective { };

	Matrix4x4(_Perspective, Angle<T> fov, T aspect, T z_near, T z_far)
	 : Base(typename Base::NoInit())
	{
		assert(aspect > 0);
		assert(fov > Radians(T(0)));
		T height = T(1) / Tan(fov);
		T neg_depth = z_near - z_far;
		assert(neg_depth < 0.0);
		this->_m._data = {
			height / aspect, T(0), T(0), T(0),
			T(0), height, T(0), T(0),
			T(0), T(0), (z_far+z_near)/neg_depth, T(0),
			T(0), T(0), T(2)*z_near*z_far/neg_depth, T(1)
		};
	}

	/// Constructs a perspective prohection matrix from a vector and angle
	static inline Matrix4x4 Perspective(
		Angle<T> fov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		return Matrix4x4(_Perspective(), fov, aspect, z_near, z_far);
	}

	struct _LookingAt { };

	Matrix4x4(
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
	static inline Matrix4x4 LookingAt(
		const Vector<T, 3>& eye,
		const Vector<T, 3>& target
	)
	{
		return Matrix4x4(_LookingAt(), eye, target);
	}

	struct _Orbiting { };

	Matrix4x4(
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
			Cos(elevation) * Sin(azimuth)
		);
		Vector<T, 3> x(
			-Sin(azimuth),
			T(0),
			Cos(azimuth)
		);
		Vector<T, 3> y = Cross(x, z);

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
	static inline Matrix4x4 Orbiting(
		const Vector<T, 3>& target,
		T radius,
		Angle<T> azimuth,
		Angle<T> elevation
	)
	{
		return Matrix4x4(
			_Orbiting(),
			target,
			radius,
			azimuth,
			elevation
		);
	}
};

/// 4x4 float matrix
typedef Matrix4x4<GLfloat> Matrix4f;
/// 4x4 double precision matrix
typedef Matrix4x4<GLdouble> Matrix4d;


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
