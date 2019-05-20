/**
 *  @file oglplus/error/glfunc.ipp
 *  @brief Implementation of MissingFunction exception
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
const char* MissingFunction::Message() {
    return "OpenGL function called through an invalid pointer";
}

} // namespace oglplus
