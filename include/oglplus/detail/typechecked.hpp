/**
 *  @file oglplus/detail/typechecked.hpp
 *  @brief Default implementation of the Typechecked<X> wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DETAIL_TYPECHECKED_1405052234_HPP
#define OGLPLUS_DETAIL_TYPECHECKED_1405052234_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/fwd.hpp>
#include <utility>

namespace oglplus {

template <typename Tag, typename X>
class TypecheckedImpl;

template <typename X>
class Typechecked : public TypecheckedImpl<typename Classify<X>::Tag, X> {
private:
    typedef TypecheckedImpl<typename Classify<X>::Tag, X> Base;

public:
    using Base::Base;
};

} // namespace oglplus

#endif // include guard
