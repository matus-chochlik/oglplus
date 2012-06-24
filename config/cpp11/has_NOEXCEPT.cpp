/**
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  Checks for the noexcept keyword
 */
template <typename T>
T get_default(void) noexcept(T())
{
	return T();
}

int main(int argc, const char** argv)
{
	return (argc == get_default<int>())?0:1;
}
