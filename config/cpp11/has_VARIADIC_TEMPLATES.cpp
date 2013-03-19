/**
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  Checks for support for variadic templates
 */

template <typename T, T ... P>
struct vt1
{ };

template <typename ... P>
struct vt2
{
	static unsigned size(void)
	{
		return sizeof...(P);
	}
};

int main(int argc, const char** argv)
{
	typedef vt1<int, 1, 2, 3, 4, 5, 6, 7> a;
	vt2<short, int, long, float, double, a> b;
	return (b.size() == 6)?0:1;
}
