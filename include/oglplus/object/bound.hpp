/**
 *  @file oglplus/object/bound.hpp
 *  @brief Operations on currently bound objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_BOUND_1405011014_HPP
#define OGLPLUS_OBJECT_BOUND_1405011014_HPP

#include <oglplus/object/name.hpp>

namespace oglplus {

template <typename ObjTag>
class BoundObjOps {
public:
    BoundObjOps(void) noexcept {
    }

    template <typename X>
    BoundObjOps(X) noexcept {
    }
};

template <typename ObjTag>
class ObjectOps<tag::CurrentBound, ObjTag>
  : public ObjZeroOps<tag::CurrentBound, ObjTag>
  , public BoundObjOps<ObjTag> {
protected:
    ObjectOps(ObjectName<ObjTag> name) noexcept
      : ObjZeroOps<tag::CurrentBound, ObjTag>(name) {
    }

public:
    typedef typename BoundObjOps<ObjTag>::Target Target;

    ObjectOps(ObjectOps&&) = default;
    ObjectOps(const ObjectOps&) = default;
    ObjectOps& operator=(ObjectOps&&) = default;
    ObjectOps& operator=(const ObjectOps&) = default;
};

template <typename ObjTag>
class Reference<ObjectOps<tag::CurrentBound, ObjTag>>
  : public ObjectOps<tag::CurrentBound, ObjTag> {
private:
    typedef ObjectOps<tag::CurrentBound, ObjTag> Base;

public:
    Reference(void)
      : ObjectOps<tag::CurrentBound, ObjTag>(ObjBindingOps<ObjTag>::Binding()) {
    }

    Reference(typename Base::Target init_tgt)
      : ObjectOps<tag::CurrentBound, ObjTag>(
          ObjBindingOps<ObjTag>::Binding(init_tgt)) {
        this->target = init_tgt;
    }
};

} // namespace oglplus

#endif // include guard
