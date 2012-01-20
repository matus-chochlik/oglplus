/**
 *  @file oglplus/blit_filter.hpp
 *  @brief Enumeration of Blit operation filtering modes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BLIT_FILTER_1201201108_HPP
#define OGLPLUS_BLIT_FILTER_1201201108_HPP

namespace oglplus {

/// Enumeration of blit operation filtering modes
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BlitFramebuffer}
 */
enum class BlitFilter : GLenum
{
#include <oglplus/enums/blit_filter.ipp>
};

} // namespace oglplus

#endif // include guard
