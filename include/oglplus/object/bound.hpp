/**
 *  @file oglplus/object/bound.hpp
 *  @brief Operations on currently bound objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_BOUND_1405011014_HPP
#define OGLPLUS_OBJECT_BOUND_1405011014_HPP

#include <oglplus/object/name.hpp>

namespace oglplus {

template <typename ObjTag>
class ObjectOps<tag::CurrentBound, ObjTag>
 : public ObjCommonOps<ObjTag>
 , public BoundObjOps<ObjTag>
{
protected:
	ObjectOps(void) { }
public:
	typedef typename BoundObjOps<ObjTag>::Target Target;
};

template <typename ObjTag>
class Reference<ObjectOps<tag::CurrentBound, ObjTag>>
 : public ObjectOps<tag::CurrentBound, ObjTag>
{
private:
	typedef ObjectOps<tag::CurrentBound, ObjTag> Base;
public:
	Reference(void)
	{
		this->_copy(ObjBindingOps<ObjTag>::Binding());
	}

	Reference(typename Base::Target init_tgt)
	{
		this->_copy(ObjBindingOps<ObjTag>::Binding(init_tgt));
		this->target = init_tgt;
	}
};

} // namespace oglplus

#endif // include guard
