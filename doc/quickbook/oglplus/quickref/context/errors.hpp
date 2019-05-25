/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_Errors
namespace context {

class Errors {
public:
    static __ErrorCode GetError(); /*<
    Returns the currently set __ErrorCode.
    See [glfunc GetError].
    >*/
};

} // namespace context
//]
