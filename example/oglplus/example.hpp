/**
 *  .file example/example.hpp
 *  Declares a common base class for examples
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef __OGLPLUS_EXAMPLE_EXAMPLE_1119071146_HPP__
#define __OGLPLUS_EXAMPLE_EXAMPLE_1119071146_HPP__

#include <memory>

namespace oglplus {

struct Example
{
	virtual ~Example(void)
	{ }

	// Hint for the main function whether to continue rendering
	// Implementations of the main function may choose to ignore
	// the result of this function
	virtual bool Continue(unsigned duration)
	{
		return duration < 3; // [seconds]
	}

	virtual void Render(void) = 0;
};

std::unique_ptr<Example> makeExample(void);

} // namespace oglplus

#endif // include guard
