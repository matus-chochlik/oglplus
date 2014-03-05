/**
 *  @file oglplus/binding.hpp
 *  @brief Object-target binding utilities
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BINDING_1107121519_HPP
#define OGLPLUS_BINDING_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

/// A managed Object that is currently bound to a specified target
template <typename Object>
class Current
 : public Managed<Object>
{
private:
	typedef typename ObjectBaseOps<Object>::Type ObjectOps_;
public:
	/// Creates a reference to the object currently bound to target
	Current(typename Object::Target target)
	 : Managed<Object>(BindingQuery<ObjectOps_>::QueryBinding(target))
	{ }
};

/// Class that remembers the currently bound Object and rebinds it when destroyed
template <typename Object>
class AutoRebind
{
private:
	Current<Object> _obj;
	typename Object::Target _target;
public:
	AutoRebind(typename Object::Target target)
	 : _obj(target)
	 , _target(target)
	{ }

	~AutoRebind(void)
	{
		_obj.Bind(_target);
	}
};

} // namespace oglplus

#endif // include guard
