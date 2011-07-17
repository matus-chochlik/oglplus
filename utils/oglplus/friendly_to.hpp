/**
 *  @file oglplus/friendly_to.hpp
 *  @brief Implementation of the FriendlyTo helper utility class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef UTILS_OGLPLUS_FRIENDLY_TO_1107121519_HPP
#define UTILS_OGLPLUS_FRIENDLY_TO_1107121519_HPP

namespace oglplus {

template <typename Object>
class FriendlyTo
{
protected:
	static auto GetHandle(const Object& object) ->
	decltype(object._handle)
	{
		return object._handle;
	}
};

} // namespace oglplus

#endif // include guard
