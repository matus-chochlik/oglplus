/*
 *  .file devel/test.hpp
 *  Declares a common base class for test applications
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef __OGLPLUS_DEVEL_TEST_1119071146_HPP__
#define __OGLPLUS_DEVEL_TEST_1119071146_HPP__

#include <memory>

namespace oglplus {

struct Test
{
	virtual ~Test(void)
	{ }

	virtual bool Continue(double duration)
	{
		return duration < 3.0; // [seconds]
	}

	virtual void Render(double time) = 0;
};

std::unique_ptr<Test> makeTest(void);

} // namespace oglplus

#endif // include guard
