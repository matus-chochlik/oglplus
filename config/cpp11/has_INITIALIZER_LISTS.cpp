/**
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#include <vector>

int main(int argc, const char** argv)
{
	std::vector<int> v({0,1,2,3,4,5,6,7,8,9});
	return (v.size() == 10)?0:1;
}
