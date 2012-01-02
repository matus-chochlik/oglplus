/**
 *  @file oglplus/glfunc.hpp
 *  @brief Helper macro for optional checking of availability of GL function
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_GLFUNC_1201020903_HPP
#define OGLPLUS_GLFUNC_1201020903_HPP

#include <oglplus/config.hpp>

namespace oglplus {

/* TODO: something like this can be enabled if the GL functions
 * are actually pointers to functions, to add additional checking.
 *
template <typename RV, typename ... Params>
inline auto _checked_glfunc(RV (*pfn)(Params...)) -> decltype(pfn)
{
	return pfn;
}

template <typename RV, typename ... Params>
inline auto _checked_glfunc(RV (**ppfn)(Params...)) -> decltype(*ppfn)
{
	if(!ppfn || !*ppfn) throw 0;
	return *ppfn;
}

#define OGLPLUS_GLFUNC(FUNCNAME) \
	::oglplus::_checked_glfunc(&::gl##FUNCNAME)
*/

#ifndef OGLPLUS_GLFUNC
#define OGLPLUS_GLFUNC(FUNCNAME) \
	::gl##FUNCNAME
#endif

} // namespace oglplus

#endif // include guard
