/**
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  Checks for the override keyword
 */
struct intf
{
	virtual ~intf(void) { }
	virtual int func(const char*) = 0;
};

class impl
 : public intf
{
public:
	int func(const char*) override
	{
		return 0;
	}
};

int main(int argc, const char** argv)
{
	impl x;
	intf* pi = &x;
	return pi->func(argv[0]);
}
