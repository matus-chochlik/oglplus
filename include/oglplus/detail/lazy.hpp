/**
 *  @file oglplus/detail/lazy.hpp
 *  @brief Default implementation of the Lazy<X> wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DETAIL_LAZY_1405052234_HPP
#define OGLPLUS_DETAIL_LAZY_1405052234_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/fwd.hpp>
#include <utility>

namespace oglplus {

template <typename Tag, typename X>
class LazyImpl;

template <typename X>
class Lazy : public LazyImpl<typename Classify<X>::Tag, X> {
private:
    typedef LazyImpl<typename Classify<X>::Tag, X> Base;

public:
    using Base::Base;
};

} // namespace oglplus

#endif // include guard
