/**
 *  @file oglplus/auxiliary/fwd.hpp
 *  @brief Helper forward declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_FWD_1107121519_HPP
#define OGLPLUS_AUX_FWD_1107121519_HPP

namespace oglplus {
namespace aux {

template <typename OpsTag, typename VarTag, typename TypTag>
class ProgVarSetters;

template <typename OpsTag, typename T>
class ProgVarCallers;

template <
	typename OpsTag,
	typename VarTag,
	typename TypTag,
	typename T,
	std::size_t MaxCount
> class ProgVarSetOps;

template <typename VarTag, typename ChkTag>
class ProgVarTypecheck;

} // namespace aux
} // namespace oglplus

#endif // include guard
