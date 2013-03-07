/**
 *  .file oglplus/auxiliary/vector_1.ipp
 *  .brief Specialization of Vector for 1D vectors
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

template <typename T>
class Vector<T, 1>
 : public VectorBase<T, 1>
{
private:
	typedef VectorBase<T, 1> Base;
public:
	Vector(void)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = T(0))
	{ }

	template <typename U>
	Vector(const Vector<U, 1>& vector)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = T(std::declval<U>()))
	 : Base(vector)
	{ }

	Vector(const T (&v)[1])
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

	T x(void) const
	OGLPLUS_NOEXCEPT_IF(T(std::declval<T&>()))
	{
		return this->At(0);
	}

	friend Vector Negated(const Vector& a)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() = -std::declval<T>())
	{
		return Vector(-a[0]);
	}

	friend Vector Added(const Vector& a, const Vector& b)
	OGLPLUS_NOEXCEPT_IF(
		std::declval<T&>()=
		std::declval<T>()+
		std::declval<T>()
	)
	{
		return Vector(a[0]+b[0]);
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
		return Vector(a[0]-b[0]);
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
		return Vector(a[0]*v);
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
		return Vector(a[0]/v);
	}

	Vector& operator /= (T v)
	OGLPLUS_NOEXCEPT_IF(std::declval<T&>() /= std::declval<T>())
	{
		this->DivideBy(v);
		return *this;
	}
};

