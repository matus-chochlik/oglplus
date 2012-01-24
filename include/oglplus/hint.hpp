/**
 *  @file oglplus/hint.hpp
 *  @brief Enumeration of hint targets and options
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_HINT_1201201108_HPP
#define OGLPLUS_HINT_1201201108_HPP

namespace oglplus {

/// Enumeration of hint targets
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Hint}
 */
enum class HintTarget : GLenum
{
#include <oglplus/enums/hint_target.ipp>
};

/// Enumeration of hint options
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Hint}
 */
enum class HintOption : GLenum
{
#include <oglplus/enums/hint_option.ipp>
};

} // namespace oglplus

#endif // include guard
