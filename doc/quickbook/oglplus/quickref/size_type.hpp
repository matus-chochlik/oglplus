/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_size_impl

template <typename T>
struct SizeImpl
{
public:
	SizeImpl(void) /*<
	Constructs a zero size instance.
	>*/
	noexcept;

	template <typename X, typename = typename is_integral<X>::type>
	SizeImpl(X v); /*<
	Conversion from other signed or unsigned integral types.
	Throws if the passed value is negative or out of range of [^T].
	>*/

	template <typename X, typename = typename is_integral<X>::type>
	SizeImpl(X v, std::nothrow_t)
	noexcept; /*<
	Conversion from other signed or unsigned integral types.
	Does not throw.
	>*/

	T get(void) const
	noexcept;

	explicit
	operator bool (void) const
	noexcept; /*<
	Indicates if the stored value is valid i.e. nonnegativa and was
	in range of [^T] when initialized.
	>*/

	bool operator ! (void) const
	noexcept; /*<
	Indicates if the stored value is invalid i.e. negative or was
	out of range of [^T] when initialized.
	>*/

	operator T (void) const; /*<
	Implicit conversion to [^T].
	>*/

	template <typename X>
	explicit
	operator X (void) const; /*<
	Explicit conversion to other (integral) types. May throw if the
	stored value is negative and [^X] is unsigned or if it is
	out of range of [^X].
	>*/

	friend bool operator == (SizeImpl s1, SizeImpl s2);

	friend bool operator != (SizeImpl s1, SizeImpl s2);

	friend bool operator <  (SizeImpl s1, SizeImpl s2);

	friend bool operator <= (SizeImpl s1, SizeImpl s2);

	friend bool operator >  (SizeImpl s1, SizeImpl s2);

	friend bool operator >= (SizeImpl s1, SizeImpl s2);

	friend bool operator + (SizeImpl s1, SizeImpl s2);

	friend bool operator - (SizeImpl s1, SizeImpl s2);

	friend bool operator * (SizeImpl s1, SizeImpl s2);

	friend bool operator / (SizeImpl s1, SizeImpl s2);

	friend bool operator % (SizeImpl s1, SizeImpl s2);
};

//]
//[oglplus_size_type_def

typedef __SizeImpl<GLsizei> SizeType;
typedef __SizeImpl<GLsizeiptr> BigSizeType;

//]

