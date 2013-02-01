/**
 *  @file oglplus/lib.hpp
 *  @brief All-in-one Include file for the separatelly-built library
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_LIB_1208310818_HPP
#define OGLPLUS_LIB_1208310818_HPP

#ifndef OGLPLUS_IMPLEMENTING_LIBRARY
#define OGLPLUS_IMPLEMENTING_LIBRARY 1
#endif

#include <oglplus/config.hpp>
#include <oglplus/string.hpp>
#include <oglplus/fwd.hpp>

#include <oglplus/auxiliary/strings.hpp>
#include <oglplus/auxiliary/base_range.hpp>
#include <oglplus/auxiliary/uniform_typecheck.hpp>
#include <oglplus/auxiliary/info_log.hpp>

#include <oglplus/imports/blend_file.hpp>

namespace oglplus {

// EnumValueName implementations
#include <oglplus/lib/enum_value_name.ipp>
// EnumValueRange implementations
#include <oglplus/lib/enum_value_range.ipp>

} // namespace oglplus

#undef OGLPLUS_IMPLEMENTING_LIBRARY

#endif // include guard
