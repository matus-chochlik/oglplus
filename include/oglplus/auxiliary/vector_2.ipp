/**
 *  .file oglplus/auxiliary/vector_2.ipp
 *  .brief Specialization of Vector for 2D vectors
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

template <typename T>
class Vector<T, 2>
 : public VectorBase<T, 2>
{
private:
	typedef VectorBase<T, 2> Base;
public:
	Vector(void)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = T(0))
	{ }

	template <typename U>
	Vector(const Vector<U, 2>& vector)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = T(std::declval<U>()))
	 : Base(vector)
	{ }

	Vector(const T (&v)[2])
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	 : Base(v)
	{ }

	Vector(const T* v, std::size_t n)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	 : Base(v, n)
	{ }

	explicit Vector(T v0)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	 : Base(v0)
	{ }

	Vector(T v0, T v1)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	 : Base(nullptr)
	{
		this->_elem[0] = v0;
		this->_elem[1] = v1;
	}

	Vector(const Vector<T, 1>& v, T v1)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	 : Base(nullptr)
	{
		this->_elem[0] = v[0];
		this->_elem[1] = v1;
	}

	explicit Vector(const Matrix<T, 1, 2>& matrix)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	 : Base(matrix)
	{ }

	explicit Vector(const Matrix<T, 2, 1>& matrix)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = std::declval<T>())
	 : Base(matrix)
	{ }

	T x(void) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T&>()))
	{
		return this->At(0);
	}

	T y(void) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T&>()))
	{
		return this->At(1);
	}

	friend Vector Negated(const Vector& a)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = -std::declval<T>())
	{
		return Vector(-a[0], -a[1]);
	}

	friend Vector Added(const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()+
		std::declval<T>()
	)
	{
		return Vector(a[0]+b[0], a[1]+b[1]);
	}

	Vector& operator += (const Vector& v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() += std::declval<T>())
	{
		this->Add(v);
		return *this;
	}

	friend Vector Subtracted(const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()-
		std::declval<T>()
	)
	{
		return Vector(a[0]-b[0], a[1]-b[1]);
	}

	Vector& operator -= (const Vector& v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() -= std::declval<T>())
	{
		this->Subtract(v);
		return *this;
	}


	friend Vector Multiplied(const Vector& a, T v)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()*
		std::declval<T>()
	)
	{
		return Vector(a[0]*v, a[1]*v);
	}

	Vector& operator *= (T v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() *= std::declval<T>())
	{
		this->MultiplyBy(v);
		return *this;
	}

	friend Vector Divided(const Vector& a, T v)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()/
		std::declval<T>()
	)
	{
		return Vector(a[0]/v, a[1]/v);
	}

	Vector& operator /= (T v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() /= std::declval<T>())
	{
		this->DivideBy(v);
		return *this;
	}
};

