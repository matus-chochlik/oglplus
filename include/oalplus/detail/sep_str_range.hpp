/**
 *  .file oalplus/detail/sep_str_range.hpp
 *  .brief Range for traversal of separated string values
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_AUX_SEP_STR_RANGE_1305291314_HPP
#define OALPLUS_AUX_SEP_STR_RANGE_1305291314_HPP

#include <oglplus/detail/sep_str_range.hpp>
#include <oalplus/string.hpp>

namespace oalplus {
namespace aux {

using SepStrRange = oglplus::aux::SepStrRangeTpl<String>;

} // namespace aux
} // namespace oalplus

#endif // include guard
