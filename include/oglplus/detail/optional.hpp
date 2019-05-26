/**
 *  @file oglplus/detail/optional.hpp
 *  @brief Default implementation of the Optional<X> wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DETAIL_OPTIONAL_1405052234_HPP
#define OGLPLUS_DETAIL_OPTIONAL_1405052234_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/fwd.hpp>
#include <utility>

namespace oglplus {

template <typename Tag, typename X>
class OptionalImpl;

template <typename X>
class Optional : public OptionalImpl<typename Classify<X>::Tag, X> {
private:
    using Base = OptionalImpl<typename Classify<X>::Tag, X>;

public:
    using Base::Base;

    template <typename T1>
    Optional& operator=(T1&& value) {
        Base::operator=(std::forward<T1>(value));
        return *this;
    }
};

} // namespace oglplus

#endif // include guard
