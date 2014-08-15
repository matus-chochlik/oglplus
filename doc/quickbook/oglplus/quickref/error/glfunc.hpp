/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_error_MissingFunction
namespace oglplus {

class MissingFunction
 : public __Error
{
public:
	MissingFunction(const char* message);
};

} // namespace oglplus
//]

